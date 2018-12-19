#!/bin/bash

case "$1" in
    clean)
	echo "clean"
	rm -f test
	rm -f tt
	rm -f invoke.so
	;;
    make)
	echo "make"
	gcc -o test test.c
	gcc -fPIC -shared -o invoke.so invoke.c -ldl
	mv test tt
	;;
    run)
	echo "run"
	LD_PRELOAD=./invoke.so ./tt aaaaaaaaaaa
	;;
    all)
	echo "all"
	$0 clean
	$0 make
	$0 run
	;;

esac

