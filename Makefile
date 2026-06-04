# Dev tasks for TimelyNG. Equivalent recipes exist in the justfile.
#   Host unit tests:        run inside `nix develop .#test`   (needs a host cc)
#   Pebble app + emulator:  run inside `nix develop`          (needs pebble CLI)

CC       ?= cc
CFLAGS   ?= -I src -I tests -Wall -Wextra -std=c11
BUILD    := build
TEST_BIN := $(BUILD)/test_suite
TEST_SRC := $(wildcard tests/*.c) src/timefmt.c src/layout.c src/calendar.c src/vibes.c src/suntimes.c src/math.c

# emulator platform: aplite | basalt | chalk | diorite | emery | flint
EMU  ?= emery
SHOT ?= $(BUILD)/screenshot-$(EMU).png

.PHONY: help test test-xml test-clean build install run shot logs kill app-clean sdk

help:
	@echo "Host tests (nix develop .#test):  test  test-xml  test-clean"
	@echo "Pebble (nix develop):             build  run  shot  logs  kill  app-clean  sdk"
	@echo "Vars: EMU=$(EMU)  SHOT=$(SHOT)"

## ---- host unit tests ----
test: $(TEST_BIN)
	$(TEST_BIN)

test-xml: $(TEST_BIN)
	$(TEST_BIN) --output=$(BUILD)/test-results.xml

$(TEST_BIN): $(TEST_SRC) $(wildcard src/*.h tests/*.h)
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN)

test-clean:
	rm -f $(TEST_BIN) $(BUILD)/test-results.xml

## ---- Pebble app + emulator ----
build:
	pebble build

run install: build          ## build + (re)install on the emulator
	pebble install --emulator $(EMU)

shot: build                 ## build + install + grab a screenshot to $(SHOT)
	pebble install --emulator $(EMU)
	sleep 4
	pebble screenshot $(SHOT) --no-open
	@echo "saved $(SHOT)"

logs:                       ## stream app logs from the emulator
	pebble logs --emulator $(EMU)

kill:                       ## stop the running emulator
	pebble kill

app-clean:                  ## pebble clean (forces SDK reconfigure)
	pebble clean

sdk:                        ## install the Pebble SDK (first-time setup)
	pebble sdk install latest
