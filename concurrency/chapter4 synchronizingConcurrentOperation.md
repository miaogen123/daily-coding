### 读Chapter4的随笔

****

-   使用条件变量来同步, **std\::conditional_variable和std\::conditional_variable_any**, 前者只能使用mutex,后者可使用任何满足条件的类(性能上会有一定损耗)
-   即使所有等待线程没有被notify_one唤醒, 只要条件满足，也一定会有线程因为spurious wake并检查条件而唤醒 
-   使用条件变量一定会用到锁，对于只是起到通知作用的线程来说，可以使用花括号+guard_lock降低时间损耗
-   与条件变量配套使用的锁应该支持lock与unlock
-   spurious wake:线程在等待锁和条件过程中的唤醒检查，次数不定，如果条件变量使用了含有side-effects的函数,可能会发生多次的副作用
-   对于member const 成员函数，如果内部有锁的话，锁是需要声明为mutable的，因为对于锁的操作是mutable的
-   又一次的接触了future对象，这次是通过条件变量引出的，上次是modern effective cpp中的
-   future obj:suitable for one-off event.
-   async:第一个参数如果是类成员函数的指针，那么第二个参数是类本身，或者指针或者std::ref()修饰一下
-   std\::packed_task和std\::promise:前者是后者的高阶抽象:promise只是设置了共享的状态,而packed_task则在内部完成了一个task,
    -    std\::packed_task<int(double)> 非完全匹配, 参数可以使用int，返回值也可使用double
    -    从std::packed_task用get_future得到future对象
    -    std::通过std\::packed_task向thread 传递任务，另一个线程用来获取任务的结果。
    -    可以直接调用
-   同std::packed_task类似,std\::promise同样和std\::future配对使用，同样有get_future方法，当promise使用set_value方法，对应的等待future会得到通知，如果promise被销毁，会有一个exception 存储起来(std\::packed_task也会),(书上讲了一个细节，标准没有规定保存的exception是引用还是一个copy)
-   std::promise有一个叫做set_exception方法用来设置exception
    -   一种办法是使用try...catch语句，在catch里面设置 some_promise.set_exception(std::current_exception());
    -   另一种是直接使用some_promise.set_exception(std::make_exception_ptr(std\::logic_error("出错"))
    -   或者直接destory promise(std::packed_task)
-   std::shared_future可供多个线程进行异步读取
-   std::future 中的数据只允许被读取一次
-   future提供了.share()方法可以用来创建一个future的备份，进而创建shared_future
-   时钟的时钟周期是用分数来表示的，如std::ratio<1,25>意思是每秒25次tick, 程序运行时的时钟周期并非是一成不变的
-   steady_clock：是指时钟周期不会发生改变的clock,像std::chrono\::system_clock就不是一个steady_clock
-   还有一个时钟是std::chrono\::high_resolution_clock.
-   chrono中还有duration模板,第一个参数相当于个数，第二个相当于单位,使用分数std\::ratio<>, 如std::duration<int, std\::ratio<1,10>> 就意味着每一个int里面都有1/10个秒
-   chrono有很多predefine typedef, 如nanosecond,microsecond,等
-   c\++14提供了一些trick,std::chrono_literals如15ns,16ms等,
-   duration的转化可以使用duration_cast<目标单位>, 但转化是truncated，not rounded，
-   同时duration也支持加减乘除的运算
-   future的wait函数返回3种状态future_status::time_out, ready, deferred
-   std::time_point使用两个参数，第一个是指明使用的时钟，第二个是使用的单位
-   条件变量也是可使用时间的的,如wait_for，wait_until
-   time_mutex和recursive_mutex也是支持时间点的
-   functional_programming(FP):函数的返回值与参数有关,与外部的状态无关， **复习的时候补一下FP的内容**
-   CSP paradigm：所有线程都是概念上完全单独的，但是可以通过channel通信，又叫做**Actor model**
-   书上的ATM的例子给我的感觉是，就像是一个**状态机式的编程**, 每一个状态的处理与改变都需要有消息，这样的编程模式，对于并发来讲简单是简单了，对于变化性较大的程序,**估计很难胜任**，因为程序的状态过多，不易理解与维护
-   std::experimental空间下属的packed_task, promise, future 提供了对于continuation的支持, 相较于std\::future，experimental下的三个函数提供了直接添加后续函数的功能
-   当原来的EXP\::future调用then()方法以后，原来的future就不在有效(only use once),同时返回一个新的EXP\::future
-   continuation func不能被传参数,他的参数应该是确定了的，他的唯一参数由依赖的EXP::future 决定, **详见chapter4-4.3**
-   在线程内部

        try{
            p.set_value_at_thread_exit(value);
        }catch{
            p.set_exception_at_thread_exit(std::current_exception());
        }//通过这样的方法来设置返回值，或者返回时异常
-   对于一系列的task,如果不想主进程被影响,可以使用EXP的then()这样一连串的lambda来做
-   continuation提供了一个有趣(nifty)的特性future_unwrapping：对于.then()传入continuation FUNC(CONFUN), 如果confun返回一个future<some_type>那么，then返回的不是一个future<future<some_type>>, 而是unwrapping 的future<some_type>
-   **4.4.5节的listing4.22提到#1的代码会被重复唤醒,不知道为什么，个人理解，每一次get只对一个future的状态进行监听，其他的future状态会影响？？**
-   标准提供了std\::EXP::shared_future,允许多个对象调用then(),使用共享状态
-   std\::EXP::when_all: 针对需要等待多个future的情况，当所有的vector中所有的future完成了的时候，返回一个future<vector<future<some_type>>>，方便进行处理
-   std\::EXP\::when_any与std\::EXP::when_all相对的特性，任何一个ready都将触发操作
-   when_any和when_all(除了使用迭代器以外)都支持variadic参数，此时的返回值是一个对应的future<some_type>>的tuple,而且参数(future)都是by value，所以可以显式的使用std::move(f1),传入参数(4.4.6),如果使用的是一对迭代器，返回的则是一个vector
-   std\::EXP\::latch是一个计数器，当值为0时变成ready, std\::EXP\::barrier,则保证当相关的线程都到达此点的时候，才会进行下一步
-   **4.4.8对于latch调用count_down操作和调用wait操作是同步??**
-   latch提供的方法：count_down, wait, is_ready_,count_down_and_wait.
-   barrier提供的方法：arrive_and_wait, arrive_and_drop
-   barrier同步的时候还是需要一个count，内部可能使用了latch
-   flex_barrier相对于barrier灵活的地方是，前者多了一个构造函数，允许在thread_num之外再加上一个Func，**Func返回-1则表示线程数目不变,返回0 or more 会指定下一轮的thread_count**
-   **??但flex_barrier的thread_count发生改变了以后，下一论运行的线程是怎么样，比如线程数量减少了**
****
