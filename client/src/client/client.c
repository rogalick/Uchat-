#include "client.h"
GtkWidget *entryspawn;
client_context_t *client_context;

static int messagenumber = 0;
static int n = 0;

static void destroy(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}


void back_to_menu(GtkWidget *back, int sockfd){
    gtk_widget_destroy(grid);
    gtk_widget_destroy(back);
    main_menu(sockfd);
}

void do_login(GtkWidget *entryspawn, int sockfd){
    // char *buffer = (char *)gtk_entry_get_text(GTK_ENTRY(login));
    // char *bufferPassword = (char *)gtk_entry_get_text(GTK_ENTRY(Password));
    // send(sockfd,buffer,sizeof(buffer),0);
    // send(sockfd,bufferPassword,sizeof(bufferPassword),0);

    
    //another function

    gtk_widget_destroy(grid);
    scroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (fixed), scroll, 0,50);

    leftbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(leftbox,300,50);
    gtk_widget_set_name(leftbox,"leftbox");
    gtk_fixed_put(GTK_FIXED (fixed), leftbox, 0,0);

    leftmenu = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(leftbox), leftmenu, TRUE, TRUE, 0);
    gtk_widget_set_name(leftmenu,"leftmenu");
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/menu_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (leftmenu), icon);

    searchmenu = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchmenu),"Search");
    gtk_widget_set_name(searchmenu,"searchmenu");
    gtk_box_pack_start(GTK_BOX(leftbox),searchmenu, TRUE, TRUE, 10);
    

    newchatbutton = gtk_button_new();
    gtk_box_pack_end(GTK_BOX(leftbox), newchatbutton, TRUE, TRUE, 0);
    g_signal_connect(newchatbutton, "clicked", G_CALLBACK(create_row), NULL);
    iconn = gdk_pixbuf_new_from_file("./media/img/plus_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (newchatbutton), icon);

    rightbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(rightbox,724,50);
    gtk_widget_set_name(rightbox,"rightbox");
    gtk_fixed_put(GTK_FIXED (fixed), rightbox, 300,0);

    listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox,"listboxleft");
    gtk_widget_set_size_request(scroll,300,718);
    gtk_container_add(GTK_CONTAINER(scroll), listbox);

    downbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(downbox,724,50);
    gtk_widget_set_name(downbox,"downbox");
    gtk_fixed_put(GTK_FIXED (fixed), downbox, 300,718);

    newmessedgentry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(newmessedgentry),"Write a message...");
    gtk_widget_set_name(newmessedgentry,"newmessedgentry");
    gtk_box_pack_start(GTK_BOX(downbox),newmessedgentry, TRUE, TRUE, 0);
    g_signal_connect(newmessedgentry, "activate", G_CALLBACK(create_message), NULL);

    scrollmess = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (fixed), scrollmess, 300,50);
    gtk_widget_set_name(scrollmess,"scrollmess");
    gtk_widget_set_size_request(GTK_WIDGET(scrollmess),724,668);

    listboxmess = gtk_list_box_new();
    gtk_widget_set_name(listboxmess,"listboxmess");
    gtk_container_add(GTK_CONTAINER(scrollmess), listboxmess);

     gtk_widget_show_all(window);
}


void create_message(GtkWidget *newmessedgentry, gpointer data){
    GtkWidget *row;
    row = gtk_list_box_row_new();
    gtk_widget_set_name(row,"message");
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listboxmess),row,n);
    messagenumber++;

    gridmenu = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(row), gridmenu);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_grid_attach(GTK_GRID(gridmenu), icon, 0, 0, 1, 2);

    labellmenu = gtk_label_new("Vlad");
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu, 1, 0, 1, 1);

    labellmenu2 = gtk_label_new("Kill me please \nHello");
    gtk_widget_set_name(labellmenu2,"labellmenu2");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu2, 1, 1, 1, 1);

    labellmenu3 = gtk_label_new("Yesterday");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu3, 2, 0, 1, 1);
    gtk_widget_set_name(labellmenu3,"labellmenu3");

    fileMenu = gtk_menu_new();
    gtk_menu_popup_at_pointer (GTK_MENU (fileMenu),trigger_event);
    Password = gtk_button_new_with_label("fdfdf");
    gtk_container_add(fileMenu,Password);

    gtk_widget_show_all(window);
}


