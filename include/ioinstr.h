#ifndef __GLIBC_IOINSTR_INTERNAL_H__
#define __GLIBC_IOINSTR_INTERNAL_H__

#ifndef __ASSEMBLER__

typedef enum {
	GLIBC_SYSCALL_NO_INTERCEPT = 0,
	GLIBC_SYSCALL_INTERCEPTED = 1,
} glibc_syscall_intercept_result_t;

//structure containing the functions pointers to call
typedef glibc_syscall_intercept_result_t (*glibc_syscall_intercepter_t)(unsigned long int * result, long syscall_number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

extern void __glibc_syscall_intercepter_set(glibc_syscall_intercepter_t intercepter);
libc_hidden_proto(__glibc_syscall_intercepter_set);

#ifdef GLIBC_ENABLE_SYSCALL_INTERCEPT
extern glibc_syscall_intercepter_t glibc_syscall_intercepter;
#define GLIBC_SYSCALL_INTERCEPT(result, syscall_number, arg1, arg2, arg3, arg4, arg5, arg6) \
	if (glibc_syscall_intercepter != NULL) \
		intercep_result = glibc_syscall_intercepter((result), (syscall_number), (arg1), (arg2), (arg3), (arg4), (arg5), (arg6));
#else
#define GLIBC_SYSCALL_INTERCEPT(result, ...)
#endif

#endif

#endif //__GLIBC_IOINSTR_INTERNAL_H__

