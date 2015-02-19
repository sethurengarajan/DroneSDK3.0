// Includes
#include "CNetworkInterface.h"
#include "Utility.hpp"

// Namespaces
using namespace std;
using namespace rebop;

CNetworkInterface::CNetworkInterface()
{
	// Initialize pointers
	m_pNetworkALManager 		= nullptr;
	m_pNetworkManager			= nullptr;
	m_tRxThread					= nullptr;
	m_tTxThread					= nullptr;
	m_tMonitorThread			= nullptr;

	// Init attributes
	m_killMonitor				= false;
	m_isConnected				= false;
}

CNetworkInterface::~CNetworkInterface()
{
}

bool CNetworkInterface::Initialize()
{
	LOG( INFO ) << "Initializing AR Network Interface...";

	// Perform network discovery
	if( !PerformNetworkDiscovery() )
	{
		m_isConnected = false;
		return false;
	}

	// Start network connection with drone
	if( !InitializeNetworkManagers() )
	{
		m_isConnected = false;
		return false;
	}

	// Start network connection with drone
	if( !StartNetworkThreads() )
	{
		m_isConnected = false;
		return false;
	}

	LOG( INFO ) << "AR Network Interface successfully initialized.";

	// Next, if we have a user registered callback, call that
	if( m_pConnectionCallback != nullptr )
	{
		LOG( INFO ) << "Activating connection callback.";
		m_pConnectionCallback();
	}
	else
	{
		// LOG( WARNING ) << "No connection callback registered!";
	}

	m_isConnected = true;
	return true;
}

bool CNetworkInterface::PerformNetworkDiscovery()
{
	LOG( INFO ) << "Performing network discovery...";

	bool failed = false;

	eARDISCOVERY_ERROR err = ARDISCOVERY_OK;

	// Create connection data object - allocation
	// Use the JSON callbacks to get the data back to the network settings object
	ARDISCOVERY_Connection_ConnectionData_t *discoveryData = ARDISCOVERY_Connection_New( SendJsonCallback, ReceiveJsonCallback, &m_networkSettings, &err );

	// Check for errors in creation
	if( discoveryData == nullptr || err != ARDISCOVERY_OK )
	{
		LOG( ERROR ) << "Error while creating discoveryData: " << ARDISCOVERY_Error_ToString( err );
		failed = true;
	}

	// If successful, perform network discovery with the target
	if( !failed )
	{
		eARDISCOVERY_ERROR err = ARDISCOVERY_Connection_ControllerConnection( discoveryData, m_networkSettings.DISCOVERY_PORT, m_networkSettings.TARGET_USB_IP_ADDRESS );

		if( err != ARDISCOVERY_OK )
		{
			LOG( ERROR ) << "Error while opening discovery connection: " << ARDISCOVERY_Error_ToString( err );
			failed = true;
		}
	}

	// Free memory
	ARDISCOVERY_Connection_Delete( &discoveryData );

	if( failed )
	{
		LOG( INFO ) << "Network discovery failed!";
		return false;
	}
	else
	{
		LOG( INFO ) << "Network discovery complete.";
		return true;
	}
}

bool CNetworkInterface::InitializeNetworkManagers()
{
	LOG( INFO ) << "Initializing Network Manager and Network Abstraction Layer Manager...";

	eARNETWORK_ERROR netError 		= ARNETWORK_OK;
	eARNETWORKAL_ERROR netAlError 	= ARNETWORKAL_OK;

	// 0 means default, -1 means no ping
	int pingDelay 					= 0;
	int timeoutSecs					= 1;

	// Create the ARNetworkALManager - allocation
	m_pNetworkALManager = ARNETWORKAL_Manager_New( &netAlError );

	if( m_pNetworkALManager == nullptr || netAlError != ARNETWORKAL_OK )
	{
		LOG( ERROR ) << "Failed to create Network Abstraction Layer Manager.";
		return false;
	}

	// Initialize the ARNetworkALManager
	netAlError = ARNETWORKAL_Manager_InitWifiNetwork( m_pNetworkALManager, m_networkSettings.TARGET_USB_IP_ADDRESS, m_networkSettings.m_outboundPort, m_networkSettings.m_inboundPort, timeoutSecs );

	if( netAlError != ARNETWORKAL_OK )
	{
		LOG( ERROR ) << "Failed to initialize Network Abstraction Layer Manager.";
		return false;
	}

	// Create the ARNetworkManager.
	m_pNetworkManager = ARNETWORK_Manager_New(
		m_pNetworkALManager,
		m_networkSettings.m_outboundParameters.size(),
		m_networkSettings.m_outboundParameters.data(),
		m_networkSettings.m_inboundParameters.size(),
		m_networkSettings.m_inboundParameters.data(),
		pingDelay,
		OnDisconnect,
		NULL,
		&netError );

	if (netError != ARNETWORK_OK)
	{
		LOG( ERROR ) << "Failed to create Network Manager.";
		return false;
	}

	LOG( INFO ) << "Network Manager and Network Abstraction Layer Manager initialized!";

	return true;
}

