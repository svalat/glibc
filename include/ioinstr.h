#ifndef __GLIBC_IOINSTR_INTERNAL_H__
#define __GLIBC_IOINSTR_INTERNAL_H__

//include public API
#include "../ioinstr/ioinstr.h"

//define global
extern glibc_ioinstr_hooks_t * __glibc_ioinstr_hooks;
extern __thread int __glib_ioinstr_entered;

libc_hidden_proto (glibc_ioinstr_set)
extern glibc_ioinstr_hooks_t * __glibc_ioinstr_set(glibc_ioinstr_hooks_t * hooks); 
libc_hidden_proto (__glibc_ioinstr_set)

libc_hidden_proto (glibc_ioinstr_get)
extern glibc_ioinstr_hooks_t * __glibc_ioinstr_get(void);
libc_hidden_proto (__glibc_ioinstr_get)

#endif //__GLIBC_IOINSTR_INTERNAL_H__

