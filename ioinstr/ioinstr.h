#ifndef __GLIBC_HEADER__
#define __GLIBC_HEADER__

#include <sys/types.h>
#include <unistd.h>
#include <sysdep.h>

//C++ handling
#ifdef __cplusplus
extern "C" {
#endif

//types to be used
struct stat;
struct stat64;
struct statfs;
struct statfs64;
struct file_handle;

//used when an intercept function ignore the incomming call
//to defer to next stage or standard calls
#define GLIBC_IOINSTR_IGNORED (-2)

//structure containing the functions pointers to call
struct glibc_ioinstr_hooks_s {
	int (*open)(const char *pathname, int flags, int mode);
	int (*open64)(const char *pathname, int flags, int mode);
	int (*openat)(int fd, const char *pathname, int flags, int mode);
	int (*openat64)(int fd, const char *pathname, int flags, int mode);
	int (*creat)(const char *file, mode_t mode);
	int (*creat64)(const char *file, mode_t mode);
	int (*fdatasync)(int fd);
	int (*fstat)(int fd, struct stat *buf);
	int (*fstat64)(int fd, struct stat64 *buf);
	int (*fstatat)(int fd, const char *file, struct stat *buf, int flag);
	int (*fstatat64)(int fd, const char *file, struct stat64 *buf, int flags);
	int (*fstatfs)(int fd, struct statfs *buf);
	int (*fstatfs64)(int fd, struct statfs64 *buf);
	int (*fsync)(int fd);
	int (*ftruncate)(int fd, off_t length);
	int (*ftruncate64)(int fd, off64_t length);
	off_t (*lseek)(int fd, off_t offset, int whence);
	off64_t (*lseek64)(int fd, off64_t offset, int whence);
	int (*lstat)(const char *file, struct stat *buf);
	int (*lstat64)(const char *file, struct stat *buf);
	int (*open_by_handle_at)(int mount_fd, struct file_handle *handle, int flags);
	int (*posix_fadvise)(int fd, off_t offset, off_t len, int advise);
	int (*posix_fadvise64)(int fd, off64_t offset, off64_t len, int advise);
	int (*posix_fallocate)(int fd, __off_t offset, __off_t len);
	int (*posix_fallocate64)(int fd, __off64_t offset, __off64_t len);
	ssize_t (*pread)(int fd, void *buf, size_t count, off_t offset);
	ssize_t (*pread64)(int fd, void *buf, size_t count, off64_t offset);
	ssize_t (*preadv)(int fd, const struct iovec *vector, int count, off_t offset);
	ssize_t (*preadv2)(int fd, const struct iovec *vector, int count, off_t offset, int flags);
	ssize_t (*preadv64)(int fd, const struct iovec *vector, int count, off64_t offset);
	ssize_t (*preadv64v2)(int fd, const struct iovec *vector, int count, off64_t offset,int flags);
	ssize_t (*pwrite)(int fd, const void *buf, size_t count, off_t offset);
	ssize_t (*pwrite64)(int fd, const void *buf, size_t count, off64_t offset);
	ssize_t (*pwritev)(int fd, const struct iovec *vector, int count, off_t offset);
	ssize_t (*pwritev2)(int fd, const struct iovec *vector, int count, off_t offset, int flags);
	ssize_t (*pwritev64)(int fd, const struct iovec *vector, int count, off64_t offset);
	ssize_t (*pwritev64v2)(int fd, const struct iovec *vector, int count, off64_t offset,int flags);
	ssize_t (*read)(int fd, void *buf, size_t nbytes);
	ssize_t (*readahead)(int fd, off64_t offset, size_t count);
	ssize_t (*readv)(int fd, const struct iovec *iov, int iovcnt);
	int (*rename)(const char *old, const char *new);
	int (*renameat)(int oldfd, const char *old, int newfd, const char *new);
	int (*renameat2)(int oldfd, const char *old, int newfd, const char *new,unsigned int flags);
	ssize_t (*splice)(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len,unsigned int flags);
	int (*stat)(const char *file, struct stat *buf);
	int (*stat64)(const char *file, struct stat64 *buf);
	int (*statfs)(const char *file, struct statfs *buf);
	int (*statfs64)(const char *file, struct statfs64 *buf);
	int (*sync_file_range)(int fd, off64_t offset, off64_t len, unsigned int flags);
	int (*truncate)(const char *path, off_t length);
	int (*truncate64)(const char *path, off64_t length);
	ssize_t (*write)(int fd, const void *buf, size_t nbytes);
	ssize_t (*writev)(int fd, const struct iovec *iov, int iovcnt);
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