void CNetworkInterface::Cleanup()
{
	LOG( INFO ) << "Cleaning up AR Network Interface...";

	// Close all connections, kill threads, and clean up memory used for networking
	StopNetwork();

	// TODO: Implement monitor thread
	// Kill the monitor thread
//	if( m_tMonitorThread != nullptr )
//	{
//		m_killMonitor = true;
//		ARSAL_Thread_Join( m_tMonitorThread, nullptr );
//		ARSAL_Thread_Destroy( &( m_tMonitorThread ) );
//		m_tMonitorThread = nullptr;
//	}

	LOG( INFO ) << "Cleaned up AR Network Interface.";
}


void CNetworkInterface::OnDisconnect( ARNETWORK_Manager_t* networkManagerIn, ARNETWORKAL_Manager_t* networkALManagerIn, void* customDataIn )
{
	// This function will be called if the drone somehow disconnects or if the connection is closed manually
	CNetworkInterface *networkInterface = (CNetworkInterface*)customDataIn;

	if( !networkInterface )
	{
		return;
	}

	LOG( INFO ) << "Disconnected from the target!";

	// First and foremost, set our connection status to false and wake up the monitor thread to try to reconnect
	networkInterface->m_isConnected = false;
	// TODO: condition variable wakeup for monitor thread

	// Next, if we have a user registered callback, call that!
	if( networkInterface->m_pDisconnectionCallback != nullptr )
	{
		LOG( INFO ) << "Activating disconnection callback.";
		networkInterface->m_pDisconnectionCallback();
	}
	else
	{
		LOG( WARNING ) << "No disconnection callback registered!";
	}
}

bool CNetworkInterface::StartNetworkThreads()
{
	LOG( INFO ) << "Starting Tx and Rx Threads...";

	// Create and start Rx Thread
	if( ARSAL_Thread_Create( &( m_tRxThread ), ARNETWORK_Manager_ReceivingThreadRun, m_pNetworkManager ) != 0 )
	{
		LOG( ERROR ) << "Creation of Rx thread failed.";
		return false;
	}

	// Create and start Tx Thread
	if( ARSAL_Thread_Create( &( m_tRxThread ), ARNETWORK_Manager_SendingThreadRun, m_pNetworkManager ) != 0 )
	{
		LOG( ERROR ) << "Creation of Tx thread failed.";
		return false;
	}

	LOG( INFO ) << "Tx and Rx Threads started!";

	// TODO: Implement monitor thread
//	LOG( INFO ) << "Starting Monitor Thread...";
//
//	// Create and start Monitor Thread
//	if( ARSAL_Thread_Create( &( m_tMonitorThread ), MonitorThreadFunction, this ) != 0 )
//	{
//		LOG( ERROR ) << "Creation of Monitor thread failed.";
//		return false;
//	}
//
//	LOG( INFO ) << "Monitor Thread started!";

	return true;
}

