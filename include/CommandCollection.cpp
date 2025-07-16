#include "CommandCollection.hpp"

namespace Emulator
{
	void CommandCollection::addFunctions(int8_t val, void(*callback)(const Emulator*, const CommandComparator&))
	{
		if (callback_functions_last_id >= CALLBACK_FUNCTIONS_SIZE)
		{
			throw TooManyCallbacks();
		}

		this->callback_functions[callback_functions_last_id] = callback;
		this->comporators[CommandComparator(val, 0b11111000)] = callback_functions_last_id++;
	}

	CommandCollection::CommandCollection()
	{
		// MOVA1
		addFunctions(0b00000, [](const Emulator* emul, const CommandComparator& comp) {
				
			});
	}
}