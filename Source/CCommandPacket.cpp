// Includes
#include <stdlib.h>
#include "CCommandPacket.h"

using namespace rebop;

CCommandPacket::CCommandPacket()
{
	// Unallocated data packet (used for reading)
	m_pData 		= nullptr;
	m_bufferSize 	= 0;
	m_dataSize		= 0;
}

CCommandPacket::CCommandPacket( int sizeIn )
{
	// Allocated data packet (used for writing)
	m_bufferSize 	= sizeIn;
	m_dataSize		= 0;

	m_pData = (uint8_t*)malloc( sizeof( uint8_t ) * m_bufferSize );
}

CCommandPacket::~CCommandPacket()
{
	// Free memory
	if( m_pData != nullptr )
	{
		free( m_pData );
		m_pData = nullptr;
	}
}


