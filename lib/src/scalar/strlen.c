#include <scalar.h>

// size_t strlen_scalar(const char *str)
// {
//    size_t len = 0;
//    while (*str != '\0') {
//       len++;
//       str++;
//    }
//    return len;
// }


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define HIMAGIC 0x8080808080808080ULL
#define LOMAGIC 0x0101010101010101ULL

size_t strlen_scalar(const char *str)
{
    const char *char_ptr;
    const uint64_t *longword_ptr;
    uint64_t longword, himagic, lomagic;

    for (char_ptr = str; ((uintptr_t)char_ptr & 7) != 0; ++char_ptr) {
        if (*char_ptr == '\0')
            return char_ptr - str;
    }

    longword_ptr = (const uint64_t *)char_ptr;

    while (true) {
        longword = *longword_ptr++;

        if (((longword - LOMAGIC) & ~longword & HIMAGIC) != 0) {
            const char *cp = (const char *)(longword_ptr - 1);
            
            if (cp[0] == 0) return cp - str;
            if (cp[1] == 0) return cp - str + 1;
            if (cp[2] == 0) return cp - str + 2;
            if (cp[3] == 0) return cp - str + 3;
            if (cp[4] == 0) return cp - str + 4;
            if (cp[5] == 0) return cp - str + 5;
            if (cp[6] == 0) return cp - str + 6;
            if (cp[7] == 0) return cp - str + 7;
        }
    }
}