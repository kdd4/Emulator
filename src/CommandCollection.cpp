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

				emulator->updateFlag(result, result >> 8 != 0);

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
				
				emulator->updateFlag(result, result >> 8 != 0);

				emulator->write(r3, page, result);
			});
	}
}