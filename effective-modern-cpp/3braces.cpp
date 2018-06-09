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
	Widget(Widget& temp){
		std::cout<<"I'm in ";
		temp_value=temp.temp_value; 
	}
private:

	int temp_value;
	int temp_value2;
};

int main(void)
{
	//copy constructor
	Widget small_widget(12, 23.234);
	cout<<endl;
	//Widget middle_widget{12, 23.234};
	//Widget middle_widget{{}};
	Widget middle_widget{};
	std::initializer_list<string> str_list{};
	std::initializer_list<string> int_list{};
	cout<<endl;
	cout<<"inside string";
	cout<<endl;
	for(const auto& temp:str_list){
		cout<<temp;
	}
	cout<<"inside int";
	cout<<endl;
	for(const auto& temp:int_list){
		cout<<temp;
	}
	//Widget middle_widget=small_widget;
	//narrow conversion
	//double x=10, y=12.3;
	//int z(x+y);
	//cout<<z<<endl;


	return 0;
}
