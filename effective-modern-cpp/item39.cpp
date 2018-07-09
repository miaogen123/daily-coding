#include<iostream>
#include<windows.h>
#include<atomic>
#include<thread>
#include<chrono>
#include<future> 
using namespace std;
using namespace std::literals;
//
//测试一下利用future来同步


std::promise<void> commu_channel;
std::atomic<bool> poll_flag(false);
std::condition_variable cv; 

void f()
{
	std::this_thread::sleep_for(1s);
}

//FIXME:: 下面的 这个模板 有问题
template <typename T, typename... param>
inline std::future<typename std::result_of<T(param...)>::type>
ReallyAsync(T&& f, param&&... params){
	return async(std::launch::async, 
			std::forward<T>(f),
			std::forward<param>(params)...);
}


void react()
{
	std::cout<<"hello i'm in the react"<<endl;
}

void detect()
{

	cout<<"inside the detect!!!"<<endl;
	thread to_react([](){commu_channel.get_future().wait();react();});
	to_react.detach();
	while(!poll_flag)
		Sleep(1);
	commu_channel.set_value();

}

int main(void)
{
	
	cout<<"ready to work!!!"<<endl;
	//ReallyAsync(detect);
	auto detect_async=std::async(std::launch::async,detect);
	cout<<"to work!!!"<<endl;

	poll_flag=true;
	auto futu=std::async(f);
	while(futu.wait_for(100ms)!=std::future_status::ready){}
	return 0;

}
