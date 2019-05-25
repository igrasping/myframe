#ifndef __MYUTILS_H__
#define __MYUTILS_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t my_random_num(int min, int max);

double my_get_time();

bool my_set_nonblock(int fd, bool b);

const char* my_get_error();

void* my_dll_open(const char* dl_path);

void* my_dll_use(void *handle, const char *symbol);

int my_dll_close(void *handle);

#ifdef __cplusplus
}
#endif

#endif // __MYUTILS_H__
