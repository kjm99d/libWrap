#pragma once
// ======================================================================= //
#if __cplusplus
#include <ctime> //C++
#else
#include <time.h> // C
#endif
// ======================================================================= //
class TimeDiff {
public:
	TimeDiff();
	~TimeDiff();

	void SetExpired(int year, int month, int day);
	bool Check();

private:
	time_t current;
	time_t expired;
};
// ======================================================================= //