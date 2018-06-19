#include <iostream>
#include <exception>
using namespace std;

void pay_eff() noexcept
{
    try
    {
        int* myarray= new int[10000000000];
    }
    catch (exception& e)
    {
        cout << "Standard exception: " << e.what() << endl;
    }
    return ;
}

int main () {
	pay_eff();
}
