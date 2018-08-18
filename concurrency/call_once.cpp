#include<iostream>
#include<thread>
#include<mutex>	
#include<vector>
#include<string>

using namespace std;

class TestCallOnce
{
public:	
	TestCallOnce(){}
	void init(){
		hello=new temp;
		std::cout<<"i'm initing\n";
	}
	int getvi1(){
		call_once(IsInitFlag, init, this);
		cout<<"1 out "<<hello->vi[1];
		return hello->vi[1];
	}
	int getvi2(){
		call_once(IsInitFlag, init, this);
		cout<<"2 out "<<hello->vi[0];
		return hello->vi[0];
	}
private:
	class temp{
		public:
			std::vector<int> vi {100, 10};
	};
	temp* hello;
	std::once_flag IsInitFlag;
};
int main(void)
{

	TestCallOnce temp1;
	thread t1(TestCallOnce::getvi1, &temp1);
	thread t2(TestCallOnce::getvi2,&temp1);
	t1.join();
	t2.join();
	return 0;
}
