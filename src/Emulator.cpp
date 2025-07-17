#include "Emulator.hpp"

#include <cstring>
#include <iostream>

namespace Emulator {

	Emulator::Emulator(int8_t memory[MEM_SIZE])
		: flag(0), program_cnt(0), is_mem_changed(false)
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

		if (this->program_cnt >= MEM_SIZE) {
			return 0;
		}

		return this->memory[this->program_cnt];
	}

	int8_t Emulator::read(uint8_t address, uint8_t page) const
	{
		if (page < 0 || page > 7) 
		{
			throw WrongPage();
		}

		return this->memory[(int(page) << 8) + address];
	}

	void Emulator::write(uint8_t address, uint8_t page, int8_t val)
	{
		if (page < 0 || page > 7)
		{
			throw WrongPage();
		}

		this->memory[(int(page) << 8) + address] = val;
		is_mem_changed = true;
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

	void Emulator::updateFlag(int8_t val, bool overfill)
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

	void Emulator::setProgramCnt(uint8_t address, int8_t page)
	{
		if (page < 0 || page > 7)
		{
			throw WrongPage();
		}

		this->program_cnt = (int(page) << 8) + address - 1;
	}

	int Emulator::getProgramCnt() const
	{
		return this->program_cnt;
	}

	bool Emulator::getIsMemChanged() const
	{
		return is_mem_changed;
	}

	const int8_t* Emulator::getMemory() const
	{
		return memory;
	}

	int8_t* Emulator::getMemory()
	{
		return memory;
	}

	bool Emulator::cicle()
	{
		is_mem_changed = false;

		if (this->program_cnt >= MEM_SIZE) {
			return false;
		}

		int8_t command = this->memory[this->program_cnt];

		void (*callback_func)(IEmulator*, const CommandComparator&);

		commands.getFunction(command, callback_func);

		callback_func(this, command);

		this->program_cnt++;

		return true;
	}
}