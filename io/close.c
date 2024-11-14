// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	int res = syscall(__NR_close, fd);

	if (res < 0) {
		errno = -res;
	} else {
		return res;
	}

	return -1;
}
