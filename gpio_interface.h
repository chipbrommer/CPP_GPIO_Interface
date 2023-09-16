///////////////////////////////////////////////////////////////////////////////
//!
//! @file		gpio_interface.h
//! 
//! @brief		A linux class to represent and handle interfacing with a GPIO
//! 
//! @author		Chip Brommer
//!
///////////////////////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////////////////////
//
//  Includes:
//          name                        reason included
//          --------------------        ---------------------------------------
#include <string>						// Strings
#include <iostream>						// IO
#include <map>							// Error map
//
//	Defines:
//          name                        reason defined
//          --------------------        ---------------------------------------
#ifndef     GPIO_H						// Define the gpio class 
#define     GPIO_H
// 
///////////////////////////////////////////////////////////////////////////////

namespace Essentials
{
	namespace Utilities
	{
		const static uint8_t GPIO_VERSION_MAJOR = 0;
		const static uint8_t GPIO_VERSION_MINOR = 1;
		const static uint8_t GPIO_VERSION_PATCH = 0;
		const static uint8_t GPIO_VERSION_BUILD = 0;

		/// @brief Printable string of the class version
		const static std::string GpioVersion = "GPIO Interface v" +
			std::to_string(GPIO_VERSION_MAJOR) + "." +
			std::to_string(GPIO_VERSION_MINOR) + "." +
			std::to_string(GPIO_VERSION_PATCH) + " - b" +
			std::to_string(GPIO_VERSION_BUILD) + ".\n";

		/// @brief class enum for error codes
		enum class GpioError : uint8_t
		{
			NONE,
		};

		/// @brief class enum for edge types
		enum class GpioEdge : uint8_t
		{
			NONE,
			RISING,
			FALLING,
			BOTH
		};

		enum class GpioDirection : uint8_t
		{
			IN,
			OUT
		};

		/// @brief Error enum to readable string conversion map
		static std::map<GpioError, std::string> TerminalErrorMap
		{
			{GpioError::NONE,
				std::string("Error Code " + std::to_string((uint8_t)GpioError::NONE) + ": No error.")},
		};

		/// @brief A class to interface with GPIOs 
		class GpioInterface
		{
		public:
			GpioInterface(uint16_t gpio, GpioDirection direction);
			~GpioInterface();
			std::string GetLastError();
			std::string GetGpioPath();
			void SetValue();
			void GetValue();
			std::string GetValueFilePath();
			void SetEdge(GpioEdge edge);
			GpioEdge GetEdge();
			std::string GetEdgeFilePath();
			void SetDirection(GpioDirection direction);
			GpioDirection GetDirection();
			
		protected:
		private:
			void ExportGpio();
			void UnexportGpio();

			GpioError	mLastError;
			const uint16_t	mGpioNumber;
		};
	}
}

#endif