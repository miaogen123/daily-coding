//https://blog.csdn.net/tcpipstack/article/details/45173633
//编写一个程序，程序会启动4个线程，向4个文件A，B，C，D里写入数据，每个线程只能写一个值。 
//    线程A：只写A
//    线程B：只写B 
//    线程C：只写C 
//    线程D：只写D 
//
//4个文件A，B，C，D。 
//
//程序运行起来，4个文件的写入结果如下： 
//    A：ABCDABCD... 
//    B：BCDABCDA... 
//    C：CDABCDAB... 
//    D：DABCDABC... 
//

#include<iostream>
#include<Windows.h>
#include<thread>
#include<exception>
#include<fstream>
#include<vector>
#include<string>
#include<condition_variable>
#include<mutex>


using namespace std;

std::mutex fourchamutex;
std::condition_variable waitCon;
char Gcha='A';

namespace {
	const int maxWriteTime=3;
}

class OfstreamList{
public:
	vector<ofstream> ofslist;
	OfstreamList(string fileA, string fileB, string fileC, string fileD){
		ofstream ofsA(fileA);
		ofstream ofsB(fileB);
		ofstream ofsC(fileC);
		ofstream ofsD(fileD);
		ofslist.push_back(std::move(ofsA));
		ofslist.push_back(std::move(ofsB));
		ofslist.push_back(std::move(ofsC));
		ofslist.push_back(std::move(ofsD));
	}

	void changeState(){
		if(count==3)
			Gcha=(Gcha-'A'+2)%4+'A';
		else
			Gcha=(Gcha-'A'+1)%4+'A';
		count=(count+1)%4;
	}

	ofstream& currentOfs(){
		int temp=count;
		changeState();
		return ofslist[temp];
	}
private:
	int count=0;
	char NextCha='B';
};

void stateChange(char cha){
	static OfstreamList  ofslist("A.txt", "B.txt", "C.txt", "D.txt");
	Sleep(100);
	ofslist.currentOfs()<<cha;
}

void WriteStdin(char cha){
	
	while(true){
		try{
			std::unique_lock<mutex> oneLock(fourchamutex);
			waitCon.wait(oneLock, [cha,&Gcha ](){return Gcha==cha;});
			stateChange(cha);
			oneLock.unlock();
			waitCon.notify_all();
		}catch(exception & e){
			cout<<e.what()<<endl;
		}
	}
}


int main(void)
{
	thread A, B, C,D;
	A=std::thread(WriteStdin, 'A');
	B=std::thread(WriteStdin, 'B');
	C=std::thread(WriteStdin, 'C');
	D=std::thread(WriteStdin, 'D');
	A.join();
	B.join();
	C.join();
	D.join();
	waitCon.notify_one();
	return 0;
}
