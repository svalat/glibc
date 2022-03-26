#include "ioinstr.h"
#include <stdlib.h>

glibc_syscall_intercepter_t glibc_syscall_intercepter = NULL;

void __glibc_syscall_intercepter_set(glibc_syscall_intercepter_t intercepter)
{
	glibc_syscall_intercepter = intercepter;
}

libc_hidden_def (__glibc_syscall_intercepter_set)
weak_alias(__glibc_syscall_intercepter_set, glibc_syscall_intercepter_set)
//libc_hidden_weak (glibc_syscall_intercepter_set)
