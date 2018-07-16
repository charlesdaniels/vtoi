#include "../src/vtoi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int failed;

char* status2str(vtoi_status s) {
	if (s == VTOI_STATUS_OK) {
		return "OK";
	} else if (s == VTOI_STATUS_TOOSHORT) {
		return "TOOSHORT";
	} else if (s == VTOI_STATUS_INVALID_RADIX) {
		return "INVALID_RADIX";
	} else if (s == VTOI_STATUS_INVALID_CHAR) {
		return "INVALID_CHAR";
	} else if (s == VTOI_STATUS_INSANITY) {
		return "INSANITY";
	} else if (s == VTOI_STATUS_NOMEMORY) {
		return "NOMEMORY";
	} else {
		return "UNKNOWN";
	}
}

void test_vtoi_parse(char* str, unsigned long expected_val,
		vtoi_status expected_status) {

	vtoi_status s;
	unsigned long actual_val;

	s = VTOI_STATUS_INSANITY;

	actual_val = vtoi_parse(&s, str);

	printf("'%s' -> %lu (expected %lu), status: %s (expected %s)... ",
			str,
			actual_val,
			expected_val,
			status2str(s),
			status2str(expected_status));

	if ((actual_val == expected_val) && (s == expected_status)) { 
		printf("PASS\n");
	} else {
		printf("FAIL\n");
		failed += 1;
	}

}

void test_format_hex(unsigned long value, char* expected) {
	char* actual;
	vtoi_status s;

	actual = vtoi_format_hex(&s, value);

	printf("%lu -> '%s' (expected '%s'), status: %s... ",
			value,
			actual,
			expected,
			status2str(s));

	if (!(strcmp(actual, expected) && (s == VTOI_STATUS_OK))) {
		printf("PASS\n");
	} else{
		printf("FAIL\n");
		failed ++;
	}

}

