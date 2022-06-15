#include <stdio.h>
#include <string>
#include <Windows.h>
#pragma hdrstop

#pragma comment(lib, "libWrap.lib")
#include "wrap.h"


int main(int argc, const char* argv[])
{
	while (true)
	{
		WRAP_FILE* f = new WRAP_FILE("E:\\ddd.txt", WRAP_FILE_OPEN_MODE::WRITE);
		f->Open();
		int s = 10;
		printf("Size = %d \n", s);

		void * buf = malloc((s * sizeof(char)) + 1);
		memset(buf, 65, s + 1);
		int r = f->Write(buf, s);
		printf("String [%d] = %s",r, (char *)buf);



		f->Close();
		delete f;
		printf("Write \n");
		//break;

		Sleep(3000);

	}
	return 0;
}