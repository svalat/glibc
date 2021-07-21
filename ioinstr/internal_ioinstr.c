#include "ioinstr.h"
#include <stdlib.h>

glibc_ioinstr_hooks_t * __glibc_ioinstr_hooks = NULL;
__thread int __glib_ioinstr_entered = 0;
