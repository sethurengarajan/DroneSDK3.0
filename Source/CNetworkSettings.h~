#pragma once

// Includes
#include <array>
#include <libARNetwork/ARNetwork.h>

namespace rebop
{

// IDs for the I/O buffers
enum class EInboundBufferId
{
	INBOUND								= 127,
	INBOUND_WITH_ACK					= 126
};
enum class EOutboundBufferId
{
	OUTBOUND							= 10,
	OUTBOUND_WITH_ACK					= 11,
};

class CNetworkSettings
{
public:
	// Constants
	// Indices for your arrays
	const int OUTBOUND_INDEX 				= 0;
	const int OUTBOUND_WITH_ACK_INDEX		= 1;
	const int INBOUND_INDEX					= 0;
	const int INBOUND_WITH_ACK_INDEX 		= 1;

	const char* TARGET_WIFI_IP_ADDRESS 		= "192.168.42.1";		// The default IP address when connecting over wifi
	const char* TARGET_USB_IP_ADDRESS 		= "192.168.43.1";		// The default IP address when connecting over USB ethernet
	const int DISCOVERY_PORT 				= 44444;				// The port on the vehicle that you perform discovery on
	const int OUTBOUND_PORT 				= 54321;				// The port on the vehicle that you are sending commands to
	const int INBOUND_PORT 					= 43210;				// The port on your machine that you are listening for commands on

	// Attributes
	int m_outboundPort;		// This is the port we write to. We'll ask the target for the port they are using during discovery. By default, this is 54321.
	int m_inboundPort;		// This is the port we listen on. We'll tell the target what this is during discovery. By default this is 43210.

	// These are parameters for your I/O buffers. Generally you'll have four I/O buffers: two for outbound messages, two for inbound messages, each with an ACK and NONACK version.
	std::array<ARNETWORK_IOBufferParam_t, 2> m_outboundParameters;
	std::array<ARNETWORK_IOBufferParam_t, 2> m_inboundParameters;

	// Methods
	CNetworkSettings();
	virtual ~CNetworkSettings();

	void InitializeIOParameters();
};

}
