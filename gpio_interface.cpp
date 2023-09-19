///////////////////////////////////////////////////////////////////////////////
//!
//! @file		gpio_interface.cpp
//! 
//! @brief		Implementation of the gpio interface class
//! 
//! @author		Chip Brommer
//!
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Includes:
//          name                        reason included
//          --------------------        ---------------------------------------
#include	"gpio_interface.h"			// GPIO Interface Class
//
///////////////////////////////////////////////////////////////////////////////

namespace Essentials
{
	namespace Utilities
	{
		GpioInterface::GpioInterface(uint16_t gpio, GpioDirection direction = GpioDirection::IN) : mGpioNumber(gpio)
		{
			ExportGpio();

			SetDirection(direction);
		}

		GpioInterface::~GpioInterface()
		{
			UnexportGpio();
		}

		std::string GpioInterface::GetLastError()
		{
			return GpioErrorMap[mLastError];
		}

		std::string GpioInterface::GetGpioPath()
		{
			std::stringstream path;
			path << "/sys/class/gpio/gpio" << mGpioNumber << "/";
			return path.str();
		}

		int GpioInterface::SetValue(bool value)
		{
			// Path to the "edge" file
			std::string valueFilePath = GetGpioPath() + "value";

			// Write the edge string to the "edge" file
			std::ofstream valueFile(valueFilePath);
			if (!valueFile.is_open())
			{
				mLastError = GpioError::FILE_OPEN_FAILURE;
				return (int)mLastError;
			}

			valueFile << (value ? "1" : "0");
			return 0;
		}

		int GpioInterface::GetValue() 
		{
			// Path to the "value" file
			std::string valueFilePath = GetGpioPath() + "value";

			// Read the content of the "value" file
			std::ifstream valueFile(valueFilePath, std::ifstream::in);
			if (!valueFile.is_open())
			{
				mLastError = GpioError::FILE_OPEN_FAILURE;
				return (int)mLastError;
			}

			int value;
			valueFile >> value;
			return value;
		}

		int GpioInterface::SetEdge(GpioEdge edge)
		{
			std::string edgeStr;

			switch (edge)
			{
			case GpioEdge::NONE:	edgeStr = "none";		break;
			case GpioEdge::RISING:	edgeStr = "rising";		break;
			case GpioEdge::FALLING: edgeStr = "falling";	break;
			case GpioEdge::BOTH:	edgeStr = "both";		break;
			}

			// Path to the "edge" file
			std::string edgeFilePath = GetGpioPath() + "edge";

			// Write the edge string to the "edge" file
			std::ofstream edgeFile(edgeFilePath);
			if (!edgeFile.is_open())
			{
				mLastError = GpioError::SET_EDGE_FAILURE;
				return (int)mLastError;
			}
			edgeFile << edgeStr;
			return 0;
		}

		GpioEdge GpioInterface::GetEdge()
		{
			// Path to the "edge" file
			std::string directionFilePath = GetGpioPath() + "edge";

			// Read the content of the "direction" file
			std::ifstream directionFile(directionFilePath);
			if (!directionFile.is_open())
			{
				mLastError = GpioError::FILE_OPEN_FAILURE;
				return GpioEdge::UNKNOWN;
			}

			std::string edgeStr;
			directionFile >> edgeStr;

			// Map the string to the corresponding GpioDirection enum
			if (edgeStr == "none")
			{
				return GpioEdge::NONE;
			}
			else if (edgeStr == "rising")
			{
				return GpioEdge::RISING;
			}
			else if (edgeStr == "falling")
			{
				return GpioEdge::FALLING;
			}
			else if (edgeStr == "both")
			{
				return GpioEdge::BOTH;
			}
			else
			{
				return GpioEdge::UNKNOWN;
			}
		}

		int GpioInterface::SetDirection(GpioDirection direction)
		{
			std::string dir;

			switch (direction)
			{
				case GpioDirection::IN:		dir = "in";		break;
				case GpioDirection::OUT:	dir = "out";	break;
				default: mLastError = GpioError::BAD_DIRECTION; return (int)mLastError;
			}

			std::ofstream directionFile(GetGpioPath() + "direction");
			directionFile << dir;
			return 0;
		}

		GpioDirection GpioInterface::GetDirection()
		{
			// Path to the "direction" file
			std::string directionFilePath = GetGpioPath() + "direction";

			// Read the content of the "direction" file
			std::ifstream directionFile(directionFilePath);
			if (!directionFile.is_open())
			{
				mLastError = GpioError::FILE_OPEN_FAILURE;
				return GpioDirection::UNKNOWN;
			}

			std::string directionStr;
			directionFile >> directionStr;

			// Map the string to the corresponding GpioDirection enum
			if (directionStr == "in")
			{
				return GpioDirection::IN;
			}
			else if (directionStr == "out")
			{
				return GpioDirection::OUT;
			}
			else
			{
				return GpioDirection::UNKNOWN;
			}
		}

		void GpioInterface::ExportGpio()
		{
			std::ofstream exportFile("/sys/class/gpio/export");
			exportFile << mGpioNumber;
		}

		void GpioInterface::UnexportGpio()
		{
			std::ofstream unexportFile("/sys/class/gpio/unexport");
			unexportFile << mGpioNumber;
		}
    }
}