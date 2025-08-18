CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -I.

TEST_BIN=tests/test_libIOTCAPIsT

$(TEST_BIN): libIOTCAPIsT.c tests/test_libIOTCAPIsT.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: test clean

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN)
