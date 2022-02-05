#include "io.h"

int main()
{
	io::file f("F:/data.txt", "r");

	if (f.open() && f.mmap())
	{
		while (!f.eof())
		{
			io::string line = f.readline();

			if (f.line_count() % 1000000 == 0) 
			{
				std::cout << f.line_count() << '\t' << line << std::endl;
			}
		}
	}

	return 0;
}