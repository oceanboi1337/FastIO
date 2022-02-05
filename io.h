#include <Windows.h>
#include <io.h>
#include <fstream>
#include <iostream>

namespace io
{
	class file
	{
	private:
		void* map_handle;
		void* data;

		FILE* fd;

		std::string path;
		std::string mode;
		std::size_t file_size;

	public:
		file(std::string path, std::string mode);

		std::string readline();

		bool open();
		bool is_open();
		bool mmap();
	};
}