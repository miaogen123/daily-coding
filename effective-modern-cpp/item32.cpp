#include<iostream>
#include<functional>

using namespace std;
//可以验证c++14 的init capture(generalized lambda capture)
//以及使用std::bind 在C++11下模拟
class Widget
{
	public:
	Widget(){	}
	Widget(const Widget& rhs){cout<<"hello copy"<<endl;}
	Widget& operator=(Widget&& rhs){cout<<"hello move"<<endl;return rhs;}
};



int main(void)
{
	Widget temp;
	//事实上，这里还是进行了copy ctor
	auto hello=[data=std::move(temp)]{};
	//c++11
	auto hello_2=std::bind([](const auto &temp){}, std::move(temp));

	return 0;
}
