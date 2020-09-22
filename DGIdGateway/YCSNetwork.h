/*
 *   Copyright (C) 2009-2014,2016,2017,2018,2020 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	YCSNetwork_H
#define	YCSNetwork_H

#include "DGIdNetwork.h"
#include "YSFDefines.h"
#include "UDPSocket.h"
#include "RingBuffer.h"
#include "Timer.h"

#include <cstdint>
#include <string>

class CYCSNetwork : public CDGIdNetwork {
public:
	CYCSNetwork(unsigned int localPort, const std::string& name, const sockaddr_storage& addr, unsigned int addrLen, const std::string& callsign, unsigned int rxFrequency, unsigned int txFrequency, const std::string& locator, const std::string& description, unsigned int id, unsigned int dgId, bool debug);
	virtual ~CYCSNetwork();

	virtual std::string getDesc(unsigned int dgId);

	virtual unsigned int getDGId();

	virtual bool open();

	virtual DGID_STATUS getStatus();

	virtual void link();

	virtual void write(unsigned int dgId, const unsigned char* data);

	virtual unsigned int read(unsigned int dgId, unsigned char* data);

	virtual void clock(unsigned int ms);

	virtual void unlink();

	virtual void close();

private:
	CUDPSocket                 m_socket;
	bool                       m_debug;
	sockaddr_storage           m_addr;
	unsigned int               m_addrLen;
	unsigned char*             m_poll;
	unsigned char*             m_options;
	unsigned char*             m_info;
	unsigned char*             m_unlink;
	CRingBuffer<unsigned char> m_buffer;
	CTimer                     m_pollTimer;
	std::string                m_name;
	DGID_STATUS                m_state;
	unsigned int               m_dgId;

	void writePoll();
};

#endif
