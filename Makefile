# Host-side unit tests for the pure logic in src/ (no Pebble SDK).
# Equivalent recipes exist in the justfile. Tools provided by flake.nix dev shell.
CC       ?= cc
CFLAGS   ?= -I src -I tests -Wall -Wextra -std=c11
BUILD    := build
TEST_BIN := $(BUILD)/test_timefmt
TEST_SRC := tests/test_timefmt.c src/timefmt.c

.PHONY: test test-xml clean

test: $(TEST_BIN)
	$(TEST_BIN)

test-xml: $(TEST_BIN)
	$(TEST_BIN) --output=$(BUILD)/test-results.xml

$(TEST_BIN): $(TEST_SRC) src/timefmt.h tests/utest.h
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN)

clean:
	rm -f $(TEST_BIN) $(BUILD)/test-results.xml
