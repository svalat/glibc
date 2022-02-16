/* Linux writev syscall implementation.
   Copyright (C) 2017-2021 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <unistd.h>
#include <sys/uio.h>
#include <sysdep-cancel.h>

#include <ioinstr.h>

ssize_t
__writev (int fd, const struct iovec *iov, int iovcnt)
{
  /* Instrumentation */
  if (__glibc_ioinstr_hooks != NULL && __glib_ioinstr_entered == false && __glibc_ioinstr_hooks->writev != NULL) {
    __glib_ioinstr_entered = true;
    ssize_t ret = __glibc_ioinstr_hooks->writev(fd, iov, iovcnt);
    __glib_ioinstr_entered = false;
    return ret;
  }

  /* Standard implementation */
  return SYSCALL_CANCEL (writev, fd, iov, iovcnt);
}
libc_hidden_def (__writev)
weak_alias (__writev, writev)
