# Host-side unit tests for the pure logic in src/ (no Pebble SDK).
# Equivalent recipes exist in the Makefile. Tools provided by flake.nix dev shell.
cc       := env_var_or_default("CC", "cc")
cflags   := "-I src -I tests -Wall -Wextra -std=c11"
build    := "build"
test_bin := build / "test_timefmt"
test_src := "tests/test_timefmt.c src/timefmt.c"

# build + run the unit tests
test: build-tests
    ./{{test_bin}}

# build + run the tests, emitting a JUnit XML report
test-xml: build-tests
    ./{{test_bin}} --output={{build}}/test-results.xml

# compile the test binary
build-tests:
    mkdir -p {{build}}
    {{cc}} {{cflags}} {{test_src}} -o {{test_bin}}

# remove host test artifacts
clean:
    rm -f {{test_bin}} {{build}}/test-results.xml
