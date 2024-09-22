# 0 "cdecl.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "cdecl.c"
# 27 "cdecl.c"
# 1 "pjl_config.h" 1
# 35 "pjl_config.h"
# 1 "config.h" 1
# 1914 "config.h"
# 1 "/usr/include/stdbool.h" 1 3 4
# 1915 "config.h" 2
# 1932 "config.h"
# 1 "../lib/assert.h" 1
# 22 "../lib/assert.h"
       
# 23 "../lib/assert.h" 3



# 1 "/usr/include/assert.h" 1 3 4
# 1 "/usr/include/features.h" 1 3 4
# 2 "/usr/include/assert.h" 2 3 4
# 19 "/usr/include/assert.h" 3 4

# 19 "/usr/include/assert.h" 3 4
_Noreturn void __assert_fail (const char *, const char *, int, const char *);
# 27 "../lib/assert.h" 2 3
# 1933 "config.h" 2
# 36 "pjl_config.h" 2







# 1 "../lib/attribute.h" 1
# 44 "pjl_config.h" 2
# 28 "cdecl.c" 2
# 1 "cdecl.h" 1
# 31 "cdecl.h"
# 1 "types.h" 1
# 39 "types.h"
# 1 "slist.h" 1
# 36 "slist.h"
# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 101 "../lib/stddef.h" 3
# 1 "/usr/include/stddef.h" 1 3 4
# 19 "/usr/include/stddef.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 15 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned wchar_t;
# 49 "/usr/include/bits/alltypes.h" 3 4
typedef struct { long long __ll; long double __ld; } max_align_t;
# 58 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned long size_t;
# 68 "/usr/include/bits/alltypes.h" 3 4
typedef long ptrdiff_t;
# 20 "/usr/include/stddef.h" 2 3 4
# 102 "../lib/stddef.h" 2 3
# 37 "slist.h" 2
# 1 "../lib/unistd.h" 1
# 21 "../lib/unistd.h"
       
# 22 "../lib/unistd.h" 3
# 40 "../lib/unistd.h" 3
# 1 "/usr/include/fortify/unistd.h" 1 3 4
# 21 "/usr/include/fortify/unistd.h" 3 4
__extension__

# 1 "/usr/include/unistd.h" 1 3 4
# 37 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 73 "/usr/include/bits/alltypes.h" 3 4
typedef long ssize_t;




typedef long intptr_t;
# 170 "/usr/include/bits/alltypes.h" 3 4
typedef long off_t;
# 243 "/usr/include/bits/alltypes.h" 3 4
typedef int pid_t;
# 253 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned uid_t;




typedef unsigned gid_t;
# 268 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned useconds_t;
# 38 "/usr/include/unistd.h" 2 3 4

int pipe(int [2]);
int pipe2(int [2], int);
int close(int);
int posix_close(int, int);
int dup(int);
int dup2(int, int);
int dup3(int, int, int);
off_t lseek(int, off_t, int);
int fsync(int);
int fdatasync(int);

ssize_t read(int, void *, size_t);
ssize_t write(int, const void *, size_t);
ssize_t pread(int, void *, size_t, off_t);
ssize_t pwrite(int, const void *, size_t, off_t);

int chown(const char *, uid_t, gid_t);
int fchown(int, uid_t, gid_t);
int lchown(const char *, uid_t, gid_t);
int fchownat(int, const char *, uid_t, gid_t, int);

int link(const char *, const char *);
int linkat(int, const char *, int, const char *, int);
int symlink(const char *, const char *);
int symlinkat(const char *, int, const char *);
ssize_t readlink(const char *
# 64 "/usr/include/unistd.h"
                            __restrict__
# 64 "/usr/include/unistd.h" 3 4
                                      , char *
# 64 "/usr/include/unistd.h"
                                              __restrict__
# 64 "/usr/include/unistd.h" 3 4
                                                        , size_t);
ssize_t readlinkat(int, const char *
# 65 "/usr/include/unistd.h"
                                   __restrict__
# 65 "/usr/include/unistd.h" 3 4
                                             , char *
# 65 "/usr/include/unistd.h"
                                                     __restrict__
# 65 "/usr/include/unistd.h" 3 4
                                                               , size_t);
int unlink(const char *);
int unlinkat(int, const char *, int);
int rmdir(const char *);
int truncate(const char *, off_t);
int ftruncate(int, off_t);






int access(const char *, int);
int faccessat(int, const char *, int, int);

int chdir(const char *);
int fchdir(int);
char *getcwd(char *, size_t);

unsigned alarm(unsigned);
unsigned sleep(unsigned);
int pause(void);

pid_t fork(void);
pid_t _Fork(void);
int execve(const char *, char *const [], char *const []);
int execv(const char *, char *const []);
int execle(const char *, const char *, ...);
int execl(const char *, const char *, ...);
int execvp(const char *, char *const []);
int execlp(const char *, const char *, ...);
int fexecve(int, char *const [], char *const []);
_Noreturn void _exit(int);

pid_t getpid(void);
pid_t getppid(void);
pid_t getpgrp(void);
pid_t getpgid(pid_t);
int setpgid(pid_t, pid_t);
pid_t setsid(void);
pid_t getsid(pid_t);
char *ttyname(int);
int ttyname_r(int, char *, size_t);
int isatty(int);
pid_t tcgetpgrp(int);
int tcsetpgrp(int, pid_t);

uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);
int getgroups(int, gid_t []);
int setuid(uid_t);
int seteuid(uid_t);
int setgid(gid_t);
int setegid(gid_t);

char *getlogin(void);
int getlogin_r(char *, size_t);
int gethostname(char *, size_t);
char *ctermid(char *);

int getopt(int, char * const [], const char *);
extern char *optarg;
extern int optind, opterr, optopt;

long pathconf(const char *, int);
long fpathconf(int, int);
long sysconf(int);
size_t confstr(int, char *, size_t);






int setreuid(uid_t, uid_t);
int setregid(gid_t, gid_t);
int lockf(int, int, off_t);
long gethostid(void);
int nice(int);
void sync(void);
pid_t setpgrp(void);
char *crypt(const char *, const char *);
void encrypt(char *, int);
void swab(const void *
# 150 "/usr/include/unistd.h"
                     __restrict__
# 150 "/usr/include/unistd.h" 3 4
                               , void *
# 150 "/usr/include/unistd.h"
                                       __restrict__
# 150 "/usr/include/unistd.h" 3 4
                                                 , ssize_t);




int usleep(unsigned);
unsigned ualarm(unsigned, unsigned);






int brk(void *);
void *sbrk(intptr_t);
pid_t vfork(void);
int vhangup(void);
int chroot(const char *);
int getpagesize(void);
int getdtablesize(void);
int sethostname(const char *, size_t);
int getdomainname(char *, size_t);
int setdomainname(const char *, size_t);
int setgroups(size_t, const gid_t *);
char *getpass(const char *);
int daemon(int, int);
void setusershell(void);
void endusershell(void);
char *getusershell(void);
int acct(const char *);
long syscall(long, ...);
int execvpe(const char *, char *const [], char *const []);
int issetugid(void);
int getentropy(void *, size_t);
extern int optreset;



extern char **environ;
int setresuid(uid_t, uid_t, uid_t);
int setresgid(gid_t, gid_t, gid_t);
int getresuid(uid_t *, uid_t *, uid_t *);
int getresgid(gid_t *, gid_t *, gid_t *);
char *get_current_dir_name(void);
int syncfs(int);
int euidaccess(const char *, int);
int eaccess(const char *, int);
ssize_t copy_file_range(int, off_t *, int, off_t *, size_t, unsigned);
pid_t gettid(void);
# 260 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/posix.h" 1 3 4
# 261 "/usr/include/unistd.h" 2 3 4
# 24 "/usr/include/fortify/unistd.h" 2 3 4
# 41 "../lib/unistd.h" 2 3
# 82 "../lib/unistd.h" 3
# 1 "../lib/stddef.h" 1 3
# 27 "../lib/stddef.h" 3
       
# 28 "../lib/stddef.h" 3
# 83 "../lib/unistd.h" 2 3
# 117 "../lib/unistd.h" 3
# 1 "../lib/stdlib.h" 1 3
# 20 "../lib/stdlib.h" 3
       
# 21 "../lib/stdlib.h" 3
# 37 "../lib/stdlib.h" 3
# 1 "/usr/include/fortify/stdlib.h" 1 3 4
# 21 "/usr/include/fortify/stdlib.h" 3 4
__extension__

# 1 "/usr/include/stdlib.h" 1 3 4
# 21 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 22 "/usr/include/stdlib.h" 2 3 4

int atoi (const char *);
long atol (const char *);
long long atoll (const char *);
double atof (const char *);

float strtof (const char *
# 28 "/usr/include/stdlib.h"
                         __restrict__
# 28 "/usr/include/stdlib.h" 3 4
                                   , char **
# 28 "/usr/include/stdlib.h"
                                            __restrict__
# 28 "/usr/include/stdlib.h" 3 4
                                                      );
double strtod (const char *
# 29 "/usr/include/stdlib.h"
                          __restrict__
# 29 "/usr/include/stdlib.h" 3 4
                                    , char **
# 29 "/usr/include/stdlib.h"
                                             __restrict__
# 29 "/usr/include/stdlib.h" 3 4
                                                       );
long double strtold (const char *
# 30 "/usr/include/stdlib.h"
                                __restrict__
# 30 "/usr/include/stdlib.h" 3 4
                                          , char **
# 30 "/usr/include/stdlib.h"
                                                   __restrict__
# 30 "/usr/include/stdlib.h" 3 4
                                                             );

long strtol (const char *
# 32 "/usr/include/stdlib.h"
                        __restrict__
# 32 "/usr/include/stdlib.h" 3 4
                                  , char **
# 32 "/usr/include/stdlib.h"
                                           __restrict__
# 32 "/usr/include/stdlib.h" 3 4
                                                     , int);
unsigned long strtoul (const char *
# 33 "/usr/include/stdlib.h"
                                  __restrict__
# 33 "/usr/include/stdlib.h" 3 4
                                            , char **
# 33 "/usr/include/stdlib.h"
                                                     __restrict__
# 33 "/usr/include/stdlib.h" 3 4
                                                               , int);
long long strtoll (const char *
# 34 "/usr/include/stdlib.h"
                              __restrict__
# 34 "/usr/include/stdlib.h" 3 4
                                        , char **
# 34 "/usr/include/stdlib.h"
                                                 __restrict__
# 34 "/usr/include/stdlib.h" 3 4
                                                           , int);
unsigned long long strtoull (const char *
# 35 "/usr/include/stdlib.h"
                                        __restrict__
# 35 "/usr/include/stdlib.h" 3 4
                                                  , char **
# 35 "/usr/include/stdlib.h"
                                                           __restrict__
# 35 "/usr/include/stdlib.h" 3 4
                                                                     , int);

int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);
void *aligned_alloc(size_t, size_t);

_Noreturn void abort (void);
int atexit (void (*) (void));
_Noreturn void exit (int);
_Noreturn void _Exit (int);
int at_quick_exit (void (*) (void));
_Noreturn void quick_exit (int);

char *getenv (const char *);

int system (const char *);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));
void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);
long long llabs (long long);

typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;
typedef struct { long long quot, rem; } lldiv_t;

div_t div (int, int);
ldiv_t ldiv (long, long);
lldiv_t lldiv (long long, long long);

int mblen (const char *, size_t);
int mbtowc (wchar_t *
# 73 "/usr/include/stdlib.h"
                    __restrict__
# 73 "/usr/include/stdlib.h" 3 4
                              , const char *
# 73 "/usr/include/stdlib.h"
                                            __restrict__
# 73 "/usr/include/stdlib.h" 3 4
                                                      , size_t);
int wctomb (char *, wchar_t);
size_t mbstowcs (wchar_t *
# 75 "/usr/include/stdlib.h"
                         __restrict__
# 75 "/usr/include/stdlib.h" 3 4
                                   , const char *
# 75 "/usr/include/stdlib.h"
                                                 __restrict__
# 75 "/usr/include/stdlib.h" 3 4
                                                           , size_t);
size_t wcstombs (char *
# 76 "/usr/include/stdlib.h"
                      __restrict__
# 76 "/usr/include/stdlib.h" 3 4
                                , const wchar_t *
# 76 "/usr/include/stdlib.h"
                                                 __restrict__
# 76 "/usr/include/stdlib.h" 3 4
                                                           , size_t);




size_t __ctype_get_mb_cur_max(void);
# 101 "/usr/include/stdlib.h" 3 4
int posix_memalign (void **, size_t, size_t);
int setenv (const char *, const char *, int);
int unsetenv (const char *);
int mkstemp (char *);
int mkostemp (char *, int);
char *mkdtemp (char *);
int getsubopt (char **, char *const *, char **);
int rand_r (unsigned *);






char *realpath (const char *
# 115 "/usr/include/stdlib.h"
                           __restrict__
# 115 "/usr/include/stdlib.h" 3 4
                                     , char *
# 115 "/usr/include/stdlib.h"
                                             __restrict__
# 115 "/usr/include/stdlib.h" 3 4
                                                       );
long int random (void);
void srandom (unsigned int);
char *initstate (unsigned int, char *, size_t);
char *setstate (char *);
int putenv (char *);
int posix_openpt (int);
int grantpt (int);
int unlockpt (int);
char *ptsname (int);
char *l64a (long);
long a64l (const char *);
void setkey (const char *);
double drand48 (void);
double erand48 (unsigned short [3]);
long int lrand48 (void);
long int nrand48 (unsigned short [3]);
long mrand48 (void);
long jrand48 (unsigned short [3]);
void srand48 (long);
unsigned short *seed48 (unsigned short [3]);
void lcong48 (unsigned short [7]);



# 1 "../lib/alloca.h" 1 3 4
# 141 "/usr/include/stdlib.h" 2 3 4
char *mktemp (char *);
int mkstemps (char *, int);
int mkostemps (char *, int, int);
void *valloc (size_t);
void *memalign(size_t, size_t);
int getloadavg(double *, int);
int clearenv(void);


void *reallocarray (void *, size_t, size_t);
void qsort_r (void *, size_t, size_t, int (*)(const void *, const void *, void *), void *);



int ptsname_r(int, char *, size_t);
char *ecvt(double, int, int *, int *);
char *fcvt(double, int, int *, int *);
char *gcvt(double, int, char *);
char *secure_getenv(const char *);
struct __locale_struct;
float strtof_l(const char *
# 161 "/usr/include/stdlib.h"
                          __restrict__
# 161 "/usr/include/stdlib.h" 3 4
                                    , char **
# 161 "/usr/include/stdlib.h"
                                             __restrict__
# 161 "/usr/include/stdlib.h" 3 4
                                                       , struct __locale_struct *);
double strtod_l(const char *
# 162 "/usr/include/stdlib.h"
                           __restrict__
# 162 "/usr/include/stdlib.h" 3 4
                                     , char **
# 162 "/usr/include/stdlib.h"
                                              __restrict__
# 162 "/usr/include/stdlib.h" 3 4
                                                        , struct __locale_struct *);
long double strtold_l(const char *
# 163 "/usr/include/stdlib.h"
                                 __restrict__
# 163 "/usr/include/stdlib.h" 3 4
                                           , char **
# 163 "/usr/include/stdlib.h"
                                                    __restrict__
# 163 "/usr/include/stdlib.h" 3 4
                                                              , struct __locale_struct *);
# 24 "/usr/include/fortify/stdlib.h" 2 3 4
# 38 "../lib/stdlib.h" 2 3
# 118 "../lib/unistd.h" 2 3
# 166 "../lib/unistd.h" 3
# 1 "../lib/sys/types.h" 1 3
# 20 "../lib/sys/types.h" 3
       
# 21 "../lib/sys/types.h" 3
# 46 "../lib/sys/types.h" 3
# 1 "/usr/include/sys/types.h" 1 3 4
# 57 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 27 "/usr/include/bits/alltypes.h" 3 4
typedef int blksize_t;




typedef unsigned int nlink_t;
# 88 "/usr/include/bits/alltypes.h" 3 4
typedef long register_t;




typedef long time_t;




typedef long suseconds_t;





typedef signed char int8_t;




typedef signed short int16_t;




typedef signed int int32_t;




typedef signed long int64_t;
# 149 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned long u_int64_t;
# 160 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned mode_t;
# 175 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned long ino_t;




typedef unsigned long dev_t;
# 190 "/usr/include/bits/alltypes.h" 3 4
typedef long blkcnt_t;




typedef unsigned long fsblkcnt_t;




typedef unsigned long fsfilcnt_t;
# 217 "/usr/include/bits/alltypes.h" 3 4
typedef void * timer_t;




typedef int clockid_t;




typedef long clock_t;
# 248 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned id_t;
# 263 "/usr/include/bits/alltypes.h" 3 4
typedef int key_t;
# 281 "/usr/include/bits/alltypes.h" 3 4
typedef struct __pthread * pthread_t;





typedef int pthread_once_t;




typedef unsigned pthread_key_t;




typedef int pthread_spinlock_t;




typedef struct { unsigned __attr; } pthread_mutexattr_t;




typedef struct { unsigned __attr; } pthread_condattr_t;




typedef struct { unsigned __attr; } pthread_barrierattr_t;




typedef struct { unsigned __attr[2]; } pthread_rwlockattr_t;
# 386 "/usr/include/bits/alltypes.h" 3 4
typedef struct { union { int __i[sizeof(long)==8?14:9]; volatile int __vi[sizeof(long)==8?14:9]; unsigned long __s[sizeof(long)==8?7:9]; } __u; } pthread_attr_t;




typedef struct { union { int __i[sizeof(long)==8?10:6]; volatile int __vi[sizeof(long)==8?10:6]; volatile void *volatile __p[sizeof(long)==8?5:6]; } __u; } pthread_mutex_t;
# 401 "/usr/include/bits/alltypes.h" 3 4
typedef struct { union { int __i[12]; volatile int __vi[12]; void *__p[12*sizeof(int)/sizeof(void*)]; } __u; } pthread_cond_t;
# 411 "/usr/include/bits/alltypes.h" 3 4
typedef struct { union { int __i[sizeof(long)==8?14:8]; volatile int __vi[sizeof(long)==8?14:8]; void *__p[sizeof(long)==8?7:8]; } __u; } pthread_rwlock_t;




typedef struct { union { int __i[sizeof(long)==8?8:5]; volatile int __vi[sizeof(long)==8?8:5]; void *__p[sizeof(long)==8?4:5]; } __u; } pthread_barrier_t;
# 58 "/usr/include/sys/types.h" 2 3 4


typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned u_int32_t;
typedef char *caddr_t;
typedef unsigned char u_char;
typedef unsigned short u_short, ushort;
typedef unsigned u_int, uint;
typedef unsigned long u_long, ulong;
typedef long long quad_t;
typedef unsigned long long u_quad_t;
# 1 "/usr/include/endian.h" 1 3 4
# 10 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 134 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned short uint16_t;




typedef unsigned int uint32_t;




typedef unsigned long uint64_t;
# 11 "/usr/include/endian.h" 2 3 4
# 19 "/usr/include/endian.h" 3 4
static inline uint16_t __bswap16(uint16_t __x)
{
 return __x<<8 | __x>>8;
}

static inline uint32_t __bswap32(uint32_t __x)
{
 return __x>>24 | __x>>8&0xff00 | __x<<8&0xff0000 | __x<<24;
}

static inline uint64_t __bswap64(uint64_t __x)
{
 return __bswap32(__x)+0ULL<<32 | __bswap32(__x>>32);
}
# 71 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/fortify/sys/select.h" 1 3 4
# 21 "/usr/include/fortify/sys/select.h" 3 4
__extension__

# 1 "/usr/include/sys/select.h" 1 3 4
# 16 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 232 "/usr/include/bits/alltypes.h" 3 4
struct timeval { time_t tv_sec; suseconds_t tv_usec; };




struct timespec { time_t tv_sec; int :8*(sizeof(time_t)-sizeof(long))*(1234==4321); long tv_nsec; int :8*(sizeof(time_t)-sizeof(long))*(1234!=4321); };
# 357 "/usr/include/bits/alltypes.h" 3 4
typedef struct __sigset_t { unsigned long __bits[128/sizeof(long)]; } sigset_t;
# 17 "/usr/include/sys/select.h" 2 3 4



typedef unsigned long fd_mask;

typedef struct {
 unsigned long fds_bits[1024 / 8 / sizeof(long)];
} fd_set;






int select (int, fd_set *
# 31 "/usr/include/sys/select.h"
                        __restrict__
# 31 "/usr/include/sys/select.h" 3 4
                                  , fd_set *
# 31 "/usr/include/sys/select.h"
                                            __restrict__
# 31 "/usr/include/sys/select.h" 3 4
                                                      , fd_set *
# 31 "/usr/include/sys/select.h"
                                                                __restrict__
# 31 "/usr/include/sys/select.h" 3 4
                                                                          , struct timeval *
# 31 "/usr/include/sys/select.h"
                                                                                            __restrict__
# 31 "/usr/include/sys/select.h" 3 4
                                                                                                      );
int pselect (int, fd_set *
# 32 "/usr/include/sys/select.h"
                         __restrict__
# 32 "/usr/include/sys/select.h" 3 4
                                   , fd_set *
# 32 "/usr/include/sys/select.h"
                                             __restrict__
# 32 "/usr/include/sys/select.h" 3 4
                                                       , fd_set *
# 32 "/usr/include/sys/select.h"
                                                                 __restrict__
# 32 "/usr/include/sys/select.h" 3 4
                                                                           , const struct timespec *
# 32 "/usr/include/sys/select.h"
                                                                                                    __restrict__
# 32 "/usr/include/sys/select.h" 3 4
                                                                                                              , const sigset_t *
# 32 "/usr/include/sys/select.h"
                                                                                                                                __restrict__
# 32 "/usr/include/sys/select.h" 3 4
                                                                                                                                          );
# 24 "/usr/include/fortify/sys/select.h" 2 3 4
# 72 "/usr/include/sys/types.h" 2 3 4
# 47 "../lib/sys/types.h" 2 3
# 68 "../lib/sys/types.h" 3
typedef long long off64_t;
# 167 "../lib/unistd.h" 2 3
# 710 "../lib/unistd.h" 3
# 1 "../lib/getopt-cdefs.h" 1 3
# 711 "../lib/unistd.h" 2 3
# 1 "../lib/getopt-pfx-core.h" 1 3
# 64 "../lib/getopt-pfx-core.h" 3
# 1 "../lib/getopt-core.h" 1 3
# 28 "../lib/getopt-core.h" 3








extern char *
# 36 "../lib/getopt-core.h"
            rpl_optarg
# 36 "../lib/getopt-core.h" 3
                  ;
# 50 "../lib/getopt-core.h" 3
extern int 
# 50 "../lib/getopt-core.h"
          rpl_optind
# 50 "../lib/getopt-core.h" 3
                ;




extern int 
# 55 "../lib/getopt-core.h"
          rpl_opterr
# 55 "../lib/getopt-core.h" 3
                ;



extern int 
# 59 "../lib/getopt-core.h"
          rpl_optopt
# 59 "../lib/getopt-core.h" 3
                ;
# 91 "../lib/getopt-core.h" 3
extern int 
# 91 "../lib/getopt-core.h"
          rpl_getopt 
# 91 "../lib/getopt-core.h" 3
                 (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nonnull__ (2, 3)));


# 65 "../lib/getopt-pfx-core.h" 2 3
# 712 "../lib/unistd.h" 2 3



# 857 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 891 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 969 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1042 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1087 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1225 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1261 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1297 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1334 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1374 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy
                                                                               ;

extern int _gl_cxxalias_dummy;
# 1411 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1464 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy
                                                                               ;


extern int _gl_cxxalias_dummy;
# 1704 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 2082 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 2215 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 2358 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 2525 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 2639 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 2734 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;


extern int _gl_cxxalias_dummy;
# 2904 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 3004 "../lib/unistd.h" 3
extern int _gl_cxxalias_dummy
                                                          ;

extern int _gl_cxxalias_dummy;



# 38 "slist.h" 2


# 93 "slist.h"

# 93 "slist.h"
typedef struct slist slist_t;
typedef struct slist_node slist_node_t;
# 107 "slist.h"
typedef int (*slist_cmp_fn_t)( void const *i_data, void const *j_data );
# 116 "slist.h"
typedef void* (*slist_dup_fn_t)( void const *data );
# 128 "slist.h"
typedef 
# 128 "slist.h" 3 4
       _Bool 
# 128 "slist.h"
            (*slist_equal_fn_t)( void const *i_data, void const *j_data );







typedef void (*slist_free_fn_t)( void *data );
# 146 "slist.h"
typedef 
# 146 "slist.h" 3 4
       _Bool 
# 146 "slist.h"
            (*slist_pred_fn_t)( slist_node_t *node, void *data );






struct slist {
  slist_node_t *head;
  slist_node_t *tail;
  size_t len;
};




struct slist_node {
  slist_node_t *next;
  void *data;
};
# 188 "slist.h"
__attribute__ ((__warn_unused_result__))
void* slist_at_nocheck( slist_t const *list, size_t offset );
# 202 "slist.h"
void slist_cleanup( slist_t *list, slist_free_fn_t free_fn );
# 216 "slist.h"
__attribute__ ((__warn_unused_result__))
int slist_cmp( slist_t const *i_list, slist_t const *j_list,
               slist_cmp_fn_t cmp_fn );
# 234 "slist.h"
__attribute__ ((__warn_unused_result__))
slist_t slist_dup( slist_t const *src_list, ssize_t n, slist_dup_fn_t dup_fn );
# 248 "slist.h"
__attribute__ ((__warn_unused_result__))

# 249 "slist.h" 3 4
_Bool 
# 249 "slist.h"
    slist_equal( slist_t const *i_list, slist_t const *j_list,
                  slist_equal_fn_t equal_fn );
# 267 "slist.h"


# 268 "slist.h" 3 4
_Bool 
# 268 "slist.h"
    slist_free_if( slist_t *list, slist_pred_fn_t pred_fn, void *data );
# 281 "slist.h"
__attribute__ ((__warn_unused_result__))
void* slist_pop_back( slist_t *list );
# 295 "slist.h"
__attribute__ ((__warn_unused_result__))
void* slist_pop_front( slist_t *list );
# 309 "slist.h"
void slist_push_back( slist_t *list, void *data );
# 322 "slist.h"
void slist_push_front( slist_t *list, void *data );
# 335 "slist.h"
void slist_push_list_back( slist_t *dst_list, slist_t *src_list );
# 348 "slist.h"
void slist_push_list_front( slist_t *dst_list, slist_t *src_list );
# 367 "slist.h"
__attribute__ ((__warn_unused_result__)) inline
void* slist_at( slist_t const *list, size_t offset ) {
  return offset < list->len ? slist_at_nocheck( list, offset ) : 
# 369 "slist.h" 3 4
                                                                ((void*)0)
# 369 "slist.h"
                                                                    ;
}
# 387 "slist.h"
__attribute__ ((__warn_unused_result__)) inline
void* slist_atr( slist_t const *list, size_t roffset ) {
  return roffset < list->len ?
    slist_at_nocheck( list, list->len - (roffset + 1) ) : 
# 390 "slist.h" 3 4
                                                         ((void*)0)
# 390 "slist.h"
                                                             ;
}
# 407 "slist.h"
__attribute__ ((__warn_unused_result__)) inline
void* slist_back( slist_t const *list ) {
  return list->tail != 
# 409 "slist.h" 3 4
                      ((void*)0) 
# 409 "slist.h"
                           ? list->tail->data : 
# 409 "slist.h" 3 4
                                                ((void*)0)
# 409 "slist.h"
                                                    ;
}
# 422 "slist.h"
__attribute__ ((__warn_unused_result__)) inline

# 423 "slist.h" 3 4
_Bool 
# 423 "slist.h"
    slist_empty( slist_t const *list ) {
  return list->head == 
# 424 "slist.h" 3 4
                      ((void*)0)
# 424 "slist.h"
                          ;
}
# 441 "slist.h"
__attribute__ ((__warn_unused_result__)) inline
void* slist_front( slist_t const *list ) {
  return list->head != 
# 443 "slist.h" 3 4
                      ((void*)0) 
# 443 "slist.h"
                           ? list->head->data : 
# 443 "slist.h" 3 4
                                                ((void*)0)
# 443 "slist.h"
                                                    ;
}
# 456 "slist.h"
inline
void slist_init( slist_t *list ) {
  *list = (slist_t){ 0 };
}
# 471 "slist.h"
__attribute__ ((__warn_unused_result__)) inline
size_t slist_len( slist_t const *list ) {
  return list->len;
}
# 498 "slist.h"
__attribute__ ((__warn_unused_result__))
slist_t slist_move( slist_t *list );






# 40 "types.h" 2
# 1 "util.h" 1
# 35 "util.h"
# 1 "../lib/assert.h" 1
# 22 "../lib/assert.h"
       
# 23 "../lib/assert.h" 3



# 1 "/usr/include/assert.h" 1 3 4
# 19 "/usr/include/assert.h" 3 4

# 19 "/usr/include/assert.h" 3 4
_Noreturn void __assert_fail (const char *, const char *, int, const char *);
# 27 "../lib/assert.h" 2 3
# 36 "util.h" 2
# 1 "../lib/ctype.h" 1
# 29 "../lib/ctype.h"
       
# 30 "../lib/ctype.h" 3





# 1 "/usr/include/ctype.h" 1 3 4
# 10 "/usr/include/ctype.h" 3 4
int isalnum(int);
int isalpha(int);
int isblank(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);


static inline int __isspace(int _c)
{
 return _c == ' ' || (unsigned)_c-'\t' < 5;
}
# 46 "/usr/include/ctype.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 351 "/usr/include/bits/alltypes.h" 3 4
typedef struct __locale_struct * locale_t;
# 47 "/usr/include/ctype.h" 2 3 4

int isalnum_l(int, locale_t);
int isalpha_l(int, locale_t);
int isblank_l(int, locale_t);
int iscntrl_l(int, locale_t);
int isdigit_l(int, locale_t);
int isgraph_l(int, locale_t);
int islower_l(int, locale_t);
int isprint_l(int, locale_t);
int ispunct_l(int, locale_t);
int isspace_l(int, locale_t);
int isupper_l(int, locale_t);
int isxdigit_l(int, locale_t);
int tolower_l(int, locale_t);
int toupper_l(int, locale_t);

int isascii(int);
int toascii(int);
# 36 "../lib/ctype.h" 2 3
# 37 "util.h" 2
# 1 "/usr/include/errno.h" 1 3 4
# 10 "/usr/include/errno.h" 3 4
# 1 "/usr/include/bits/errno.h" 1 3 4
# 11 "/usr/include/errno.h" 2 3 4


__attribute__((const))

int *__errno_location(void);



extern char *program_invocation_short_name, *program_invocation_name;
# 38 "util.h" 2

# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 40 "util.h" 2
# 1 "../lib/stdint.h" 1
# 27 "../lib/stdint.h"
       
# 28 "../lib/stdint.h" 3
# 77 "../lib/stdint.h" 3
# 1 "/usr/include/stdint.h" 1 3 4
# 20 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 63 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned long uintptr_t;
# 124 "/usr/include/bits/alltypes.h" 3 4
typedef signed long intmax_t;




typedef unsigned char uint8_t;
# 154 "/usr/include/bits/alltypes.h" 3 4
typedef unsigned long uintmax_t;
# 21 "/usr/include/stdint.h" 2 3 4

typedef int8_t int_fast8_t;
typedef int64_t int_fast64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

typedef uint8_t uint_fast8_t;
typedef uint64_t uint_fast64_t;

typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
# 95 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/stdint.h" 1 3 4
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 96 "/usr/include/stdint.h" 2 3 4
# 78 "../lib/stdint.h" 2 3







# 1 "../lib/limits.h" 1 3
# 20 "../lib/limits.h" 3
       
# 21 "../lib/limits.h" 3
# 41 "../lib/limits.h" 3
# 1 "/usr/include/limits.h" 1 3 4





# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 7 "/usr/include/limits.h" 2 3 4
# 40 "/usr/include/limits.h" 3 4
# 1 "/usr/include/bits/limits.h" 1 3 4
# 41 "/usr/include/limits.h" 2 3 4
# 42 "../lib/limits.h" 2 3
# 86 "../lib/stdint.h" 2 3
# 41 "util.h" 2
# 1 "../lib/stdio.h" 1
# 20 "../lib/stdio.h"
       
# 21 "../lib/stdio.h" 3
# 55 "../lib/stdio.h" 3
# 1 "/usr/include/fortify/stdio.h" 1 3 4
# 21 "/usr/include/fortify/stdio.h" 3 4
__extension__

# 1 "/usr/include/stdio.h" 1 3 4
# 26 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 328 "/usr/include/bits/alltypes.h" 3 4
typedef struct _IO_FILE FILE;





typedef __builtin_va_list va_list;




typedef __builtin_va_list __isoc_va_list;
# 27 "/usr/include/stdio.h" 2 3 4
# 56 "/usr/include/stdio.h" 3 4
typedef union _G_fpos64_t {
 char __opaque[16];
 long long __lldata;
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *
# 70 "/usr/include/stdio.h"
                       __restrict__
# 70 "/usr/include/stdio.h" 3 4
                                 , const char *
# 70 "/usr/include/stdio.h"
                                               __restrict__
# 70 "/usr/include/stdio.h" 3 4
                                                         );
FILE *freopen(const char *
# 71 "/usr/include/stdio.h"
                         __restrict__
# 71 "/usr/include/stdio.h" 3 4
                                   , const char *
# 71 "/usr/include/stdio.h"
                                                 __restrict__
# 71 "/usr/include/stdio.h" 3 4
                                                           , FILE *
# 71 "/usr/include/stdio.h"
                                                                   __restrict__
# 71 "/usr/include/stdio.h" 3 4
                                                                             );
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *
# 86 "/usr/include/stdio.h"
                 __restrict__
# 86 "/usr/include/stdio.h" 3 4
                           , fpos_t *
# 86 "/usr/include/stdio.h"
                                     __restrict__
# 86 "/usr/include/stdio.h" 3 4
                                               );
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *
# 89 "/usr/include/stdio.h"
                  __restrict__
# 89 "/usr/include/stdio.h" 3 4
                            , size_t, size_t, FILE *
# 89 "/usr/include/stdio.h"
                                                    __restrict__
# 89 "/usr/include/stdio.h" 3 4
                                                              );
size_t fwrite(const void *
# 90 "/usr/include/stdio.h"
                         __restrict__
# 90 "/usr/include/stdio.h" 3 4
                                   , size_t, size_t, FILE *
# 90 "/usr/include/stdio.h"
                                                           __restrict__
# 90 "/usr/include/stdio.h" 3 4
                                                                     );

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);

char *fgets(char *
# 101 "/usr/include/stdio.h"
                 __restrict__
# 101 "/usr/include/stdio.h" 3 4
                           , int, FILE *
# 101 "/usr/include/stdio.h"
                                        __restrict__
# 101 "/usr/include/stdio.h" 3 4
                                                  );




int fputs(const char *
# 106 "/usr/include/stdio.h"
                     __restrict__
# 106 "/usr/include/stdio.h" 3 4
                               , FILE *
# 106 "/usr/include/stdio.h"
                                       __restrict__
# 106 "/usr/include/stdio.h" 3 4
                                                 );
int puts(const char *);

int printf(const char *
# 109 "/usr/include/stdio.h"
                      __restrict__
# 109 "/usr/include/stdio.h" 3 4
                                , ...);
int fprintf(FILE *
# 110 "/usr/include/stdio.h"
                 __restrict__
# 110 "/usr/include/stdio.h" 3 4
                           , const char *
# 110 "/usr/include/stdio.h"
                                         __restrict__
# 110 "/usr/include/stdio.h" 3 4
                                                   , ...);
int sprintf(char *
# 111 "/usr/include/stdio.h"
                 __restrict__
# 111 "/usr/include/stdio.h" 3 4
                           , const char *
# 111 "/usr/include/stdio.h"
                                         __restrict__
# 111 "/usr/include/stdio.h" 3 4
                                                   , ...);
int snprintf(char *
# 112 "/usr/include/stdio.h"
                  __restrict__
# 112 "/usr/include/stdio.h" 3 4
                            , size_t, const char *
# 112 "/usr/include/stdio.h"
                                                  __restrict__
# 112 "/usr/include/stdio.h" 3 4
                                                            , ...);

int vprintf(const char *
# 114 "/usr/include/stdio.h"
                       __restrict__
# 114 "/usr/include/stdio.h" 3 4
                                 , __isoc_va_list);
int vfprintf(FILE *
# 115 "/usr/include/stdio.h"
                  __restrict__
# 115 "/usr/include/stdio.h" 3 4
                            , const char *
# 115 "/usr/include/stdio.h"
                                          __restrict__
# 115 "/usr/include/stdio.h" 3 4
                                                    , __isoc_va_list);
int vsprintf(char *
# 116 "/usr/include/stdio.h"
                  __restrict__
# 116 "/usr/include/stdio.h" 3 4
                            , const char *
# 116 "/usr/include/stdio.h"
                                          __restrict__
# 116 "/usr/include/stdio.h" 3 4
                                                    , __isoc_va_list);
