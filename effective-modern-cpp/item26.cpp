#include<iostream>
#include<string>

using namespace std;
class T_base
{
public:
	template<typename T>
	T_base(T&& tmp):tp(std::forward<T>(tmp)){std::cout<<"inside the template "<<endl;}
	
	//error
	template<>
	T_base(string&& tmp):tp(tmp){std::cout<<"inside the specifial ctor"<<endl;}

	T_base(const T_base& rhs)=default;
private:
	string tp;

};

class T_derived:public T_base
{
public:
	T_derived(string tp1,string tp2 ):tp1(tp1), T_base(tp2){
		//T_base(tp2);
	}
private:
	std::string tp1;
};


int main(void)
{

	const auto tmp("hello");
	const T_base u_r_test(tmp);

	cout<<"auto copy"<<endl;
	auto new_T(u_r_test);

	cout<<"derived class "<<endl;
	T_derived t_d("hello", "world"); 
	return 0;
}
