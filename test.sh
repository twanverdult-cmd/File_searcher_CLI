#!/bin/sh
# Simple smoke test: creates a temp dir with files and checks that `find` can locate them.
set -e

dir=$(mktemp -d)
trap 'rm -rf "$dir"' EXIT

touch "$dir/hello.txt" "$dir/world.md"

found=$(find "$dir" -name "hello.txt")
if [ "$found" = "$dir/hello.txt" ]; then
  echo "PASS: file found"
else
  echo "FAIL: file not found"
  exit 1
fi
