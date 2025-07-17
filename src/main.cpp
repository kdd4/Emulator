#include <iostream>ì
#include <vector>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include "Emulator.hpp"

int main()
{
	signed char code[MEM_SIZE];

	#ifdef _WIN32
	_setmode(_fileno(stdin), _O_BINARY);
	#endif

	std::vector<signed char> buffer(
		(std::istreambuf_iterator<char>(std::cin)),
		std::istreambuf_iterator<char>()
	);

	if (buffer.size() > MEM_SIZE)
	{
		std::cout << "Error: wrong data size" << std::endl;
		return 2;
	}

	memcpy_s(code, MEM_SIZE, buffer.data(), buffer.size());

	Emulator::Emulator emul(code);

	printf("prog_cnt,A1,A2,A3,{mem | -}\n");

	try 
	{
		while (emul.cicle())
		{
			int prog_cnt = emul.getProgramCnt();
			int A1 = emul.getReg(0), A2 = emul.getReg(1), A3 = emul.getReg(2);

			printf("%d,%d,%d,%d,", prog_cnt, A1, A2, A3);

			if (emul.getIsMemChanged()) 
			{
				std::cout.write((char*)emul.getMemory(), MEM_SIZE);
				std::cout << std::endl;
			}
			else
			{
				printf(",-\n");
			}
		}
	}
	catch (std::exception& exc) 
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}

	return 0;
}