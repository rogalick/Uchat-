#include "libmx.h"

// Allocates memmory for new array.
char **mx_new_strarr(int size) {
    char **arr = (char **)malloc(size + 1);
    char *msg;

    if (arr == NULL) {
        msg = "malloc error\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    arr[size] = NULL;
    return arr;
}
