#include<iostream>
#include<vector>
#include<unordered_map>
#include<typeinfo>

using namespace std;

// with universal reference you can pass a constant to template
template<typename T>
decltype(auto) re_tu(T&& a, T&&b){
	return a+b;
}

int main(void)
{

	cout<<"the int add "<<endl;
	cout<<re_tu<int>(1, 2)<<endl;
	cout<<"the float add "<<endl;
	cout<<re_tu<double>(1.0, 2.3)<<endl;
	return 0;
}
