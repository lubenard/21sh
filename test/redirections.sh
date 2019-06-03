#!/bin/bash

# Because we can pass argv[1] as first command, we can automate it
# Please run this script inside the executable's directory

compare_function()
{
	if cmp -s "$1" "$2"; then
		printf '\e[32mThe file "%s" is the same as "%s"\n\033[0m' "$1" "$2"
		return 0
	else
		printf '\033[31mThe file "%s" is different from "%s"\n\033[0m' "$1" "$2"
		vimdiff $1 $2
		return 1
	fi
}

pwd
rm -rf file1 compare1
make -C ../
cp ../auteur .

# Basic redirections
../21sh "cat auteur > file1"
cat auteur > compare1
compare_function file1 compare1

rm file* compare*

../21sh "cat auteur >> file1"
cat auteur >> compare1
compare_function file1 compare1

rm file* compare*

# Multiple redirections
../21sh "cat auteur > file1 >> file2"
cat auteur > compare1 >> compare2
compare_function file1 compare1
compare_function file2 compare2
