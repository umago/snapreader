/* Copyright (C) 2012 Lucas Alvares Gomes <lucasagomes@gmail.com>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>
#include <getopt.h>
#include "snap_reader.h"
#include "delta_writer.h"
#include "delta_merger.h"

int main(int argc, char **argv)
{
	int c;
	int action = -1;
	enum ACTIONS { MERGE, DELTA, NUM_ACTIONS };

	if ((c = getopt(argc, argv, "m:d:")) == -1)
		goto usage_exit;

	switch (c){
		case 'm':
			if (argc <= 3)
				goto usage_exit;

			action = MERGE;
			break;
		case 'd':
			if (argc <= 2)
				goto usage_exit;

			action = DELTA;
			break;
		default:
			goto usage_exit;
	}

	if (action == MERGE) {
		std::string delta = argv[2];
		std::string device = argv[3];

		DeltaMerger delta_merger = DeltaMerger();
		delta_merger.merge(delta, device);

	} else if (action == DELTA) {
		std::string source_device = argv[2];

		DeltaWriter delta_writer = DeltaWriter(source_device);
		delta_writer.makeDelta("delta");

	} else
		goto usage_exit;

	return 0;

usage_exit:
	std::cout << "Usage: " << std::endl;
	std::cout << argv[0] << " <cow_device>" << std::endl;
	std::cout << argv[0] << " -m " << "<delta> " << "<device>" << std::endl;
	exit(1);
}
