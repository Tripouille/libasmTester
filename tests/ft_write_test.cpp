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

ssize_t wrap_write(int out, int in, const void *src, size_t nbyte, int erronoValue)
{
	errno = 0;
	int tripouille[42];
	ssize_t r = ft_write(out, src, nbyte);
	//cout << "errno value = " << errno << endl;
	errnocheck(erronoValue);
	if (erronoValue == EXIT_SUCCESS)
	{
		char dst[100]; memset(dst, 'X', 100); dst[99] = 0;
		read(in, dst, nbyte);
		char eof = EOF; char c = 0; write(out, &eof, 1); read(in, &c, 1);
		check(!memcmp(dst, (char const *)src, nbyte) && c == eof);
	}
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	signal(SIGPIPE, SIG_IGN);
	CATEGORY("ft_write");

	int p[2]; pipe(p);
	/* 1-2-3 */ check(wrap_write(p[1], p[0], "Tripouille", 3, EXIT_SUCCESS) == 3);	close(p[0]); close(p[1]); pipe(p);
	/* 4-5-6 */ check(wrap_write(p[1], p[0], "", 0, EXIT_SUCCESS) == 0);			close(p[0]); close(p[1]); pipe(p);
	/* 7-8-9 */ check(wrap_write(p[1], p[0], "", 1, EXIT_SUCCESS) == 1);			close(p[0]); close(p[1]);
	/* 10-11 */ check(wrap_write(  -1, p[0], "", 1, EBADF) == -1);					pipe(p); close(p[0]);
	/* 12-13 */ check(wrap_write(p[1], p[0], "", 1, EPIPE) == -1);					close(p[1]); pipe(p);
	/* 14-15 */ check(wrap_write(p[1], p[0], NULL, 1, EINVAL) == -1);				close(p[0]); close(p[1]);
	cout << ENDL;
	return (0);
}
