#include "server.h"
#include <signal.h> 

/*
 * Declaration of structure, which contains  server context.
 * a. fd_set read_descriptors - bitarray, which contains 
 *    all conected client sockets. (it is needed for select)
 * b. connected_client_list_t list - linked list of connected client sockets.
 */
static server_context_t ctx;

// Initialize mutex with default settings.
static pthread_mutex_t ctx_mutex = PTHREAD_MUTEX_INITIALIZER;

// if quit == true, server exits.
static bool quit = false; 

static void server_context_init(void) {
    pthread_mutex_lock(&ctx_mutex);
    FD_ZERO (&ctx.read_descriptors);
    ctx.head.sock_fd = -1;
    ctx.head.is_logged = false;
    ctx.head.next = NULL;
    pthread_mutex_unlock(&ctx_mutex);
}

static void server_context_free(void) {
    pthread_mutex_lock(&ctx_mutex);
    for (connected_client_list_t *p = ctx.head.next; p != NULL; p = p->next) {
        close(p->sock_fd);
    }
    socket_list_free(&ctx.head);
    pthread_mutex_unlock(&ctx_mutex);
}

/*
 * Checks, whether client closed the connection.
 * if true => deletes socket from server context.
 */
static bool update_connections(fd_set *descriptors) {
    char buffer[256];
    bool status = true;
    if (descriptors == NULL) return false;

    pthread_mutex_lock(&ctx_mutex);  
    for (connected_client_list_t *s = ctx.head.next; s != NULL; s = s->next) {
        if (recv(s->sock_fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
            printf("Connection on socket with socket fd %d was closed\n", s->sock_fd);
            close(s->sock_fd);
            FD_CLR(s->sock_fd, &ctx.read_descriptors);
            if (socket_list_remove(&ctx.head, s->sock_fd) < 0) {
                status = false;
            }
        }
    }
    *descriptors = ctx.read_descriptors;    
    pthread_mutex_unlock(&ctx_mutex);
    return status;
}

// Determines how much time select will wait for incomming connections.
static struct timeval wait_time() {
    struct timeval tv;
    tv.tv_sec  = 1; // seconds.
    tv.tv_usec = 0; // mili-seconds.
    return tv;
}

static void *handle_server(void *param) {
    int status;
    char buffer[256];
    bzero(buffer,256);
    int buf_len;
    fd_set read_descriptors;
    // Setting waiting time for select.
    struct timeval tv = wait_time();

    while(!quit) {    
        update_connections(&read_descriptors);
        printf("wait for incomming packets...\n");
        status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);
        // if no sockets are availabe => continue loop.
        if (status <= 0) continue;
        
        pthread_mutex_lock(&ctx_mutex);
        /*
         * Going through each opened socket and determine, whether socket is active.
         * if true => receive packet from socket => alalyze this packet =>
         * change db if it`s needed and form new packet to send.
         * Go through linked list with opened sockets(connected clients) and check,
         * whether socket node has the same attribute(user_login) as specified in new packet.
         * if node was found -> send packet to socket, specified in it. Otherwise, just 
         * change db depending on packet => as user is getting logged, all new data retrieves 
         * from db.
         */
        for (connected_client_list_t *p = ctx.head.next; p != NULL; p = p->next) {
            if (FD_ISSET(p->sock_fd, &read_descriptors)) {
                buf_len = recv(p->sock_fd, buffer, 255, 0);
                printf("There was received %d bytes from socket %d\n", buf_len, p->sock_fd); // Debug.
                if (buf_len < 0) continue;

                // Modify db and forms packet, which must be send to specified in packet client(login).
                char *send_packet = mx_database_communication(buffer);
                // if (send_packet == NULL) // Connection was closed but update has not been made yet.
                    // continue;
                printf(">%s\n", buffer);
                /* 
                 * Retrieves user`s login from packet. Packet will be send on this login,
                 * if user with this login is connected to the server.
                 */
                // char *client_login = get_value_buy_key(send_packet, "TO");

                /* Makes user logged in. */
                // if (send_packet && !strcmp(get_value_buy_key(send_packet, "TYPE"), "login_s") && !strcmp(get_value_buy_key(send_packet, "STATUS"), "true"))
                    p->is_logged = true;
                
                for (connected_client_list_t *s = ctx.head.next; s != NULL; s = s->next) {
                    if (s->is_logged) { // && !strcmp(client_login, s->login)
                        send(s->sock_fd, send_packet, buf_len, 0);
                        printf("Sending of %d bytes\n",buf_len); // Debug.
                    }
                }                    
                // refreshing buffer.
                bzero(buffer,256);
                // free(send_packet);
                // free(client_login)
            }            
        }
        pthread_mutex_unlock(&ctx_mutex);
    }
    printf("handle_server thread was finished\n"); // Debug.
    return NULL;
}


int main(int argc, char **argv) {
    argv_validator(argc);
    int port             = get_port(argv);
    int listening_socket = listening_socket_init(port);
    database_init();
    server_context_init();

    /* 
     * Making sockfd listening for incomming requests.
     * The second argument - number of max. number of requests. 
     */
    listen(listening_socket, 128);

    pthread_t server_thread;
    int err = pthread_create(&server_thread, NULL, handle_server, NULL);
    error("Can not create new thread", err);

    /* 
     * Loop, which waits for incomming requests.
     * accept() creates new socket, which will be used for certain client.
     * Place new socket in linked list of opening sockets and in fd_set array. 
     */
    while(!quit) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int newsockfd = accept(listening_socket, (struct sockaddr *)&client, &client_len);

        // if acception error, continue the loop.
        if (newsockfd < 0) continue;

        /*
         * When new connection comes in, created socket is getting placed in 
         * linked list with opening sockets. If socket was successfully placed in llist,
         * it is also getting placed in fd_set bitarray (it`s needed for select.)
         * * Mutex is used because `ctx.head` is also used in handle_server thread.
         */
        pthread_mutex_lock(&ctx_mutex);
        int status = socket_list_add(&ctx.head, newsockfd);
        if (status == 0) {
            FD_SET(newsockfd, &ctx.read_descriptors);
            printf("New connection was accepted, socket = %d\n", newsockfd);
        }
        pthread_mutex_unlock(&ctx_mutex);
        error("Unable to add socket descriptor to the list", status);
    }
    sleep(2);
    server_context_free();
    printf("Main thread was finished\n");
    exit(0);
}