int vsnprintf(char *
# 117 "/usr/include/stdio.h"
                   __restrict__
# 117 "/usr/include/stdio.h" 3 4
                             , size_t, const char *
# 117 "/usr/include/stdio.h"
                                                   __restrict__
# 117 "/usr/include/stdio.h" 3 4
                                                             , __isoc_va_list);

int scanf(const char *
# 119 "/usr/include/stdio.h"
                     __restrict__
# 119 "/usr/include/stdio.h" 3 4
                               , ...);
int fscanf(FILE *
# 120 "/usr/include/stdio.h"
                __restrict__
# 120 "/usr/include/stdio.h" 3 4
                          , const char *
# 120 "/usr/include/stdio.h"
                                        __restrict__
# 120 "/usr/include/stdio.h" 3 4
                                                  , ...);
int sscanf(const char *
# 121 "/usr/include/stdio.h"
                      __restrict__
# 121 "/usr/include/stdio.h" 3 4
                                , const char *
# 121 "/usr/include/stdio.h"
                                              __restrict__
# 121 "/usr/include/stdio.h" 3 4
                                                        , ...);
int vscanf(const char *
# 122 "/usr/include/stdio.h"
                      __restrict__
# 122 "/usr/include/stdio.h" 3 4
                                , __isoc_va_list);
int vfscanf(FILE *
# 123 "/usr/include/stdio.h"
                 __restrict__
# 123 "/usr/include/stdio.h" 3 4
                           , const char *
# 123 "/usr/include/stdio.h"
                                         __restrict__
# 123 "/usr/include/stdio.h" 3 4
                                                   , __isoc_va_list);
int vsscanf(const char *
# 124 "/usr/include/stdio.h"
                       __restrict__
# 124 "/usr/include/stdio.h" 3 4
                                 , const char *
# 124 "/usr/include/stdio.h"
                                               __restrict__
# 124 "/usr/include/stdio.h" 3 4
                                                         , __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *
# 128 "/usr/include/stdio.h"
                 __restrict__
# 128 "/usr/include/stdio.h" 3 4
                           , char *
# 128 "/usr/include/stdio.h"
                                   __restrict__
# 128 "/usr/include/stdio.h" 3 4
                                             , int, size_t);
void setbuf(FILE *
# 129 "/usr/include/stdio.h"
                 __restrict__
# 129 "/usr/include/stdio.h" 3 4
                           , char *
# 129 "/usr/include/stdio.h"
                                   __restrict__
# 129 "/usr/include/stdio.h" 3 4
                                             );

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *
# 137 "/usr/include/stdio.h"
                    __restrict__
# 137 "/usr/include/stdio.h" 3 4
                              , size_t, const char *
# 137 "/usr/include/stdio.h"
                                                    __restrict__
# 137 "/usr/include/stdio.h" 3 4
                                                              );
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *
# 145 "/usr/include/stdio.h"
                            __restrict__
# 145 "/usr/include/stdio.h" 3 4
                                      , ...);
int vdprintf(int, const char *
# 146 "/usr/include/stdio.h"
                             __restrict__
# 146 "/usr/include/stdio.h" 3 4
                                       , __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **
# 154 "/usr/include/stdio.h"
                       __restrict__
# 154 "/usr/include/stdio.h" 3 4
                                 , size_t *
# 154 "/usr/include/stdio.h"
                                           __restrict__
# 154 "/usr/include/stdio.h" 3 4
                                                     , int, FILE *
# 154 "/usr/include/stdio.h"
                                                                  __restrict__
# 154 "/usr/include/stdio.h" 3 4
                                                                            );
ssize_t getline(char **
# 155 "/usr/include/stdio.h"
                      __restrict__
# 155 "/usr/include/stdio.h" 3 4
                                , size_t *
# 155 "/usr/include/stdio.h"
                                          __restrict__
# 155 "/usr/include/stdio.h" 3 4
                                                    , FILE *
# 155 "/usr/include/stdio.h"
                                                            __restrict__
# 155 "/usr/include/stdio.h" 3 4
                                                                      );
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);




char *cuserid(char *);
void setlinebuf(FILE *);
void setbuffer(FILE *, char *, size_t);
int fgetc_unlocked(FILE *);
int fputc_unlocked(int, FILE *);
int fflush_unlocked(FILE *);
size_t fread_unlocked(void *, size_t, size_t, FILE *);
size_t fwrite_unlocked(const void *, size_t, size_t, FILE *);
void clearerr_unlocked(FILE *);
int feof_unlocked(FILE *);
int ferror_unlocked(FILE *);
int fileno_unlocked(FILE *);
int getw(FILE *);
int putw(int, FILE *);
char *fgetln(FILE *, size_t *);
int asprintf(char **, const char *, ...);
int vasprintf(char **, const char *, __isoc_va_list);



char *fgets_unlocked(char *, int, FILE *);
int fputs_unlocked(const char *, FILE *);

typedef ssize_t (cookie_read_function_t)(void *, char *, size_t);
typedef ssize_t (cookie_write_function_t)(void *, const char *, size_t);
typedef int (cookie_seek_function_t)(void *, off_t *, int);
typedef int (cookie_close_function_t)(void *);

typedef struct _IO_cookie_io_functions_t {
 cookie_read_function_t *read;
 cookie_write_function_t *write;
 cookie_seek_function_t *seek;
 cookie_close_function_t *close;
} cookie_io_functions_t;

FILE *fopencookie(void *, const char *, cookie_io_functions_t);
# 24 "/usr/include/fortify/stdio.h" 2 3 4
# 56 "../lib/stdio.h" 2 3
# 75 "../lib/stdio.h" 3
# 1 "/usr/include/stdarg.h" 1 3 4
# 10 "/usr/include/stdarg.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 11 "/usr/include/stdarg.h" 2 3 4
# 76 "../lib/stdio.h" 2 3

# 1 "../lib/stddef.h" 1 3
# 27 "../lib/stddef.h" 3
       
# 28 "../lib/stddef.h" 3
# 78 "../lib/stdio.h" 2 3





# 1 "../lib/sys/types.h" 1 3
# 20 "../lib/sys/types.h" 3
       
# 21 "../lib/sys/types.h" 3
# 84 "../lib/stdio.h" 2 3
# 981 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1022 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1041 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy
                                                                   ;
# 1060 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1147 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy
                                                                        ;
# 1203 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1222 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy
                                                                       ;
# 1244 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy

                                          ;
# 1295 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy
                                                                            ;
# 1477 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy

                                          ;
# 1518 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1534 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1570 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy


                                          ;
# 1612 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy

                                          ;
# 1651 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1864 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1889 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1905 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1921 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 1944 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 2053 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;
# 2188 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 2413 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy

                                                                   ;
# 2495 "../lib/stdio.h" 3
extern int _gl_cxxalias_dummy
                                                                   ;
# 42 "util.h" 2
# 1 "../lib/stdlib.h" 1
# 20 "../lib/stdlib.h"
       
# 21 "../lib/stdlib.h" 3
# 62 "../lib/stdlib.h" 3
# 1 "../lib/stddef.h" 1 3
# 27 "../lib/stddef.h" 3
       
# 28 "../lib/stddef.h" 3
# 63 "../lib/stdlib.h" 2 3
# 1081 "../lib/stdlib.h" 3
extern int _gl_cxxalias_dummy
                                                                        ;



extern int _gl_cxxalias_dummy;
# 1104 "../lib/stdlib.h" 3
extern int _gl_cxxalias_dummy
                                                                        ;



extern int _gl_cxxalias_dummy;
# 1126 "../lib/stdlib.h" 3
extern int _gl_cxxalias_dummy;



extern int _gl_cxxalias_dummy;
# 1379 "../lib/stdlib.h" 3
extern int _gl_cxxalias_dummy
                                                                            ;
# 1566 "../lib/stdlib.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1720 "../lib/stdlib.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 43 "util.h" 2
# 1 "../lib/string.h" 1
# 20 "../lib/string.h"
       
# 21 "../lib/string.h" 3
# 41 "../lib/string.h" 3
# 1 "/usr/include/fortify/string.h" 1 3 4
# 21 "/usr/include/fortify/string.h" 3 4
__extension__

# 1 "/usr/include/string.h" 1 3 4
# 25 "/usr/include/string.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 26 "/usr/include/string.h" 2 3 4

void *memcpy (void *
# 27 "/usr/include/string.h"
                   __restrict__
# 27 "/usr/include/string.h" 3 4
                             , const void *
# 27 "/usr/include/string.h"
                                           __restrict__
# 27 "/usr/include/string.h" 3 4
                                                     , size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *
# 33 "/usr/include/string.h"
                   __restrict__
# 33 "/usr/include/string.h" 3 4
                             , const char *
# 33 "/usr/include/string.h"
                                           __restrict__
# 33 "/usr/include/string.h" 3 4
                                                     );
char *strncpy (char *
# 34 "/usr/include/string.h"
                    __restrict__
# 34 "/usr/include/string.h" 3 4
                              , const char *
# 34 "/usr/include/string.h"
                                            __restrict__
# 34 "/usr/include/string.h" 3 4
                                                      , size_t);

char *strcat (char *
# 36 "/usr/include/string.h"
                   __restrict__
# 36 "/usr/include/string.h" 3 4
                             , const char *
# 36 "/usr/include/string.h"
                                           __restrict__
# 36 "/usr/include/string.h" 3 4
                                                     );
char *strncat (char *
# 37 "/usr/include/string.h"
                    __restrict__
# 37 "/usr/include/string.h" 3 4
                              , const char *
# 37 "/usr/include/string.h"
                                            __restrict__
# 37 "/usr/include/string.h" 3 4
                                                      , size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *
# 43 "/usr/include/string.h"
                     __restrict__
# 43 "/usr/include/string.h" 3 4
                               , const char *
# 43 "/usr/include/string.h"
                                             __restrict__
# 43 "/usr/include/string.h" 3 4
                                                       , size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *
# 52 "/usr/include/string.h"
                   __restrict__
# 52 "/usr/include/string.h" 3 4
                             , const char *
# 52 "/usr/include/string.h"
                                           __restrict__
# 52 "/usr/include/string.h" 3 4
                                                     );

size_t strlen (const char *);

char *strerror (int);


# 1 "/usr/include/fortify/strings.h" 1 3 4
# 20 "/usr/include/fortify/strings.h" 3 4
# 1 "/usr/include/strings.h" 1 3 4
# 12 "/usr/include/strings.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 13 "/usr/include/strings.h" 2 3 4




int bcmp (const void *, const void *, size_t);
void bcopy (const void *, void *, size_t);
void bzero (void *, size_t);
char *index (const char *, int);
char *rindex (const char *, int);



int ffs (int);
int ffsl (long);
int ffsll (long long);


int strcasecmp (const char *, const char *);
int strncasecmp (const char *, const char *, size_t);

int strcasecmp_l (const char *, const char *, locale_t);
int strncasecmp_l (const char *, const char *, size_t, locale_t);
# 21 "/usr/include/fortify/strings.h" 2 3 4
# 60 "/usr/include/string.h" 2 3 4





char *strtok_r (char *
# 65 "/usr/include/string.h"
                     __restrict__
# 65 "/usr/include/string.h" 3 4
                               , const char *
# 65 "/usr/include/string.h"
                                             __restrict__
# 65 "/usr/include/string.h" 3 4
                                                       , char **
# 65 "/usr/include/string.h"
                                                                __restrict__
# 65 "/usr/include/string.h" 3 4
                                                                          );
int strerror_r (int, char *, size_t);
char *stpcpy(char *
# 67 "/usr/include/string.h"
                  __restrict__
# 67 "/usr/include/string.h" 3 4
                            , const char *
# 67 "/usr/include/string.h"
                                          __restrict__
# 67 "/usr/include/string.h" 3 4
                                                    );
char *stpncpy(char *
# 68 "/usr/include/string.h"
                   __restrict__
# 68 "/usr/include/string.h" 3 4
                             , const char *
# 68 "/usr/include/string.h"
                                           __restrict__
# 68 "/usr/include/string.h" 3 4
                                                     , size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *
# 75 "/usr/include/string.h"
                       __restrict__
# 75 "/usr/include/string.h" 3 4
                                 , const char *
# 75 "/usr/include/string.h"
                                               __restrict__
# 75 "/usr/include/string.h" 3 4
                                                         , size_t, locale_t);
void *memmem(const void *, size_t, const void *, size_t);




void *memccpy (void *
# 81 "/usr/include/string.h"
                    __restrict__
# 81 "/usr/include/string.h" 3 4
                              , const void *
# 81 "/usr/include/string.h"
                                            __restrict__
# 81 "/usr/include/string.h" 3 4
                                                      , int, size_t);



char *strsep(char **, const char *);
size_t strlcat (char *, const char *, size_t);
size_t strlcpy (char *, const char *, size_t);
void explicit_bzero (void *, size_t);




int strverscmp (const char *, const char *);
char *strchrnul(const char *, int);
char *strcasestr(const char *, const char *);
void *memrchr(const void *, int, size_t);
void *mempcpy(void *, const void *, size_t);
# 24 "/usr/include/fortify/string.h" 2 3 4
# 42 "../lib/string.h" 2 3
# 56 "../lib/string.h" 3
# 1 "../lib/stddef.h" 1 3
# 27 "../lib/stddef.h" 3
       
# 28 "../lib/stddef.h" 3
# 57 "../lib/string.h" 2 3
# 725 "../lib/string.h" 3
extern void free (void *);
# 797 "../lib/string.h" 3
extern int _gl_cxxalias_dummy
                                                                 ;

extern int _gl_cxxalias_dummy;
# 819 "../lib/string.h" 3
extern int _gl_cxxalias_dummy

                                                                             ;
# 900 "../lib/string.h" 3
extern int _gl_cxxalias_dummy

                               ;
# 1185 "../lib/string.h" 3
 __attribute__ ((__nonnull__ (1))) 
# 1185 "../lib/string.h"
__attribute__ ((__malloc__)) __attribute__ ((__malloc__ (free, 1))) 
# 1185 "../lib/string.h" 3
char * strdup (char const *__s)


                                                                  ;
# 1211 "../lib/string.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1265 "../lib/string.h" 3
 __attribute__ ((__nonnull__ (1))) 
# 1265 "../lib/string.h"
__attribute__ ((__malloc__)) __attribute__ ((__malloc__ (free, 1))) 
# 1265 "../lib/string.h" 3
char * strndup (char const *__s, size_t __n)


                                                                  ;


extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1318 "../lib/string.h" 3
extern int _gl_cxxalias_dummy;

extern int _gl_cxxalias_dummy;
# 1432 "../lib/string.h" 3
extern int _gl_cxxalias_dummy
                                                                            ;
extern int _gl_cxxalias_dummy;
# 44 "util.h" 2
# 1 "/usr/include/sysexits.h" 1 3 4
# 45 "util.h" 2
# 1 "/usr/include/time.h" 1 3 4
# 33 "/usr/include/time.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 34 "/usr/include/time.h" 2 3 4






struct tm {
 int tm_sec;
 int tm_min;
 int tm_hour;
 int tm_mday;
 int tm_mon;
 int tm_year;
 int tm_wday;
 int tm_yday;
 int tm_isdst;
 long tm_gmtoff;
 const char *tm_zone;
};

clock_t clock (void);
time_t time (time_t *);
double difftime (time_t, time_t);
time_t mktime (struct tm *);
size_t strftime (char *
# 58 "/usr/include/time.h"
                      __restrict__
# 58 "/usr/include/time.h" 3 4
                                , size_t, const char *
# 58 "/usr/include/time.h"
                                                      __restrict__
# 58 "/usr/include/time.h" 3 4
                                                                , const struct tm *
# 58 "/usr/include/time.h"
                                                                                   __restrict__
# 58 "/usr/include/time.h" 3 4
                                                                                             );
struct tm *gmtime (const time_t *);
struct tm *localtime (const time_t *);
char *asctime (const struct tm *);
char *ctime (const time_t *);
int timespec_get(struct timespec *, int);
# 73 "/usr/include/time.h" 3 4
size_t strftime_l (char * 
# 73 "/usr/include/time.h"
                          __restrict__
# 73 "/usr/include/time.h" 3 4
                                    , size_t, const char * 
# 73 "/usr/include/time.h"
                                                            __restrict__
# 73 "/usr/include/time.h" 3 4
                                                                      , const struct tm * 
# 73 "/usr/include/time.h"
                                                                                           __restrict__
# 73 "/usr/include/time.h" 3 4
                                                                                                     , locale_t);

struct tm *gmtime_r (const time_t *
# 75 "/usr/include/time.h"
                                  __restrict__
# 75 "/usr/include/time.h" 3 4
                                            , struct tm *
# 75 "/usr/include/time.h"
                                                         __restrict__
# 75 "/usr/include/time.h" 3 4
                                                                   );
struct tm *localtime_r (const time_t *
# 76 "/usr/include/time.h"
                                     __restrict__
# 76 "/usr/include/time.h" 3 4
                                               , struct tm *
# 76 "/usr/include/time.h"
                                                            __restrict__
# 76 "/usr/include/time.h" 3 4
                                                                      );
char *asctime_r (const struct tm *
# 77 "/usr/include/time.h"
                                 __restrict__
# 77 "/usr/include/time.h" 3 4
                                           , char *
# 77 "/usr/include/time.h"
                                                   __restrict__
# 77 "/usr/include/time.h" 3 4
                                                             );
char *ctime_r (const time_t *, char *);

void tzset (void);

struct itimerspec {
 struct timespec it_interval;
 struct timespec it_value;
};
# 102 "/usr/include/time.h" 3 4
int nanosleep (const struct timespec *, struct timespec *);
int clock_getres (clockid_t, struct timespec *);
int clock_gettime (clockid_t, struct timespec *);
int clock_settime (clockid_t, const struct timespec *);
int clock_nanosleep (clockid_t, int, const struct timespec *, struct timespec *);
int clock_getcpuclockid (pid_t, clockid_t *);

struct sigevent;
int timer_create (clockid_t, struct sigevent *
# 110 "/usr/include/time.h"
                                             __restrict__
# 110 "/usr/include/time.h" 3 4
                                                       , timer_t *
# 110 "/usr/include/time.h"
                                                                  __restrict__
# 110 "/usr/include/time.h" 3 4
                                                                            );
int timer_delete (timer_t);
int timer_settime (timer_t, int, const struct itimerspec *
# 112 "/usr/include/time.h"
                                                         __restrict__
# 112 "/usr/include/time.h" 3 4
                                                                   , struct itimerspec *
# 112 "/usr/include/time.h"
                                                                                        __restrict__
# 112 "/usr/include/time.h" 3 4
                                                                                                  );
int timer_gettime (timer_t, struct itimerspec *);
int timer_getoverrun (timer_t);

extern char *tzname[2];





