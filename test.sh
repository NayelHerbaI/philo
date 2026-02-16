#!/usr/bin/env bash
set -u

BIN="${1:-./philo}"

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
NC="\033[0m"

PASS=0
FAIL=0

ok() { echo -e "${GREEN}OK${NC}  $1"; PASS=$((PASS+1)); }
ko() { echo -e "${RED}KO${NC}  $1"; FAIL=$((FAIL+1)); }

run_case() {
  local name="$1"; shift
  local expect_exit="$1"; shift          # "0" | "nonzero" | "any"
  local expect_in="$1"; shift            # regex to find (or "" to ignore)
  local forbid_in="$1"; shift            # regex to forbid (or "" to ignore)

  local out rc
  out="$("$BIN" "$@" 2>&1)"
  rc=$?

  # exit code check
  local exit_ok=0
  case "$expect_exit" in
    0)       [ "$rc" -eq 0 ] && exit_ok=1 ;;
    nonzero) [ "$rc" -ne 0 ] && exit_ok=1 ;;
    any)     exit_ok=1 ;;
    *)       exit_ok=1 ;;
  esac

  if [ "$exit_ok" -ne 1 ]; then
    ko "$name (exit=$rc, expected $expect_exit)"
    echo "  cmd: $BIN $*"
    echo "  out: ${out:-<empty>}"
    return
  fi

  # expected pattern
  if [ -n "$expect_in" ]; then
    if ! echo "$out" | grep -E -q "$expect_in"; then
      ko "$name (missing: /$expect_in/)"
      echo "  cmd: $BIN $*"
      echo "  out: ${out:-<empty>}"
      return
    fi
  fi

  # forbidden pattern
  if [ -n "$forbid_in" ]; then
    if echo "$out" | grep -E -q "$forbid_in"; then
      ko "$name (forbidden matched: /$forbid_in/)"
      echo "  cmd: $BIN $*"
      echo "  out: ${out:-<empty>}"
      return
    fi
  fi

  ok "$name"
}

echo -e "${YELLOW}..${NC} Binary: $BIN"
if [ ! -x "$BIN" ]; then
  echo -e "${RED}KO${NC}  binary not found/executable: $BIN"
  exit 1
fi

echo
echo "=== Basic argc handling ==="
run_case "no args -> error"               nonzero  "Input error|Error|usage" "" || true
run_case "too few args -> error"          nonzero  "Input error|Error|usage" "" 1 800 200 || true
run_case "too many args -> error"         nonzero  "Input error|Error|usage" "" 1 800 200 200 3 7 || true

echo
echo "=== Digits validation ==="
run_case "letter in arg -> error"         nonzero  "Input error|Error" "" 5 800 2a0 200 || true
run_case "space in arg -> error"          nonzero  "Input error|Error" "" "5" "800" "200 " "200" || true
run_case "empty string -> error"          nonzero  "Input error|Error" "" "" 800 200 200 || true

echo
echo "=== Zero / negative (should error) ==="
run_case "0 philosophers -> error"        nonzero  "Input error|Error" "" 0 800 200 200 || true
run_case "t_die=0 -> error"               nonzero  "Input error|Error" "" 5 0 200 200 || true
run_case "must_eat=0 -> error"            nonzero  "Input error|Error" "" 5 800 200 200 0 || true
# If you reject '-', this should also be an error
run_case "negative -> error"              nonzero  "Input error|Error" "" 5 -800 200 200 || true

echo
echo "=== Valid inputs (should NOT print Input error / Setup error) ==="
# Here we don't know yet if your program exits 0 immediately or keeps running,
# so we accept any exit code, but we forbid error messages.
run_case "valid (5 800 200 200)"          any      "" "Input error|Setup error|Malloc error" 5 800 200 200 || true
run_case "valid with must_eat (5 ... 3)"  any      "" "Input error|Setup error|Malloc error" 5 800 200 200 3 || true

echo
echo "=== Int range probe (if you intended INT bounds) ==="
# These will usually be rejected if you enforce int max
run_case "too big number -> error"        nonzero  "Input error|Error" "" 999999999999 800 200 200 || true
run_case "INT_MAX ok?"                    any      "" "Input error|Setup error|Malloc error" 2147483647 800 200 200 || true

echo
echo "===================="
echo -e "PASS: ${GREEN}${PASS}${NC}"
echo -e "FAIL: ${RED}${FAIL}${NC}"
echo "===================="

# return non-zero if failures
[ "$FAIL" -eq 0 ]
