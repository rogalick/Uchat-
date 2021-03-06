#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include "cJSON.h"
#include "libmx.h"


typedef struct client_context_s {
	int sockfd;
	int write_pipe;
	int read_pipe;
} client_context_t;


static GtkWidget *grid;
void error(char *msg, int status);
void back_to_menu(GtkWidget *back, int sockfd);
void main_menu();
void do_login(GtkWidget *entryspawn, int sockfd);
void create_row(GtkWidget *labell, gpointer data);
void create_message(GtkWidget *newmessedgentry, gpointer data);

// Json lib. API
char *json_packet_former(int num, ...);
char *get_value_by_key(char *json_str, char *key);

// Logic
void do_registration(GtkWidget *Registration, client_context_t *client_context);


GtkWidget *login;
GtkWidget *nickname;
GtkWidget *Password;
GtkWidget *SecondPassword;
GtkWidget *Registration;
//static GtkWidget *newbutton;
static GtkWidget *fixed;
static GtkWidget *window;
static GtkWidget *grid;
static GtkWidget *labell;
static GtkWidget *labell2;
static GtkWidget *labell3;
static GtkWidget *scroll;
static GtkWidget *listbox;
static GtkWidget *listboxmess;
static GtkWidget *row;
static GtkWidget *gridmenu;
static GtkWidget *labellmenu;
static GtkWidget *labellmenu2;
static GtkWidget *labellmenu3;
static GtkWidget *icon;
static GtkWidget *leftbox;
static GtkWidget *rightbox;
static GtkWidget *downbox;
static GtkWidget *leftmenu;
static GtkWidget *searchmenu;
static GtkWidget *newchatbutton;

static GtkWidget *newmessedgentry;
static GtkWidget *scrollmess;
static GtkWidget *fileMenu;
static GdkEventTouch *trigger_event;