#include "CommandComparator.hpp"
#include "CommandCollection.hpp"

namespace Emulator 
{
	void CommandCollection::addFunctions(int8_t val, void(*callback)(IEmulator*, const CommandComparator&))
	{
		if (this->callback_functions_last_id >= CALLBACK_FUNCTIONS_SIZE)
		{
			throw TooManyCallbacks();
		}

		this->callback_functions[callback_functions_last_id] = callback;
		this->comporators[CommandComparator(val, 0b00011111)] = callback_functions_last_id++;
	}

	CommandCollection::CommandCollection()
	{
		// MOV A1
		addFunctions(0b00000, [](IEmulator* emulator, const CommandComparator& command) 
			{
				int8_t constant = emulator->readNextByte();
				emulator->setReg(0, constant);
			});

		// MOV A2
		addFunctions(0b00001, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t constant = emulator->readNextByte();
				emulator->setReg(1, constant);
			});

		// MOV A3
		addFunctions(0b00010, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t constant = emulator->readNextByte();
				emulator->setReg(2, constant);
			});

		// ADD
		addFunctions(0b00100, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) + emulator->read(r2, page);

				emulator->updateFlag(result, result != int8_t(result));

				emulator->write(r3, page, result);
			});

		// ADC
		addFunctions(0b00101, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = emulator->read(r1, page) + emulator->read(r2, page) + emulator->getFlag() & 1;
				
				emulator->updateFlag(result, result != int8_t(result));

				emulator->write(r3, page, result);
			});

		// SUB
		addFunctions(0b00100, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) - emulator->read(r2, page);

				emulator->updateFlag(result, result != int8_t(result));

				emulator->write(r3, page, result);
			});

		// SBB
		addFunctions(0b00101, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = emulator->read(r1, page) - emulator->read(r2, page) - emulator->getFlag() & 1;

				emulator->updateFlag(result, result != int8_t(result));

				emulator->write(r3, page, result);
			});

		// MUL
		addFunctions(0b01000, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) * emulator->read(r2, page);

				emulator->updateFlag(result, result != int8_t(result));

				emulator->write(r3, page, result);
			});

		// DIV
		addFunctions(0b01001, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) / emulator->read(r2, page);

				emulator->updateFlag(result, false);

				emulator->write(r3, page, result);
			});

		// MOD
		addFunctions(0b01010, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) % emulator->read(r2, page);

				emulator->updateFlag(result, false);

				emulator->write(r3, page, result);
			});

		// ABS
		addFunctions(0b01011, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r3 = emulator->getReg(2);

				int result = abs(emulator->read(r1, page));

				emulator->updateFlag(result, false);

				emulator->write(r3, page, result);
			});

		// AND
		addFunctions(0b01100, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) & emulator->read(r2, page);

				emulator->updateFlag(result, false);

				emulator->write(r3, page, result);
			});

		// OR
		addFunctions(0b01101, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) | emulator->read(r2, page);

				emulator->updateFlag(result, false);

				emulator->write(r3, page, result);
			});

		// XOR
		addFunctions(0b01110, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r2 = emulator->getReg(1);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) ^ emulator->read(r2, page);

				emulator->updateFlag(result, false);

				emulator->write(r3, page, result);
			});

		// NOT
		addFunctions(0b01111, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r3 = emulator->getReg(2);

				int result = ~emulator->read(r1, page);

				emulator->updateFlag(result, false);

				emulator->write(r3, page, result);
			});

		// JMP
		addFunctions(0b10000, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r3 = emulator->getReg(2);

				emulator->setProgramCnt(r3, page);
			});

		// JB
		addFunctions(0b10001, [](IEmulator* emulator, const CommandComparator& command)
			{
				if (((emulator->getFlag() >> 1) & 1) != 1) {
					return;
				}

				int8_t page = command.getPage();
				int8_t r3 = emulator->getReg(2);

				emulator->setProgramCnt(r3, page);
			});

		// JNZ
		addFunctions(0b10010, [](IEmulator* emulator, const CommandComparator& command)
			{
				if (((emulator->getFlag() >> 2) & 1) != 1) {
					return;
				}

				int8_t page = command.getPage();
				int8_t r3 = emulator->getReg(2);

				emulator->setProgramCnt(r3, page);
			});

		// MOVS
		addFunctions(0b10101, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r3 = emulator->getReg(2);

				emulator->write(r3, page, emulator->read(r1, page));

				emulator->setReg(0, r1 + 1);
				emulator->setReg(2, r3 + 1);
			});

		// CMPS
		addFunctions(0b10111, [](IEmulator* emulator, const CommandComparator& command)
			{
				int8_t page = command.getPage();
				int8_t r1 = emulator->getReg(0);
				int8_t r3 = emulator->getReg(2);

				int result = (int)emulator->read(r1, page) - emulator->read(r3, page);

				emulator->updateFlag(result, result != int8_t(result));
			});
	}

	void CommandCollection::getFunction(int8_t command, void(*callback)(IEmulator*, const CommandComparator&)) const
	{
		int func_ind = comporators.at(CommandComparator(command));

		callback = callback_functions[func_ind];
	}
}