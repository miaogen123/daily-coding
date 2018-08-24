//通过sleep函数,测试async的两种launch方式
#include<iostream>
#include<vector>
#include<string>
#include<future>
#include<windows.h>

using namespace std;

int sleep3sec(){
	Sleep(3000);
	cout<<"hello  world"<<endl;
	return 0;
}

int main(void)
{

	//auto retVal=std::async(std::launch::deferred, sleep3sec);   //7s
	auto retVal=std::async(std::launch::async, sleep3sec);    //3s
	Sleep(3000);
	cout<<retVal.get()<<endl;

	return 0;
}
