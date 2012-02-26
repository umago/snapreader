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
#include <fstream>
#include "delta_writer.h"
#include "snap_reader.h"
#include "config.h"

DeltaWriter::DeltaWriter()
{
	snap_reader = NULL;
}

DeltaWriter::DeltaWriter(std::string device)
{
	setDevice(device);
}

DeltaWriter::~DeltaWriter()
{
	if (snap_reader)
		delete snap_reader;
}

void DeltaWriter::setDevice(std::string device)
{
	dev = device;
	snap_reader = new SnapReader(dev);
}

void DeltaWriter::makeDelta(std::string path)
{
	if (! snap_reader)
		throw DeviceNotSet();

	std::list<SnapException> sector_list;
	std::list<SnapException>::iterator it;
	std::ofstream ofs(path.c_str(), std::ios::out | std::ios::binary);
	int index = 0;
	int rsize = 0;
	char chunk[snap_reader->chunk_size];

	ofs.write((char *) &snap_reader->chunk_size, sizeof(snap_reader->chunk_size));

	while (1){
		sector_list = snap_reader->getSectorListFromIndex(index);

		if (sector_list.size() == 0)
			break;

		for (it = sector_list.begin(); it != sector_list.end() ; it++){
			rsize = snap_reader->readData((char *) &chunk, snap_reader->chunk_size, (it->newsec * SECTOR_SIZE) + (USER_SEEK * SECTOR_SIZE));
			ofs.write((char *) &it->oldsec, sizeof(it->oldsec));
			ofs.write(chunk, rsize);
		}

		index++;
	}

	ofs.close();
}
