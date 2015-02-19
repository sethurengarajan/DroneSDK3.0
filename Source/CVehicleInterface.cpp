// Includes
#include "CVehicleInterface.h"
#include "Utility.hpp"

// Set up easylogger
INITIALIZE_EASYLOGGINGPP

// Namespaces
using namespace rebop;

CVehicleInterface::CVehicleInterface()
{
	// Init attributes
	m_isConnected = false;
}

CVehicleInterface::~CVehicleInterface()
{

}

void CVehicleInterface::Initialize()
{
	// Initialize the network interface
	m_isConnected = m_networkInterface.Initialize();
}

void CVehicleInterface::Update()
{

}

void CVehicleInterface::Cleanup()
{
	// Shutdown the network
	m_networkInterface.Cleanup();
}

bool CVehicleInterface::IsConnected()
{
	return m_isConnected;
}