char *strptime (const char *
# 122 "/usr/include/time.h"
                           __restrict__
# 122 "/usr/include/time.h" 3 4
                                     , const char *
# 122 "/usr/include/time.h"
                                                   __restrict__
# 122 "/usr/include/time.h" 3 4
                                                             , struct tm *
# 122 "/usr/include/time.h"
                                                                          __restrict__
# 122 "/usr/include/time.h" 3 4
                                                                                    );
extern int daylight;
extern long timezone;
extern int getdate_err;
struct tm *getdate (const char *);




int stime(const time_t *);
time_t timegm(struct tm *);
# 46 "util.h" 2


# 1167 "util.h"

# 1167 "util.h"
__attribute__ ((__warn_unused_result__))
char const* base_name( char const *path_name );
# 1181 "util.h"
__attribute__ ((__warn_unused_result__))
char* check_prefix_strdup( char const *prefix, size_t prefix_len,
                           char const *s );
# 1196 "util.h"
__attribute__ ((__warn_unused_result__))
void* check_realloc( void *p, size_t size );
# 1207 "util.h"
__attribute__((format(printf, (3), (3)+1)))
void check_snprintf( char *buf, size_t buf_size, char const *format, ... );
# 1220 "util.h"
__attribute__ ((__warn_unused_result__))
char* check_strdup( char const *s );
# 1234 "util.h"
__attribute__ ((__warn_unused_result__))
char* check_strdup_suffix( char const *s, char const *suffix,
                           size_t suffix_len );
# 1249 "util.h"
__attribute__ ((__warn_unused_result__))
char* check_strdup_tolower( char const *s );
# 1263 "util.h"
__attribute__ ((__warn_unused_result__))
char* check_strndup( char const *s, size_t n );
# 1284 "util.h"
__attribute__ ((__warn_unused_result__))
unsigned long long check_strtoull( char const *s, unsigned long long min,
                                   unsigned long long max );
# 1296 "util.h"
__attribute__ ((__warn_unused_result__)) inline
char const* empty_if_null( char const *s ) {
  return s == 
# 1298 "util.h" 3 4
             ((void*)0) 
# 1298 "util.h"
                  ? "" : s;
}
# 1311 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1312 "util.h" 3 4
_Bool 
# 1312 "util.h"
    false_set( 
# 1312 "util.h" 3 4
               _Bool 
# 1312 "util.h"
                    *flag ) {
  return !*flag && (*flag = 
# 1313 "util.h" 3 4
                           1
# 1313 "util.h"
                               );
}
# 1328 "util.h"
__attribute__((format(printf, (2), (2)+1)))
_Noreturn void fatal_error( int status, char const *format, ... );
# 1339 "util.h"
__attribute__ ((__warn_unused_result__))

# 1340 "util.h" 3 4
_Bool 
# 1340 "util.h"
    fd_is_file( int fd );
# 1387 "util.h"
void fput_list( FILE *out, void const *elt,
                char const* (*gets)( void const **ppelt ) );
# 1399 "util.h"
void fputs_quoted( char const *s, char quote, FILE *fout );
# 1410 "util.h"
void fputs_sp( char const *s, FILE *out );
# 1421 "util.h"
void fputsp_s( char const *s, FILE *out );
# 1435 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1436 "util.h" 3 4
_Bool 
# 1436 "util.h"
    is_01_bit( uint64_t n ) {
  return (n & (n - 1)) == 0;
}
# 1455 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1456 "util.h" 3 4
_Bool 
# 1456 "util.h"
    is_0n_bit_only_in_set( uint64_t n, uint64_t set ) {
  return (n & set) == n;
}
# 1472 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1473 "util.h" 3 4
_Bool 
# 1473 "util.h"
    is_1_bit( uint64_t n ) {
  return n != 0 && is_01_bit( n );
}
# 1492 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1493 "util.h" 3 4
_Bool 
# 1493 "util.h"
    is_1_bit_in_set( uint64_t n, uint64_t set ) {
  return is_1_bit( n & set );
}
# 1510 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1511 "util.h" 3 4
_Bool 
# 1511 "util.h"
    is_1_bit_only_in_set( uint64_t n, uint64_t set ) {
  return is_1_bit( n ) && is_1_bit_in_set( n, set );
}
# 1530 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1531 "util.h" 3 4
_Bool 
# 1531 "util.h"
    is_1n_bit_only_in_set( uint64_t n, uint64_t set ) {
  return n != 0 && is_0n_bit_only_in_set( n, set );
}
# 1545 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1546 "util.h" 3 4
_Bool 
# 1546 "util.h"
    is_ident( char c ) {
  return isalnum( c ) || c == '_';
}
# 1560 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1561 "util.h" 3 4
_Bool 
# 1561 "util.h"
    is_ident_first( char c ) {
  return 
# 1562 "util.h" 3 4
        (0 ? isalpha(
# 1562 "util.h"
        c
# 1562 "util.h" 3 4
        ) : (((unsigned)(
# 1562 "util.h"
        c
# 1562 "util.h" 3 4
        )|32)-'a') < 26) 
# 1562 "util.h"
                     || c == '_';
}
# 1574 "util.h"
__attribute__ ((__warn_unused_result__))
uint32_t ls_bit1_32( uint32_t n );
# 1586 "util.h"
__attribute__ ((__warn_unused_result__))
uint32_t ms_bit1_32( uint32_t n );
# 1600 "util.h"
__attribute__ ((__warn_unused_result__)) inline
char const* null_if_empty( char const *s ) {
  return s != 
# 1602 "util.h" 3 4
             ((void*)0) 
# 1602 "util.h"
                  && *(((s)) += strspn( ((s)), (" \n\t\r\f\v") )) == '\0' ? 
# 1602 "util.h" 3 4
                                             ((void*)0) 
# 1602 "util.h"
                                                  : s;
}
# 1613 "util.h"
__attribute__ ((__warn_unused_result__))
char const* parse_identifier( char const *s );
# 1626 "util.h"
_Noreturn void perror_exit( int status );
# 1636 "util.h"
__attribute__ ((__warn_unused_result__))

# 1637 "util.h" 3 4
_Bool 
# 1637 "util.h"
    path_is_file( char const *path );
# 1646 "util.h"
__attribute__ ((__warn_unused_result__))

# 1647 "util.h" 3 4
_Bool 
# 1647 "util.h"
    str_is_affirmative( char const *s );
# 1659 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1660 "util.h" 3 4
_Bool 
# 1660 "util.h"
    str_is_empty( char const *s ) {
  return *(((s)) += strspn( ((s)), (" \n\t\r\f\v") )) == '\0';
}
# 1686 "util.h"
__attribute__ ((__warn_unused_result__))

# 1687 "util.h" 3 4
_Bool 
# 1687 "util.h"
    str_is_ident_prefix( char const *ident, size_t ident_len, char const *s,
                          size_t s_len );
# 1700 "util.h"
__attribute__ ((__warn_unused_result__))

# 1701 "util.h" 3 4
_Bool 
# 1701 "util.h"
    str_is_prefix( char const *si, char const *sj );
# 1715 "util.h"

char* str_realloc_cat( char *dst, char const *sep, char const *src );
# 1730 "util.h"

char* str_realloc_pcat( char const *src, char const *sep, char *dst );
# 1748 "util.h"
__attribute__ ((__warn_unused_result__))
int strncmp_in_set( char const *si, char const *sj, size_t n,
                    char const *charset );







void strn_rtrim( char const *s, size_t *s_len );
# 1768 "util.h"
__attribute__ ((__warn_unused_result__))
size_t strnspn( char const *s, char const *charset, size_t n );
# 1781 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1782 "util.h" 3 4
_Bool 
# 1782 "util.h"
    true_or_set( 
# 1782 "util.h" 3 4
                 _Bool 
# 1782 "util.h"
                      *flag ) {
  return *flag || !(*flag = 
# 1783 "util.h" 3 4
                           1
# 1783 "util.h"
                               );
}
# 1796 "util.h"
__attribute__ ((__warn_unused_result__)) inline

# 1797 "util.h" 3 4
_Bool 
# 1797 "util.h"
    true_clear( 
# 1797 "util.h" 3 4
                _Bool 
# 1797 "util.h"
                     *flag ) {
  return *flag && !(*flag = 
# 1798 "util.h" 3 4
                           0
# 1798 "util.h"
                                );
}
# 1809 "util.h"
inline
void fput_sep( char const *sep, 
# 1810 "util.h" 3 4
                               _Bool 
# 1810 "util.h"
                                    *sep_flag, FILE *fout ) {
  if ( true_or_set( sep_flag ) )
    do { if ( __builtin_expect( !!((fputs( (sep), (fout) ) == 
# 1812 "util.h" 3 4
   (-1)
# 1812 "util.h"
   )), 0 ) ) perror_exit( (
# 1812 "util.h" 3 4
   74
# 1812 "util.h"
   ) ); } while (0);
}





void wait_for_debugger_attach( void );
# 1828 "util.h"

# 41 "types.h" 2
# 63 "types.h"
enum c_alignas_kind {
  C_ALIGNAS_NONE,
  C_ALIGNAS_BYTES,
  C_ALIGNAS_SNAME,
  C_ALIGNAS_TYPE
};




enum c_array_kind {
  C_ARRAY_SIZE_NONE,
  C_ARRAY_SIZE_INT,
  C_ARRAY_SIZE_NAME,
  C_ARRAY_SIZE_VLA
};




enum c_capture_kind {
  C_CAPTURE_VARIABLE,
  C_CAPTURE_COPY,
  C_CAPTURE_REFERENCE,
  C_CAPTURE_THIS,
  C_CAPTURE_STAR_THIS
};




enum c_cast_kind {
  C_CAST_C,
  C_CAST_CONST,
  C_CAST_DYNAMIC,
  C_CAST_REINTERPRET,
  C_CAST_STATIC
};






enum c_func_member {
  C_FUNC_UNSPECIFIED = 0,
  C_FUNC_MEMBER = 1 << 0,
  C_FUNC_NON_MEMBER = 1 << 1
};




enum c_graph {
  C_GRAPH_NONE,
  C_GRAPH_DI,
  C_GRAPH_TRI
};
# 131 "types.h"
enum c_op_id {
  C_OP_NONE,
  C_OP_CO_AWAIT,
  C_OP_NEW,
  C_OP_NEW_ARRAY,
  C_OP_DELETE,
  C_OP_DELETE_ARRAY,
  C_OP_EXCLAMATION,
  C_OP_EXCLAMATION_EQUAL,
  C_OP_PERCENT,
  C_OP_PERCENT_EQUAL,
  C_OP_AMPERSAND,
  C_OP_AMPERSAND_AMPERSAND,
  C_OP_AMPER_EQUAL,
  C_OP_PARENTHESES,
  C_OP_STAR,
  C_OP_STAR_EQUAL,
  C_OP_PLUS,
  C_OP_PLUS_PLUS,
  C_OP_PLUS_EQUAL,
  C_OP_COMMA,
  C_OP_MINUS,
  C_OP_MINUS_MINUS,
  C_OP_MINUS_EQUAL,
  C_OP_MINUS_GREATER,
  C_OP_MINUS_GREATER_STAR,
  C_OP_DOT,
  C_OP_DOT_STAR,
  C_OP_SLASH,
  C_OP_SLASH_EQUAL,
  C_OP_COLON_COLON,
  C_OP_LESS,
  C_OP_LESS_LESS,
  C_OP_LESS_LESS_EQUAL,
  C_OP_LESS_EQUAL,
  C_OP_LESS_EQUAL_GREATER,
  C_OP_EQUAL,
  C_OP_EQUAL_EQUAL,
  C_OP_GREATER,
  C_OP_GREATER_EQUAL,
  C_OP_GREATER_GREATER,
  C_OP_GREATER_GREATER_EQUAL,
  C_OP_QUESTION_MARK_COLON,
  C_OP_BRACKETS,
  C_OP_CARET,
  C_OP_CARET_EQUAL,
  C_OP_PIPE,
  C_OP_PIPE_EQUAL,
  C_OP_PIPE_PIPE,
  C_OP_TILDE,
};




enum cdecl_debug {
  CDECL_DEBUG_NO = 0,
  CDECL_DEBUG_YES = 1 << 0,






  CDECL_DEBUG_OPT_AST_UNIQUE_ID = 1 << 1
};






enum cdecl_show {




  CDECL_SHOW_PREDEFINED = 1 << 0,






  CDECL_SHOW_USER_DEFINED = 1 << 1,







  CDECL_SHOW_OPT_IGNORE_LANG = 1 << 2
};







enum decl_flags {
# 241 "types.h"
  C_ENG_DECL = 1 << 0,







  C_ENG_OPT_OMIT_DECLARE = 1 << 1,
# 260 "types.h"
  C_GIB_PRINT_CAST = 1 << 8,
# 278 "types.h"
  C_GIB_PRINT_DECL = 1 << 9,
# 297 "types.h"
  C_GIB_OPT_MULTI_DECL = 1 << 10,
# 316 "types.h"
  C_GIB_OPT_OMIT_TYPE = 1 << 11,
# 328 "types.h"
  C_GIB_OPT_SEMICOLON = 1 << 12,
# 345 "types.h"
  C_GIB_TYPEDEF = 1 << 13,
# 379 "types.h"
  C_GIB_USING = 1 << 14,
};
# 425 "types.h"
typedef struct c_alignas c_alignas_t;
typedef enum c_alignas_kind c_alignas_kind_t;
typedef struct c_apple_block_ast c_apple_block_ast_t;
typedef struct c_array_ast c_array_ast_t;
typedef enum c_array_kind c_array_kind_t;
typedef struct c_ast c_ast_t;
typedef slist_t c_ast_list_t;
typedef struct c_ast_pair c_ast_pair_t;
typedef struct c_bit_field_ast c_bit_field_ast_t;
typedef struct c_builtin_ast c_builtin_ast_t;
# 443 "types.h"
typedef slist_node_t c_capture_t;

typedef struct c_capture_ast c_capture_ast_t;
typedef enum c_capture_kind c_capture_kind_t;
typedef struct c_cast_ast c_cast_ast_t;
typedef enum c_cast_kind c_cast_kind_t;
typedef struct c_concept_ast c_concept_ast_t;
typedef struct c_constructor_ast c_constructor_ast_t;
typedef struct c_csu_ast c_csu_ast_t;
typedef struct c_enum_ast c_enum_ast_t;
typedef enum c_func_member c_func_member_t;
typedef struct c_function_ast c_function_ast_t;
typedef enum c_graph c_graph_t;
typedef struct c_lambda_ast c_lambda_ast_t;
typedef uint32_t c_lang_id_t;
typedef struct c_loc c_loc_t;
# 467 "types.h"
typedef short c_loc_num_t;
# 477 "types.h"
typedef struct c_name_ast c_name_ast_t;
typedef enum c_op_id c_op_id_t;
typedef struct c_operator c_operator_t;
typedef struct c_operator_ast c_operator_ast_t;
# 489 "types.h"
typedef slist_node_t c_param_t;

typedef struct c_parent_ast c_parent_ast_t;
typedef struct c_ptr_mbr_ast c_ptr_mbr_ast_t;
typedef struct c_ptr_ref_ast c_ptr_ref_ast_t;






typedef slist_node_t c_scope_t;

typedef struct c_sglob c_sglob_t;
typedef slist_t c_sname_t;
typedef struct c_struct_bind_ast c_struct_bind_ast_t;
typedef uint64_t c_tid_t;
typedef struct c_typedef c_typedef_t;
typedef struct c_typedef_ast c_typedef_ast_t;
typedef struct c_type c_type_t;
typedef struct c_udef_conv_ast c_udef_conv_ast_t;
typedef struct c_udef_lit_ast c_udef_lit_ast_t;
typedef enum cdecl_debug cdecl_debug_t;
typedef enum cdecl_show cdecl_show_t;
typedef enum decl_flags decl_flags_t;
# 527 "types.h"
typedef slist_t p_arg_list_t;

typedef struct p_macro p_macro_t;
typedef struct p_param p_param_t;
typedef slist_t p_param_list_t;
typedef struct p_token p_token_t;
typedef slist_t p_token_list_t;
typedef slist_node_t p_token_node_t;
typedef union user_data user_data_t;

typedef c_loc_t YYLTYPE;
# 552 "types.h"
typedef int (*bsearch_cmp_fn_t)( void const *i_data, void const *j_data );
# 563 "types.h"
typedef int (*qsort_cmp_fn_t)( void const *i_data, void const *j_data );







struct c_loc {
  c_loc_num_t first_line;
  c_loc_num_t first_column;
  c_loc_num_t last_line;
  c_loc_num_t last_column;
};




struct c_alignas {
  c_alignas_kind_t kind;
  c_loc_t loc;




  union {
    unsigned bytes;
    c_sname_t sname;
    c_ast_t *type_ast;
  };
};





struct c_ast_pair {



  c_ast_t *ast;






  c_ast_t *target_ast;
};
# 622 "types.h"
union user_data {
  
# 623 "types.h" 3 4
 _Bool 
# 623 "types.h"
                     b;

  char c;
  signed char sc;
  unsigned char uc;

  short s;
  int i;
  long l;
  long long ll;

  unsigned short us;
  unsigned int ui;
  unsigned long ul;
  unsigned long long ull;

  int8_t i8;
  int16_t i16;
  int32_t i32;
  int64_t i64;

  uint8_t u8;
  uint16_t u16;
  uint32_t u32;
  uint64_t u64;

  float f;
  double d;

  void *p;
  void const *pc;
};
# 32 "cdecl.h" 2
# 94 "cdecl.h"
extern 
# 94 "cdecl.h" 3 4
      _Bool 
# 94 "cdecl.h"
                   cdecl_is_initialized;
extern char const *cdecl_input_path;
extern 
# 96 "cdecl.h" 3 4
      _Bool 
# 96 "cdecl.h"
                   cdecl_is_interactive;
extern 
# 97 "cdecl.h" 3 4
      _Bool 
# 97 "cdecl.h"
                   cdecl_is_testing;
extern char const *me;
# 109 "cdecl.h"
__attribute__ ((__warn_unused_result__))

# 110 "cdecl.h" 3 4
_Bool 
# 110 "cdecl.h"
    is_cppdecl( void );







void cdecl_quit( void );
# 29 "cdecl.c" 2
# 1 "c_ast.h" 1
# 34 "c_ast.h"
# 1 "c_kind.h" 1
# 48 "c_kind.h"
enum c_ast_kind {
# 81 "c_kind.h"
  K_PLACEHOLDER = 1 << 0,






  K_BUILTIN = 1 << 1,






  K_CAPTURE = 1 << 2,






  K_CLASS_STRUCT_UNION = 1 << 3,






  K_CONCEPT = 1 << 4,
# 125 "c_kind.h"
  K_NAME = 1 << 5,






