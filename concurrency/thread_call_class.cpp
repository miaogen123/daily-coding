#include<iostream>
#include<memory>
#include<vector>
#include<exception>
#include<windows.h>
#include<string>
#include<thread>

using namespace std;

namespace {
	constexpr auto THREAD_BASIC_NUM=4;
}

class Hello
{
public:
	Hello(std::string argu=""):hell(argu){}
	//Hello(Hello &copid)=delete;
	std::string operator()(){
		std::cout<<"i'm in the Hello"<<endl;
		Sleep(3);
		std::cout<<"wake up"<<std::endl;
		return hell;
	}

private:
	std::string hell;
};

class thread_guard
{
	//用在要求join很严格的情况下
public:
	explicit thread_guard(std::thread& thr_in):thr(thr_in){}
	~thread_guard()
	{
		std::cout<<"i'm still alive"<<std::endl;
		if(thr.joinable()){
			thr.join();
		}
	}
	thread_guard(const thread_guard &)=delete;
	thread_guard& operator=(const thread_guard &)=delete;
private:
	//class 内定义对于变量的引用
	std::thread& thr;
};

int main(void)
{

	//test: hardware_councurrency
	//int thread_num=0;
	//if(std::thread::hardware_concurrency()==0){
	//	thread_num=THREAD_BASIC_NUM;
	//}else{
	//	thread_num=std::thread::hardware_concurrency();
	//}
	//cout<< "the num of concurrency ="<<thread_num<<endl;

	//test: the get_id() on unattached thread object;
	//thread temp_test_id;
	//try{
	//	cout<<temp_test_id.get_id()<<endl;
	//}catch(exception &e){
	//	cout<<e.what()<<endl;
	//}


	//test:output the chinese character, failed
	//try{
	//	locale loc("zh_CN.UTF-8");
	//	locale::global(loc);
	//}catch(exception &e){
	//	cout<<e.what()<<endl;
	//}

	Hello world;
	thread hello(world);
	thread_guard th_guard(hello);
	cout<<hello.get_id()<<endl;;
	cout<<"main end"<<endl;
	//thread hello([](){cout<<"hello world"<<endl

	thread test_lock([](unique_ptr<string> up_string){Sleep(3);std::cout<<*up_string;}, unique_ptr<string>(new string("i am MG")));
	thread test1([](){Sleep(2);cout<<"hh";});

	//test_lock=std::move(test1);
	//cout<<test_lock.get_id();
	//thread to_get(std::move(test_lock));
	//to_get.detach();

	//hello.detach();
	//Sleep(3);
	//if (hello.joinable()){
	//	cout<<"joinalbe"<<endl;
	//	hello.join();
	//}
	//else{
	//	cout<<"not joinalbe,you liar"<<endl;
	//}

	return 0;
}
