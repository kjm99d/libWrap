#pragma once

typedef enum _WRAP_FILE_OPEN_MODE {
	READ = 1,
	WRITE,
} WRAP_FILE_OPEN_MODE;

class WRAP_FILE {
public:
	WRAP_FILE();
	~WRAP_FILE();

	WRAP_FILE(const char *path, WRAP_FILE_OPEN_MODE mode);

	// ================================== //

	int Open();
	int Close();
	
	int Write(void *buffer, const int buffer_write_size);
	int Read(void *buffer, const int buffer_read_size);
	
	int Size();
	int Pos();
	

protected:
	void * fd;
	const char * path;
	WRAP_FILE_OPEN_MODE mode;
	int file_byte_size;

private:
	const char * wrap_open_type_to_fopen_type(WRAP_FILE_OPEN_MODE wrap_file_mode);
	bool check_wrap_open_read_write_permission(int call_type);

	int get_file_byte_size();
};