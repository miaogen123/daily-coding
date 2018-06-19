//if you do would like this code to run, use a lastest compiler
#include<iostream>

using namespace std;

class Temp{
public:
constexpr int get_compile_value(){
	//auto count=1;
	//for(auto an_count=2;an_count<3;an_count++){
	//	count+=an_count;
	//}
	return temp=23;
}

//modifiable
void temp_modify(){
	temp=23;
}
private:
	int temp;

};
int main(void)
{

	auto name=Temp().get_compile_value();
	//try to modify the name.
	name=15;
	cout<<name<<endl;
	return 0;
}