int main() {
	failed = 0;

	/* test hex */
	test_vtoi_parse("h1", 1, VTOI_STATUS_OK);
	test_vtoi_parse("h2", 2, VTOI_STATUS_OK);
	test_vtoi_parse("h3", 3, VTOI_STATUS_OK);
	test_vtoi_parse("h4", 4, VTOI_STATUS_OK);
	test_vtoi_parse("h5", 5, VTOI_STATUS_OK);
	test_vtoi_parse("h6", 6, VTOI_STATUS_OK);
	test_vtoi_parse("h7", 7, VTOI_STATUS_OK);
	test_vtoi_parse("h8", 8, VTOI_STATUS_OK);
	test_vtoi_parse("h9", 9, VTOI_STATUS_OK);
	test_vtoi_parse("ha", 10, VTOI_STATUS_OK);
	test_vtoi_parse("hb", 11, VTOI_STATUS_OK);
	test_vtoi_parse("hc", 12, VTOI_STATUS_OK);
	test_vtoi_parse("hd", 13, VTOI_STATUS_OK);
	test_vtoi_parse("he", 14, VTOI_STATUS_OK);
	test_vtoi_parse("hf", 15, VTOI_STATUS_OK);
	test_vtoi_parse("h10", 16, VTOI_STATUS_OK);
	test_vtoi_parse("h11", 17, VTOI_STATUS_OK);
	test_vtoi_parse("h12", 18, VTOI_STATUS_OK);
	test_vtoi_parse("h13", 19, VTOI_STATUS_OK);
	test_vtoi_parse("h14", 20, VTOI_STATUS_OK);
	test_vtoi_parse("h15", 21, VTOI_STATUS_OK);
	test_vtoi_parse("h16", 22, VTOI_STATUS_OK);
	test_vtoi_parse("h17", 23, VTOI_STATUS_OK);
	test_vtoi_parse("h18", 24, VTOI_STATUS_OK);
	test_vtoi_parse("h19", 25, VTOI_STATUS_OK);
	test_vtoi_parse("h1a", 26, VTOI_STATUS_OK);
	test_vtoi_parse("h1b", 27, VTOI_STATUS_OK);
	test_vtoi_parse("h1c", 28, VTOI_STATUS_OK);
	test_vtoi_parse("h1d", 29, VTOI_STATUS_OK);
	test_vtoi_parse("h1e", 30, VTOI_STATUS_OK);
	test_vtoi_parse("h1f", 31, VTOI_STATUS_OK);

	/* test octal */
	test_vtoi_parse("o1", 1, VTOI_STATUS_OK);
	test_vtoi_parse("o2", 2, VTOI_STATUS_OK);
	test_vtoi_parse("o3", 3, VTOI_STATUS_OK);
	test_vtoi_parse("o4", 4, VTOI_STATUS_OK);
	test_vtoi_parse("o5", 5, VTOI_STATUS_OK);
	test_vtoi_parse("o6", 6, VTOI_STATUS_OK);
	test_vtoi_parse("o7", 7, VTOI_STATUS_OK);
	test_vtoi_parse("o10", 8, VTOI_STATUS_OK);
	test_vtoi_parse("o11", 9, VTOI_STATUS_OK);
	test_vtoi_parse("o12", 10, VTOI_STATUS_OK);
	test_vtoi_parse("o13", 11, VTOI_STATUS_OK);
	test_vtoi_parse("o14", 12, VTOI_STATUS_OK);
	test_vtoi_parse("o15", 13, VTOI_STATUS_OK);
	test_vtoi_parse("o16", 14, VTOI_STATUS_OK);
	test_vtoi_parse("o17", 15, VTOI_STATUS_OK);
	test_vtoi_parse("o20", 16, VTOI_STATUS_OK);
	test_vtoi_parse("o21", 17, VTOI_STATUS_OK);
	test_vtoi_parse("o22", 18, VTOI_STATUS_OK);
	test_vtoi_parse("o23", 19, VTOI_STATUS_OK);
	test_vtoi_parse("o24", 20, VTOI_STATUS_OK);
	test_vtoi_parse("o25", 21, VTOI_STATUS_OK);
	test_vtoi_parse("o26", 22, VTOI_STATUS_OK);
	test_vtoi_parse("o27", 23, VTOI_STATUS_OK);
	test_vtoi_parse("o30", 24, VTOI_STATUS_OK);
	test_vtoi_parse("o31", 25, VTOI_STATUS_OK);
	test_vtoi_parse("o32", 26, VTOI_STATUS_OK);
	test_vtoi_parse("o33", 27, VTOI_STATUS_OK);
	test_vtoi_parse("o34", 28, VTOI_STATUS_OK);
	test_vtoi_parse("o35", 29, VTOI_STATUS_OK);
	test_vtoi_parse("o36", 30, VTOI_STATUS_OK);
	test_vtoi_parse("o37", 31, VTOI_STATUS_OK);

	/* test decimal */
	test_vtoi_parse("d1", 1, VTOI_STATUS_OK);
	test_vtoi_parse("d2", 2, VTOI_STATUS_OK);
	test_vtoi_parse("d3", 3, VTOI_STATUS_OK);
	test_vtoi_parse("d4", 4, VTOI_STATUS_OK);
	test_vtoi_parse("d5", 5, VTOI_STATUS_OK);
	test_vtoi_parse("d6", 6, VTOI_STATUS_OK);
	test_vtoi_parse("d7", 7, VTOI_STATUS_OK);
	test_vtoi_parse("d8", 8, VTOI_STATUS_OK);
	test_vtoi_parse("d9", 9, VTOI_STATUS_OK);
	test_vtoi_parse("d10", 10, VTOI_STATUS_OK);
	test_vtoi_parse("d11", 11, VTOI_STATUS_OK);
	test_vtoi_parse("d12", 12, VTOI_STATUS_OK);
	test_vtoi_parse("d13", 13, VTOI_STATUS_OK);
	test_vtoi_parse("d14", 14, VTOI_STATUS_OK);
	test_vtoi_parse("d15", 15, VTOI_STATUS_OK);
	test_vtoi_parse("d16", 16, VTOI_STATUS_OK);
	test_vtoi_parse("d17", 17, VTOI_STATUS_OK);
	test_vtoi_parse("d18", 18, VTOI_STATUS_OK);
	test_vtoi_parse("d19", 19, VTOI_STATUS_OK);
	test_vtoi_parse("d20", 20, VTOI_STATUS_OK);
	test_vtoi_parse("d21", 21, VTOI_STATUS_OK);
	test_vtoi_parse("d22", 22, VTOI_STATUS_OK);
	test_vtoi_parse("d23", 23, VTOI_STATUS_OK);
	test_vtoi_parse("d24", 24, VTOI_STATUS_OK);
	test_vtoi_parse("d25", 25, VTOI_STATUS_OK);
	test_vtoi_parse("d26", 26, VTOI_STATUS_OK);
	test_vtoi_parse("d27", 27, VTOI_STATUS_OK);
	test_vtoi_parse("d28", 28, VTOI_STATUS_OK);
	test_vtoi_parse("d29", 29, VTOI_STATUS_OK);
	test_vtoi_parse("d30", 30, VTOI_STATUS_OK);
	test_vtoi_parse("d31", 31, VTOI_STATUS_OK);
	test_vtoi_parse("1", 1, VTOI_STATUS_OK);
	test_vtoi_parse("2", 2, VTOI_STATUS_OK);
	test_vtoi_parse("3", 3, VTOI_STATUS_OK);
	test_vtoi_parse("4", 4, VTOI_STATUS_OK);
	test_vtoi_parse("5", 5, VTOI_STATUS_OK);
	test_vtoi_parse("6", 6, VTOI_STATUS_OK);
	test_vtoi_parse("7", 7, VTOI_STATUS_OK);
	test_vtoi_parse("8", 8, VTOI_STATUS_OK);
	test_vtoi_parse("9", 9, VTOI_STATUS_OK);
	test_vtoi_parse("10", 10, VTOI_STATUS_OK);
	test_vtoi_parse("11", 11, VTOI_STATUS_OK);
	test_vtoi_parse("12", 12, VTOI_STATUS_OK);
	test_vtoi_parse("13", 13, VTOI_STATUS_OK);
	test_vtoi_parse("14", 14, VTOI_STATUS_OK);
	test_vtoi_parse("15", 15, VTOI_STATUS_OK);
	test_vtoi_parse("16", 16, VTOI_STATUS_OK);
	test_vtoi_parse("17", 17, VTOI_STATUS_OK);
	test_vtoi_parse("18", 18, VTOI_STATUS_OK);
	test_vtoi_parse("19", 19, VTOI_STATUS_OK);
	test_vtoi_parse("20", 20, VTOI_STATUS_OK);
	test_vtoi_parse("21", 21, VTOI_STATUS_OK);
	test_vtoi_parse("22", 22, VTOI_STATUS_OK);
	test_vtoi_parse("23", 23, VTOI_STATUS_OK);
	test_vtoi_parse("24", 24, VTOI_STATUS_OK);
	test_vtoi_parse("25", 25, VTOI_STATUS_OK);
	test_vtoi_parse("26", 26, VTOI_STATUS_OK);
	test_vtoi_parse("27", 27, VTOI_STATUS_OK);
	test_vtoi_parse("28", 28, VTOI_STATUS_OK);
	test_vtoi_parse("29", 29, VTOI_STATUS_OK);
	test_vtoi_parse("30", 30, VTOI_STATUS_OK);
	test_vtoi_parse("31", 31, VTOI_STATUS_OK);

	/* check binary */
	test_vtoi_parse("b1", 1, VTOI_STATUS_OK);
	test_vtoi_parse("b10", 2, VTOI_STATUS_OK);
	test_vtoi_parse("b11", 3, VTOI_STATUS_OK);
	test_vtoi_parse("b100", 4, VTOI_STATUS_OK);
	test_vtoi_parse("b101", 5, VTOI_STATUS_OK);
	test_vtoi_parse("b110", 6, VTOI_STATUS_OK);
	test_vtoi_parse("b111", 7, VTOI_STATUS_OK);
	test_vtoi_parse("b1000", 8, VTOI_STATUS_OK);
	test_vtoi_parse("b1001", 9, VTOI_STATUS_OK);
	test_vtoi_parse("b1010", 10, VTOI_STATUS_OK);
	test_vtoi_parse("b1011", 11, VTOI_STATUS_OK);
	test_vtoi_parse("b1100", 12, VTOI_STATUS_OK);
	test_vtoi_parse("b1101", 13, VTOI_STATUS_OK);
	test_vtoi_parse("b1110", 14, VTOI_STATUS_OK);
	test_vtoi_parse("b1111", 15, VTOI_STATUS_OK);
	test_vtoi_parse("b10000", 16, VTOI_STATUS_OK);
	test_vtoi_parse("b10001", 17, VTOI_STATUS_OK);
	test_vtoi_parse("b10010", 18, VTOI_STATUS_OK);
	test_vtoi_parse("b10011", 19, VTOI_STATUS_OK);
	test_vtoi_parse("b10100", 20, VTOI_STATUS_OK);
	test_vtoi_parse("b10101", 21, VTOI_STATUS_OK);
	test_vtoi_parse("b10110", 22, VTOI_STATUS_OK);
	test_vtoi_parse("b10111", 23, VTOI_STATUS_OK);
	test_vtoi_parse("b11000", 24, VTOI_STATUS_OK);
	test_vtoi_parse("b11001", 25, VTOI_STATUS_OK);
	test_vtoi_parse("b11010", 26, VTOI_STATUS_OK);
	test_vtoi_parse("b11011", 27, VTOI_STATUS_OK);
	test_vtoi_parse("b11100", 28, VTOI_STATUS_OK);
	test_vtoi_parse("b11101", 29, VTOI_STATUS_OK);
	test_vtoi_parse("b11110", 30, VTOI_STATUS_OK);
	test_vtoi_parse("b11111", 31, VTOI_STATUS_OK);

	/* check invalid radix detection */
	test_vtoi_parse("aaaa", 0, VTOI_STATUS_INVALID_RADIX);

	/* check invalid char detection */
	test_vtoi_parse("h...", 0, VTOI_STATUS_INVALID_CHAR);

	/* check string to short conditions */
	test_vtoi_parse("", 0, VTOI_STATUS_TOOSHORT);

	/* text hex formatting */
	test_format_hex(1, "h1");
	test_format_hex(12345, "h3039");
	test_format_hex(12345678, "hBC614E");

	printf("finished. %d test cases failed\n", failed);
	exit(failed);

}
