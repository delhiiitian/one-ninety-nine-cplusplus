/* C++ in 199 Pages - 9.9 Calling C code
 * legacy_tax.h - the header of an old C library. The extern "C" block lets
 * C++ files include it too; C compilers skip it because __cplusplus is not defined. */
#ifndef LEGACY_TAX_H
#define LEGACY_TAX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Returns the GST amount in paise for a price in paise at a rate in percent. */
long gst_paise(long price_paise, int rate_percent);

/* Writes a formatted amount such as "Rs 1234.50" into buffer. */
void format_rupees(long paise, char* buffer, int buffer_size);

#ifdef __cplusplus
}
#endif

#endif
