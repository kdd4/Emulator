#include "CommandComparator.hpp"

namespace Emulator 
{

	CommandComparator::CommandComparator(int8_t val, int8_t mask = 0xFF)
		: val(val), mask(mask)
	{}

	bool CommandComparator::operator==(const CommandComparator& right) const
	{
		int8_t unitedMask = this->mask & right.mask;
		return ((this->val ^ right.val) & unitedMask) == 0;
	}

	int8_t CommandComparator::getMask() const
	{
		return this->mask;
	}

	void CommandComparator::setMask(int8_t mask)
	{
		this->mask = mask;
	}

	int8_t CommandComparator::getVal() const
	{
		return this->val;
	}

	void CommandComparator::setVal(int8_t val)
	{
		this->val = val;
	}

	int8_t CommandComparator::getPage() const
	{
		return (val >> 5) & 0x7;
	}
}