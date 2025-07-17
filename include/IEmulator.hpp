#pragma once

#include <cstdint>

namespace Emulator {

	class IEmulator 
	{
	public:
		virtual int8_t readNextByte() = 0;

		virtual int8_t read(uint8_t address, uint8_t page) const = 0;
		virtual void write(uint8_t address, uint8_t page, int8_t val) = 0;

		virtual int8_t getReg(int ind) const = 0;
		virtual void setReg(int ind, int8_t val) = 0;

		/// 0 - overfill, 1 - less 0, 2 - not equal 0
		virtual int getFlag() const = 0;

		/// 0 - overfill, 1 - less 0, 2 - not equal 0
		virtual void updateFlag(int8_t val, bool overfill = false) = 0;

		virtual void setProgramCnt(uint8_t address, int8_t page) = 0;
	};

}