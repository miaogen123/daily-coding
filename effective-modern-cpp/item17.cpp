//to test whether move operation is  deleted when declaring the copy operation
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<typeinfo>

using namespace std;

class Test{
public:
	Test(std::string temp="default"):big(temp){}
	Test(const Test& copy){
		std::cout<<"i'm in the Test copy "<<endl;
		big=copy.big;
	}
	const auto out_string(){
		return big;
	}
   Test(Test && moved){
    	std::cout<<"i'm in the Test move "<<moved.out_string()<<endl;
    	big=moved.big;
    }
    void set_string(std::string && in){
		big=in;
	}
private:
	string big;
	struct home{
		string new_st;
		string new_de;
		vector<std::string> heom;
		vector<std::string> hm;
		vector<std::string> ho;
		vector<std::string> hh;
	};
};

int main(void)
{

	Test temp1;
	cout<<temp1.out_string()<<endl;

	Test temp2("i'm yours");
	//讲道理下面使用的move，但是却没有显示move constructor的消息
	Test temp3(std::move(temp2));

	cout<<temp2.out_string()<<endl;
	cout<<temp3.out_string()<<endl;

	cout<<&temp2<<endl;
	cout<<&temp3<<endl;

	temp2.set_string("nihao");

	cout<<temp2.out_string()<<endl;
	cout<<temp3.out_string()<<endl;

	//测试类内定义一个类，而不调用，会不会增加类本身的大小,
	//buhui
	cout<< sizeof(temp2)<<endl;
	return 0;
}
