extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

# define O_DIRECT	 040000

#include <fcntl.h>
#include "sigsegv.hpp"
#include "check.hpp"
#include "string.h"

int iTest = 1;

ssize_t wrap_read(int fd, char const *s, size_t nbyte, int erronoValue)
{
	errno = 0;
	int tripouille[42]; char buffer[100] = {0};
	ssize_t r = ft_read(fd, buffer, nbyte);
	//cout << "errno value = " << errno << endl;
	errnocheck(erronoValue); char c = -1; read(fd, &c, 1);
	if (erronoValue == EXIT_SUCCESS)
		check(!memcmp(s, buffer, nbyte) && (c == -1 || c == s[nbyte]));
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	signal(SIGPIPE, SIG_IGN);
	CATEGORY("ft_read");

	int fd = open("files/file", O_RDONLY);
	/* 1-2-3 */ check(wrap_read(fd, "Tripouille", 0, EXIT_SUCCESS) == 0);	close(fd); fd = open("files/file", O_RDONLY);
	/* 4-5-6 */ check(wrap_read(fd, "Tripouille", 3, EXIT_SUCCESS) == 3);	close(fd); fd = open("files/file", O_RDONLY);
	/* 7-8-9 */ check(wrap_read(fd, "Tripouille", 10, EXIT_SUCCESS) == 10);	close(fd);
	/* 10-11 */ check(wrap_read(-1, "", 1, EBADF) == -1);					fd = open("files", O_RDONLY);					
	/* 12-13 */ check(wrap_read(fd, "", 1, EISDIR) == -1);					close(fd);
	cout << ENDL;
	return (0);
}