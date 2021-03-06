#include "client.h"

/*
 * This is registration module.
 * It is called, when user press register. button on reg. page.
 * This functional:
 *      1. Reads all data from input boxes on reg. page.
 *      2. Validates read data. (checks, whether input was an empty str or
 *          any of forbidden chars were used.)
 *      3. Froms reg_c packet and sends it to the server.
 */


#define OKEY                      0
#define PASS_FORBIDDEN_SYMBOLS    1
#define PASS_DIFFERENT            2
#define NICK_FORBIDDEN_SYMBOLS    3
#define LOGIN_FORBIDDEN_SYMBOLS   4
#define NICKNAME_IS_EMPTY         5
#define LOGIN_IS_EMPTY            6
#define PASSWORD_1_IS_EMPTY       7
#define PASSWORD_2_IS_EMPTY       8


// Validates syntax of login input.
static int login_validator(char *input_login) {
    char *forbidden_symbols = " :";
    
    if (mx_symbols_in_str(input_login, forbidden_symbols))
        return LOGIN_FORBIDDEN_SYMBOLS;

    if ((int)strlen(input_login) == 0)
        return LOGIN_IS_EMPTY;
    return OKEY;
}

// Validates syntax of nick input.
static int nick_validator(char *input_nick) {
    char *forbidden_symbols = " :";

    if (mx_symbols_in_str(input_nick, forbidden_symbols))
        return NICK_FORBIDDEN_SYMBOLS;
    if ((int)strlen(input_nick) == 0)
        return NICKNAME_IS_EMPTY;
    return OKEY;
}

// Validates syntax of password input.
static int pass_validator(char *password_1, char *password_2) {
    char *forbidden_symbols = " :";

    if (mx_symbols_in_str(password_1, forbidden_symbols))
        return PASS_FORBIDDEN_SYMBOLS;
    if (strcmp(password_1, password_2) != 0)
        return PASS_DIFFERENT;
    if ((int)strlen(password_1) == 0)
        return PASSWORD_1_IS_EMPTY;
    if ((int)strlen(password_2) == 0)
        return PASSWORD_2_IS_EMPTY;
    return OKEY;
}

// Makes validation of all inputed data.
static int validate(char *input_login, char *input_nick, char *input_password, char *input_password_confirm) {
    int validate_login_status = login_validator(input_login);
    int validate_nick_status  = nick_validator(input_nick);
    int validate_pass_status  = pass_validator(input_password, input_password_confirm);

    if (validate_login_status != OKEY)
        return validate_login_status;
    else if (validate_nick_status != OKEY)
        return validate_nick_status;
    else if (validate_pass_status != OKEY)
        return validate_pass_status;
    return OKEY;
}

static char *make_packet(char *input_login, char *input_nick, char *input_password) {
    char *login_pair = mx_strjoin("LOGIN:", input_login);
    char *pass_pair  = mx_strjoin("PASSWORD:", input_password);
    char *nick_pair  = mx_strjoin("NICKNAME:", input_nick);

    char *packet = json_packet_former(4, "TYPE:reg_c", login_pair, pass_pair, nick_pair);
    free(login_pair);
    free(pass_pair);
    free(nick_pair);
    return packet;
}

void do_registration(GtkWidget *Registration, client_context_t *client_context) {
    // Getting data from input boxes.
    char *input_login            = (char *)gtk_entry_get_text(GTK_ENTRY(login));
    char *input_nick             = (char *)gtk_entry_get_text(GTK_ENTRY(nickname));
    char *input_password         = (char *)gtk_entry_get_text(GTK_ENTRY(Password));
    char *input_password_confirm = (char *)gtk_entry_get_text(GTK_ENTRY(SecondPassword));


    // Input values validation
    char *packet;
    int validate_status = validate(input_login, input_nick, input_password, input_password_confirm);
    if (validate_status != OKEY) {
        // тут должен быть функционал, который выводит пользователю сообщение (validate_status) об неправильном синтаксисе инпута.
    }
    else {
        packet = make_packet(input_login, input_nick, input_password);
        send(client_context->sockfd, packet, (int)strlen(packet), 0); // sending registration packet to the server.
        free(packet);
    }
}


