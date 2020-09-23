#!/bin/bash
./$1 units/ka.json units/ke.json > output.txt
./$1 units/ka.json units/ki.json >> output.txt
./$1 units/ke.json units/ki.json >> output.txt

./$1 units/ke.json units/ka.json >> output.txt
./$1 units/ki.json units/ka.json >> output.txt
./$1 units/ki.json units/ke.json >> output.txt

diff output.txt $2

exit $?
