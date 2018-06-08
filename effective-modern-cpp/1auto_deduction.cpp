#include<iostream>

using namespace std;

decltype(auto) get_string_list(){
	return {1,2,3};
}

auto get_key(){
	return 24;
}

int main(void)
{
	auto x=27;
	auto xi(27);
	auto xid={12, 23, 23};
	auto xidc{23};

	//error:
	//auto xk={12, 3.0, 2 }
	for(auto temp :xid){
		cout<<temp<<"\t";
	}
	cout<< get_key()<<endl;

	return 0;
}
