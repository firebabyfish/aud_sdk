#!/bin/sh

if [ $# -eq 0 ]; then
	make all -j
	cp out/*.bin /mnt/d/work/workspace/wch/FLASH/
	cp out/*.hex /mnt/d/work/workspace/wch/FLASH/
	cp out/*.elf /mnt/d/work/workspace/wch/FLASH/
	cp out/*.map /mnt/d/work/workspace/wch/FLASH/
elif [ "$1" = "clean" ]; then
	echo "rm -rf out"
	rm -rf out
else
	echo "Error argument"
fi