  K_TYPEDEF = 1 << 6,




  K_VARIADIC = 1 << 7,
# 146 "c_kind.h"
  K_ARRAY = 1 << 8,






  K_CAST = 1 << 9,
# 163 "c_kind.h"
  K_ENUM = 1 << 10,






  K_POINTER = 1 << 11,






  K_POINTER_TO_MEMBER = 1 << 12,






  K_REFERENCE = 1 << 13,






  K_RVALUE_REFERENCE = 1 << 14,






  K_STRUCTURED_BINDING = 1 << 15,
# 207 "c_kind.h"
  K_CONSTRUCTOR = 1 << 16,




  K_DESTRUCTOR = 1 << 17,
# 223 "c_kind.h"
  K_APPLE_BLOCK = 1 << 18,






  K_FUNCTION = 1 << 19,






  K_LAMBDA = 1 << 20,






  K_OPERATOR = 1 << 21,






  K_UDEF_CONV = 1 << 22,






  K_UDEF_LIT = 1 << 23,
};
typedef enum c_ast_kind c_ast_kind_t;
# 406 "c_kind.h"
__attribute__ ((__warn_unused_result__))
char const* c_kind_name( c_ast_kind_t kind );
# 35 "c_ast.h" 2
# 1 "c_sname.h" 1
# 32 "c_sname.h"
# 1 "c_type.h" 1
# 31 "c_type.h"
# 1 "c_lang.h" 1
# 32 "c_lang.h"
# 1 "options.h" 1
# 35 "options.h"
# 1 "color.h" 1
# 33 "color.h"
# 1 "strbuf.h" 1
# 36 "strbuf.h"
# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 37 "strbuf.h" 2
# 1 "../lib/string.h" 1
# 20 "../lib/string.h"
       
# 21 "../lib/string.h" 3
# 38 "strbuf.h" 2


# 58 "strbuf.h"
struct strbuf {
  char *str;
  size_t len;
  size_t cap;
};
typedef struct strbuf strbuf_t;
# 77 "strbuf.h"
void strbuf_cleanup( strbuf_t *sbuf );
# 90 "strbuf.h"
inline
void strbuf_init( strbuf_t *sbuf ) {
  *sbuf = (strbuf_t){ 0 };
}
# 107 "strbuf.h"

char* strbuf_paths( strbuf_t *sbuf, char const *component );
# 124 "strbuf.h"
 __attribute__((format(printf, (2), (2)+1)))
char* strbuf_printf( strbuf_t *sbuf, char const *format, ... );
# 141 "strbuf.h"

char* strbuf_putsn( strbuf_t *sbuf, char const *s, size_t s_len );
# 155 "strbuf.h"
 inline
char* strbuf_putc( strbuf_t *sbuf, char c ) {
  return strbuf_putsn( sbuf, &c, 1 );
}
# 172 "strbuf.h"
 inline
char* strbuf_puts( strbuf_t *sbuf, char const *s ) {
  return strbuf_putsn( sbuf, s, strlen( s ) );
}
# 188 "strbuf.h"

char* strbuf_puts_quoted( strbuf_t *sbuf, char quote, char const *s );
# 199 "strbuf.h"


# 200 "strbuf.h" 3 4
_Bool 
# 200 "strbuf.h"
    strbuf_reserve( strbuf_t *sbuf, size_t res_len );
# 216 "strbuf.h"
void strbuf_reset( strbuf_t *sbuf );
# 234 "strbuf.h"
void strbuf_sepsn( strbuf_t *sbuf, char const *sep, size_t sep_len,
                   
# 235 "strbuf.h" 3 4
                  _Bool 
# 235 "strbuf.h"
                       *sep_flag );
# 255 "strbuf.h"
void strbuf_sepsn_putsn( strbuf_t *sbuf, char const *sep, size_t sep_len,
                         
# 256 "strbuf.h" 3 4
                        _Bool 
# 256 "strbuf.h"
                             *sep_flag, char const *s, size_t s_len );
# 275 "strbuf.h"
inline
void strbuf_sepsn_puts( strbuf_t *sbuf, char const *sep, size_t sep_len,
                        
# 277 "strbuf.h" 3 4
                       _Bool 
# 277 "strbuf.h"
                            *sep_flag, char const *s ) {
  strbuf_sepsn_putsn( sbuf, sep, sep_len, sep_flag, s, strlen( s ) );
}
# 298 "strbuf.h"
inline
void strbuf_sepc_putsn( strbuf_t *sbuf, char sep, 
# 299 "strbuf.h" 3 4
                                                 _Bool 
# 299 "strbuf.h"
                                                      *sep_flag, char const *s,
                        size_t s_len ) {
  strbuf_sepsn_putsn( sbuf, &sep, 1, sep_flag, s, s_len );
}
# 320 "strbuf.h"
inline
void strbuf_sepc_puts( strbuf_t *sbuf, char sep, 
# 321 "strbuf.h" 3 4
                                                _Bool 
# 321 "strbuf.h"
                                                     *sep_flag,
                       char const *s ) {
  strbuf_sepsn_putsn( sbuf, &sep, 1, sep_flag, s, strlen( s ) );
}
# 336 "strbuf.h"
__attribute__ ((__warn_unused_result__)) inline
char* strbuf_take( strbuf_t *sbuf ) {
  char *const rv_str = sbuf->str;
  strbuf_init( sbuf );
  return rv_str;
}






# 34 "color.h" 2





# 1 "../lib/stdio.h" 1
# 20 "../lib/stdio.h"
       
# 21 "../lib/stdio.h" 3
# 40 "color.h" 2


# 102 "color.h"
enum color_when {
  COLOR_NEVER,
  COLOR_ISATTY,
  COLOR_NOT_FILE,
  COLOR_ALWAYS
};
typedef enum color_when color_when_t;


extern char const *sgr_caret;
extern char const *sgr_error;
extern char const *sgr_help_keyword;
extern char const *sgr_help_nonterm;
extern char const *sgr_help_punct;
extern char const *sgr_help_title;
extern char const *sgr_locus;
extern char const *sgr_macro_no_expand;
extern char const *sgr_macro_punct;
extern char const *sgr_macro_subst;
extern char const *sgr_prompt;
extern char const *sgr_warning;
# 135 "color.h"
inline
void color_end( FILE *file, char const *sgr_color ) {
  if ( sgr_color != 
# 137 "color.h" 3 4
                   ((void*)0) 
# 137 "color.h"
                        )
    do { if ( __builtin_expect( !!((fputs( ("\33[m" "\33[K"), (file) ) == 
# 138 "color.h" 3 4
   (-1)
# 138 "color.h"
   )), 0 ) ) perror_exit( (
# 138 "color.h" 3 4
   74
# 138 "color.h"
   ) ); } while (0);
}
# 150 "color.h"
inline
void color_start( FILE *file, char const *sgr_color ) {
  if ( sgr_color != 
# 152 "color.h" 3 4
                   ((void*)0) 
# 152 "color.h"
                        )
    do { if ( __builtin_expect( !!((fprintf( (file), "\33[%sm" "\33[K", sgr_color ) < 0)), 0 ) ) perror_exit( (
# 153 "color.h" 3 4
   74
# 153 "color.h"
   ) ); } while (0);
}
# 166 "color.h"
inline
void color_strbuf_end( strbuf_t *sbuf, char const *sgr_color ) {
  if ( sgr_color != 
# 168 "color.h" 3 4
                   ((void*)0) 
# 168 "color.h"
                        )
    strbuf_puts( sbuf, "\33[m" "\33[K" );
}
# 182 "color.h"
inline
void color_strbuf_start( strbuf_t *sbuf, char const *sgr_color ) {
  if ( sgr_color != 
# 184 "color.h" 3 4
                   ((void*)0) 
# 184 "color.h"
                        )
    strbuf_printf( sbuf, "\33[%sm" "\33[K", sgr_color );
}






void colors_init( void );






# 36 "options.h" 2
# 58 "options.h"
extern 
# 58 "options.h" 3 4
      _Bool 
# 58 "options.h"
                   opt_alt_tokens;
# 68 "options.h"
extern cdecl_debug_t opt_cdecl_debug;

extern color_when_t opt_color_when;
extern char const *opt_config_path;
extern 
# 72 "options.h" 3 4
      _Bool 
# 72 "options.h"
                   opt_east_const;
extern 
# 73 "options.h" 3 4
      _Bool 
# 73 "options.h"
                   opt_echo_commands;
extern 
# 74 "options.h" 3 4
      _Bool 
# 74 "options.h"
                   opt_english_types;


extern c_tid_t opt_explicit_ecsu_btids;

extern char const *opt_file;
# 89 "options.h"
extern c_graph_t opt_graph;
extern 
# 90 "options.h" 3 4
      _Bool 
# 90 "options.h"
                   opt_infer_command;
extern c_lang_id_t opt_lang_id;
extern unsigned opt_lineno;


extern 
# 95 "options.h" 3 4
      _Bool 
# 95 "options.h"
                   opt_permissive_types;

extern 
# 97 "options.h" 3 4
      _Bool 
# 97 "options.h"
                   opt_prompt;
extern 
# 98 "options.h" 3 4
      _Bool 
# 98 "options.h"
                   opt_read_config;
extern 
# 99 "options.h" 3 4
      _Bool 
# 99 "options.h"
                   opt_semicolon;
extern 
# 100 "options.h" 3 4
      _Bool 
# 100 "options.h"
                   opt_trailing_ret;
extern 
# 101 "options.h" 3 4
      _Bool 
# 101 "options.h"
                   opt_typedefs;
extern 
# 102 "options.h" 3 4
      _Bool 
# 102 "options.h"
                   opt_using;


extern c_ast_kind_t opt_west_decl_kinds;


extern char const OPT_CDECL_DEBUG_ALL[];


extern char const OPT_ECSU_ALL[];


extern char const OPT_WEST_DECL_ALL[];




extern int yy_flex_debug;



extern int yydebug;
# 139 "options.h"
__attribute__ ((__warn_unused_result__))
char const* cdecl_debug_str( void );
# 154 "options.h"
__attribute__ ((__warn_unused_result__))
char const* explicit_ecsu_str( void );
# 169 "options.h"
__attribute__ ((__warn_unused_result__))
char const* explicit_int_str( void );
# 182 "options.h"
__attribute__ ((__warn_unused_result__))

# 183 "options.h" 3 4
_Bool 
# 183 "options.h"
    is_explicit_int( c_tid_t btids );






void lang_set( c_lang_id_t lang_id );
# 211 "options.h"
__attribute__ ((__warn_unused_result__))

# 212 "options.h" 3 4
_Bool 
# 212 "options.h"
    parse_cdecl_debug( char const *debug_format );
# 237 "options.h"
__attribute__ ((__warn_unused_result__))

# 238 "options.h" 3 4
_Bool 
# 238 "options.h"
    parse_explicit_ecsu( char const *ecsu_format );
# 267 "options.h"
__attribute__ ((__warn_unused_result__))

# 268 "options.h" 3 4
_Bool 
# 268 "options.h"
    parse_explicit_int( char const *ei_format );
# 294 "options.h"
__attribute__ ((__warn_unused_result__))

# 295 "options.h" 3 4
_Bool 
# 295 "options.h"
    parse_west_decl( char const *wd_format );
# 308 "options.h"
__attribute__ ((__warn_unused_result__))
char const* west_decl_str( void );
# 33 "c_lang.h" 2






# 1 "../lib/assert.h" 1
# 22 "../lib/assert.h"
       
# 23 "../lib/assert.h" 3



# 1 "/usr/include/assert.h" 1 3 4
# 19 "/usr/include/assert.h" 3 4

# 19 "/usr/include/assert.h" 3 4
_Noreturn void __assert_fail (const char *, const char *, int, const char *);
# 27 "../lib/assert.h" 2 3
# 40 "c_lang.h" 2

# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 42 "c_lang.h" 2


# 1388 "c_lang.h"

# 1388 "c_lang.h"
struct c_lang {
  char const *name;
  
# 1390 "c_lang.h" 3 4
 _Bool 
# 1390 "c_lang.h"
               is_alias;
  c_lang_id_t lang_id;
};
typedef struct c_lang c_lang_t;
# 1404 "c_lang.h"
struct c_lang_lit {
  c_lang_id_t lang_ids;
  char const *literal;
};
typedef struct c_lang_lit c_lang_lit_t;
# 1424 "c_lang.h"
__attribute__ ((__warn_unused_result__))
char const* c_lang___cplusplus( c_lang_id_t lang_id );
# 1439 "c_lang.h"
__attribute__ ((__warn_unused_result__))
char const* c_lang___STDC_VERSION__( c_lang_id_t lang_id );
# 1452 "c_lang.h"
__attribute__ ((__warn_unused_result__)) inline
c_lang_id_t c_lang_and_newer( c_lang_id_t lang_id ) {
  lang_id &= ~((1u << 0) | (1u << 1));
  
# 1455 "c_lang.h" 3 4
 ((void)((
# 1455 "c_lang.h"
 is_1_bit( lang_id )
# 1455 "c_lang.h" 3 4
 ) || (__assert_fail(
# 1455 "c_lang.h"
 "is_1_bit( lang_id )"
# 1455 "c_lang.h" 3 4
 , "c_lang.h", 1455, __func__),0)))
# 1455 "c_lang.h"
                              ;
  return (~(((lang_id)) - 1u));
}
# 1474 "c_lang.h"
__attribute__ ((__warn_unused_result__))
char const* c_lang_coarse_name( c_lang_id_t lang_ids );
# 1485 "c_lang.h"
__attribute__ ((__warn_unused_result__))
c_lang_id_t c_lang_find( char const *name );
# 1502 "c_lang.h"
__attribute__ ((__warn_unused_result__))
c_lang_id_t c_lang_is_one( c_lang_id_t lang_ids );
# 1515 "c_lang.h"
__attribute__ ((__warn_unused_result__))
char const* c_lang_literal( c_lang_lit_t const *lang_lit );
# 1530 "c_lang.h"
__attribute__ ((__warn_unused_result__))
char const* c_lang_name( c_lang_id_t lang_id );
# 1545 "c_lang.h"
__attribute__ ((__warn_unused_result__)) inline
c_lang_id_t c_lang_newer( c_lang_id_t lang_id ) {
  lang_id &= ~((1u << 0) | (1u << 1));
  
# 1548 "c_lang.h" 3 4
 ((void)((
# 1548 "c_lang.h"
 is_1_bit( lang_id )
# 1548 "c_lang.h" 3 4
 ) || (__assert_fail(
# 1548 "c_lang.h"
 "is_1_bit( lang_id )"
# 1548 "c_lang.h" 3 4
 , "c_lang.h", 1548, __func__),0)))
# 1548 "c_lang.h"
                              ;
  return (~(((((lang_id))) - 1u) | ((lang_id))));
}
# 1562 "c_lang.h"
__attribute__ ((__warn_unused_result__)) inline
c_lang_id_t c_lang_newest( c_lang_id_t lang_ids ) {
  return ms_bit1_32( lang_ids & ~((1u << 0) | (1u << 1)) );
}
# 1579 "c_lang.h"
__attribute__ ((__warn_unused_result__))
c_lang_t const* c_lang_next( c_lang_t const *lang );
# 1592 "c_lang.h"
__attribute__ ((__warn_unused_result__)) inline
c_lang_id_t c_lang_oldest( c_lang_id_t lang_ids ) {
  return ls_bit1_32( lang_ids & ~((1u << 0) | (1u << 1)) ) | (lang_ids & ((1u << 0) | (1u << 1)));
}
# 1638 "c_lang.h"
__attribute__ ((__warn_unused_result__))
char const* c_lang_which( c_lang_id_t lang_ids );
# 1656 "c_lang.h"
__attribute__ ((__warn_unused_result__))
c_lang_id_t is_reserved_name( char const *name );
# 1669 "c_lang.h"
__attribute__ ((__warn_unused_result__)) inline

# 1670 "c_lang.h" 3 4
_Bool 
# 1670 "c_lang.h"
    opt_lang_is_any( c_lang_id_t lang_ids ) {
  return (opt_lang_id & lang_ids) != 0u;
}
# 1686 "c_lang.h"
__attribute__ ((__warn_unused_result__)) inline
char const* c_lang___STDC__( c_lang_id_t lang_id ) {
  
# 1688 "c_lang.h" 3 4
 ((void)((
# 1688 "c_lang.h"
 is_1_bit( lang_id )
# 1688 "c_lang.h" 3 4
 ) || (__assert_fail(
# 1688 "c_lang.h"
 "is_1_bit( lang_id )"
# 1688 "c_lang.h" 3 4
 , "c_lang.h", 1688, __func__),0)))
# 1688 "c_lang.h"
                              ;
  return (lang_id & ((~((((1u << 3))) - 1u)) & ((((((1u << 8))) - 1u) | ((1u << 8))) & ~((1u << 0) | (1u << 1))))) != 0u ? "1" : 
# 1689 "c_lang.h" 3 4
                                                        ((void*)0)
# 1689 "c_lang.h"
                                                            ;
}






# 32 "c_type.h" 2





# 1 "../lib/assert.h" 1
# 22 "../lib/assert.h"
       
# 23 "../lib/assert.h" 3



# 1 "/usr/include/assert.h" 1 3 4
# 19 "/usr/include/assert.h" 3 4

# 19 "/usr/include/assert.h" 3 4
_Noreturn void __assert_fail (const char *, const char *, int, const char *);
# 27 "../lib/assert.h" 2 3
# 38 "c_type.h" 2

# 1 "../lib/inttypes.h" 1
# 25 "../lib/inttypes.h"
       
# 26 "../lib/inttypes.h" 3
# 41 "../lib/inttypes.h" 3
# 1 "/usr/include/inttypes.h" 1 3 4
# 12 "/usr/include/inttypes.h" 3 4
# 1 "/usr/include/bits/alltypes.h" 1 3 4
# 13 "/usr/include/inttypes.h" 2 3 4

typedef struct { intmax_t quot, rem; } imaxdiv_t;

intmax_t imaxabs(intmax_t);
imaxdiv_t imaxdiv(intmax_t, intmax_t);

intmax_t strtoimax(const char *
# 19 "/usr/include/inttypes.h"
                              __restrict__
# 19 "/usr/include/inttypes.h" 3 4
                                        , char **
# 19 "/usr/include/inttypes.h"
                                                 __restrict__
# 19 "/usr/include/inttypes.h" 3 4
                                                           , int);
uintmax_t strtoumax(const char *
# 20 "/usr/include/inttypes.h"
                               __restrict__
# 20 "/usr/include/inttypes.h" 3 4
                                         , char **
# 20 "/usr/include/inttypes.h"
                                                  __restrict__
# 20 "/usr/include/inttypes.h" 3 4
                                                            , int);

