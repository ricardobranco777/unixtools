#!/usr/bin/env bash

set -e

fail() {
	echo FAILED
	exit 1
}

trap fail ERR

for bin in strerror strsignal; do
	echo "Testing $bin"
	bin="./$bin"
	# Test list
	test $($bin | wc -l) -gt 30
	# Test 1
	test $($bin 1 | wc -l) -eq 1
	# Test -n
	test $($bin -n | grep -c '^[0-9])') -eq 0
	# Test sorted
	test "$($bin | sort -n)" = "$($bin)"
	# Get first & last
	first=$($bin | awk 'NR == 1 { print $2 }')
	last=$($bin | awk 'END { print $2 }')
	$bin "$first" | grep -q "$first"
	$bin "$last" | grep -q "$last"
	! $bin -n "$first" | grep -q "$first"
	! $bin -n "$last" | grep -q "$last"
	# Test errors
	! $bin 666 2>/dev/null 
	$bin 777 2>&1 | grep -q "Unknown"
done

echo PASSED
