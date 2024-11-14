#include <unistd.h>

int puts(char *str)
{
    int ret;

    while (*str != 0) {
        ret = write(1, str, 1);
        if (ret == -1) {
            return -1;
        }
        str++;
    }
    write(1, "\n", 1);

    return 1;
}
