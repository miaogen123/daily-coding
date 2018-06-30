#include<iostream>
#include<Windows.h>
#include<string>
#include<thread>
#include<vector>

using namespace std;

void get_word(string &key_word ){
	while( key_word!= "exit"){
		cin>>key_word;
	}
}

int main(void)
{

	string key_word("");
	thread asyn_io(get_word,std::ref(key_word));
	asyn_io.detach();
	while(1){
		Sleep(1000);
		cout<<"the key_word="<<key_word<<endl;
	}
	return 0;
}
