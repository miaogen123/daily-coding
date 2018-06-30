#include<iostream>
#include<string>
#include<vector>

using namespace std;
template<typename T>
void f(std::vector<T>&& param);

void p(std::vector<string>&& tp)
{
	auto youga=std::move(tp);
	cout<<youga[1]<<endl;
}

int main(void)
{

	auto para("hhhh");
	std::vector<std::string> vec={para, "niho"};
	//下面的是错误的
	//f(vec);
	p(std::move(vec));
	//static_assert(vec[0]);
	for(const auto &temp:vec){
		cout<<temp<<endl;
		cout<<"inside"<<endl;
	}
	//Do not use a move on lvalue.
	//cout<<vec[0]<<endl;
	cout<<"inside"<<endl;
	return 0;
}


template<typename T>
void f(T&& param){
	cout<<param<<endl;
}
