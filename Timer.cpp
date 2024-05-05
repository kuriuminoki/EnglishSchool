#include "Timer.h"
#include "Define.h"

#include <sstream>
#include <string>


using namespace std;


string getTimeString(long long int cnt) {
	long long int seconds = cnt / FPS;
	long long int minutes = seconds / 60;
	long long int hour = minutes / 60;
	seconds %= 60;
	minutes %= 60;

	ostringstream oss;
	oss << hour << "ŽžŠÔ " << minutes << "•ª " << seconds << "•b";
	return oss.str();
}
