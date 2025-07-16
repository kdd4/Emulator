#include "Emulator.hpp"

#include <cstring>

namespace Emulator {

	Emulator::Emulator(int8_t memory[MEM_SIZE])
		: flag(0), program_cnt(0)
	{
		std::memcpy(this->memory, memory, MEM_SIZE);

		for (int ind = 0; ind < REGISTER_COUNT; ++ind)
		{
			regs[ind] = 0;
		}
	}

	int8_t Emulator::readNextByte()
	{
		this->program_cnt++;
		return this->memory[this->program_cnt];
	}

	int8_t Emulator::read(int8_t address, int8_t page) const
	{
		if (page < 0 || page > 7) 
		{
			throw WrongPage();
		}

		return this->memory[int(page) << 8 + address];
	}

	void Emulator::write(int8_t address, int8_t page, int8_t val)
	{
		if (page < 0 || page > 7)
		{
			throw WrongPage();
		}

		this->memory[int(page) << 8 + address] = val;
	}

	int8_t Emulator::getReg(int ind) const
	{
		if (ind < 0 || ind > 2)
		{
			throw WrongRegId();
		}

		return this->regs[ind];
	}

	void Emulator::setReg(int ind, int8_t val)
	{
		if (ind < 0 || ind > 2)
		{
			throw WrongRegId();
		}

		this->regs[ind] = val;
	}

	int Emulator::getFlag() const
	{
		return this->flag;
	}

	void Emulator::updateFlag(int8_t val, bool overfill = false)
	{
		this->flag = 0;

		if (overfill) {
			this->flag |= 1;
		}

		if (val < 0) {
			this->flag |= 2;
		}

		if (val != 0) {
			this->flag |= 4;
		}
	}

	void Emulator::setProgramCnt(int address, int8_t page)
	{
		if (page < 0 || page > 7)
		{
			throw WrongPage();
		}

		this->program_cnt = int(page) << 8 + address;
	}

	bool Emulator::cicle()
	{
		if (this->program_cnt >= MEM_SIZE) {
			return false;
		}

		int8_t command = this->memory[this->program_cnt];

		void (*callback_func)(IEmulator*, const CommandComparator&);

		commands.getFunction(command, callback_func);

		callback_func(this, command);
	}
}