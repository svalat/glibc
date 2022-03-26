#ifndef __GLIBC_SYSCALL_INTERCEPTER_HEADER__
#define __GLIBC_SYSCALL_INTERCEPTER_HEADER__

//C++ handling
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	GLIBC_SYSCALL_NO_INTERCEPT = 0,
	GLIBC_SYSCALL_INTERCEPTED = 1,
} glibc_syscall_intercept_result_t;

//structure containing the functions pointers to call
typedef glibc_syscall_intercept_result_t (*glibc_syscall_intercepter_t)(unsigned long int * result, long syscall_number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

extern void glibc_syscall_intercepter_set(glibc_syscall_intercepter_t intercepter);

#ifdef GLIBC_ENABLE_SYSCALL_INTERCEPT
extern glibc_syscall_intercepter_t glibc_syscall_intercepter;
#else
#define glibc_syscall_intercepter(result, ...) GLIBC_SYSCALL_NO_INTERCEPT
#endif

//end of C++ handling
#ifdef __cplusplus
}
#endif


#endif //__GLIBC_HEADER__
