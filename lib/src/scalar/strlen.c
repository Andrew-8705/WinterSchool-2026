#include <scalar.h>

size_t strlen_scalar(const char *str)
{
   size_t len = 0;
   while (*str != '\0') {
      len++;
      str++;
   }
   return len;
}
