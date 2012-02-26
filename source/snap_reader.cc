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

#include <list>
#include <cstring>
#include <fstream>
#include "snap_reader.h"
#include "config.h"

SnapReader::SnapReader(std::string device)
{
        fd = new std::ifstream(device.c_str(), std::ios::in | std::ios::binary);

	readHeader();

	if (header.is_valid != 1)
		throw SnapIsNotValid();

        chunk_size = header.chunk_size * SECTOR_SIZE;
        exceptions_per_area = chunk_size / EXCEPTION_SIZE;
}

SnapReader::~SnapReader()
{
	fd->close();
        delete fd;
}

int SnapReader::readData(char *buffer, int size, int offset)
{
        fd->seekg(offset, std::ios::beg);
	fd->read(buffer, size);
	return fd->gcount();
}

void SnapReader::readHeader()
{
	readData((char *) &header, sizeof(SnapHeader), USER_SEEK * SECTOR_SIZE);
}

int SnapReader::getMetadataArea(char *buffer, int index)
{
        int area;

        area = 1 + (exceptions_per_area + 1) * index;
        return readData(buffer, chunk_size, (area * chunk_size) + (USER_SEEK * SECTOR_SIZE));
}

std::list<SnapException> SnapReader::getSectorListFromIndex(int index)
{
        SnapException except;
	std::list<SnapException> list;
	char *buffer;
	int i, size;

	buffer = new char[chunk_size];
	size = getMetadataArea(buffer, index);

        for (i = 0; i < size; i += EXCEPTION_SIZE){
		memcpy(&except, buffer + i, EXCEPTION_SIZE);

        	if (except.newsec == 0)
			break;

		except.newsec = except.newsec << 3;
		except.oldsec = except.oldsec << 3;

		list.push_back(except);
	}

	delete buffer;

	return list;
}

std::list<SnapException> SnapReader::getSectorList()
{
	std::list<SnapException> final_list;
	std::list<SnapException> temp_list;
	int index = 0;

	while (1){
		temp_list = getSectorListFromIndex(index);

		if (temp_list.size() == 0)
			break;

		final_list.splice(final_list.end(), temp_list);
		index++;
	}

	return final_list;

}
