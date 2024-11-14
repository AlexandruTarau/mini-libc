// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	mode_t mode = 0;
	va_list args;
	va_start(args, flags);

	// Check if there is O_CREAT flag
	if (flags & O_CREAT) {
		// If there is, we get the mode argument
		mode = va_arg(args, mode_t);
	}

	va_end(args);

	int res = syscall(__NR_open, filename, flags, mode);

	if (res < 0) {
		errno = -res;
	} else {
		return res;
	}

	return -1;
}