intmax_t wcstoimax(const wchar_t *
# 22 "/usr/include/inttypes.h"
                                 __restrict__
# 22 "/usr/include/inttypes.h" 3 4
                                           , wchar_t **
# 22 "/usr/include/inttypes.h"
                                                       __restrict__
# 22 "/usr/include/inttypes.h" 3 4
                                                                 , int);
uintmax_t wcstoumax(const wchar_t *
# 23 "/usr/include/inttypes.h"
                                  __restrict__
# 23 "/usr/include/inttypes.h" 3 4
                                            , wchar_t **
# 23 "/usr/include/inttypes.h"
                                                        __restrict__
# 23 "/usr/include/inttypes.h" 3 4
                                                                  , int);
# 42 "../lib/inttypes.h" 2 3
# 40 "c_type.h" 2


# 68 "c_type.h"

# 68 "c_type.h"
struct c_type {
# 77 "c_type.h"
  c_tid_t btids;
# 86 "c_type.h"
  c_tid_t stids;






  c_tid_t atids;
};
# 108 "c_type.h"
enum c_tpid {



  C_TPID_NONE = 0,







  C_TPID_BASE = 1 << 0,
# 131 "c_type.h"
  C_TPID_STORE = 1 << 1,







  C_TPID_ATTR = 1 << 2
};
typedef enum c_tpid c_tpid_t;
# 1047 "c_type.h"
extern c_type_t const T_NONE;
extern c_type_t const T_ANY;
extern c_type_t const T_ANY_const_CLASS;
extern c_type_t const T_const_char;
extern c_type_t const T_TS_typedef;
# 1070 "c_type.h"
__attribute__ ((__warn_unused_result__))

# 1071 "c_type.h" 3 4
_Bool 
# 1071 "c_type.h"
    c_tid_add( c_tid_t *dst_tids, c_tid_t new_tids, c_loc_t const *new_loc );
# 1088 "c_type.h"
__attribute__ ((__warn_unused_result__))
char const* c_tid_english( c_tid_t tids );
# 1107 "c_type.h"
__attribute__ ((__warn_unused_result__))
char const* c_tid_error( c_tid_t tids );
# 1124 "c_type.h"
__attribute__ ((__warn_unused_result__))
char const* c_tid_gibberish( c_tid_t tids );
# 1139 "c_type.h"
__attribute__ ((__warn_unused_result__))
c_tid_t c_tid_normalize( c_tid_t tids );
# 1173 "c_type.h"
__attribute__ ((__warn_unused_result__))

# 1174 "c_type.h" 3 4
_Bool 
# 1174 "c_type.h"
    c_tid_scope_order_ok( c_tid_t i_btids, c_tid_t j_btids );
# 1184 "c_type.h"
__attribute__ ((__warn_unused_result__))
c_tpid_t c_tid_tpid( c_tid_t tids );
# 1204 "c_type.h"
__attribute__ ((__warn_unused_result__))

# 1205 "c_type.h" 3 4
_Bool 
# 1205 "c_type.h"
    c_type_add( c_type_t *dst_type, c_type_t const *new_type,
                 c_loc_t const *new_loc );
# 1219 "c_type.h"
__attribute__ ((__warn_unused_result__))

# 1220 "c_type.h" 3 4
_Bool 
# 1220 "c_type.h"
    c_type_add_tid( c_type_t *dst_type, c_tid_t new_tids,
                     c_loc_t const *new_loc );
# 1233 "c_type.h"
__attribute__ ((__warn_unused_result__))
c_type_t c_type_and( c_type_t const *i_type, c_type_t const *j_type );
# 1245 "c_type.h"
void c_type_and_eq_compl( c_type_t *dst_type, c_type_t const *rm_type );







__attribute__ ((__warn_unused_result__))
c_lang_id_t c_type_check( c_type_t const *type );
# 1271 "c_type.h"
__attribute__ ((__warn_unused_result__))
char const* c_type_english( c_type_t const *type );
# 1286 "c_type.h"
__attribute__ ((__warn_unused_result__))

# 1287 "c_type.h" 3 4
_Bool 
# 1287 "c_type.h"
    c_type_equiv( c_type_t const *i_type, c_type_t const *j_type );
# 1299 "c_type.h"
__attribute__ ((__warn_unused_result__))
c_tid_t c_type_get_tid( c_type_t const *type, c_tid_t tids );
# 1317 "c_type.h"
__attribute__ ((__warn_unused_result__))
char const* c_type_gibberish( c_type_t const *type );
# 1330 "c_type.h"
__attribute__ ((__warn_unused_result__))

# 1331 "c_type.h" 3 4
_Bool 
# 1331 "c_type.h"
    c_type_is_any( c_type_t const *i_type, c_type_t const *j_type );
# 1347 "c_type.h"
__attribute__ ((__warn_unused_result__))
char const* c_type_name_ecsu( c_type_t const *type );
# 1367 "c_type.h"
__attribute__ ((__warn_unused_result__))
char const* c_type_error( c_type_t const *type );
# 1381 "c_type.h"
__attribute__ ((__warn_unused_result__))
c_type_t c_type_or( c_type_t const *i_type, c_type_t const *j_type );
# 1397 "c_type.h"
void c_type_or_eq( c_type_t *dst_type, c_type_t const *add_type );
# 1408 "c_type.h"
 inline
c_tid_t c_tid_check( c_tid_t tids, c_tpid_t tpid ) {
  
# 1410 "c_type.h" 3 4
 ((void)((
# 1410 "c_type.h"
 (tids & 0xFull) == tpid
# 1410 "c_type.h" 3 4
 ) || (__assert_fail(
# 1410 "c_type.h"
 "(tids & TX_TPID_MASK) == tpid"
# 1410 "c_type.h" 3 4
 , "c_type.h", 1410, __func__),0)))
# 1410 "c_type.h"
                                        ;



  return tids;
}
# 1425 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline

# 1426 "c_type.h" 3 4
_Bool 
# 1426 "c_type.h"
    c_tid_is_compl( c_tid_t tids ) {





  return (tids & 0x8) != 0;
}
# 1447 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline
c_tid_t c_tid_compl( c_tid_t tids ) {
  
# 1449 "c_type.h" 3 4
 ((void)((
# 1449 "c_type.h"
 !c_tid_is_compl( tids )
# 1449 "c_type.h" 3 4
 ) || (__assert_fail(
# 1449 "c_type.h"
 "!c_tid_is_compl( tids )"
# 1449 "c_type.h" 3 4
 , "c_type.h", 1449, __func__),0)))
# 1449 "c_type.h"
                                  ;
  return ~tids ^ 0xFull;
}
# 1463 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline

# 1464 "c_type.h" 3 4
_Bool 
# 1464 "c_type.h"
    c_tid_is_except_any( c_tid_t tids, c_tid_t is_tids, c_tid_t except_tids ) {
  return (tids & (is_tids | except_tids)) == is_tids;
}
# 1476 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline
c_tid_t c_tid_no_tpid( c_tid_t tids ) {
  return tids & ~0xFull;
}
# 1490 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline

# 1491 "c_type.h" 3 4
_Bool 
# 1491 "c_type.h"
    c_tid_is_any( c_tid_t i_tids, c_tid_t j_tids ) {
  
# 1492 "c_type.h" 3 4
 ((void)((
# 1492 "c_type.h"
 c_tid_tpid( i_tids ) == c_tid_tpid( j_tids )
# 1492 "c_type.h" 3 4
 ) || (__assert_fail(
# 1492 "c_type.h"
 "c_tid_tpid( i_tids ) == c_tid_tpid( j_tids )"
# 1492 "c_type.h" 3 4
 , "c_type.h", 1492, __func__),0)))
# 1492 "c_type.h"
                                                       ;
  return c_tid_no_tpid( i_tids & j_tids ) != 0ull;
}
# 1507 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline

# 1508 "c_type.h" 3 4
_Bool 
# 1508 "c_type.h"
    c_tid_is_none( c_tid_t tids ) {
  return c_tid_no_tpid( tids ) == 0ull;
}
# 1523 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline

# 1524 "c_type.h" 3 4
_Bool 
# 1524 "c_type.h"
    c_tid_is_size_t( c_tid_t tids ) {
  c_tid_check( tids, C_TPID_BASE );
  return (tids & c_tid_compl( (0x0000000000004000ull | C_TPID_BASE) )) == ((0x0000000000040000ull | C_TPID_BASE) | (0x0000000000008000ull | C_TPID_BASE));
}
# 1537 "c_type.h"
__attribute__ ((__warn_unused_result__)) inline

# 1538 "c_type.h" 3 4
_Bool 
# 1538 "c_type.h"
    c_type_is_none( c_type_t const *type ) {
  return c_type_equiv( type, &T_NONE );
}






# 33 "c_sname.h" 2
# 41 "c_sname.h"
# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 42 "c_sname.h" 2


# 151 "c_sname.h"
struct c_scope_data {



  char *name;





  c_type_t type;
};
typedef struct c_scope_data c_scope_data_t;
# 175 "c_sname.h"
__attribute__ ((__warn_unused_result__))
int c_scope_data_cmp( c_scope_data_t const *i_data,
                      c_scope_data_t const *j_data );
# 188 "c_sname.h"
__attribute__ ((__warn_unused_result__))
c_scope_data_t* c_scope_data_dup( c_scope_data_t const *data );






void c_scope_data_free( c_scope_data_t *data );
# 208 "c_sname.h"
void c_sname_append_name( c_sname_t *sname, char *name );
# 220 "c_sname.h"
inline
void c_sname_append_sname( c_sname_t *dst, c_sname_t *src ) {
  slist_push_list_back( dst, src );
}
# 232 "c_sname.h"
__attribute__ ((__warn_unused_result__))

# 233 "c_sname.h" 3 4
_Bool 
# 233 "c_sname.h"
    c_sname_check( c_sname_t const *sname, c_loc_t const *sname_loc );
# 246 "c_sname.h"
void c_sname_cleanup( c_sname_t *sname );
# 256 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
int c_sname_cmp( c_sname_t const *i_sname, c_sname_t const *j_sname ) {
  return slist_cmp(
    i_sname, j_sname, ((slist_cmp_fn_t)(uintptr_t)(&c_scope_data_cmp))
  );
}
# 272 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
size_t c_sname_count( c_sname_t const *sname ) {
  return slist_len( sname );
}
# 285 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
c_sname_t c_sname_dup( c_sname_t const *sname ) {
  return slist_dup(
    sname, -1, ((slist_dup_fn_t)(uintptr_t)(&c_scope_data_dup))
  );
}







__attribute__ ((__warn_unused_result__)) inline

# 299 "c_sname.h" 3 4
_Bool 
# 299 "c_sname.h"
    c_sname_empty( c_sname_t const *sname ) {
  return slist_empty( sname );
}
# 313 "c_sname.h"
void c_sname_free( c_sname_t *sname );
# 328 "c_sname.h"
__attribute__ ((__warn_unused_result__))
char const* c_sname_global_name( c_sname_t const *sname );
# 342 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
c_type_t const* c_sname_global_type( c_sname_t const *sname ) {
  return c_sname_empty( sname ) ? &T_NONE : &((c_scope_data_t*)(uintptr_t)(((sname)->head)->data))->type;
}
# 359 "c_sname.h"
inline
void c_sname_init( c_sname_t *sname ) {
  slist_init( sname );
}
# 374 "c_sname.h"
inline
void c_sname_init_name( c_sname_t *sname, char *name ) {
  slist_init( sname );
  c_sname_append_name( sname, name );
}
# 391 "c_sname.h"
__attribute__ ((__warn_unused_result__))

# 392 "c_sname.h" 3 4
_Bool 
# 392 "c_sname.h"
    c_sname_is_ctor( c_sname_t const *sname );







__attribute__ ((__warn_unused_result__))

# 401 "c_sname.h" 3 4
_Bool 
# 401 "c_sname.h"
    c_sname_is_inline_nested_namespace( c_sname_t const *sname );
# 413 "c_sname.h"
void c_sname_list_cleanup( slist_t *list );
# 428 "c_sname.h"
__attribute__ ((__warn_unused_result__))
char const* c_sname_local_name( c_sname_t const *sname );
# 442 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
c_type_t const* c_sname_local_type( c_sname_t const *sname ) {
  return c_sname_empty( sname ) ? &T_NONE : &((c_scope_data_t*)(uintptr_t)(((sname)->tail)->data))->type;
}
# 471 "c_sname.h"
__attribute__ ((__warn_unused_result__))

# 472 "c_sname.h" 3 4
_Bool 
# 472 "c_sname.h"
    c_sname_match( c_sname_t const *sname, c_sglob_t const *sglob );
# 494 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
c_sname_t c_sname_move( c_sname_t *sname ) {
  return slist_move( sname );
}
# 513 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
char const* c_sname_name_atr( c_sname_t const *sname, size_t roffset ) {
  c_scope_data_t const *const data = slist_atr( sname, roffset );
  return data != 
# 516 "c_sname.h" 3 4
                ((void*)0) 
# 516 "c_sname.h"
                     ? data->name : "";
}
# 529 "c_sname.h"
__attribute__ ((__warn_unused_result__))
size_t c_sname_parse( char const *s, c_sname_t *rv_sname );
# 542 "c_sname.h"
__attribute__ ((__warn_unused_result__))

# 543 "c_sname.h" 3 4
_Bool 
# 543 "c_sname.h"
    c_sname_parse_dtor( char const *s, c_sname_t *rv_sname );
# 554 "c_sname.h"
inline
void c_sname_prepend_sname( c_sname_t *dst, c_sname_t *src ) {
  slist_push_list_front( dst, src );
}
# 575 "c_sname.h"
__attribute__ ((__warn_unused_result__))
c_sname_t c_sname_scope_sname( c_sname_t const *sname );
# 590 "c_sname.h"
__attribute__ ((__warn_unused_result__)) inline
c_type_t const* c_sname_scope_type( c_sname_t const *sname ) {
  c_scope_data_t const *const data = slist_atr( sname, 1 );
  return data != 
# 593 "c_sname.h" 3 4
                ((void*)0) 
# 593 "c_sname.h"
                     ? &data->type : &T_NONE;
}
# 609 "c_sname.h"
void c_sname_set( c_sname_t *dst_sname, c_sname_t *src_sname );
# 627 "c_sname.h"
void c_sname_set_all_types( c_sname_t *sname );
# 638 "c_sname.h"
inline
void c_sname_set_scope_type( c_sname_t *sname, c_type_t const *type ) {
  c_scope_data_t *const data = slist_atr( sname, 1 );
  if ( data != 
# 641 "c_sname.h" 3 4
              ((void*)0) 
# 641 "c_sname.h"
                   )
    data->type = *type;
}
# 653 "c_sname.h"
void c_sname_warn( c_sname_t const *sname, c_loc_t const *sname_loc );






# 36 "c_ast.h" 2
# 44 "c_ast.h"
# 1 "../lib/assert.h" 1
# 22 "../lib/assert.h"
       
# 23 "../lib/assert.h" 3



# 1 "/usr/include/assert.h" 1 3 4
# 19 "/usr/include/assert.h" 3 4

# 19 "/usr/include/assert.h" 3 4
_Noreturn void __assert_fail (const char *, const char *, int, const char *);
# 27 "../lib/assert.h" 2 3
# 45 "c_ast.h" 2

# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 47 "c_ast.h" 2


# 119 "c_ast.h"

# 119 "c_ast.h"
typedef unsigned c_ast_id_t;
# 129 "c_ast.h"
enum c_ast_visit_dir {
  C_VISIT_DOWN,
  C_VISIT_UP
};
typedef enum c_ast_visit_dir c_ast_visit_dir_t;
# 144 "c_ast.h"
typedef 
# 144 "c_ast.h" 3 4
       _Bool 
# 144 "c_ast.h"
            (*c_ast_visit_fn_t)( c_ast_t const *ast, user_data_t user_data );
# 193 "c_ast.h"
struct c_parent_ast {
  c_ast_t *of_ast;
};




struct c_array_ast {
  c_ast_t *of_ast;
  c_array_kind_t kind;
  union {
    unsigned size_int;
    char const *size_name;
  };
};
# 218 "c_ast.h"
struct c_apple_block_ast {
  c_ast_t *ret_ast;
  c_ast_list_t param_ast_list;
};
# 230 "c_ast.h"
struct c_bit_field_ast {



  _Alignas(c_ast_t*) char unused_234[ sizeof(c_ast_t*) ];


  unsigned bit_width;
};







struct c_builtin_ast {



  _Alignas(c_ast_t*) char unused_250[ sizeof(c_ast_t*) ];


  unsigned bit_width;





  union {
    struct {
      unsigned width;
    } BitInt;
  };
};




struct c_capture_ast {
  c_capture_kind_t kind;
};




struct c_cast_ast {
  c_ast_t *to_ast;
  c_cast_kind_t kind;
};




struct c_concept_ast {



  _Alignas(c_ast_t*) char unused_288[ sizeof(c_ast_t*) ];
  _Alignas(unsigned) char unused_289[ sizeof(unsigned) ];


  c_sname_t concept_sname;
};







struct c_constructor_ast {



  _Alignas(c_ast_t*) char unused_305[ sizeof(c_ast_t*) ];


  c_ast_list_t param_ast_list;
};







struct c_csu_ast {




  _Alignas(c_ast_t*) char unused_322[ sizeof(c_ast_t*) ];
  _Alignas(unsigned) char unused_323[ sizeof(unsigned) ];


  c_sname_t csu_sname;
};







struct c_enum_ast {
  c_ast_t *of_ast;
  unsigned bit_width;
  c_sname_t enum_sname;
};




struct c_function_ast {
  c_ast_t *ret_ast;
  c_ast_list_t param_ast_list;
  c_func_member_t member;
};







struct c_lambda_ast {
  c_ast_t *ret_ast;
  c_ast_list_t param_ast_list;
  c_ast_list_t capture_ast_list;
};
# 370 "c_ast.h"
struct c_name_ast {



  _Alignas(c_ast_t*) char unused_374[ sizeof(c_ast_t*) ];
  _Alignas(unsigned) char unused_375[ sizeof(unsigned) ];


  c_sname_t sname;
};







struct c_operator_ast {
  c_ast_t *ret_ast;
  c_ast_list_t param_ast_list;
  c_func_member_t member;
  c_operator_t const *operator;
};
# 424 "c_ast.h"
struct c_ptr_mbr_ast {
  c_ast_t *to_ast;




  _Alignas(unsigned) char unused_430[ sizeof(unsigned) ];


  c_sname_t class_sname;
};




struct c_ptr_ref_ast {
  c_ast_t *to_ast;
};




struct c_struct_bind_ast {
# 466 "c_ast.h"
  slist_t sname_list;
};
# 480 "c_ast.h"
struct c_typedef_ast {
  c_ast_t const *for_ast;
  unsigned bit_width;
};




