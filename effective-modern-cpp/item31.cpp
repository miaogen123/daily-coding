#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
//TODO:1测试一下static 与[=]
//TODO:2[] 捕获全部

void help()
{
	auto h=0;
	vector<int> kkk{1,2,3,3};
	auto  temp=std::find_if(kkk.begin(),kkk.end(), [=](int value){return value>h;});
	cout<<*temp<<endl;
}

int main(void)
{
	help();

	return 0;
} 