void create_row(GtkWidget *labell, gpointer data){
    GtkWidget *row;
    row = gtk_list_box_row_new();
    gtk_widget_set_name(row,"chatrow");
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listbox),row,n);
    n++;

    gridmenu = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(row), gridmenu);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_grid_attach(GTK_GRID(gridmenu), icon, 0, 0, 1, 2);

    labellmenu = gtk_label_new("Vlad");
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu, 1, 0, 1, 1);

    labellmenu2 = gtk_label_new("Kill me please");
    gtk_widget_set_name(labellmenu2,"labellmenu2");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu2, 1, 1, 1, 1);

    labellmenu3 = gtk_label_new("Yesterday");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu3, 2, 0, 1, 1);
    gtk_widget_set_name(labellmenu3,"labellmenu3");

    gtk_widget_show_all(window);
}


void make_registration(GtkWidget *Registration, client_context_t *client_context){
    GtkWidget *back;

    gtk_widget_destroy(grid);

    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 350,175);

    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokeball.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 128,128, GDK_INTERP_BILINEAR);
    GtkWidget *iconnn = gtk_image_new_from_pixbuf(iconn);
     gtk_widget_set_name(iconnn,"image");
     gtk_grid_attach(GTK_GRID(grid), iconnn, 1, 98, 1, 1);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login),"Login");
    gtk_grid_attach(GTK_GRID(grid), login, 1, 99, 1, 1);

    nickname = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(nickname),"Username");
    gtk_grid_attach(GTK_GRID(grid), nickname, 1, 100, 1, 1);

    labell = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell, 1, 101, 1, 1);

    Password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password),"Password");
    gtk_grid_attach(GTK_GRID(grid), Password, 1, 102, 1, 1);

    SecondPassword = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(SecondPassword),"Confirm your password");
    gtk_grid_attach(GTK_GRID(grid), SecondPassword, 1, 103, 1, 1);

    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 104, 1, 1);


    Registration = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(do_registration), client_context);
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 105, 1, 1);

    labell3 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell3, 1, 106, 1, 1);

    back = gtk_button_new_with_label("Back to Login");
    gtk_widget_set_name(back,"log");
    g_signal_connect(back, "clicked", G_CALLBACK(back_to_menu), client_context->sockfd);
    gtk_grid_attach(GTK_GRID(grid), back, 1, 107, 1, 1);
    //gtk_fixed_put(GTK_FIXED (fixed), back, 550,540);

    gtk_widget_show_all(window);
    }
// Checks, wether user specified input correctly.
static void argv_validator(int argc, char **argv) {
    char *msg;

    if (argc != 3) {
        msg = "usage: ./client ip_address port\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }

    int port = atoi(argv[2]);
    if (port == 0) {
        msg = "Invalid port number\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}

void main_menu() {
    //GtkWidget *scroll;
    //GtkWidget *view;
    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 350,175);

    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokeball.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 128,128, GDK_INTERP_BILINEAR);
    GtkWidget *iconnn = gtk_image_new_from_pixbuf(iconn);
    // iconn = gtk_image_new_from_file("Unknown.jpeg");
     gtk_widget_set_name(iconnn,"image");
     gtk_grid_attach(GTK_GRID(grid), iconnn, 1, 98, 1, 1);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login),"Login");
    gtk_widget_set_name(login,"login");
    gtk_grid_attach(GTK_GRID(grid), login, 1, 99, 1, 1);

    labell = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell, 1, 100, 1, 1);

    Password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password),"Password");
    gtk_widget_set_name(Password,"Password");
    gtk_grid_attach(GTK_GRID(grid), Password, 1, 101, 1, 1);
    
    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 102, 1, 1);

    entryspawn = gtk_button_new_with_label("Login");
    gtk_widget_set_name(entryspawn,"log");
    g_signal_connect(entryspawn, "clicked", G_CALLBACK(do_login), client_context->sockfd);
    gtk_grid_attach(GTK_GRID(grid), entryspawn, 1, 103, 1, 1);

    labell3 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell3, 1, 104, 1, 1);

    Registration = gtk_button_new_with_label("Sign In");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(make_registration), client_context);
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 105, 1, 1);

    gtk_widget_set_size_request(GTK_WIDGET(window),1024,768);
    //gtk_window_set_resizable(GTK_WIDGET(window), FALSE);
    gtk_widget_show_all(window);

    // fd_set read_descriptors;
    // FD_ZERO(&read_descriptors);
    // FD_SET(client_context->read_pipe, &read_descriptors);
    // struct timeval tv;
    // tv.tv_sec  = 1; // seconds.
    // tv.tv_usec = 0; // mili-seconds.
    // int status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);
    // // if no sockets are availabe => continue loop.
    // if (status > 0) {
    //     char buf[1000];
    //     bzero(buf, 1000);
    //     read(client_context->read_pipe, buf, 1000);
    //     printf(">>>>%s\n", buf);
    //     bzero(buf, 1000);
    // }
    // else {
    //     printf("%d\n", status);
    // }

}

