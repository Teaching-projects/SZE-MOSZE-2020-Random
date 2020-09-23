#!/bin/bash
./a.out units/ka.json units/ke.json > attack_test.txt
./a.out units/ka.json units/ki.json >> attack_test.txt
./a.out units/ke.json units/ki.json >> attack_test.txt

./a.out units/ke.json units/ka.json >> attack_test.txt
./a.out units/ki.json units/ka.json >> attack_test.txt
./a.out units/ki.json units/ke.json >> attack_test.txt

diff attack_test.txt attack_test_target.txt
