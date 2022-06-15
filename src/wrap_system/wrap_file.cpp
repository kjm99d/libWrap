#include <stdio.h>
#pragma hdrstop
#pragma warning(disable:4996)


#include "wrap_file.h"

WRAP_FILE::WRAP_FILE() : fd(nullptr)
{

}

WRAP_FILE::~WRAP_FILE()
{
	if (fd != NULL) {
		fclose((FILE*)fd);
		fd = NULL;
	}
}

WRAP_FILE::WRAP_FILE(const char *path, WRAP_FILE_OPEN_MODE wrap_file_mode)
{
	this->fd = NULL;

	this->path = path;
	this->mode = wrap_file_mode;
}

int WRAP_FILE::Open()
{
	int ret = -1;
	const char * path = this->path;
	const char * mode = wrap_open_type_to_fopen_type(this->mode);

	this->fd = (void *)fopen(path, mode);
	if (fd) 
	{
		ret = 1;
		//file_byte_size = get_file_byte_size();
	}

	return ret;
}

int WRAP_FILE::Close()
{
	if (fd != NULL) {
		fclose((FILE*)fd);
		fd = NULL;
	}

	return 1;
}

int WRAP_FILE::Write(void *buffer, const int buffer_write_size)
{
	int ret = -1;
	bool write_permission = check_wrap_open_read_write_permission(WRAP_FILE_OPEN_MODE::WRITE);
	if (write_permission)
	{
		ret = 1;

		size_t success_write_byte = fwrite(buffer, 1, buffer_write_size, (FILE *)fd);
		ret = (int)success_write_byte;
	}
	else {
		
	}


	return ret;
}

int WRAP_FILE::Read(void *buffer, const int buffer_read_size)
{
	int ret = -1;
	bool read_permission = check_wrap_open_read_write_permission(WRAP_FILE_OPEN_MODE::READ);
	if (read_permission)
	{
		ret = 1;

		size_t success_read_byte = fread(buffer, 1, buffer_read_size, (FILE *)fd);
		ret = (int)success_read_byte;
	}
	else {

	}



	return ret;
}

int WRAP_FILE::Size()
{
	return file_byte_size;
}

int WRAP_FILE::Pos()
{
	return ftell((FILE *)fd);
}

const char * WRAP_FILE::wrap_open_type_to_fopen_type(WRAP_FILE_OPEN_MODE wrap_file_mode)
{
	const char *ret;


	switch (wrap_file_mode)
	{
	case WRAP_FILE_OPEN_MODE::READ:
		ret = "rb";
		break;

	case WRAP_FILE_OPEN_MODE::WRITE:
		ret = "wb";
		break;
	default:
		ret = nullptr;
		break;
	}

	return ret;
}

bool WRAP_FILE::check_wrap_open_read_write_permission(int call_type)
{
	bool ret = false;

	if (mode == (call_type & mode)) {
		ret = true;
	}

	return ret;
}

int WRAP_FILE::get_file_byte_size()
{
	int ret = -1;
	int current_pos;
	current_pos = ftell((FILE *)fd);
	fseek((FILE *)fd, 0, SEEK_END);
	ret = ftell((FILE *)fd);
	fseek((FILE *)fd, current_pos, SEEK_SET);

	return ret;
}
