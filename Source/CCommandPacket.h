#pragma once

#include <stdint.h>

namespace rebop
{

class CCommandPacket
{
public:
	// Attributes
	uint8_t *m_pData;	// Raw Data
	int m_bufferSize;	// Amount of memory allocated for the buffer
	int m_dataSize;		// The actual number of bytes stored in the buffer (used by command generator)

	// Methods
	CCommandPacket();				// Unallocated
	CCommandPacket( int sizeIn );	// Preallocated for command generation
	virtual ~CCommandPacket();
};

}
