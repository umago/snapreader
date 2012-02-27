snapreader
=======

snapreader is a delta extractor and merger for the dmsetup target snapshot.
Its a study purpose project, and can serve as base for many others crazy
projects involving extracting the differences between devices and merging it
back into the original device (if wanted).

Fork it and test it, theres some scripts included to facilitate testing, and
only one machine is required.

Have fun!!

Testing
-------

    WARNING: 
    YOU'LL NEED ROOT ACCESS TO DO THE TESTS. SO TAKE CARE!

[root@umago snapreader]# cd scripts

[root@umago scripts]# ./create_files.sh

**...**

**SUCCESS: Files created**


[root@umago scripts]# sh setup_loops.sh

**SUCCESS: Loops are ready**


[root@umago scripts]# mount /dev/mapper/snap /media

[root@umago scripts]# vim /media/some_data

**Write something...**


[root@umago scripts]# umount /media

[root@umago scripts]# sh remove_loops.sh

**SUCCESS: Loops were removed**


[root@umago scripts]# cd ../source 

[root@umago source]# ./snapreader -d ../scripts/cow_device 

[root@umago source]# ls delta 

**delta**


[root@umago source]# ./snapreader -m delta ../scripts/main_device 


* * *


`Let's test the merge :)`


[root@umago source]# losetup /dev/loop1 ../scripts/main_device 

[root@umago source]# mount /dev/loop1 /media

[root@umago source]# ls /media/some_data

**/media/some_data**


[root@umago source]# umount /media

[root@umago source]# losetup -d /dev/loop1

`Yeah it works!`

License
-------

snapreader is distributed under the terms of the GNU General Public License, version 2.
See the [COPYING][1] file for more information.

Contributor list
----------------

Lucas Alvares Gomes (aka umago) <lucasagomes@gmail.com>

Contributing
------------

1. Fork it
2. Create a branch (`git checkout -b <branch name>`)
3. Commit your changes (`git commit -am "Added ..."`)
4. Push to the branch (`git push origin <branch name>`)
5. Create an [Issue][2] with a link to your branch

[1]: https://github.com/umago/snapreader/blob/master/COPYING
[2]: http://github.com/umago/snapreader/issues
