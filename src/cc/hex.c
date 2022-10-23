#include "hex.h"
#include "gmssl/hex.h"
#include <stdlib.h>

char *bytes_to_hex(const uint8_t *bytes, size_t len)
{
    char *hex = malloc(len * 2 + 1);
    if (!hex)
    {
        return NULL;
    }
    for (size_t i = 0; i < len; i++)
    {
        sprintf(hex + i * 2, "%02X", bytes[i]);
    }
    hex[len * 2] = 0;
    return hex;
}

XX_MEM *hex_to_mem(const char *hex, size_t len)
{
    XX_MEM *mem = XX_MEM_new((len + 1) / 2);
    if (!mem)
    {
        return NULL;
    }
    if (hex_to_bytes(hex, len, mem->ptr, &mem->len) != 1)
    {
        XX_MEM_free(mem);
        return NULL;
    }
    return mem;
}
