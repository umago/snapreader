#!/bin/sh
# Lucas Alvares Gomes <lucasagomes@gmail.com>

if [ ! $(id -u) -eq 0 ]; then
   echo "This script must be run as root"
   exit 1
fi

dmsetup remove_all

rc=$?
if [ ! $rc -eq 0 ]
then

	echo "\nFAILED: the mapped device is mounted?"
	exit $rc

fi

losetup -d /dev/loop1
losetup -d /dev/loop2

rc=$?
if [ ! $rc -eq 0 ]
then

	echo "\nFAILED: Loops are busy"
	exit $rc

fi

echo "\nSUCCESS: Loops were removed"
