# Host-side unit tests for the pure modules in src/ (no Pebble SDK).
# Equivalent recipes in the Makefile; tools provided by the flake dev shell.
cc       := env_var_or_default("CC", "cc")
cflags   := "-I src -I tests -Wall -Wextra -std=c11"
build    := "build"
test_bin := build / "test_suite"
test_src := "tests/*.c src/timefmt.c src/layout.c src/calendar.c"

# build + run the unit-test suite
test: build-tests
    ./{{test_bin}}

# build + run the suite, emitting a JUnit XML report
test-xml: build-tests
    ./{{test_bin}} --output={{build}}/test-results.xml

# compile the test binary
build-tests:
    mkdir -p {{build}}
    {{cc}} {{cflags}} {{test_src}} -o {{test_bin}}

# remove host test artifacts
clean:
    rm -f {{test_bin}} {{build}}/test-results.xml
