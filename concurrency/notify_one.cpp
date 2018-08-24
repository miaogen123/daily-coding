//试一下notify_one的对象为空的时候
//   即使所有等待线程没有被notify_one唤醒, 只要条件满足，也一定会有线程因为spurious wake并检查条件而唤醒 
#include<iostream>
#include<vector>
#include<string>
#include<chrono>
#include<thread>
#include<condition_variable>

using namespace std;

std::mutex testNotify_one;
std::condition_variable conVar;

void th1(int i){
	this_thread::sleep_for(std::chrono::seconds(2));
	std::unique_lock<std::mutex> lk(testNotify_one);
	conVar.wait(lk, [](){return true;});
	cout<<"i'm th"<<i<<endl;


}
void th2(){
	std::unique_lock<std::mutex> lk(testNotify_one);
	cout<<"hello world"<<endl;
	lk.unlock();
	conVar.notify_one();

}

int main(void)
{

	thread td1(th1, 1);
	thread td2(th2);
	thread td3(th1, 2);
	thread td4(th1, 3);
	td1.detach();
	td2.detach();
	td3.detach();
	td4.join();
	return 0;
}
