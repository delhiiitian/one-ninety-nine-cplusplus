/* C++ in 199 Pages - 9.9 Calling C code
 * legacy_tax.c - plain C, compiled with a C compiler (gcc). */
#include <stdio.h>
#include "legacy_tax.h"

long gst_paise(long price_paise, int rate_percent) {
    return (price_paise * rate_percent + 50) / 100;   /* round to the nearest paisa */
}

void format_rupees(long paise, char* buffer, int buffer_size) {
    snprintf(buffer, (size_t)buffer_size, "Rs %ld.%02ld", paise / 100, paise % 100);
}
