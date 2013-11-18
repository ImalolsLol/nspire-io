/**
 * @file console.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * C++ specific UART header
 */

extern "C" {
	#include <os.h>
	#ifdef BUILDLIB
		#include <nspireio/nspireio.h>
	#endif
}

#include <nspireio/ios_base.ipp>

#ifndef UART_HPP
#define UART_HPP

namespace nio
{
	class uart : public ios_base<uart>
	{
	public:
		uart();
		bool ready();
		
		virtual void put(char ch);
		virtual void write(const char* s, streamsize n);
		virtual void flush();
		
		virtual int gcount() const;
		virtual char get();
		virtual void get(char& c);
		virtual void get(char* s, streamsize n);
		virtual void getline(char* s, streamsize n);
	};
}

#endif
