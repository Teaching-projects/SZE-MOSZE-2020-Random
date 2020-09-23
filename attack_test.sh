#!/bin/bash
./a.out units/ka.json units/ke.json > $1
./a.out units/ka.json units/ki.json >> $1
./a.out units/ke.json units/ki.json >> $1

./a.out units/ke.json units/ka.json >> $1
./a.out units/ki.json units/ka.json >> $1
./a.out units/ki.json units/ke.json >> $1

diff $1 $2

exit $?
