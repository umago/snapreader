#!/bin/sh
# Lucas Alvares Gomes <lucasagomes@gmail.com>

if [ ! $(id -u) -eq 0 ]; then
   echo "This script must be run as root"
   exit 1
fi

dd if=/dev/zero of=main_device bs=1M count=30
dd if=/dev/zero of=cow_device bs=1M count=30

if [ -e main_device ]
then

	losetup /dev/loop1 main_device

	rc=$?
	if [ ! $rc -eq 0 ]
	then

		echo "\nFAILED: Cannt setup /dev/loop1"
		exit $rc

	fi

	mkfs.ext4 /dev/loop1
	sync
	losetup -d /dev/loop1

	echo "\nSUCCESS: Files created"
	exit 0
fi

echo "\nFAILED: Files not created"
exit 1
