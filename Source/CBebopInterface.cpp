// Includes
#include "CBebopInterface.h"
#include "Utility.hpp"

// Namespaces
using namespace rebop;

CBebopInterface::CBebopInterface()
{

}

CBebopInterface::~CBebopInterface()
{
}


void CBebopInterface::Update()
{
	// TODO: Create a low frequency thread to manage reconnection behaviour and treat the entire interface as a subsystem
}

bool CBebopInterface::Takeoff()
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingTakeOff(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send takeoff command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate takeoff command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::setCameraAngle(int number) {
	CCommandPacket packet( 128 );
	LOG( INFO ) << "Entering method  - set camera angle.";
	LOG( INFO ) << number;
	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3CameraOrientation(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			number, number );
	LOG( INFO ) << "Command initiated - ARCOMMANDS_Generator_GenerateARDrone3CameraOrientation";
	LOG( INFO ) << cmdError;
	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send command - change angle.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate command - change angle. Err: " << cmdError;
		return false;
	}
	LOG( INFO ) << "Exiting method  - change angle.";
	return true;


}

bool CBebopInterface::takePicture(int number)
{
	CCommandPacket packet( 128 );
	LOG( INFO ) << "Entering method  - take picture.";
	LOG( INFO ) << number;
	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3MediaRecordPicture(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			number );
	LOG( INFO ) << "Command initiated - ARCOMMANDS_Generator_GenerateARDrone3MediaRecordPicture";
	LOG( INFO ) << cmdError;
	LOG( INFO ) << packet.m_pData;
	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send command - take picture.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate command - take picture. Err: " << cmdError;
		return false;
	}
	LOG( INFO ) << "Exiting method  - take picture.";
	return true;

}


bool CBebopInterface::sendPCMD(int number)
{

	CCommandPacket packet( 128 );
	LOG( INFO ) << "Entering method  - sendPCMD.";
	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingPCMD(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			0, //flag
			0, //roll
			0, //pitch
			number, //yaw
			0, //gaz
			0 //psi
		 );
	LOG( INFO ) << "Command initiated - ARCOMMANDS_Generator_GenerateARDrone3PilotingPCMD";
	LOG( INFO ) << cmdError;
	LOG( INFO ) << packet.m_pData;
	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send command - PCMD.";
			return false;
		}
		
	}
	else
	{
		LOG( ERROR ) << "Failed to generate command - PCMD. Err: " << cmdError;
		return false;
	}
	LOG( INFO ) << "Exiting method  - PCMD.";
	return true;
}

bool CBebopInterface::Land()
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingLanding(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send landing command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate landing command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::Emergency()
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingEmergency(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send emergency command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate emergency command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::NavigateHome( ENavigateHome startOrStopIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingNavigateHome(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			(uint8_t)startOrStopIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send NavigateHome command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate NavigateHome command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SendPilotCommand( const TPilotCommand& commandIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingPCMD(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			commandIn.flag,
			commandIn.roll,
			commandIn.pitch,
			commandIn.yaw,
			commandIn.gaz,
			commandIn.psi );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should not be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND, true ) )
		{
			LOG( ERROR ) << "Failed to send Pilot Command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate Pilot Command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetAutoTakeoffMode( EAutoTakeoffMode modeIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingAutoTakeOffMode(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			(uint8_t)modeIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send AutoTakeoffMode command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate AutoTakeoffMode command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::Flip( EFlipDirection directionIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3AnimationsFlip(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			(eARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION)directionIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send Flip command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate Flip command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetMaxAltitude( float maxAltitudeMetersIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingSettingsMaxAltitude(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			maxAltitudeMetersIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send AutoTakeoffMode command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate AutoTakeoffMode command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetMaxTilt( float maxTiltDegreesIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingSettingsMaxTilt(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			maxTiltDegreesIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send SetMaxTilt command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate SetMaxTilt command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetMaxVerticalSpeed( float maxVerticalSpeedMetersPerSecIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3SpeedSettingsMaxVerticalSpeed(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			maxVerticalSpeedMetersPerSecIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send SetMaxVerticalSpeed command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate SetMaxVerticalSpeed command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetMaxRotationSpeed( float maxRotationSpeedDegPerSecIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3SpeedSettingsMaxRotationSpeed(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			maxRotationSpeedDegPerSecIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send SetMaxRotationSpeed command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate SetMaxRotationSpeed command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetAbsoluteControlMode( EAbsoluteControlMode modeIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingSettingsAbsolutControl(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			(uint8_t)modeIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send SetAbsoluteControlMode command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate SetAbsoluteControlMode command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetHullProtectionPresence( EHullPresence presenceIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3SpeedSettingsHullProtection(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			(uint8_t)presenceIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send SetHullProtectionPresence command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate SetHullProtectionPresence command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetOutdoorMode( EOutdoorMode modeIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3SpeedSettingsOutdoor(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			(uint8_t)modeIn );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send SetOutdoorMode command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate SetOutdoorMode command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::SetGpsHomeLocation( const TGpsHomeLocation& locationIn )
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3GPSSettingsSetHome(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize,
			locationIn.latitude,
			locationIn.longitude,
			locationIn.altitude );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send SetGpsHomeLocation command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate SetGpsHomeLocation command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool rebop::CBebopInterface::FlatTrim()
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3PilotingFlatTrim(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send takeoff command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate flat trim command. Err: " << cmdError;
		return false;
	}

	return true;
}

bool CBebopInterface::ResetGpsHome()
{
	CCommandPacket packet( 128 );

	// Generate command
	eARCOMMANDS_GENERATOR_ERROR cmdError = ARCOMMANDS_Generator_GenerateARDrone3GPSSettingsResetHome(
			packet.m_pData,
			packet.m_bufferSize,
			&packet.m_dataSize );

	if( cmdError == ARCOMMANDS_GENERATOR_OK )
	{
		// Command should be acknowledged
		if( !m_networkInterface.SendData( packet, EOutboundBufferId::OUTBOUND_WITH_ACK, true ) )
		{
			LOG( ERROR ) << "Failed to send ResetGpsHome command.";
			return false;
		}
	}
	else
	{
		LOG( ERROR ) << "Failed to generate ResetGpsHome command. Err: " << cmdError;
		return false;
	}

	return true;
}
