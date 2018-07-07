### 读Chapter7的随笔

***
####  Item 35: Prefer task-based programming to threadbased.

-   给出software thread 的几个缺点;
    -   线程数目受限：当线程数超过限制以后，即使函数被声明为noexcept，同样会报std::system_error
    -   oversubscription:这里是指线程在不同的cpu调度时出现的性能下降
-   std::async()保证在你需要这个返回结果的时候，scheduler保证这个结果是可以求出的
-   在一些情况下，thread 可能更合适(少数)
    -   需要访问线程的底层实现API（pthread or win32实现）
    -   需要自己优化线程的使用
    -   需要实现一些基于thread的技术，如thread pool

####  Item 36:Specify std::launch::async if asynchronicity is essential.

-   默认的std::async()可能是同步运行也可能是异步运行，取决于具体情况
-   显式的有两种启动方式，std\::launch\::async和std\::launch\::defererd，前者立即执行，后者等到get或者wait被调用的时候,
    默认的policy是这两者的或运算
-   对于defered的异步任务调用wait_for或者wait_until会产生std\::future_status\::deferred

####  Item 37:Make std::threads unjoinable on all paths

-   class的成员函数在初始化的时候，按照其被声明的顺序初始化，所以将thread对象放在最后声明，可以是使thread在其他的条件具备了以后，在进行初始化并运行
-   std::thread 只有在调用成员函数join，detach，或者进行了move操作时，才会从joinable -> unjoinable
-   对一个joinable的thread 进行destructor会导致程序终止，这是为什么要保证unjoinable on all way.也是为什么在 c++ concurrency in action中作者建议，对于thread对象，拿到以后要吗就join要么就detach别延误

####  Item 38: Be aware of varying thread handle destructor behavior.

-   **有点难**,容我找到中文版拜读一下

####  Item 39: Consider void futures for one-shot event communication.

-   多线程同步的问题：提前唤醒，导致reacting thread 永久等待; spurious wakeup(虚假唤醒):
-   对于条件变量，使用lambda表达式，在lambda里面判断唤醒条件是否满足，来防止虚假唤醒
-   在上下文切换时间很短的时候，可以是atmoic<bool> flag 来进行同步
-   两个进程之间的话，使用future或者shared_future,（使用future的痛点在于，一次性操作，使用heap 内存)

####  Item 40: Use std::atomic for concurrency, volatile for special memory.

-   在atmoic对象被赋值的时候，确保了编译器不会擅自的reorder your code.但如果atomic 对象的赋值之后的变量赋值，被赋值者是一个volatile,则可以被reorder
-   volatile 用在memory-mapping I/O上，可以避免违反目的的编译器优化
-   volatile std::atomic\<int> vai; //这样声明可以用来在并发情况下访问特殊内存
***


