#include <internal/syscall.h>
#include <errno.h>
#include <time.h>

int nanosleep(const struct timespec *t1, struct timespec *t2) {
    long res = syscall(__NR_nanosleep, t1, t2);

    if (res < 0) {
        errno = -res;
    } else {
        return 0;
    }

    return -1;
}

unsigned int sleep(unsigned int sec) {
    struct timespec t1 = {sec, 0}, t2;

    int res = nanosleep(&t1, &t2);

    // If the nanosleep is interupted by a signal then return the remaining time in seconds
    if (res == -1) {
        if (errno == EINTR) {
            return t2.tv_sec;
        }
    }

    return 0;
}
