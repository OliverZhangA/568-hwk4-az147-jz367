#!/bin/bash
taskset -c 0 ./client testin0.txt 1 12345 & taskset -c 1 ./client testin1.txt 2 99999 & taskset -c 2 ./client testin2.txt 3 555555 & taskset -c 3 ./client testin3.txt 4 111111