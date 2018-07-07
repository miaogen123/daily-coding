#include<iostream>
#include<thread>
#include<chrono>
#include<future>

using namespace std;
using namespace std::literals;
//验证wait_for 死循环以及 really Async

void f()
{
	std::this_thread::sleep_for(1s);
}
template <typename T, typename... param>
inline std::future<typename std::result_of<T(param...)>::type>
ReallyAsync(T&& f, param&&... params){
	return async(std::launch::async, 
			std::forward<T>(f),
			std::forward<param>(params)...);
}

int main(void)
{
	auto futu=std::async(f);
	while(futu.wait_for(100ms)!=std::future_status::ready){}
	return 0;
}
