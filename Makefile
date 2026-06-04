# Host-side unit tests for the pure modules in src/ (no Pebble SDK).
# Equivalent recipes in justfile; tools provided by the flake dev shell.
CC       ?= cc
CFLAGS   ?= -I src -I tests -Wall -Wextra -std=c11
BUILD    := build
TEST_BIN := $(BUILD)/test_suite
# All test files + the pure (Pebble-free) modules under test.
TEST_SRC := $(wildcard tests/*.c) src/timefmt.c src/layout.c src/calendar.c

.PHONY: test test-xml clean

test: $(TEST_BIN)
	$(TEST_BIN)

test-xml: $(TEST_BIN)
	$(TEST_BIN) --output=$(BUILD)/test-results.xml

$(TEST_BIN): $(TEST_SRC) $(wildcard src/*.h tests/*.h)
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN)

clean:
	rm -f $(TEST_BIN) $(BUILD)/test-results.xml