struct c_udef_conv_ast {
  c_ast_t *to_ast;





  _Alignas(c_ast_list_t) char unused_495[ sizeof(c_ast_list_t) ];

};







struct c_udef_lit_ast {
  c_ast_t *ret_ast;
  c_ast_list_t param_ast_list;
};




struct c_ast {
  c_alignas_t align;
  unsigned depth;
  c_ast_t const *dup_from_ast;
  
# 517 "c_ast.h" 3 4
 _Bool 
# 517 "c_ast.h"
                 is_param_pack;
  c_ast_kind_t kind;
  c_loc_t loc;
  c_sname_t sname;
  c_type_t type;
  c_ast_t *parent_ast;
  c_ast_t const *param_of_ast;
  c_ast_id_t unique_id;




  union {
    c_parent_ast_t parent;
    c_array_ast_t array;
    c_bit_field_ast_t bit_field;
    c_apple_block_ast_t block;
    c_builtin_ast_t builtin;
    c_capture_ast_t capture;
    c_cast_ast_t cast;
    c_csu_ast_t csu;
    c_concept_ast_t concept;
    c_constructor_ast_t ctor;

    c_enum_ast_t enum_;
    c_function_ast_t func;
    c_lambda_ast_t lambda;
    c_name_ast_t name;
    c_operator_ast_t oper;

    c_ptr_mbr_ast_t ptr_mbr;
    c_ptr_ref_ast_t ptr_ref;
    c_struct_bind_ast_t struct_bind;
    c_typedef_ast_t tdef;
    c_udef_conv_ast_t udef_conv;
    c_udef_lit_ast_t udef_lit;

  };
};
# 576 "c_ast.h"
void c_ast_cleanup( void );
# 588 "c_ast.h"
__attribute__ ((__warn_unused_result__))
c_ast_t* c_ast_dup( c_ast_t const *ast, c_ast_list_t *node_list );
# 601 "c_ast.h"
__attribute__ ((__warn_unused_result__))

# 602 "c_ast.h" 3 4
_Bool 
# 602 "c_ast.h"
    c_ast_equal( c_ast_t const *i_ast, c_ast_t const *j_ast );
# 619 "c_ast.h"
void c_ast_free( c_ast_t *ast );
# 634 "c_ast.h"
__attribute__ ((__warn_unused_result__)) inline

# 635 "c_ast.h" 3 4
_Bool 
# 635 "c_ast.h"
    c_ast_is_orphan( c_ast_t const *ast ) {
  return ast->param_of_ast == 
# 636 "c_ast.h" 3 4
                              ((void*)0) 
# 636 "c_ast.h"
                                   &&
          (ast->parent_ast == 
# 637 "c_ast.h" 3 4
                             ((void*)0) 
# 637 "c_ast.h"
                                  || ast->parent_ast->parent.of_ast != ast);
}
# 649 "c_ast.h"
__attribute__ ((__warn_unused_result__)) inline

# 650 "c_ast.h" 3 4
_Bool 
# 650 "c_ast.h"
    c_ast_is_parent( c_ast_t const *ast ) {
  return ast != 
# 651 "c_ast.h" 3 4
               ((void*)0) 
# 651 "c_ast.h"
                    && (ast->kind & ( ( ( K_FUNCTION | K_LAMBDA | K_OPERATOR ) | K_APPLE_BLOCK | K_UDEF_CONV | K_UDEF_LIT ) | ( K_POINTER | K_POINTER_TO_MEMBER ) | ( K_REFERENCE | K_RVALUE_REFERENCE ) | K_ARRAY | K_CAST | K_ENUM )) != 0;
}
# 663 "c_ast.h"
__attribute__ ((__warn_unused_result__)) inline

# 664 "c_ast.h" 3 4
_Bool 
# 664 "c_ast.h"
    c_ast_is_referrer( c_ast_t const *ast ) {
  return ast != 
# 665 "c_ast.h" 3 4
               ((void*)0) 
# 665 "c_ast.h"
                    && (ast->kind & ( ( ( ( K_FUNCTION | K_LAMBDA | K_OPERATOR ) | K_APPLE_BLOCK | K_UDEF_CONV | K_UDEF_LIT ) | ( K_POINTER | K_POINTER_TO_MEMBER ) | ( K_REFERENCE | K_RVALUE_REFERENCE ) | K_ARRAY | K_CAST | K_ENUM ) | K_TYPEDEF )) != 0;
}
# 675 "c_ast.h"
void c_ast_list_cleanup( c_ast_list_t *list );
# 688 "c_ast.h"
void c_ast_list_set_param_of( c_ast_list_t *param_ast_list, c_ast_t *func_ast );
# 703 "c_ast.h"
__attribute__ ((__warn_unused_result__))
c_ast_t* c_ast_new( c_ast_kind_t kind, unsigned depth, c_loc_t const *loc,
                    c_ast_list_t *node_list );
# 717 "c_ast.h"
__attribute__ ((__warn_unused_result__)) inline
c_param_t const* c_ast_params( c_ast_t const *ast ) {
  
# 719 "c_ast.h" 3 4
 ((void)((
# 719 "c_ast.h"
 is_1_bit_only_in_set( ast->kind, ( ( ( K_FUNCTION | K_LAMBDA | K_OPERATOR ) | K_APPLE_BLOCK | K_UDEF_CONV | K_UDEF_LIT ) | K_CONSTRUCTOR | K_DESTRUCTOR ) )
# 719 "c_ast.h" 3 4
 ) || (__assert_fail(
# 719 "c_ast.h"
 "is_1_bit_only_in_set( ast->kind, K_ANY_FUNCTION_LIKE )"
# 719 "c_ast.h" 3 4
 , "c_ast.h", 719, __func__),0)))
# 719 "c_ast.h"
                                                                 ;
  return ast->func.param_ast_list.head;
}
# 730 "c_ast.h"
void c_ast_set_parameter_pack( c_ast_t *ast );
# 744 "c_ast.h"
void c_ast_set_parent( c_ast_t *child_ast, c_ast_t *parent_ast );
# 758 "c_ast.h"

c_ast_t const* c_ast_visit( c_ast_t const *ast, c_ast_visit_dir_t dir,
                            c_ast_visit_fn_t visit_fn, user_data_t user_data );
# 771 "c_ast.h"
__attribute__ ((__warn_unused_result__)) inline
c_ast_t const* c_capture_ast( c_capture_t const *capture ) {
  return capture != 
# 773 "c_ast.h" 3 4
                   ((void*)0) 
# 773 "c_ast.h"
                        ? capture->data : 
# 773 "c_ast.h" 3 4
                                          ((void*)0)
# 773 "c_ast.h"
                                              ;
}
# 787 "c_ast.h"
__attribute__ ((__warn_unused_result__)) inline
c_ast_t const* c_param_ast( c_param_t const *param ) {
  return param != 
# 789 "c_ast.h" 3 4
                 ((void*)0) 
# 789 "c_ast.h"
                      ? param->data : 
# 789 "c_ast.h" 3 4
                                      ((void*)0)
# 789 "c_ast.h"
                                          ;
}






# 30 "cdecl.c" 2
# 1 "c_keyword.h" 1
# 34 "c_keyword.h"
# 1 "cdecl_parser.h" 1
# 35 "cdecl_parser.h"
# 1 "parser.h" 1
# 45 "parser.h"
extern int yydebug;





  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,
    YYerror = 256,
    YYUNDEF = 257,
    Y_cast = 258,
    Y_constant = 259,
    Y_declare = 260,
    Y_define = 261,
    Y_dynamic = 262,
    Y_explain = 263,
    Y_no = 264,
    Y_quit = 265,
    Y_reinterpret = 266,
    Y_set = 267,
    Y_show = 268,
    Y_aligned = 269,
    Y_all = 270,
    Y_array = 271,
    Y_as = 272,
    Y_binding = 273,
    Y_bit = 274,
    Y_bit_precise = 275,
    Y_bits = 276,
    Y_by = 277,
    Y_bytes = 278,
    Y_capturing = 279,
    Y_commands = 280,
    Y_constructor = 281,
    Y_conversion = 282,
    Y_copy = 283,
    Y_defined = 284,
    Y_destructor = 285,
    Y_english = 286,
    Y_evaluation = 287,
    Y_expand = 288,
    Y_expression = 289,
    Y_floating = 290,
    Y_function = 291,
    Y_initialization = 292,
    Y_into = 293,
    Y_lambda = 294,
    Y_length = 295,
    Y_linkage = 296,
    Y_literal = 297,
    Y_macros = 298,
    Y_member = 299,
    Y_non_empty = 300,
    Y_non_member = 301,
    Y_of = 302,
    Y_options = 303,
    Y_point = 304,
    Y_pointer = 305,
    Y_precise = 306,
    Y_precision = 307,
    Y_predefined = 308,
    Y_pure = 309,
    Y_reference = 310,
    Y_returning = 311,
    Y_rvalue = 312,
    Y_scope = 313,
    Y_structured = 314,
    Y_to = 315,
    Y_user = 316,
    Y_user_defined = 317,
    Y_variable = 318,
    Y_wide = 319,
    Y_width = 320,
    Y_PREC_LESS_THAN_upc_layout_qualifier = 321,
    Y_COLON_COLON = 322,
    Y_COLON_COLON_STAR = 324,
    Y_PLUS_PLUS = 325,
    Y_MINUS_MINUS = 326,
    Y_MINUS_GREATER = 327,
    Y_sizeof = 329,
    Y_DOT_STAR = 330,
    Y_MINUS_GREATER_STAR = 332,
    Y_LESS_LESS = 334,
    Y_GREATER_GREATER = 336,
    Y_LESS_EQUAL_GREATER = 338,
    Y_LESS_EQUAL = 340,
    Y_GREATER_EQUAL = 342,
    Y_EQUAL_EQUAL = 344,
    Y_EXCLAM_EQUAL = 346,
    Y_bit_and = 347,
    Y_AMPER_AMPER = 348,
    Y_PIPE_PIPE = 349,
    Y_QMARK_COLON = 350,
    Y_PERCENT_EQUAL = 352,
    Y_AMPER_EQUAL = 354,
    Y_STAR_EQUAL = 355,
    Y_PLUS_EQUAL = 357,
    Y_MINUS_EQUAL = 359,
    Y_SLASH_EQUAL = 361,
    Y_LESS_LESS_EQUAL = 363,
    Y_GREATER_GREATER_EQUAL = 365,
    Y_CARET_EQUAL = 367,
    Y_PIPE_EQUAL = 368,
    Y_auto_STORAGE = 369,
    Y_break = 370,
    Y_case = 371,
    Y_char = 372,
    Y_continue = 373,
    Y_default = 374,
    Y_do = 375,
    Y_double = 376,
    Y_else = 377,
    Y_extern = 378,
    Y_float = 379,
    Y_for = 380,
    Y_goto = 381,
    Y_if = 382,
    Y_int = 383,
    Y_long = 384,
    Y_register = 385,
    Y_return = 386,
    Y_short = 387,
    Y_static = 388,
    Y_struct = 389,
    Y_switch = 390,
    Y_typedef = 391,
    Y_union = 392,
    Y_unsigned = 393,
    Y_while = 394,
    Y_PRE_CONCAT = 395,
    Y_PRE_SPACE = 396,
    Y_PRE_define = 397,
    Y_PRE_elif = 398,
    Y_PRE_else = 399,
    Y_PRE_error = 400,
    Y_PRE_if = 401,
    Y_PRE_ifdef = 402,
    Y_PRE_ifndef = 403,
    Y_PRE_line = 404,
    Y_PRE_undef = 405,
    Y_PRE___VA_ARGS__ = 406,
    Y_PRE___VA_OPT__ = 407,
    Y_PRE_pragma = 408,
    Y_PRE_elifdef = 409,
    Y_PRE_elifndef = 410,
    Y_PRE_embed = 411,
    Y_PRE_warning = 412,
    Y_asm = 413,
    Y_const = 414,
    Y_ELLIPSIS = 415,
    Y_enum = 416,
    Y_signed = 417,
    Y_void = 418,
    Y_volatile = 419,
    Y_wchar_t = 420,
    Y__Bool = 421,
    Y__Complex = 422,
    Y__Imaginary = 423,
    Y_inline = 424,
    Y_restrict = 425,
    Y__Alignas = 426,
    Y__Alignof = 427,
    Y__Atomic_QUAL = 428,
    Y__Atomic_SPEC = 429,
    Y__Generic = 430,
    Y__Noreturn = 431,
    Y__Static_assert = 432,
    Y__Thread_local = 433,
    Y_thread = 434,
    Y_local = 435,
    Y_bool = 436,
    Y_catch = 437,
    Y_class = 438,
    Y_const_cast = 439,
    Y_CONSTRUCTOR_SNAME = 440,
    Y_delete = 441,
    Y_DESTRUCTOR_SNAME = 442,
    Y_dynamic_cast = 443,
    Y_explicit = 444,
    Y_false = 445,
    Y_friend = 446,
    Y_mutable = 447,
    Y_namespace = 448,
    Y_new = 449,
    Y_operator = 450,
    Y_OPERATOR_SNAME = 451,
    Y_private = 452,
    Y_protected = 453,
    Y_public = 454,
    Y_reinterpret_cast = 455,
    Y_static_cast = 456,
    Y_template = 457,
    Y_this = 458,
    Y_throw = 459,
    Y_true = 460,
    Y_try = 461,
    Y_typeid = 462,
    Y_typename = 463,
    Y_using = 464,
    Y_virtual = 465,
    Y_char16_t = 466,
    Y_char32_t = 467,
    Y__BitInt = 468,
    Y_reproducible = 469,
    Y_typeof = 470,
    Y_typeof_unqual = 471,
    Y_unsequenced = 472,
    Y_ATTR_BEGIN = 473,
    Y_auto_TYPE = 474,
    Y_alignas = 475,
    Y_alignof = 476,
    Y_carries = 477,
    Y_dependency = 478,
    Y_carries_dependency = 479,
    Y_constexpr = 480,
    Y_decltype = 481,
    Y_except = 482,
    Y_final = 483,
    Y_noexcept = 484,
    Y_nullptr = 485,
    Y_override = 486,
    Y_static_assert = 487,
    Y_thread_local = 488,
    Y_deprecated = 489,
    Y_auto_STRUCTURED_BINDING = 490,
    Y_discard = 491,
    Y_maybe_unused = 492,
    Y_maybe = 493,
    Y_unused = 494,
    Y_nodiscard = 495,
    Y_noreturn = 496,
    Y_char8_t = 497,
    Y_concept = 498,
    Y_consteval = 499,
    Y_constinit = 500,
    Y_co_await = 501,
    Y_co_return = 502,
    Y_co_yield = 503,
    Y_export = 504,
    Y_no_unique_address = 505,
    Y_parameter = 506,
    Y_pack = 507,
    Y_requires = 508,
    Y_unique = 509,
    Y_address = 510,
    Y_EMC__Accum = 511,
    Y_EMC__Fract = 512,
    Y_EMC__Sat = 513,
    Y_UPC_relaxed = 514,
    Y_UPC_shared = 515,
    Y_UPC_strict = 516,
    Y_GNU___attribute__ = 517,
    Y_GNU___restrict = 518,
    Y_Apple___block = 519,
    Y_Apple_block = 520,
    Y_MSC___cdecl = 521,
    Y_MSC___clrcall = 522,
    Y_MSC___declspec = 523,
    Y_MSC___fastcall = 524,
    Y_MSC___stdcall = 525,
    Y_MSC___thiscall = 526,
    Y_MSC___vectorcall = 527,
    Y_CHAR_LIT = 528,
    Y_CONCEPT_SNAME = 529,
    Y_END = 530,
    Y_ERROR = 531,
    Y_FLOAT_LIT = 532,
    Y_GLOB = 533,
    Y_INT_LIT = 534,
    Y_NAME = 535,
    Y_SET_OPTION = 536,
    Y_STR_LIT = 537,
    Y_TYPEDEF_NAME_TDEF = 538,
    Y_TYPEDEF_SNAME_TDEF = 539,
    Y_LEXER_ERROR = 540
  };
  typedef enum yytokentype yytoken_kind_t;




union YYSTYPE
{
# 1314 "parser.y"

  c_alignas_t align;
  c_ast_t *ast;
  c_ast_list_t ast_list;
  c_ast_pair_t ast_pair;
  c_cast_kind_t cast_kind;
  
# 1320 "parser.y" 3 4
 _Bool 
# 1320 "parser.y"
                     flag;
  unsigned flags;
  char const *literal;
  int int_val;
  char *name;
  c_func_member_t member;
  c_op_id_t op_id;
  p_arg_list_t *p_arg_list;
  p_param_t *p_param;
  p_param_list_t *p_param_list;
  p_token_t *p_token;
  p_token_list_t *p_token_list;
  void *ptrs[2];
  cdecl_show_t show;
  c_sname_t sname;
  slist_t sname_list;
  char *str_val;
  c_typedef_t const *tdef;
  c_tid_t tid;
  c_type_t type;
  unsigned uint_val;
# 360 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# 382 "parser.h"
extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);
# 36 "cdecl_parser.h" 2



# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 40 "cdecl_parser.h" 2
# 53 "cdecl_parser.h"
void parser_init( void );
# 62 "cdecl_parser.h"
__attribute__ ((__warn_unused_result__))

# 63 "cdecl_parser.h" 3 4
_Bool 
# 63 "cdecl_parser.h"
    yyparse_sn( char const *s, size_t s_len );
# 35 "c_keyword.h" 2
# 63 "c_keyword.h"
enum c_keyword_ctx {
  C_KW_CTX_DEFAULT,
  C_KW_CTX_ATTRIBUTE,
  C_KW_CTX_MBR_FUNC
};
typedef enum c_keyword_ctx c_keyword_ctx_t;




struct c_keyword {
  char const *literal;
  yytoken_kind_t y_token_id;
  c_keyword_ctx_t kw_ctx;
  c_tid_t tid;
  c_lang_id_t lang_ids;
# 103 "c_keyword.h"
};
typedef struct c_keyword c_keyword_t;
# 119 "c_keyword.h"
__attribute__ ((__warn_unused_result__))
c_keyword_t const* c_keyword_find( char const *literal, c_lang_id_t lang_ids,
                                   c_keyword_ctx_t kw_ctx );
# 136 "c_keyword.h"
__attribute__ ((__warn_unused_result__))
c_keyword_t const* c_keyword_next( c_keyword_t const *k );






void c_keywords_init( void );
# 31 "cdecl.c" 2
# 1 "c_typedef.h" 1
# 32 "c_typedef.h"
# 1 "red_black.h" 1
# 40 "red_black.h"

# 61 "red_black.h"
enum rb_color {
  RB_BLACK,
  RB_RED
};



