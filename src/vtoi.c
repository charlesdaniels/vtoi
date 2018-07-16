#include "vtoi.h"

/**
 * @brief Parse a null-terminated string into an unsigned integer.
 *
 * @param str
 *
 * @return
 */
unsigned long vtoi_parse(vtoi_status* status, char* str) {
	unsigned int len;
	unsigned int pos;

	/* Calculate the length. We could use strlen, but this prevents
	 * adding a dependency on string.h just for strlen, and makes it
	 * easier to check against VTOI_MAX_STR. */
	len = 0;
	for (pos = 0; pos < VTOI_MAX_STR; pos++) {
		if (str[pos] == '\0') {
			/* done reading */
			break;
		}
		len ++;
	}

	/* call parse_len, since we have a length now */
	return vtoi_parse_len(status, str, len);

}

/**
 * @brief Parse a string of known length into an bit unsigned integer. The
 * string does not need to be null terminated.
 *
 * Note that the caller is expected to ensure that the length is correct - if
 * it fails to do so, the code my segfault.
 *
 * @param str
 * @param len
 *
 * @return
 */
unsigned long vtoi_parse_len(vtoi_status* status, char* str,
		unsigned int len) {

	unsigned short radix;
	unsigned long accum;
	unsigned int pos;
	unsigned int startpos;
	unsigned int exp;
	char cursor;
	unsigned int i;
	unsigned int radix_exp;

	accum = 0;

	/* make sure the string has at least one character */
	if (len < 1) {
		*status = VTOI_STATUS_TOOSHORT;
		return 0;
	}

	/* check radix */
	radix = 10; /* default to base 10 */
	startpos = 1;
	if (str[0] == VTOI_RADIX_BINARY) {
		radix = 2;
	} else if (str[0] == VTOI_RADIX_OCTAL) {
		radix = 8;
	} else if (str[0] == VTOI_RADIX_DECIMAL) {
		radix = 10;
	} else if (str[0] == VTOI_RADIX_HEX) {
		radix = 16;
	} else if (VTOI_IS_DEC_DIGIT(str[0])){
		radix = 10;
		startpos = 0; /* account for missing radix specifier */
	} else  {
		/* invalid radix, and we can't safely assume decimal */
		*status = VTOI_STATUS_INVALID_RADIX;
		return 0;
	}

	for (pos = startpos; pos < len; pos ++) {
		cursor = str[pos];
		VTOI_HEX_SQUASH(cursor);

		/* validate that the cursor is legal */
		if (radix == 2) {
			if (! VTOI_IS_BIN_DIGIT(cursor)) {
				*status = VTOI_STATUS_INVALID_CHAR;
				return 0;
			}
		} else if (radix == 8) {
			if (! VTOI_IS_OCT_DIGIT(cursor)) {
				*status = VTOI_STATUS_INVALID_CHAR;
				return 0;
			}
		} else if (radix == 10) {
			if (! VTOI_IS_DEC_DIGIT(cursor)) {
				*status = VTOI_STATUS_INVALID_CHAR;
				return 0;
			}
		} else if (radix == 16) {
			if (! VTOI_IS_HEX_DIGIT(cursor)) {
				*status = VTOI_STATUS_INVALID_CHAR;
				return 0;
			}
		} else {
			/* unknown radix, should never happen */
			*status = VTOI_STATUS_INSANITY;
			return 0;
		}

		exp = len - pos - 1;

		/* avoid having to link against math.h just for pow() */
		radix_exp = 1;
		for (i = 0; i < exp ; i++) {
			radix_exp *= radix;
		}

		/* this is logically equivalent to:
		 * cursor * radix ^ exp */
		accum += VTOI_CHAR2INT(cursor) * radix_exp;

	}

	*status = VTOI_STATUS_OK;
	return accum;

}

char* vtoi_format_hex(vtoi_status* s, unsigned long value) {
	char* buf;
	buf = (char*) malloc(sizeof(char) * (VTOI_BITS(value) / 4 + 2));
	if (buf == NULL) {
		*s = VTOI_STATUS_NOMEMORY;
		return NULL;
	}
	vtoi_sprintf(buf, "h%lX", value);
	*s = VTOI_STATUS_OK;
	return buf;
}

