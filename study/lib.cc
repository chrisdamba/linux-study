// Implement kernel stubs with stdlib.
// Do not include any kernel headers
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <map>

std::map<const void*, size_t> g_sizes;

extern "C"
{

void panic(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  abort();
}

int printk(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int r = vprintf(fmt, args);
  va_end(args);
  return r;
}

void warn_slowpath_null(const char *file, const int line)
{
  printf("warn_slowpath_null %s:%d\n", file, line);
}

void* zalloc(size_t size)
{
  void* ret = malloc(size);
  bzero(ret, size);
  g_sizes[ret] = size;
  return ret;
}

size_t ksize(const void *p)
{
  return g_sizes[p];
}

uint32_t random_32 = 42;
uint32_t prandom_u32(void)
{
	return random_32;
}

}
