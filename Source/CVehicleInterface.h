#pragma once

// Includes
#include "CNetworkInterface.h"
#include "Utility.hpp"

namespace rebop
{

class CVehicleInterface
{
public:
	// Pointers

	// Attributes
	CNetworkInterface m_networkInterface;

	bool m_isConnected;

	//Methods
	CVehicleInterface();
	virtual ~CVehicleInterface();

	virtual void Initialize();
	virtual void Update();
	virtual void Cleanup();
	virtual bool IsConnected();
};

}
