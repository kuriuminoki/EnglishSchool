#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <string>

std::string getTimeString(long long int cnt);

class StopWatch {
private:
	long long int m_cnt;

public:
	StopWatch() { m_cnt = 0; }

	inline void init() { m_cnt = 0; }

	inline void count() { m_cnt++; }

	inline long long int getCnt() const { return m_cnt; }

};

#endif