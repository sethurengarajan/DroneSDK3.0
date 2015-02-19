// Includes
#include "CNetworkSettings.h"

// Namespaces
using namespace rebop;

CNetworkSettings::CNetworkSettings()
{
	// Init ports to default values
	m_outboundPort 	= OUTBOUND_PORT;
	m_inboundPort	= INBOUND_PORT;

	// Init I/O parameters
	InitializeIOParameters();
}

CNetworkSettings::~CNetworkSettings()
{

}

void CNetworkSettings::InitializeIOParameters()
{
	// Initialize parameters
	// int ID 								| Identifier used to find the IOBuffer in a list - Valid range : 10-127
	// eARNETWORKAL_FRAME_TYPE dataType  	| Type of the data stored in the buffer
	// int sendingWaitTimeMs 				| Time in milliseconds between two send attempts
	// int ackTimeoutMs 					| Timeout in milliseconds before retrying to send the data awaiting an acknowledgement
	// int numberOfRetryMaximum 			| Number of retry attempts before send is considered a failure
	// int32_t numberOfCell 				| Maximum number of data cells stored, where a cell is <dataCopyMaxSize> bytes wide
	// int32_t dataCopyMaxSize 				| Maximum size, in bytes, of the data copied in the buffer. The IOBuffer allocates a buffer of <numberOfCell> * >dataCopyMaxSize>
	// 										| A value of ARNETWORK_IOBUFFERPARAM_DATACOPYMAXSIZE_USE_MAX automatically allocates the maximum size allowed by the underlying media
	// int isOverwriting 					| Indicator of overwriting possibility (1 = true | 0 = false)
	//										| TODO: No idea what "isOverwriting" means

	// Outbound without ack
	m_outboundParameters[ OUTBOUND_INDEX ].ID								= (int)EOutboundBufferId::OUTBOUND;
	m_outboundParameters[ OUTBOUND_INDEX ].dataType 						= eARNETWORKAL_FRAME_TYPE::ARNETWORKAL_FRAME_TYPE_DATA;
	m_outboundParameters[ OUTBOUND_INDEX ].sendingWaitTimeMs 				= 5;
	m_outboundParameters[ OUTBOUND_INDEX ].ackTimeoutMs 					= -1;
	m_outboundParameters[ OUTBOUND_INDEX ].numberOfRetry 					= -1;
	m_outboundParameters[ OUTBOUND_INDEX ].numberOfCell 					= 10;
	m_outboundParameters[ OUTBOUND_INDEX ].dataCopyMaxSize 					= 128;
	m_outboundParameters[ OUTBOUND_INDEX ].isOverwriting 					= 0;

	// Outbound with ack
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].ID 						= (int)EOutboundBufferId::OUTBOUND_WITH_ACK;
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].dataType 				= eARNETWORKAL_FRAME_TYPE::ARNETWORKAL_FRAME_TYPE_DATA_WITH_ACK;
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].sendingWaitTimeMs 		= 20;
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].ackTimeoutMs 			= 500;
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].numberOfRetry 			= 3;
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].numberOfCell 			= 20;
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].dataCopyMaxSize 		= 128;
	m_outboundParameters[ OUTBOUND_WITH_ACK_INDEX ].isOverwriting 			= 0;

	// Inbound without ack
	m_inboundParameters[ INBOUND_INDEX ].ID									= (int)EInboundBufferId::INBOUND;
	m_inboundParameters[ INBOUND_INDEX ].dataType 							= eARNETWORKAL_FRAME_TYPE::ARNETWORKAL_FRAME_TYPE_DATA;
	m_inboundParameters[ INBOUND_INDEX ].sendingWaitTimeMs 					= 20;
	m_inboundParameters[ INBOUND_INDEX ].ackTimeoutMs 						= -1;
	m_inboundParameters[ INBOUND_INDEX ].numberOfRetry 						= -1;
	m_inboundParameters[ INBOUND_INDEX ].numberOfCell 						= 10;
	m_inboundParameters[ INBOUND_INDEX ].dataCopyMaxSize 					= 128;
	m_inboundParameters[ INBOUND_INDEX ].isOverwriting 						= 0;

	// Inbound with ack
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].ID 						= (int)EInboundBufferId::INBOUND_WITH_ACK;
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].dataType 					= eARNETWORKAL_FRAME_TYPE::ARNETWORKAL_FRAME_TYPE_DATA_WITH_ACK;
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].sendingWaitTimeMs 		= 20;
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].ackTimeoutMs	 			= 500;
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].numberOfRetry 			= 3;
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].numberOfCell 				= 20;
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].dataCopyMaxSize 			= 128;
	m_inboundParameters[ INBOUND_WITH_ACK_INDEX ].isOverwriting 			= 0;
}