void CNetworkInterface::StopNetwork()
{
	LOG( INFO ) << "Stopping Network...";

	// ARNetwork cleanup
	if( m_pNetworkManager != nullptr )
	{
		// Stop the network manager
		ARNETWORK_Manager_Stop( m_pNetworkManager );

		// Clean up the Rx thread
		if( m_tRxThread != nullptr )
		{
			ARSAL_Thread_Join( m_tRxThread, nullptr );
			ARSAL_Thread_Destroy( &( m_tRxThread ) );
			m_tRxThread = nullptr;
		}

		// Clean up the Tx thread
		if( m_tTxThread != nullptr )
		{
			ARSAL_Thread_Join( m_tTxThread, nullptr );
			ARSAL_Thread_Destroy( &( m_tTxThread ) );
			m_tTxThread = nullptr;
		}
	}

	// Clean up Network Abstraction Layer Manager
	if( m_pNetworkALManager != nullptr )
	{
		// Unlock the Network AL manager
		ARNETWORKAL_Manager_Unlock( m_pNetworkALManager );

		// Close the wifi network
		ARNETWORKAL_Manager_CloseWifiNetwork( m_pNetworkALManager );
	}

	// Free memory for network managers
	ARNETWORK_Manager_Delete( &m_pNetworkManager );
	ARNETWORKAL_Manager_Delete( &m_pNetworkALManager );

	LOG( INFO ) << "Network stopped.";
}


eARDISCOVERY_ERROR CNetworkInterface::SendJsonCallback( uint8_t *txDataIn, uint32_t *txDataSizeIn, void *customDataIn )
{
	// Cast to get the network settings object
	CNetworkSettings *settings = (CNetworkSettings*)customDataIn;

	if( settings == nullptr )
	{
		LOG( ERROR ) << "SendJsonCallback() failed: Null network settings object.";
		return eARDISCOVERY_ERROR::ARDISCOVERY_ERROR;
	}

    if( ( txDataIn != nullptr ) && ( txDataSizeIn != nullptr ) )
    {
    	// Copy the json string to the tx buffer and get the length (+1 is for the null terminator, as sprintf does not include it)
        *txDataSizeIn = sprintf( (char *)txDataIn, "{ \"%s\": %d,\n \"%s\": \"%s\",\n \"%s\": \"%s\" }",
        ARDISCOVERY_CONNECTION_JSON_D2CPORT_KEY, settings->INBOUND_PORT,
        ARDISCOVERY_CONNECTION_JSON_CONTROLLER_NAME_KEY, "name",
        ARDISCOVERY_CONNECTION_JSON_CONTROLLER_TYPE_KEY, "type" ) + 1;

        // Looks like this:
		// 		{ "d2c_port": settings->INBOUND_PORT,
		// 		"controller_name": "name",
		// 		"controller_type": "type" }
    }
    else
    {
    	// Error occurred - inputs were null
    	LOG( ERROR ) << "SendJsonCallback() failed: No valid data buffer info provided.";
    	return eARDISCOVERY_ERROR::ARDISCOVERY_ERROR;
    }

    return eARDISCOVERY_ERROR::ARDISCOVERY_OK;
}

eARDISCOVERY_ERROR CNetworkInterface::ReceiveJsonCallback( uint8_t *rxDataIn, uint32_t rxDataSizeIn, char *ipIn, void *customDataIn )
{
	// Cast to get the network settings object
	CNetworkSettings *settings = (CNetworkSettings *)customDataIn;

	if( settings == nullptr )
	{
		LOG( ERROR ) << "ReceiveJsonCallback() failed: Null network settings object.";
		return eARDISCOVERY_ERROR::ARDISCOVERY_ERROR;
	}

    // Make sure we received data and have the device manager pointer
    if( ( rxDataIn != nullptr ) && ( rxDataSizeIn != 0 ) )
    {
    	// Parse the port number from the string sent by the drone
        if( !util::ParseIntFromJsonString( (const char*)rxDataIn, ARDISCOVERY_CONNECTION_JSON_C2DPORT_KEY, settings->m_outboundPort ) )
        {
        	// Failure
        	LOG( ERROR ) << "ReceiveJsonCallback() failed: Unable to parse port number from JSON string.";
        	return eARDISCOVERY_ERROR::ARDISCOVERY_ERROR;
        }
    }
    else
    {
    	LOG( ERROR ) << "ReceiveJsonCallback() failed: No valid data received.";
    	return eARDISCOVERY_ERROR::ARDISCOVERY_ERROR;
    }

    return eARDISCOVERY_ERROR::ARDISCOVERY_OK;
}

