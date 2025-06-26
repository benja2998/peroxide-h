#!/usr/bin/bash

# Error if uname doesn't return Linux
if [[ "$(uname)" != "Linux" ]]; then
	echo "This script is intended for Linux systems only."
	exit 1
fi

# Check if uname -o doesn't return "Android"

if [[ "$(uname -o)" == "Android" ]]; then
	# Move ./src/peroxide.h to $PREFIX/include/peroxide.h
	
	if [[ -z "$PREFIX" ]]; then
		echo "Error: \$PREFIX is not set."
		exit 1
	fi

	if [[ -f "src/peroxide.h" ]]; then
		mkdir -p "$PREFIX/include"
		cp src/peroxide.h "$PREFIX/include/peroxide.h"
	else
		echo "Error: src/peroxide.h not found. Did you run this script from the correct directory?"
		exit 1
	fi
else
	# Check if the script is run as root
	
	if [[ $EUID -ne 0 ]]; then
		echo "This script must be run as root. Use 'sudo' to run it."
		exit 1
	fi

	# Move ./src/peroxide.h to /usr/local/include/peroxide.h
	if [[ -f "src/peroxide.h" ]]; then
		mkdir -p /usr/local/include
		cp src/peroxide.h /usr/local/include/peroxide.h
	else
		echo "Error: src/peroxide.h not found. Did you run this script from the correct directory?"
		exit 1
	fi
fi
