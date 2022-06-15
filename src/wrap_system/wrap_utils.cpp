#include "wrap_utils.h"
// ======================================================================= //
TimeDiff::TimeDiff() : current(0.0), expired(0.0)
{
	//struct tm* t;
	current = time(NULL); // 1970�� 1�� 1�� 0�� 0�� 0�ʺ��� �����Ͽ� ��������� ��
	//t = localtime(&current); // �������� ���� ����ü�� �ֱ�
}

TimeDiff::~TimeDiff()
{

}
void TimeDiff::SetExpired(int year, int month, int day)
{
	struct tm time_next;
	time_next.tm_year = year - 1900;
	time_next.tm_mon = month - 1;
	time_next.tm_mday = day;
	time_next.tm_hour = 0;
	time_next.tm_min = 0;
	time_next.tm_sec = 0;
	time_next.tm_isdst = 0;

	expired = mktime(&time_next);
}
bool TimeDiff::Check()
{
	double diff = difftime(expired, current);
	if (diff > 0) {
		return true;
	}
	else {
		return false;
	}
}
// ======================================================================= //