bool CNetworkInterface::Flush()
{
	// Flush all buffers in the network manager
	eARNETWORK_ERROR ret = ARNETWORK_Manager_Flush( m_pNetworkManager );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

bool CNetworkInterface::SendData( const CCommandPacket& dataIn, EOutboundBufferId outboundBufferIdIn, bool doDataCopyIn )
{
	// TODO: Make the callback a registerable callback

	// Send packet to vehicle
	eARNETWORK_ERROR ret = ARNETWORK_Manager_SendData(
		m_pNetworkManager,
		(int)outboundBufferIdIn,
		dataIn.m_pData,
		dataIn.m_bufferSize,
		nullptr,
		DefaultCommandCallback,
		( doDataCopyIn ? 1 : 0 ) );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

bool CNetworkInterface::ReadData( CCommandPacket& dataOut, EInboundBufferId inboundBufferIdIn )
{
	// Read packet from vehicle (indefinite blocking)
	eARNETWORK_ERROR ret = ARNETWORK_Manager_ReadData(
		m_pNetworkManager,
		(int)inboundBufferIdIn,
		dataOut.m_pData,
		m_kMaxBytesToRead,
		&dataOut.m_bufferSize );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

bool CNetworkInterface::TryReadData( CCommandPacket& dataOut, EInboundBufferId inboundBufferIdIn )
{
	// Read packet from vehicle (non-blocking)
	eARNETWORK_ERROR ret = ARNETWORK_Manager_TryReadData(
		m_pNetworkManager,
		(int)inboundBufferIdIn,
		dataOut.m_pData,
		m_kMaxBytesToRead,
		&dataOut.m_bufferSize );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

bool CNetworkInterface::ReadDataWithTimeout( CCommandPacket& dataOut, EInboundBufferId inboundBufferIdIn, uint32_t timeoutMsIn )
{
	// Read packet from vehicle (block for timeout duration)
	eARNETWORK_ERROR ret = ARNETWORK_Manager_ReadDataWithTimeout(
		m_pNetworkManager,
		(int)inboundBufferIdIn,
		dataOut.m_pData,
		m_kMaxBytesToRead,
		&dataOut.m_bufferSize,
		timeoutMsIn );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

bool CNetworkInterface::FlushInboundBuffer( EInboundBufferId inboundBufferIdIn )
{
	eARNETWORK_ERROR ret = ARNETWORK_Manager_FlushInputBuffer( m_pNetworkManager, (int)inboundBufferIdIn );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

bool CNetworkInterface::FlushOutboundBuffer( EOutboundBufferId outboundBufferIdIn )
{
	// WARNING: Parrot's documentation about what is an input buffer/output buffer is confusing and inconsistent.
	// Logically, you would expect the output buffer to be the buffer that you are writing commands to, but their documentation contradicts this
	// in one place, and then contradicts itself for the GetLatency function. ALl this to say, FlushInput/Output may need swapping. \/(o.o)\/
	eARNETWORK_ERROR ret = ARNETWORK_Manager_FlushOutputBuffer( m_pNetworkManager, (int)outboundBufferIdIn );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

bool CNetworkInterface::SetMinimumTimeBetweenSends( uint32_t delayMsIn )
{
	// Set the minimum time delay between sends - default value is 1ms
	// Setting a bad minimum time can cause erratic behaviour. Don't do it!
	eARNETWORK_ERROR ret = ARNETWORK_Manager_SetMinimumTimeBetweenSends( m_pNetworkManager, delayMsIn );

	if( ret != eARNETWORK_ERROR::ARNETWORK_OK )
	{
		return false;
	}

	return true;
}

int CNetworkInterface::GetEstimatedLatency()
{
	// Get the estimated latency with the vehicle in milliseconds
	// Negative value means it could not be determined
	return ARNETWORK_Manager_GetEstimatedLatency( m_pNetworkManager );
}

int CNetworkInterface::GetEstimatedMissPercentage( EOutboundBufferId outboundBufferIdIn )
{
	// Get the estimated percent of packets being dropped
	// Negative value is an error
	return ARNETWORK_Manager_GetEstimatedMissPercentage( m_pNetworkManager, (int)outboundBufferIdIn );
}


void CNetworkInterface::RegisterDisconnectionCallback( TDisconnectionCallback callbackIn )
{
	// Register the callback function to be used upon disconnection
	m_pDisconnectionCallback = callbackIn;
}

void CNetworkInterface::UnregisterDisconnectionCallback()
{
	m_pDisconnectionCallback = nullptr;
}

void CNetworkInterface::RegisterConnectionCallback( TConnectionCallback callbackIn )
{
	// Register the callback function to be used upon successful connection
	m_pConnectionCallback = callbackIn;
}

void CNetworkInterface::UnregisterConnectionCallback()
{
	m_pConnectionCallback = nullptr;
}

eARNETWORK_MANAGER_CALLBACK_RETURN CNetworkInterface::DefaultCommandCallback( int bufferIdIn, uint8_t *dataIn, void *customDataIn, eARNETWORK_MANAGER_CALLBACK_STATUS causeIn )
{
    eARNETWORK_MANAGER_CALLBACK_RETURN retval = ARNETWORK_MANAGER_CALLBACK_RETURN_DEFAULT;

    switch( causeIn )
    {
		// Data was sent
		case eARNETWORK_MANAGER_CALLBACK_STATUS::ARNETWORK_MANAGER_CALLBACK_STATUS_SENT:
		{
			break;
		}

		// Acknowledgment was received
		case eARNETWORK_MANAGER_CALLBACK_STATUS::ARNETWORK_MANAGER_CALLBACK_STATUS_ACK_RECEIVED:
		{
			break;
		}

		// Timeout occurred, data not received- This callback must return what the network manager should do with the data
		case eARNETWORK_MANAGER_CALLBACK_STATUS::ARNETWORK_MANAGER_CALLBACK_STATUS_TIMEOUT:
		{
			retval = ARNETWORK_MANAGER_CALLBACK_RETURN_DATA_POP;
			break;
		}

		// Data will not be sent
		case eARNETWORK_MANAGER_CALLBACK_STATUS::ARNETWORK_MANAGER_CALLBACK_STATUS_CANCEL:
		{
			break;
		}

		// Free the data sent without copying data
		case eARNETWORK_MANAGER_CALLBACK_STATUS::ARNETWORK_MANAGER_CALLBACK_STATUS_FREE:
		{
			break;
		}

		// Use of the data is complete, and it will not be used anymore
		case eARNETWORK_MANAGER_CALLBACK_STATUS::ARNETWORK_MANAGER_CALLBACK_STATUS_DONE:
		{
			break;
		}

		// Unknown status
		default:
		{
			LOG( ERROR ) << "Unknown callback status!";
			break;
		}
    }

    return retval;
}

void* CNetworkInterface::MonitorThreadFunction( void* dataIn )
{
	// Cast to get the network interface
	CNetworkInterface *networkInterface = (CNetworkInterface*)dataIn;

	if( networkInterface == nullptr )
	{
		LOG( ERROR ) << "Invalid pointer given to Network Monitor thread. Monitor not activated.";
		return nullptr;
	}

	while( true )
	{
		// TODO: Replace this with a condition variable so it just sleeps until alerted
		// TODO: Make sure things are threadsafe after finishing rapid prototyping. They currently are not!
		if( networkInterface->m_killMonitor == true )
		{
			break;
		}

		// Check to see if we've disconnected
		if( networkInterface->m_isConnected == false  )
		{
			// Stop network and do cleanup
			networkInterface->StopNetwork();

			// Reinitialize network and attempt to connect again
			networkInterface->Initialize();

			if( networkInterface->m_isConnected == true )
			{
				// Reconnected successfully
				continue;
			}

			// Sleep for some kind of delay between attempts (default 5s)
			sleep( m_kMonitorRetryDelay );
		}
		else
		{
			// Go back to sleep
		}
	}

	// Stop network and do cleanup
	networkInterface->StopNetwork();

	return nullptr;
}
