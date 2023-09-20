#include <stdlib.h>

char *int2str(int value, char *buf, int len) {
    int negative = value < 0;
    if (negative) value = -value; /* make value nonnegative */
    if (len < 1) return NULL; /* buffer too small */
    /* build up result from end to start */
    buf[--len] = 0; /* null terminator at end */
    do {
        if (len < 1) return NULL; /* buffer too small */
        buf[--len] = "0123456789"[value % 10]; /* add digit to buf */
        value /= 10; /* remove digit from value */
    } while (value != 0);
    if (negative) {
        if (len < 1) return NULL; /* buffer too small */
        buf[--len] = '-'; /* add minus sign */
    }
    return buf + len;
}

int main(int argc, char **argv){
    char buffer[atoi(argv[2])];
    int2str(atoi(argv[1]), buffer, atoi(argv[2]));
    return 0;
}