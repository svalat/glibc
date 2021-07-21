#include <ioinstr.h>
#include <stdlib.h>

glibc_ioinstr_hooks_t * __glibc_ioinstr_set(glibc_ioinstr_hooks_t * hooks)
{
	return NULL;
}
libc_hidden_def (__glibc_ioinstr_set)
weak_alias (__glibc_ioinstr_set, glibc_ioinstr_set)
libc_hidden_weak (glibc_ioinstr_set)
