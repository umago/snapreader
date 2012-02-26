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

#ifndef SNAP_READER_H_
#define SNAP_READER_H_

#include <list>
#include <string>
#include <fstream>

const int EXCEPTION_SIZE = 16;

typedef struct
{
	int magic_number;
    	int is_valid;
	int version;
    	int chunk_size;
} SnapHeader;

typedef struct
{
	unsigned long long oldsec;
	unsigned long long newsec;
} SnapException;

class SnapIsNotValid: public std::exception
{
	public:
		virtual const char* what() const throw(){
			return "Invalid/corrupt snapshot";
	  	}

};

class SnapReader
{
	public:
		SnapReader(std::string device);
		~SnapReader();
                int chunk_size;
                int readData(char *buffer, int size, int offset);
                std::list<SnapException> getSectorListFromIndex(int index);
                std::list<SnapException> getSectorList();
	private:
                std::ifstream *fd;
		SnapHeader header;
                int exceptions_per_area;
		void readHeader();
                int getMetadataArea(char *buffer, int index);
};

#endif
