#include<iostream>
#include<vector>
#include<unordered_map>
#include<typeinfo>
#include<memory>

using namespace std;


int main(void)
{
	//test the size of std::unique_ptr<*, lamda>  which is with a customed deleter.

	std::unique_ptr<string> p_str(new string("hello"));
	cout<<"p_str of string is"<<sizeof(p_str)<<endl;

	auto del_str=[](string* parr){delete parr;};
	std::unique_ptr<string, decltype(del_str)> p_str_bak(new string("world"),del_str);
	cout<<"p_str_bak of string is"<<sizeof(p_str)<<endl;

	//p_str和p_str_bak大小都是8，一个指针的大小

	//测试一下带有capture value 的lamda 传给unique_ptr造成大小变化
	auto str_in_lamda("temp");
	auto del_str_val=[&str_in_lamda](string* parr){delete parr;str_in_lamda="temp2";};
	std::unique_ptr<string, decltype(del_str)> p_str_bak_val(new string("world"),del_str(str_in_lamda));
	cout<<"p_str_bak of string is"<<sizeof(p_str_bak_val)<<endl;
	//带参数的lamda在unique_ptr 咋用的？

	//std::unique_ptr<string[]> string_arr(new string[3]{"nihao", "zheshi", "wode"});
	//cout<<"string_arr of 3 string is"<<sizeof(string_arr)<<endl;
	//auto del_arr= [](string *p_arr){delete []p_arr;};
	//std::unique_ptr<string[],decltype(del_arr)> string_arr(new string[3]{"nihao", "zheshi", "wode"});
	//cout<<"string_arr_bak of 3 string is"<<sizeof(string_arr)<<endl;


	//code below is for fun
	//using array=string[];
	//array mem={"nihao","dddd"};
	//for(const auto temp :mem){
	//	cout<<temp<<endl;
	//}
	//delete mem;
	//end "code below is for fun"
	return 0;
}
