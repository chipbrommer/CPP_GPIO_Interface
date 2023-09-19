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
#include <fstream>						// file stream
#include <sstream>						// string stream
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
		enum class GpioError : int8_t
		{
			NONE				= 0,
			FILE_OPEN_FAILURE	= -1,
			SET_EDGE_FAILURE	= -2,
			BAD_DIRECTION		= -3
		};

		/// @brief class enum for edge types
		enum class GpioEdge : uint8_t
		{
			NONE,
			RISING,
			FALLING,
			BOTH,
			UNKNOWN
		};

		enum class GpioDirection : uint8_t
		{
			IN,
			OUT,
			UNKNOWN
		};

		/// @brief Error enum to readable string conversion map
		static std::map<GpioError, std::string> GpioErrorMap
		{
			{GpioError::NONE,				std::string("No error.")},
			{GpioError::FILE_OPEN_FAILURE,	std::string("Failed to open file.")},
			{GpioError::SET_EDGE_FAILURE,	std::string("Failed to set gpio edge.")},
			{GpioError::BAD_DIRECTION,		std::string("Received invalid direction.")},
		};

		/// @brief A class to interface with GPIOs 
		class GpioInterface
		{
		public:
			GpioInterface(uint16_t gpio, GpioDirection direction);
			~GpioInterface();
			std::string GetLastError();
			std::string GetGpioPath();
			int SetValue(bool value);
			int GetValue();
			int SetEdge(GpioEdge edge);
			GpioEdge GetEdge();
			int SetDirection(GpioDirection direction);
			GpioDirection GetDirection();
			
		protected:
		private:
			void ExportGpio();
			void UnexportGpio();

			GpioError		mLastError;
			const uint16_t	mGpioNumber;
		};
	}
}

#endif