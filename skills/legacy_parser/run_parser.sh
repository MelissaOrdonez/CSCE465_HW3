#!/usr/bin/env bash
set -euo pipefail

# Accept exactly one argument
if [[ "$#" -ne 1 ]]; then
	echo "Usage: legacy-parser.sh <file-under-inbox>"&2
	exit 1
fi

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
HW3_DIR="$(cd -- "$SCRIPT_DIR/../../.." && pwd)"
INBOX="$(realpath -e -- "$HW3_DIR/inbox")"
PARSER="$HW3_DIR/src/legacy_log_parser"

# Resolve the supplied path and reject nonexistent files.
if ! TARGET="$(realpath -e -- "$1")"; then
	echo "Error: input file does not exist" >&2
	exit 1
fi

# Require a regular file strictly inside inbox/.
case "$TARGET" in "$INBOX"/*) ;; *)
	echo "Error: file must be inside $INBOX" >&2
	exit 1 
	;;
esac

if [[ ! -f "$Target" ]]; then
	echo "Error: input must be a regular file" >&2
	exit 1
fi

# Make sure the parser exists and is executable.
if [[ ! -x "$PARSER" ]]; then
	echo "Error: parser not found or not executable: $PARSERR" >&2
	exit 1
fi

# Pass the validated path as one argument; do not evaluate user input
exec "$PARSER" "$TARGET"
