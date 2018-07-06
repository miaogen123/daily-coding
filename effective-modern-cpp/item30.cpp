
#include<vector>
#include<iostream>

using namespace std;
//TODO:1: 测试一下braced initializer的forward
//


//template <typename T>
void f(std::vector<int>& args)
{

}

template <typename... Ts>
void fwd(Ts&&... args)
{
	f(std::forward<Ts>(args)...);
}



int main(void)
{


	return 0;
}
