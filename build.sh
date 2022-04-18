#!/bin/bash
echo -e "\e[3m\e[33mCompiling Program"
gcc -Wall -Werror -Wextra -pedantic -Wno-format -std=gnu89 *.c
# gcc -Wall -Werror -Wextra -pedantic -Wno-format -std=gnu99 *.c

if [[ "$?" == "0" ]]; then
	echo -e "\e[3m\e[92mCompilation \e[0m\e[92m\e[1m\e[107m DONE \e[0m"
	echo -e "\e[1m\e[92mRunning Program\e[0m"
else
	exit
fi

if [[ "$OS" == "Windows_NT" ]]; then
	"./a.exe"
else
	"./a.out"
fi
