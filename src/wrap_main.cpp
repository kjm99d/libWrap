#include <stdio.h>
#include <string>
#pragma hdrstop

#pragma comment(lib, "libWrap.lib")
#include "wrap.h"


int main(int argc, const char* argv[])
{
	WRAP_FILE* f = new WRAP_FILE("E:\\ddd.txt", WRAP_FILE_OPEN_MODE::READ);
	f->Open();
	int s = f->Size();
	printf("Size = %d \n", s);

	void * buf = malloc((s * sizeof(char)) + 1);
	memset(buf, 0, s + 1);
	f->Read(buf, s);
	printf("String = %s", (char *)buf);


	
	f->Close();
	delete f;

	return 0;
}