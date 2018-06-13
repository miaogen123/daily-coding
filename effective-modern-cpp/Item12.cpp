#include<iostream>
#include<vector>
#include<unordered_map>
#include<typeinfo>

using namespace std;


//Item7
//TODO: 把那个调用copy constructor的试一下
//TODO: 以及narrow conversion的
//TODO: 还有一个使用不同的构造函数的那个地方 
class Widget{
public:
	Widget(int temp, double temp2):temp_value(temp), temp_value2(temp2){
		cout<<"two arguments";
	};
	Widget(std::initializer_list<long double> init_list){
		cout<<"inside init_list"<<endl;
		for(const auto& temp:init_list ){
			cout<<temp<<endl;
		}
	}
	Widget()=delete;
	Widget(Widget& temp){
		std::cout<<"I'm in ";
		temp_value=temp.temp_value; 
	}
	string && re_right_value(){
		return "23";
	}
private:

	int temp_value;
	int temp_value2;
};


class MakeWidget{
public:
	Widget && re_right()&&{
		return std::move(Widget{2});
	}
};

int main(void)
{

	auto widget=MakeWidget().re_right;
	return 0;
}
