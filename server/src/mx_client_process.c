#include "server.h"


// Determines type of packet.
static char *packet_type_determiner(char *buffer) {
    char *packet_type = NULL;
    cJSON *parsed_str = cJSON_Parse(buffer);
    char *msg = "Json Parsing error\n";
    if (parsed_str == NULL) {
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    cJSON *type = cJSON_GetObjectItemCaseSensitive(parsed_str, "TYPE");
    if (cJSON_IsString(type) && (type->valuestring != NULL)) {
        packet_type = mx_string_copy(type->valuestring);
    }
    cJSON_Delete(parsed_str);

    return packet_type;
}


void mx_client_process(int client_socket) {
    int n;
    char buffer[256];
    bzero(buffer,256);
    while(1) {
        n = read(client_socket, buffer, 255);


        char *packet_type = packet_type_determiner(buffer);
        if (!strcmp(packet_type, "login")) {
            printf("%s\n", "Hello in login module");
        }
		
        // refreshing buffer.
        bzero(buffer,256);
    }
}
