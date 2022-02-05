#include <Windows.h>
#include <io.h>
#include <fstream>
#include <iostream>

namespace io
{
	using std::operator<<;

	class string
	{
	private:
		char* ptr;
		std::size_t size;

	public:
		string(char* ptr = nullptr, std::size_t size = 0);

		friend std::ostream& operator<<(std::ostream& os, const io::string& string);
	};

	class file
	{
	private:
		FILE* fd;

		void* map_handle;
		char* data;

		std::size_t index;
		std::size_t last_line;
		std::size_t lines;

		std::string path;
		std::string mode;
		std::size_t file_size;

	public:
		file(std::string path, std::string mode);

		io::string readline();

		std::size_t line_count();

		bool open();
		bool is_open();
		bool eof();
		bool mmap();
	};
}