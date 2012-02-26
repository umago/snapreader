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

#include <string>
#include <fstream>
#include "delta_merger.h"
#include "config.h"

bool DeltaMerger::merge(std::string delta, std::string device)
{
	int chunk_size;
	int rsize = 0;
	unsigned long long addr;
	std::ifstream ifs(delta.c_str(), std::ios::binary);
	std::ofstream ofs(device.c_str(), std::ios::binary | std::ios::in | std::ios::out);

	ifs.read((char *) &chunk_size, sizeof(chunk_size));
	char buffer[chunk_size];

	while(1){
		ifs.read((char *) &addr, sizeof(addr));
		ifs.read(buffer, chunk_size);

		rsize = ifs.gcount();
		if (rsize <= 0)
			break;

        	ofs.seekp(addr * SECTOR_SIZE, std::ios::beg);
		ofs.write(buffer, rsize);
	}

	ifs.close();
	ofs.close();

	return true;
}

