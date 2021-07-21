#include <ioinstr.h>
#include <stdlib.h>

glibc_ioinstr_hooks_t * __glibc_ioinstr_get(void)
{
	return NULL;
}
libc_hidden_def (__glibc_ioinstr_get)
weak_alias (__glibc_ioinstr_get, glibc_ioinstr_get)
libc_hidden_weak (glibc_ioinstr_get)
