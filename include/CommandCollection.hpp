#pragma once

#include "CommandComparator.hpp"
#include "IEmulator.hpp"

#include <vector>
#include <exception>

#define CALLBACK_FUNCTIONS_SIZE 20

namespace Emulator 
{
	struct TooManyCallbacks : std::exception {
		virtual const char* what() const { return "Too many functions' callbacks"; }
	};

	struct CommandNotFound : std::exception {
		virtual const char* what() const { return "Command not found"; }
	};

	class CommandCollection 
	{
	private:
		std::vector<std::pair<CommandComparator, int>> comporators;

		void (*callback_functions[CALLBACK_FUNCTIONS_SIZE])(IEmulator*, const CommandComparator&);
		int callback_functions_last_id = 0;

		void addFunctions(int8_t val, void(*callback)(IEmulator*, const CommandComparator&));

	public:
		CommandCollection();

		void getFunction(int8_t command, void(*&callback)(IEmulator*, const CommandComparator&)) const;
	};
}