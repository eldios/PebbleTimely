#!/usr/bin/env sh
# Compile every C source with the SAME strict flags the repebble cloud build
# uses, so -Werror issues (e.g. discarded-qualifiers) are caught locally instead
# of in the cloud. The local `pebble build` relaxes these via
# pbl_suppress_newer_gcc_warnings(); this check does not.
#
# Requires a prior `pebble build` (it reuses the generated headers under build/).
# Run inside the dev shell:  nix develop -c sh tools/strict-check.sh
set -eu

SDK="${HOME}/.pebble-sdk/SDKs/current/sdk-core/pebble"
CC="arm-none-eabi-gcc"

# Exact cloud flag set (see a failing cloud log). -Werror with the same
# -Wno-error= relaxations; -fsyntax-only = check only, no codegen.
COMMON="-std=c99 -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections \
-fcommon -g -fPIE -Os -D_TIME_H_ -Dtime_t=long -Wall -Wextra -Werror \
-Wno-unused-parameter -Wno-error=unused-function -Wno-error=unused-variable \
-Wno-error=builtin-declaration-mismatch -Wno-error=format-truncation \
-Wno-error=expansion-to-defined -Wno-error=zero-length-bounds \
-Wno-error=cast-function-type -Wno-error=unused-value -DRELEASE -DPBL_SDK_3 \
-fsyntax-only"

# platform | UPPER | COLOR|BW | width | height
PLATFORMS="basalt:BASALT:PBL_COLOR:144:168
diorite:DIORITE:PBL_BW:144:168
emery:EMERY:PBL_COLOR:200:228
flint:FLINT:PBL_BW:144:168"

fail=0
for entry in $PLATFORMS; do
  plat=$(echo "$entry" | cut -d: -f1)
  upper=$(echo "$entry" | cut -d: -f2)
  depth=$(echo "$entry" | cut -d: -f3)
  w=$(echo "$entry" | cut -d: -f4)
  h=$(echo "$entry" | cut -d: -f5)

  if [ ! -d "build/$plat" ]; then
    echo "strict-check: build/$plat missing — run 'pebble build' first" >&2
    exit 2
  fi

  inc="-I$SDK/$plat/include -Ibuild/$plat -Ibuild/include -Ibuild/src -Isrc -Iinclude"
  defs="-DPBL_PLATFORM_$upper -D$depth -DPBL_RECT -DPBL_DISPLAY_WIDTH=$w -DPBL_DISPLAY_HEIGHT=$h"

  echo "== strict-check: $plat =="
  for f in src/*.c; do
    if ! $CC $COMMON $inc $defs "$f" 2>&1; then
      echo "strict-check: FAILED on $f ($plat)" >&2
      fail=1
    fi
  done
done

if [ "$fail" -ne 0 ]; then
  echo "strict-check: FAILED — fix the -Werror issues above before pushing to cloud." >&2
  exit 1
fi
echo "strict-check: OK (all sources compile clean under cloud flags)"
