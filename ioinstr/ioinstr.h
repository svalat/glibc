#ifndef __GLIBC_HEADER__
#define __GLIBC_HEADER__

//C++ handling
#ifdef __cplusplus
extern "C" {
#endif

//used when an intercept function ignore the incomming call
//to defer to next stage or standard calls
#define GLIBC_IOINSTR_IGNORED (-2)

//structure containing the functions pointers to call
struct glibc_ioinstr_hooks_s {
	int (*open)(const char *pathname, int flags);
	int (*close)(int fd);
};
typedef struct glibc_ioinstr_hooks_s glibc_ioinstr_hooks_t;

extern glibc_ioinstr_hooks_t * glibc_ioinstr_set(glibc_ioinstr_hooks_t * hooks);
extern glibc_ioinstr_hooks_t * glibc_ioinstr_get(void);

//end of C++ handling
#ifdef __cplusplus
}
#endif


#endif //__GLIBC_HEADER__
