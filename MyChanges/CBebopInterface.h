#pragma once

// Includes
#include "CVehicleInterface.h"
#include "BebopCommandsAndData.h"

// Normally, this is forbidden by my style guidelines, but you SHOULD only ever be including one vehicle's namespace
using namespace rebop::commands::bebop::navigation;

namespace rebop
{

class CBebopInterface : public CVehicleInterface
{
public:
	CBebopInterface();
	virtual ~CBebopInterface();

	virtual void Update();

	bool Takeoff();
	bool Land();
	bool Emergency();
	bool FlatTrim();
	bool NavigateHome( ENavigateHome startOrStopIn );
	bool SendPilotCommand( const TPilotCommand &poseIn );
	bool SetAutoTakeoffMode( EAutoTakeoffMode modeIn );
	bool Flip( EFlipDirection directionIn );
	bool SetMaxAltitude( float maxAltitudeMetersIn );
	bool SetMaxTilt( float maxTiltDegreesIn );
	bool SetMaxVerticalSpeed( float maxVerticalSpeedMetersPerSecIn );
	bool SetMaxRotationSpeed( float maxRotationSpeedDegPerSecIn );
	bool SetAbsoluteControlMode( EAbsoluteControlMode modeIn );
	bool SetHullProtectionPresence( EHullPresence presenceIn );
	bool SetOutdoorMode( EOutdoorMode modeIn );
	bool SetGpsHomeLocation( const TGpsHomeLocation &locationIn );
	bool ResetGpsHome();
	bool takePicture(int number);
	bool sendPCMD(int number);
	bool setCameraAngle(int number);
};

}
