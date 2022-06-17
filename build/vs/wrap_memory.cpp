#include "wrap_memory.h"
// ======================================================================= //
DWORD MemoryPointer::GetPtr(DWORD base, DWORD offset)
{
	
	return *(PDWORD)(base + offset);
}
// ======================================================================= //