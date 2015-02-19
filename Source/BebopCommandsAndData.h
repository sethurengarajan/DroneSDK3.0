#pragma once

// Enumerations
namespace rebop
{
	namespace bebop
	{
		enum class ENavCommands
		{
			FlatTrim,
			Takeoff,
			SetPose,
			Land,
			Emergency,
			NavigateHome,
			SetAutoTakeoffMode,
			Flip,
			SetMaxAltitude,
			SetMaxTilt,
			SetAbsoluteControl,
			SetMaxVerticalSpeed,
			SetMaxRotationSpeed,
			SetHullProtectionPresence,
			SetOutdoorMode,
			SetGpsHome,
			ResetGpsHome
		};

		enum class EMediaCommands
		{
			RecordPicture,
			RecordVideo,
			SetCameraOrientation,
			SetPictureFormatSelection,
			SetAutoWhiteBalanceSelection,
			SetExposureSelection,
			SetExpositionSelection,
			SetSaturationSelection,
			SetTimelapseSelection,
			SetVideoAutorecordSelection
		};

		enum class ENetworkCommands
		{
			LaunchWifiScan,
			InquireAuthChannels,
			SetWifiSelection
		};

		enum class EDebugCommands
		{
			VideoEnableWobbleCancellation,
			VideoSyncAngleGyros,
			VideoManualWhiteBalance,
			UseDrone2Battery
		};
	}
}

// Data structures
namespace rebop
{
	// Command structures
	namespace commands
	{
		namespace bebop
		{
			// Nav commands
			namespace navigation
			{
				struct TPilotCommand
				{
					uint8_t flag;		// Boolean flag to activate roll/pitch movement
					int8_t roll;		// Roll consign for the drone 								[-100:100] Normalized
					int8_t pitch;		// Pitch consign for the drone 								[-100:100] Normalized
					int8_t yaw;			// Yaw rate consign for the drone 							[-100:100] Normalized
					int8_t gaz;			// Altitude rate consign for the drone 						[-100:100] Normalized
					int8_t psi;			// Magnetic north heading of the controlling device (deg) 	[-180:180] Degrees
				};

				struct TGpsHomeLocation
				{
					double latitude;	// Decimal degrees
					double longitude;	// Decimal degrees
					double altitude;	// Meters
				};

				enum class ENavigateHome
				{
					STOP 	= 0,
					START 	= 1
				};

				enum class EAutoTakeoffMode
				{
					DISABLED 	= 0,
					ENABLED 	= 1
				};

				enum class EFlipDirection
				{
					FRONT = eARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION::ARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION_FRONT,
					BACK = eARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION::ARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION_BACK,
					RIGHT = eARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION::ARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION_RIGHT,
					LEFT = eARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION::ARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION_LEFT,
					MAX = eARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION::ARCOMMANDS_ARDRONE3_ANIMATIONS_FLIP_DIRECTION_MAX
				};

				enum class EAbsoluteControlMode
				{
					DISABLED 	= 0,
					ENABLED 	= 1
				};

				enum class EHullPresence
				{
					NOT_PRESENT = 0,
					PRESENT 	= 1
				};

				enum class EOutdoorMode
				{
					INDOOR		= 0,
					OUTDOOR		= 1
				};
			}
		}
	}
}
