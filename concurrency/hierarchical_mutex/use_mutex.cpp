#include<iostream>
#include<thread>
#include<mutex>
#include<exception>

using namespace std;


class hierarchical_mutex
{
public:
	explicit hierarchical_mutex(unsigned long value) :
		hier_value(value),
		pre_hier_value(0)
	{}

	void lock()
	{
		check_for_hier_violation();
		internal_mutex.lock();
		update_hier_value();
	}
	void unlock(){
		if (this_thread_hier_value != hier_value) {
			throw std::logic_error("验证失败");
		}
		this_thread_hier_value = pre_hier_value;
		internal_mutex.unlock();
		//因为是prepre_hier_value是无符号值，-1后为取最大
		pre_hier_value = 0 - 1;
	}
	bool try_lock(){
		check_for_hier_violation();
		if (!internal_mutex.try_lock())
			return false;
		update_hier_value();
		return true;
	}
private:
	std::mutex internal_mutex;
	unsigned long const hier_value;
	unsigned long pre_hier_value;
	thread_local unsigned long this_thread_hier_value;
	//内容不多直接写在头文件里
	void check_for_hier_violation(){
		if (this_thread_hier_value < hier_value) {
			throw std::logic_error("锁继承等级出错");
		}
	}
	void update_hier_value() {
		pre_hier_value = this_thread_hier_value;
		this_thread_hier_value = hier_value;
	}

};

 thread_local unsigned long hierarchical_mutex::this_thread_hier_value(ULONG_MAX);


namespace {
	hierarchical_mutex M1(10000);
	hierarchical_mutex M2(1000);
	//std::mutex M1;
	//std::mutex M2;
}

void foo() {
	std::unique_lock<hierarchical_mutex> ul1(M1);
	std::unique_lock<hierarchical_mutex> ul2(M2);
	//std::unique_lock<mutex> ul1(M1);
	//std::unique_lock<mutex> ul2(M2);
	ul1.lock();
	ul2.lock();
}

int main(void) 
{
	hierarchical_mutex m1(10000);
	hierarchical_mutex m2(1000);
	//thread f1(foo);
	//f1.join();
	m2.lock();
	m1.lock()
	return 0;
}

