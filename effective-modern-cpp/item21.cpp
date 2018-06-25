#include<iostream>
#include<memory>
#include<string>
#include<chrono>
#include<vector>

using namespace std;

namespace {
	const auto CIRCLE_TIMES=1000000;
}

class Temp
{
public:
	Temp(std::string name):here(name){}
private:
	string here;
};

class Temp_Test{
public:
	Temp_Test(std::string temp="default"):big(temp){}
	Temp_Test(const Temp_Test& copy){
		std::cout<<"i'm in the Test copy "<<endl;
		big=copy.big;
	}
	const auto out_string(){
		return big;
	}
   Temp_Test(Temp_Test && moved){
    	std::cout<<"i'm in the Test move "<<moved.out_string()<<endl;
    	big=moved.big;
    }
    void set_string(std::string && in){
		big=in;
	}
private:
	string big;
};


int main(void)
{

	using chrono::microseconds;
	auto count=0;
	auto start = chrono::system_clock::now();
	for (count=0;count<CIRCLE_TIMES;count++){
		shared_ptr<Temp_Test> tmp(new Temp_Test("hhhhhheeee"));
	}
	auto end   = chrono::system_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

	//test with make
	auto start_make = chrono::system_clock::now();
	for (count=0;count<CIRCLE_TIMES;count++){
		auto tmp=make_shared<Temp_Test>("hhhhhheeee");
	}
	auto end_make   = chrono::system_clock::now();
	auto duration_make = chrono::duration_cast<chrono::microseconds>(end_make - start_make);
	cout<<"time without make="<<double(duration.count()) * microseconds::period::num / microseconds::period::den<<endl;
	cout<<"time with make="<<double(duration_make.count()) * microseconds::period::num / microseconds::period::den<<endl;
	return 0;
}
