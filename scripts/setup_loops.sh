#!/bin/sh
# Lucas Alvares Gomes <lucasagomes@gmail.com>

if [ ! $(id -u) -eq 0 ]; then
   echo "This script must be run as root"
   exit 1
fi

if [ ! -e main_device ]
then
	echo "Files not found! Use the create_files.sh script"
	exit 1

fi

USER_SEEK=2

losetup /dev/loop1 main_device
losetup /dev/loop2 cow_device

dev_size=`blockdev --getsize /dev/loop1`

dmsetup create main_device --table "0 $dev_size linear /dev/loop1 0"

rc=$?
if [ ! $rc -eq 0 ]
then

	echo "FAILED: dmsetup is installed?"
	losetup -d /dev/loop1
	losetup -d /dev/loop2
	exit $rc

fi

dmsetup create cow_device --table "0 $(($dev_size - USER_SEEK)) linear /dev/loop2 $USER_SEEK"
sync
dmsetup create snap --table "0 $dev_size snapshot /dev/mapper/main_device /dev/mapper/cow_device P 8"

echo "SUCCESS: Loops are ready"
