#pragma once

#include <cstdint>
#include <exception>

#include "IEmulator.hpp"
#include "CommandCollection.hpp"

#define MEM_SIZE 2048
#define REGISTER_COUNT 3

namespace Emulator {

	struct WrongPage : std::exception {
		virtual const char* what() const { return "Wrong page"; }
	};

	struct WrongRegId : std::exception {
		virtual const char* what() const { return "Wrong register id"; }
	};

	class Emulator : public IEmulator
	{
	private:
		int8_t memory[MEM_SIZE];
		int flag;
		int8_t regs[REGISTER_COUNT];
		short int program_cnt;

	public:
		Emulator(int8_t memory[MEM_SIZE]);
		int8_t readNextByte() override;

		int8_t read(int8_t address, int8_t page) const override;
		void write(int8_t address, int8_t page, int8_t val) override;

		int8_t getReg(int ind) const override;
		void setReg(int ind, int8_t val) override;

		/// 0 - overfill, 1 - less 0, 2 - not equal 0
		int getFlag() const override;

		/// 0 - overfill, 1 - less 0, 2 - not equal 0
		void updateFlag(int8_t val, bool overfill = false) override;

		bool cicle() override;
	};

}