#include<iostream>
#include<windows.h>
#include<vector>
#include<string>
#include<thread>
#include<future>

using namespace std;

int f(std::future<int> fu){
	int n=fu.get();
	if(n==-1){
		throw std::logic_error("n is not allowed to be -1\n");
	}else{
		cout<<"hello world"<<endl;
	}
}
void p(int n){
	//int n=fu.get();
	if(n==-1){
		throw std::logic_error("n is not allowed to be -1\n");
	}else{
		cout<<"hello world"<<endl;
	}
}

int main(void)
{

	std::promise<int> hh;
	std::future<int> fu_one=hh.get_future();
	thread t1(f,fu_one);
	t1.join();
	Sleep(2);
	hh.set_value(2);

	return 0;
}
