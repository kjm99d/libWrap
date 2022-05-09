#ifdef _WIN32
#include <Windows.h>
#endif
#pragma hdrstop
#include "wrap_security.h"


int GetDiskSerialNumber(const char *partition)
{
#if _WIN32
	DWORD ret = -1; // partition serial number
#else
	int ret = -1; // partition serial number
#endif
	const char * target;

	if (partition == nullptr) {
#if _WIN32
		target = "C:\\";
#else
		target = "/dev/sda1";

#endif
	}
	else {
		target = partition;
	}

#ifdef _WIN32
	DWORD sn;
	GetVolumeInformationA("C:\\", NULL, 0, &sn, NULL, NULL, NULL, 0);
	ret = sn;
#else
	printf("Not Supported ! \n");
#endif


	return ret;
}
