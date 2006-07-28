// Copyright (c) 2004, Steven Scott (progoth@gmail.com)
//
// This file is part of iTunesAlarm.
//
// iTunesAlarm is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// iTunesAlarm is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with iTunesAlarm; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#pragma once

#include <vector>
#include "t.h"

namespace DayTime {

	
	const unsigned char SUNDAY    =  1;
	const unsigned char MONDAY    =  2;
	const unsigned char TUESDAY   =  4;
	const unsigned char WEDNESDAY =  8;
	const unsigned char THURSDAY  = 16;
	const unsigned char FRIDAY    = 32;
	const unsigned char SATURDAY  = 64;
	const unsigned char ALL_DAYS  = 127;
	const unsigned char WEEKDAYS  = 62;

	const unsigned char Win2DayTime[] = {SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY};


	class TimeAndDays
	{
	public:
		TimeAndDays():time(0), day(0){}
		TimeAndDays( int hour, int minute, BYTE days );

		void setTime( int hour, int minute );

		void getTime( int &hour, int &minute ) const
		{
			minute = time & 0x3f;
			hour = (time >> 6) & 0x1f;
		}


		void getToBinary( BYTE *data ) const
		{
			((unsigned short*)data)[0] = 0x07ff & time;
			((unsigned char*)data)[2]  =   0x7f &  day;
		}

		void setFromBinary( const char *data )
		{
			time = 0x07ff & ((unsigned short*)data)[0];
			day  =   0x7f & ((unsigned char*)data)[2];
		}

		bool isIncluded( const SYSTEMTIME &o ) const
		{
			if( !( day & Win2DayTime[o.wDayOfWeek] ) ) return false;
			int hour, minute; getTime( hour, minute );
			return ( (minute == o.wMinute) && (hour == o.wHour) );
		}

		tstring getString() const;

		unsigned short time;
		unsigned char day;


		bool operator==(const TimeAndDays& o) const;
	};

	extern void contToBin( const std::vector<TimeAndDays> &in, std::string &out );
	extern void binToCont( const std::string &in, std::vector<TimeAndDays> &out );

};
