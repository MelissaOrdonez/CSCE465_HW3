#!/usr/bin/env bash
set -euo pipefail

# Accept exactly one argument
if [[ "$#" -ne 1 ]]; then
	echo "Usage: run_parser.sh <file-under-inbox>"&2
	exit 1
fi

HW3_DIR="/home/melissa-ordonez/.openclaw/workspace/Documents/csce465-agentsec/hw3"
INBOX="$(realpath -e "$HW3_DIR/inbox")"
PARSER="$HW3_DIR/src/legacy_log_parser"

if [ ! -e "$1" ]; then
	echo "Error: file does not exist: $1"
	exit 1
fi

FILE="$(realpath "$1")"

if [[ "$FILE" != "$INBOX/"* ]]; then
	echo "Error: file must be inside inbox"
	exit 1
fi

if [ ! -f "$FILE" ] || [ ! -x "$PARSER" ]; then
	echo "Error: invalid file or parser"
	exit 1
fi

exec "$PARSER" "$FILE"
