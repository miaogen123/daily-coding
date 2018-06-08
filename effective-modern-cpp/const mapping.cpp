#include<iostream>
#include<vector>
#include<unordered_map>
#include<typeinfo>

using namespace std;


//Item6
vector<bool> features()
{
	vector<bool> temp{1, 0, 1, 0, 0};
	return temp;
}

int main(void)
{
	std::unordered_map<std::string, int > m;
	m["hello"]=2;
	m["world"]=3;
	for(const std::pair<std::string, int> &temp:m){
		cout<<temp.first<<endl;
		cout<<typeid(temp.first).name()<<endl;
	}
	const string ss("nihao");
	cout<<"the type of const string "<< typeid(ss).name()<<endl;

	auto temp_bool_list=features()[2];
	cout<<temp_bool_list<<endl;

	return 0;
}
