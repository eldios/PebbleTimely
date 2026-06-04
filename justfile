# Dev tasks for TimelyNG. Equivalent recipes exist in the Makefile.
#   Host unit tests:        run inside `nix develop .#test`
#   Pebble app + emulator:  run inside `nix develop`

cc     := env_var_or_default("CC", "cc")
cflags := "-I src -I tests -Wall -Wextra -std=c11"
build  := "build"
emu    := env_var_or_default("EMU", "emery")   # aplite|basalt|chalk|diorite|emery|flint
shot   := build / ("screenshot-" + emu + ".png")
test_src := "tests/*.c src/timefmt.c src/layout.c src/calendar.c src/vibes.c"

# list the available recipes
default:
    @just --list

## ---- host unit tests ----
test: _build-tests
    ./{{build}}/test_suite

test-xml: _build-tests
    ./{{build}}/test_suite --output={{build}}/test-results.xml

_build-tests:
    mkdir -p {{build}}
    {{cc}} {{cflags}} {{test_src}} -o {{build}}/test_suite

test-clean:
    rm -f {{build}}/test_suite {{build}}/test-results.xml

## ---- Pebble app + emulator ----
# compile the .pbw
build:
    pebble build

# build + (re)install on the emulator (EMU=emery by default)
run: build
    pebble install --emulator {{emu}}

# build + install + grab a screenshot to build/screenshot-<emu>.png
shot: build
    pebble install --emulator {{emu}}
    sleep 4
    pebble screenshot {{shot}} --no-open
    @echo "saved {{shot}}"

# stream app logs from the emulator
logs:
    pebble logs --emulator {{emu}}

# stop the running emulator
kill:
    pebble kill

# pebble clean (forces SDK reconfigure)
app-clean:
    pebble clean

# install the Pebble SDK (first-time setup)
sdk:
    pebble sdk install latest
