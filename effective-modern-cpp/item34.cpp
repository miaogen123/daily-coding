#include<iostream>
#include<chrono>

using namespace std;
//验证新标准的标准后缀的使用

using Time=std::chrono::steady_clock::time_point;
using Duration=std::chrono::steady_clock::duration;

void setAlarm(Time t, Duration d){

}

int main(void)
{
	using namespace std::chrono;
	using namespace std::literals;

	//挺好使的
	setAlarm(steady_clock::now(), 30s);
	


	return 0;
}
