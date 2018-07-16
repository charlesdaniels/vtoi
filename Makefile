CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c89 -O3 -Werror

src/vtoi.o: src/vtoi.c src/vtoi.h
	$(CC) $(CFLAGS) -c -o $@ $<

test/test_vtoi: src/vtoi.o test/test_vtoi.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: run_tests
run_tests: test/test_vtoi
	cd test 2>&1 && ./test_vtoi

clean:
	rm -f src/*.o
	rm -f src/*.gch
	rm -f test/*.o
	rm -f test/*.gch
	rm test/test_vtoi
