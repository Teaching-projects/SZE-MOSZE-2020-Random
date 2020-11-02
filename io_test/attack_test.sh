#!/bin/bash
./$1 $2 > $3

diff $4 $3

exit $?
