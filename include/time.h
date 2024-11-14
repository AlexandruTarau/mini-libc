typedef long int __time_t;
typedef __time_t time_t;

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

int nanosleep(const struct timespec *t1, struct timespec *t2);
unsigned int sleep(unsigned int sec);
