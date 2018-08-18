#pragma
#include<exception>
#include<mutex>

#define UNLONG_MAX (0-1)

static thread_local unsigned long this_thread_hier_value(UNLONG_MAX);
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
	static thread_local unsigned long this_thread_hier_value;
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

