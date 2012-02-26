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

#ifndef DELTA_WRITER_H_
#define DELTA_WRITER_H_

#include <string>
#include "snap_reader.h"

class DeviceNotSet: public std::exception
{
	public:
		virtual const char* what() const throw(){
			return "Device is not set";
	  	}

};

class DeltaWriter
{
	public:
		DeltaWriter();
		DeltaWriter(std::string device);
		~DeltaWriter();
		void setDevice(std::string device);
		void makeDelta(std::string path);

	private:
		std::string dev;
		SnapReader *snap_reader;
};

#endif
