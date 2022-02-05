#include "io.h"

int main()
{
	io::file f("F:/data.txt", "r");

	if (f.open() && f.mmap())
	{
		f.readline();
	}

	return 0;
}