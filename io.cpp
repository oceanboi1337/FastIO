#include "io.h"

#include <filesystem>

io::file::file(std::string path, std::string mode)
{
	this->path = path;
	this->mode = mode;

	this->index = 0;
	this->last_line = 0;
	this->lines = 0;
}

io::string io::file::readline()
{
	if (!this->is_open())
	{
#ifdef _DEBUG
		std::cerr << "readline(): file is not open." << std::endl;
#endif
		return io::string();
	}

	for (this->index = this->last_line; this->index < this->file_size; this->index++)
	{
		if (this->data[this->index] == '\n')
		{
			io::string tmp(this->data + this->last_line, this->index - this->last_line);

			this->last_line = this->index + 1;
			this->lines++;

			return tmp;
		}
	}

	return io::string(this->data + this->last_line, this->index - this->last_line);
}

std::size_t io::file::line_count()
{
	return this->lines;
}

bool io::file::open()
{
	fopen_s(&this->fd, this->path.c_str(), this->mode.c_str());

	if (this->fd)
	{
		this->file_size = std::filesystem::file_size(this->path);
	}

	return this->is_open();
}

bool io::file::is_open()
{
	if (this->fd)
	{
		return true;
	}

	return false;
}

bool io::file::eof()
{
	return !(this->index < this->file_size);
}

bool io::file::mmap()
{
	if (!this->is_open())
	{
#ifdef _DEBUG
		std::cerr << "mmap(): file is not open." << std::endl;
#endif
	}

	this->map_handle = CreateFileMapping((void*)_get_osfhandle(_fileno(this->fd)), NULL, PAGE_READONLY, 0, 0, NULL);

	if (this->map_handle != nullptr)
	{
		this->data = reinterpret_cast<char*>(MapViewOfFileEx(this->map_handle, FILE_MAP_READ, 0, 0, this->file_size, 0));

		return true;
	}
#ifdef _DEBUG
	std::cerr << "mmap(): failed to map file." << std::endl;
#endif
	return false;
}

io::string::string(char* ptr, std::size_t size)
{
	this->ptr = ptr;
	this->size = size;
}

std::ostream& io::operator<<(std::ostream& os, const io::string& string)
{
	os.write(string.ptr, string.size);
	return os;
}