// Main window init.
void gui(int argc, char **argv, client_context_t *client_context) {
    gtk_init(&argc, &argv);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path (provider,"./media/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(provider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    main_menu();

    gtk_main();
}

static int Socket() {
    // Create socket TCP and IPv4
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Error while creating socket", sockfd);

    return sockfd;
}

static struct sockaddr_in client_address_describer(int port) {
    /*
     * Create structure, where client address is described.
     * 1. server`s address
     * 2. ip version AF_INET = IPv4
     * 3. server`s port.
     */
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);

    return client_addr;
}

void client_context_init(int sockfd, int write_pipe, int read_pipe) {
    client_context = (client_context_t *)malloc(sizeof(client_context_t));
    if (client_context == NULL) {
        char *msg = "Client context malloc error\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    client_context->sockfd     = sockfd;
    client_context->write_pipe = write_pipe;
    client_context->read_pipe  = read_pipe;
}


// System functions block. (PS. they must be moved in new folder + one file for each func.)
// System functions are functions, which handle packets received from server.
// Each function already takes packet of needed type. (packet type is checked if server_communication func. (received packets from server))
// Further login is being done in *_system functions.

/*
 * Make registration of the user.
 * Takes packet of type 'reg_s' from server.
 * analyze it -> if reg. was successful -> open user`s main view.
 * Otherwise displays fail msg in gui.
 */
void registration_system(char *packet) {
    char *msg;
    char *status = get_value_by_key(packet, "STATUS");

    if (!strcmp(status, "true")) {
        // Redirect user to char main page.
        do_login(entryspawn, client_context->sockfd);
    }
    else {
        // Registration failed. - display the corresponging msg.
        msg = get_value_by_key(packet, "MSG");
        // регестрация прошла неуспешно
        // тут у пользователя должно вывестись красным msg.
        // msg - какая ошибка возникла при регистрации.
    }
}

/*
 * Do the login of the user.
 * Takes 'login_s' packet from the server.
 * Depenging of status in login_s packet does login or displays
 * error msg. in the gui.
 */
void login_system(char *packet) {
    // login functional.
}

// End of system functions

/*
 * Thread, which receives packets from server.
 * When packet received, it is analyzed.
 * Depending on packet type, the corresponding handle function calls.
 */
void *server_communication(void *param) {
    while(1) {
        fd_set read_descriptors;
        FD_ZERO(&read_descriptors);
        FD_SET(client_context->sockfd, &read_descriptors);

        // Set time select must wait for incomming packets.
        struct timeval tv;
        tv.tv_sec  = 1; // seconds.
        tv.tv_usec = 0; // mili-seconds.

        char packet[1000];
        bzero(packet, 1000);
        int status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);
        if (status <= 0) continue;

        read(client_context->sockfd, packet, 1000);
        char *packet_type = get_value_by_key(packet, "TYPE");

        if (!strcmp(packet_type, "reg_s"))
            registration_system(packet);
        else if (!strcmp(packet_type, "login_s")) {
            // login system
            printf("login packet received\n");
        }
        else if (!strcmp(packet_type, "find_user_s")) {
            // find_user system
            printf("%s\n", "find_user packet receive");
        }
        else if (!strcmp(packet_type, "msg_s")) {
            printf("%s\n", "msg packet received");
        }


    }
    return NULL;
}

int main(int argc, char **argv) {
    argv_validator(argc, argv);
    int port                       = atoi(argv[2]);
    int sockfd                     = Socket();
    struct sockaddr_in client_addr = client_address_describer(port);

    int pipefd[2];
    pipe(pipefd);

    // Do the connect to the server.
    int res = connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    error("Error while connection", res);

    client_context_init(sockfd, pipefd[1], pipefd[0]);
    pthread_t client_thread;
    int err = pthread_create(&client_thread, NULL, server_communication, NULL);

    // Gui initialization
    gui(argc, argv, client_context);
    free(client_context);
    return 0;
}





