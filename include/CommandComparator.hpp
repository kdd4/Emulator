#pragma once
#include <cstdint>

namespace Emulator 
{

	class CommandComparator
	{
	private:
		int8_t val;
		int8_t mask;

	public:
		CommandComparator(int8_t val, int8_t mask = 0xFF);

		bool operator==(const CommandComparator& right) const;
		bool operator!=(const CommandComparator& right) const;

		int8_t getMask() const;
		void setMask(int8_t mask);

		int8_t getVal() const;
		void setVal(int8_t val);

		int8_t getPage() const;
	};

}