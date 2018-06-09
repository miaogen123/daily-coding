#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

void f(int ){
	cout<<" int";
}
void f(bool){
	cout<<" bool";
}
void f(int *){
	cout<<" void *";
}
int main(void)
{
	cout<<"call f(null)"<<endl;
	//f(NULL);   //error
	cout<<"call f(0)"<<endl;
	//f(0);   //output:int
	f((void *)0);   //output bool
	cout<<"call f(nullptr)"<<endl;
	f(nullptr);   //output: void *
	return 0;
}
