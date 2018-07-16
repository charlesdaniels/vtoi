#ifndef VTOI_H
#define VTOI_H

#include <stdlib.h>

typedef short int vtoi_status;

#ifndef NULL
#define NULL 0
#endif

#define VTOI_STATUS_OK 0

/* the input string was too short (must be at least 1 character) */
#define VTOI_STATUS_TOOSHORT 1

/* radix was not one of b, o, d, or h */
#define VTOI_STATUS_INVALID_RADIX 2

/* one or more invalid characters were found for the specified radix */
#define VTOI_STATUS_INVALID_CHAR 3

/* this indicates that a sanity check has failed, and that the vtoi code itself
 * may contain a fault */
#define VTOI_STATUS_INSANITY 4

/* a call to malloc() failed */
#define VTOI_STATUS_NOMEMORY 5 

#define VTOI_RADIX_BINARY 'b'
#define VTOI_RADIX_OCTAL 'o'
#define VTOI_RADIX_DECIMAL 'd'
#define VTOI_RADIX_HEX 'h'

#define VTOI_IS_BIN_DIGIT(c) ((c >= 48) && (c <= 49))
#define VTOI_IS_OCT_DIGIT(c) ((c >= 48) && (c <= 55))
#define VTOI_IS_DEC_DIGIT(c) ((c >= 48) && (c <= 57))
#define VTOI_IS_HEX_DIGIT(c) (((c >= 48) && (c <= 57)) || \
		((c >= 65) && (c <= 70)))

/* cleanup mixed-case hex to all uppercase */
#define VTOI_HEX_SQUASH(c) if (c >= 97 && c <= 102) {c -= 32;}

/* if the char is a decimal digit, we just subtract 48, otherwise it must be
 * a hex digit in the A..F range, so we subtract 65 (A=0), and add 10 (A=10) */
#define VTOI_CHAR2INT(c) ((VTOI_IS_DEC_DIGIT(c)) ? c - 48 : (c - 65) + 10)

/* If a string that is supposed to be null-terminated exceeds this length, we
 * give up and stop reading more characters. This is an important check for
 * MMU-less embedded systems where such a condition will not generate a 
 * segmentation fault. */
#define VTOI_MAX_STR 64

#define VTOI_BITS(x) (sizeof(x) * 8)

unsigned long vtoi_parse(vtoi_status* status, char* str);
unsigned long vtoi_parse_len(vtoi_status* status, char* str, unsigned int len);
char* vtoi_format_hex(vtoi_status* s, unsigned long value);

/* you may want to modify this bit if you need to use an alternative 
 * sprintf implementation (e.g. embedded systems). */
#include <stdio.h>
#define vtoi_sprintf sprintf

#endif