typedef enum rb_color rb_color_t;
typedef struct rb_insert_rv rb_insert_rv_t;
typedef struct rb_node rb_node_t;
typedef struct rb_tree rb_tree_t;
# 83 "red_black.h"
typedef int (*rb_cmp_fn_t)( void const *i_data, void const *j_data );







typedef void (*rb_free_fn_t)( void *data );
# 101 "red_black.h"
typedef 
# 101 "red_black.h" 3 4
       _Bool 
# 101 "red_black.h"
            (*rb_visit_fn_t)( void *node_data, void *v_data );
# 111 "red_black.h"
struct rb_node {
# 128 "red_black.h"
  void *data;

  rb_node_t *child[2];
  rb_node_t *parent;
  rb_color_t color;
};







struct rb_tree {



  rb_node_t *root;
# 162 "red_black.h"
  rb_node_t nil;






  rb_cmp_fn_t cmp_fn;
};




struct rb_insert_rv {
# 185 "red_black.h"
  rb_node_t *node;






  
# 192 "red_black.h" 3 4
 _Bool 
# 192 "red_black.h"
      inserted;
};
# 208 "red_black.h"
void rb_tree_cleanup( rb_tree_t *tree, rb_free_fn_t free_fn );
# 220 "red_black.h"
__attribute__ ((__warn_unused_result__))
void* rb_tree_delete( rb_tree_t *tree, rb_node_t *node );







__attribute__ ((__warn_unused_result__)) inline

# 230 "red_black.h" 3 4
_Bool 
# 230 "red_black.h"
    rb_tree_empty( rb_tree_t const *tree ) {
  return tree->root == &tree->nil;
}
# 247 "red_black.h"
__attribute__ ((__warn_unused_result__))
rb_node_t* rb_tree_find( rb_tree_t const *tree, void const *data );
# 258 "red_black.h"
void rb_tree_init( rb_tree_t *tree, rb_cmp_fn_t cmp_fn );
# 277 "red_black.h"
__attribute__ ((__warn_unused_result__))
rb_insert_rv_t rb_tree_insert( rb_tree_t *tree, void *data );
# 294 "red_black.h"

rb_node_t* rb_tree_visit( rb_tree_t const *tree, rb_visit_fn_t visit_fn,
                          void *v_data );






# 33 "c_typedef.h" 2
# 63 "c_typedef.h"
struct c_typedef {
  c_ast_t const *ast;
  c_lang_id_t lang_ids;
  decl_flags_t decl_flags;
  
# 67 "c_typedef.h" 3 4
 _Bool 
# 67 "c_typedef.h"
                 is_predefined;
};
# 79 "c_typedef.h"
typedef 
# 79 "c_typedef.h" 3 4
       _Bool 
# 79 "c_typedef.h"
            (*c_typedef_visit_fn_t)( c_typedef_t const *tdef, void *v_data );
# 98 "c_typedef.h"
__attribute__ ((__warn_unused_result__))
rb_node_t* c_typedef_add( c_ast_t const *type_ast, decl_flags_t decl_flags );
# 110 "c_typedef.h"
__attribute__ ((__warn_unused_result__))
c_typedef_t const* c_typedef_find_name( char const *name );
# 122 "c_typedef.h"
__attribute__ ((__warn_unused_result__))
c_typedef_t const* c_typedef_find_sname( c_sname_t const *sname );
# 134 "c_typedef.h"
__attribute__ ((__warn_unused_result__))
c_typedef_t* c_typedef_remove( rb_node_t *node );







void c_typedef_visit( c_typedef_visit_fn_t visit_fn, void *v_data );






void c_typedefs_init( void );
# 32 "cdecl.c" 2
# 1 "cdecl_command.h" 1
# 34 "cdecl_command.h"
# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 35 "cdecl_command.h" 2
# 51 "cdecl_command.h"
enum cdecl_command_kind {







  CDECL_COMMAND_LANG_ONLY,







  CDECL_COMMAND_FIRST_ARG,
# 77 "cdecl_command.h"
  CDECL_COMMAND_PROG_NAME,
};
typedef enum cdecl_command_kind cdecl_command_kind_t;




struct cdecl_command {
  char const *literal;
  cdecl_command_kind_t kind;
  c_lang_id_t lang_ids;



};
typedef struct cdecl_command cdecl_command_t;
# 103 "cdecl_command.h"
__attribute__ ((__warn_unused_result__))
cdecl_command_t const* cdecl_command_find( char const *s );
# 118 "cdecl_command.h"
__attribute__ ((__warn_unused_result__))
cdecl_command_t const* cdecl_command_next( cdecl_command_t const *command );
# 33 "cdecl.c" 2
# 1 "cdecl_keyword.h" 1
# 63 "cdecl_keyword.h"
struct cdecl_keyword {
  char const *literal;






  c_lang_id_t lang_ids;

  
# 73 "cdecl_keyword.h" 3 4
 _Bool 
# 73 "cdecl_keyword.h"
                     always_find;




  yytoken_kind_t y_token_id;
# 89 "cdecl_keyword.h"
  c_lang_lit_t const *lang_syn;
# 100 "cdecl_keyword.h"
};
typedef struct cdecl_keyword cdecl_keyword_t;
# 112 "cdecl_keyword.h"
__attribute__ ((__warn_unused_result__))
cdecl_keyword_t const* cdecl_keyword_find( char const *literal );
# 127 "cdecl_keyword.h"
__attribute__ ((__warn_unused_result__))
cdecl_keyword_t const* cdecl_keyword_next( cdecl_keyword_t const *k );






void cdecl_keywords_init( void );
# 34 "cdecl.c" 2
# 1 "cdecl_term.h" 1
# 45 "cdecl_term.h"
void cdecl_term_init( void );






__attribute__ ((__warn_unused_result__))
unsigned term_get_columns( void );
# 35 "cdecl.c" 2
# 1 "cli_options.h" 1
# 38 "cli_options.h"
# 1 "../lib/getopt.h" 1
# 25 "../lib/getopt.h"
       
# 26 "../lib/getopt.h" 3
# 34 "../lib/getopt.h" 3
# 1 "/usr/include/getopt.h" 1 3 4








# 8 "/usr/include/getopt.h" 3 4
int 
# 8 "/usr/include/getopt.h"
   rpl_getopt
# 8 "/usr/include/getopt.h" 3 4
         (int, char * const [], const char *);
extern char *
# 9 "/usr/include/getopt.h"
            rpl_optarg
# 9 "/usr/include/getopt.h" 3 4
                  ;
extern int 
# 10 "/usr/include/getopt.h"
          rpl_optind
# 10 "/usr/include/getopt.h" 3 4
                , 
# 10 "/usr/include/getopt.h"
                  rpl_opterr
# 10 "/usr/include/getopt.h" 3 4
                        , 
# 10 "/usr/include/getopt.h"
                          rpl_optopt
# 10 "/usr/include/getopt.h" 3 4
                                , optreset;

struct option {
 const char *name;
 int has_arg;
 int *flag;
 int val;
};

int getopt_long(int, char *const *, const char *, const struct option *, int *);
int getopt_long_only(int, char *const *, const char *, const struct option *, int *);
# 35 "../lib/getopt.h" 2 3
# 86 "../lib/getopt.h" 3
# 1 "../lib/getopt-pfx-ext.h" 1 3
# 68 "../lib/getopt-pfx-ext.h" 3
# 1 "../lib/getopt-ext.h" 1 3
# 27 "../lib/getopt-ext.h" 3

# 50 "../lib/getopt-ext.h" 3
struct 
# 50 "../lib/getopt-ext.h"
      rpl_option

# 51 "../lib/getopt-ext.h" 3
{
  const char *name;


  int has_arg;
  int *flag;
  int val;
};







extern int 
# 66 "../lib/getopt-ext.h"
          rpl_getopt_long 
# 66 "../lib/getopt-ext.h" 3
                      (int ___argc, char * *___argv,
   const char *__shortopts,
          const struct 
# 68 "../lib/getopt-ext.h"
                      rpl_option 
# 68 "../lib/getopt-ext.h" 3
                             *__longopts, int *__longind)
       __attribute__ ((__nonnull__ (2, 3)));
extern int 
# 70 "../lib/getopt-ext.h"
          rpl_getopt_long_only 
# 70 "../lib/getopt-ext.h" 3
                           (int ___argc, char * *___argv,
        const char *__shortopts,
               const struct 
# 72 "../lib/getopt-ext.h"
                           rpl_option 
# 72 "../lib/getopt-ext.h" 3
                                  *__longopts, int *__longind)
       __attribute__ ((__nonnull__ (2, 3)));


# 69 "../lib/getopt-pfx-ext.h" 2 3
# 87 "../lib/getopt.h" 2 3
# 39 "cli_options.h" 2
# 79 "cli_options.h"

# 79 "cli_options.h"
__attribute__ ((__warn_unused_result__))
struct rpl_option const* cli_option_next( struct rpl_option const *opt );
# 92 "cli_options.h"
void cli_options_init( int *const pargc, char const *const *pargv[const] );
# 36 "cdecl.c" 2

# 1 "config_file.h" 1
# 47 "config_file.h"
void config_init( void );
# 38 "cdecl.c" 2
# 1 "lexer.h" 1
# 40 "lexer.h"
# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 41 "lexer.h" 2
# 1 "../lib/stdio.h" 1
# 20 "../lib/stdio.h"
       
# 21 "../lib/stdio.h" 3
# 42 "lexer.h" 2


# 64 "lexer.h"
enum lexer_find_kind {



  LEXER_FIND_ANY = ~0,




  LEXER_FIND_C_KEYWORDS = (1 << 0),
# 85 "lexer.h"
  LEXER_FIND_CDECL_KEYWORDS = (1 << 1),




  LEXER_FIND_TYPES = (1 << 2)
};
typedef enum lexer_find_kind lexer_find_kind_t;
# 111 "lexer.h"
extern lexer_find_kind_t lexer_find;





extern 
# 117 "lexer.h" 3 4
      _Bool 
# 117 "lexer.h"
                         lexer_is_param_list_decl;




extern c_keyword_ctx_t lexer_keyword_ctx;


#pragma GCC diagnostic push



#pragma GCC diagnostic ignored "-Wredundant-decls"





extern int yylineno;







extern char *yytext;


#pragma GCC diagnostic pop
# 160 "lexer.h"
__attribute__ ((__warn_unused_result__)) inline

# 161 "lexer.h" 3 4
_Bool 
# 161 "lexer.h"
    is_english_to_gibberish( void ) {
  return (lexer_find & LEXER_FIND_CDECL_KEYWORDS) != 0;
}
# 173 "lexer.h"
__attribute__ ((__warn_unused_result__)) inline

# 174 "lexer.h" 3 4
_Bool 
# 174 "lexer.h"
    is_gibberish_to_english( void ) {
  return !is_english_to_gibberish();
}






void lexer_init( void );







__attribute__ ((__warn_unused_result__))
char const* lexer_input_line( size_t *rv_len );






__attribute__ ((__warn_unused_result__))
c_loc_t lexer_loc( void );
# 214 "lexer.h"
void lexer_push_string( char const *s, size_t s_len, c_loc_num_t line_no );






void lexer_pop_string( void );







void lexer_reset( 
# 229 "lexer.h" 3 4
                 _Bool 
# 229 "lexer.h"
                      hard_reset );







__attribute__ ((__warn_unused_result__))
char const* printable_yytext( void );
# 248 "lexer.h"
inline
void set_yytext( char const *s ) {
  yytext = ((char*)(s));
}
# 260 "lexer.h"
__attribute__ ((__warn_unused_result__))
int yylex( void );


#pragma GCC diagnostic push



#pragma GCC diagnostic ignored "-Wredundant-decls"
# 278 "lexer.h"
void yyrestart( FILE *in_file );


#pragma GCC diagnostic pop







# 39 "cdecl.c" 2

# 1 "p_keyword.h" 1
# 45 "p_keyword.h"
struct p_keyword {
  char const *literal;
  yytoken_kind_t y_token_id;
};
typedef struct p_keyword p_keyword_t;
# 61 "p_keyword.h"
__attribute__ ((__warn_unused_result__))
p_keyword_t const* p_keyword_find( char const *literal );






void p_keywords_init( void );
# 41 "cdecl.c" 2
# 1 "p_macro.h" 1
# 37 "p_macro.h"
# 1 "../lib/stdio.h" 1
# 20 "../lib/stdio.h"
       
# 21 "../lib/stdio.h" 3
# 38 "p_macro.h" 2


# 61 "p_macro.h"
typedef c_lang_id_t (*p_macro_dyn_fn_t)( p_token_t **ptoken );
# 72 "p_macro.h"
typedef 
# 72 "p_macro.h" 3 4
       _Bool 
# 72 "p_macro.h"
            (*p_macro_visit_fn_t)( p_macro_t const *macro, void *v_data );






struct p_param {
  char const *name;
  c_loc_t loc;
};




struct p_macro {
  char const *name;







  
# 96 "p_macro.h" 3 4
 _Bool 
# 96 "p_macro.h"
                     is_dynamic;




  union {
    p_macro_dyn_fn_t dyn_fn;




    struct {







      p_param_list_t *param_list;

      p_token_list_t replace_list;
    };
  };
};
# 134 "p_macro.h"
__attribute__ ((__warn_unused_result__))

# 135 "p_macro.h" 3 4
_Bool 
# 135 "p_macro.h"
    is_predefined_macro_name( char const *name );






void p_arg_list_cleanup( p_arg_list_t *arg_list );
# 158 "p_macro.h"
__attribute__ ((__warn_unused_result__))
p_macro_t* p_macro_define( char *name, c_loc_t const *name_loc,
                           p_param_list_t *param_list,
                           p_token_list_t *replace_list );
# 174 "p_macro.h"
__attribute__ ((__warn_unused_result__))

# 175 "p_macro.h" 3 4
_Bool 
# 175 "p_macro.h"
    p_macro_expand( char const *name, c_loc_t const *name_loc,
                     p_arg_list_t *arg_list, p_token_list_t *extra_list,
                     FILE *fout );
# 186 "p_macro.h"
__attribute__ ((__warn_unused_result__))
p_macro_t const* p_macro_find( char const *name );







__attribute__ ((__warn_unused_result__)) inline

# 196 "p_macro.h" 3 4
_Bool 
# 196 "p_macro.h"
    p_macro_is_func_like( p_macro_t const *macro ) {
  return !macro->is_dynamic && macro->param_list != 
# 197 "p_macro.h" 3 4
                                                   ((void*)0)
# 197 "p_macro.h"
                                                       ;
}
# 209 "p_macro.h"
__attribute__ ((__warn_unused_result__))

# 210 "p_macro.h" 3 4
_Bool 
# 210 "p_macro.h"
    p_macro_undef( char const *name, c_loc_t const *name_loc );







void p_macro_visit( p_macro_visit_fn_t visit_fn, void *v_data );






void p_macros_init( void );
# 234 "p_macro.h"
void p_param_free( p_param_t *param );
# 244 "p_macro.h"
void p_param_list_cleanup( p_param_list_t *param_list );






# 42 "cdecl.c" 2
# 1 "parse.h" 1
# 35 "parse.h"
# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 36 "parse.h" 2
# 1 "../lib/stdio.h" 1
# 20 "../lib/stdio.h"
       
# 21 "../lib/stdio.h" 3
# 37 "parse.h" 2
# 61 "parse.h"
__attribute__ ((__warn_unused_result__))
int cdecl_parse_cli( size_t cli_count, char const *const cli_value[const] );
# 71 "parse.h"
__attribute__ ((__warn_unused_result__))
int cdecl_parse_file( FILE *fin );
# 84 "parse.h"
__attribute__ ((__warn_unused_result__))
int cdecl_parse_string( char const *s, size_t s_len );
# 43 "cdecl.c" 2





# 1 "../lib/stddef.h" 1
# 27 "../lib/stddef.h"
       
# 28 "../lib/stddef.h" 3
# 49 "cdecl.c" 2
# 1 "../lib/stdlib.h" 1
# 20 "../lib/stdlib.h"
       
# 21 "../lib/stdlib.h" 3
# 50 "cdecl.c" 2
# 60 "cdecl.c"

# 60 "cdecl.c" 3 4
_Bool 
# 60 "cdecl.c"
           cdecl_is_initialized;
char const *cdecl_input_path;

# 62 "cdecl.c" 3 4
_Bool 
# 62 "cdecl.c"
           cdecl_is_interactive;

# 63 "cdecl.c" 3 4
_Bool 
# 63 "cdecl.c"
           cdecl_is_testing;
char const *me;
# 73 "cdecl.c"
static void cdecl_cleanup( void ) {
  c_ast_cleanup();
}



void cdecl_quit( void ) {
  exit( 
# 80 "cdecl.c" 3 4
       0 
# 80 "cdecl.c"
             );
}


# 83 "cdecl.c" 3 4
_Bool 
# 83 "cdecl.c"
    is_cppdecl( void ) {
  static char const *const NAMES[] = {
    "c++decl",
    "cppdecl",
    "cxxdecl"
  };

  for ( char const* const *name = (NAMES); name < (NAMES) + ( sizeof( ((NAMES)) ) / sizeof(0[ ((NAMES)) ]) * (!!sizeof( struct { 
# 90 "cdecl.c" 3 4
 _Static_assert
# 90 "cdecl.c"
 ( (_Generic( &(((NAMES))), typeof(*(((NAMES)))) (*)[]: 1, default : 0 )), "(NAMES)" " must be an array" ); char c; } ))); ++name ) {
    if ( strcmp( me, *name ) == 0 )
      return 
# 92 "cdecl.c" 3 4
            1
# 92 "cdecl.c"
                ;
  }
  return 
# 94 "cdecl.c" 3 4
        0
# 94 "cdecl.c"
             ;
}
# 104 "cdecl.c"
int main( int argc, char const *const argv[] ) {
  me = base_name( argv[0] );
  do { if ( __builtin_expect( !!((atexit( (&cdecl_cleanup) ) != 0)), 0 ) ) perror_exit( (
# 106 "cdecl.c" 3 4
 71
# 106 "cdecl.c"
 ) ); } while (0);
  cdecl_is_testing = str_is_affirmative( getenv( "CDECL_TEST" ) );
  if ( str_is_affirmative( getenv( "CDECL_DEBUG" ) ) )
    wait_for_debugger_attach();

  cli_options_init( &argc, &argv );
  colors_init();
  cdecl_term_init();


  c_keywords_init();
  cdecl_keywords_init();
  lexer_init();
  parser_init();
  p_keywords_init();
  p_macros_init();



  c_typedefs_init();

  if ( opt_read_config )
    config_init();

  cdecl_is_initialized = 
# 130 "cdecl.c" 3 4
                        1
# 130 "cdecl.c"
                            ;



  return cdecl_parse_cli( ((size_t)(argc)), argv );
}
