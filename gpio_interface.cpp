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
			return "";
		}

		std::string GpioInterface::GetGpioPath()
		{
			return "";
		}

		void GpioInterface::SetValue()
		{
		
		}

		void GpioInterface::GetValue() 
		{
		
		}

		std::string GpioInterface::GetValueFilePath()
		{
			return "";
		}

		void GpioInterface::SetEdge(GpioEdge edge)
		{
		
		}

		GpioEdge GpioInterface::GetEdge()
		{
		
		}

		std::string GpioInterface::GetEdgeFilePath()
		{
			return "";
		}

		void GpioInterface::SetDirection(GpioDirection direction)
		{
		
		}

		GpioDirection GpioInterface::GetDirection()
		{
		
		}

		void GpioInterface::ExportGpio()
		{

		}

		void GpioInterface::UnexportGpio()
		{

		}
    }
}