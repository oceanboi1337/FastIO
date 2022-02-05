#include "io.h"

#include <filesystem>

io::file::file(std::string path, std::string mode)
{
	this->path = path;
	this->mode = mode;
}

std::string io::file::readline()
{

}

bool io::file::open()
{
	fopen_s(&this->fd, this->path.c_str(), this->mode.c_str());

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

bool io::file::mmap()
{
	if (!this->is_open())
	{
#ifdef _DEBUG
		std::cerr << "mmap(): file is not open." << std::endl;
#endif
	}

	this->map_handle = CreateFileMapping((void*)_get_osfhandle(_fileno(this->fd)), NULL, PAGE_READWRITE | OF_SHARE_DENY_WRITE, 0, 0, NULL);

	if (this->map_handle != nullptr)
	{
		this->file_size = std::filesystem::file_size(this->path);

		this->data = MapViewOfFileEx(this->map_handle, FILE_MAP_READ, 0, 0, this->file_size, 0);

		return true;
	}
#ifdef _DEBUG
	std::cerr << "mmap(): failed to map file." << std::endl;
#endif
	return false;
}