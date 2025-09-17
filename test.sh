#!/bin/bash

# Simple test of the command interpreter

in="abbabaq"
out="0,3,5;"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "PASSED" || echo "FAILED"

in1="abbbbbbbbbbaccaq"
out1="14;"

[[ $(./cmd_int <<< "$in1") == "$out1"* ]] && echo "PASSED" || echo "FAILED"

in2="aabbbaqtest"
out2="0,1,5;"

[[ $(./cmd_int <<< "$in2") == "$out2"* ]] && echo "PASSED" || echo "FAILED"
