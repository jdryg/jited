#ifndef _DIRECT_H
#define _DIRECT_H

#ifdef _WIN32
int _chdir(char* path);
int _chdrive(int drive);
char* _getcwd(char* buffer, size_t length);
int _getdrive(void);
int _mkdir(const char* pathname);
int _rmdir(const char* pathname);

// POSIX
#define chdir _chdir
#define getcwd _getcwd
#define mkdir _mkdir
#define rmdir _rmdir
#endif

#endif // _DIRECT_H
