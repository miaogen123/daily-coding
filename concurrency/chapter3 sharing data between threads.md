### 读Chapter3的随笔

-   **多线程下的问题**：
-   竞争:
    -   解决办法: 限制访问；lock-free编程(复杂);使用事务transaction,事务要么完成要么失败重启，termed as STM(Software Transaction Memory)
-   c++17中出现了一个叫做模板参数检测的东西,所以 :

        std::lock_guard<std::mutex> Alock(Amutex)   //二者是一样的
        std::lock_guard Alock(Amutex)   //不很友好，很容易看成返回lock_guard的Alock函数
-   将全局lock封装进class，体现OO特性
-   后门机制：即便是被锁保护的资源，如果有指针或者引用指向该资源，那保护同样是无效的,**所以不要将pointer或者reference传入被保护变量中，也不要通过函数返回他，或是保存在内部变量中,简而言之,不要留出外部可以看到的接口**
-   另外有些竞争是由class interface 造成的，比如stack的top()和empty()操作，还有stack的pop操作，如果是先remove在将pop的元素传给另外的容器，就可能在构造的时候，出错，并且不可挽回
    - 可以直接将被传到的容器直接作为pop的参数,
    - 可以使用线程安全的m-c和c-c class,
    - 也可以用stack存储Pclass,即指针，但是每一个stack中对象都需要new出来，增加了负担，可以使用shared_ptr
-   书中实现一个thread_safe_stack,每一个操作内都要先获得class内的一个lock
-   std::lock(Args ...)可以一次封锁多个lock，用来解决多个资源的死锁问题，在获得了多个锁以后，为了避免忘记解锁导致死锁，最好及时的使用unique_lock或者lock_guard来拿到锁

        std::lock(lhs.m,rhs.m);
        std::lock_guard<std::mutex> lock_lhs(lhs.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock_rhs(rhs.m, std::adopt_lock);
        //adopt_lock是因为这两个锁都是已经拿到的锁，只要用adopt_lock获取所有权就可以了
-    std::lock 支持all-or-nothing 语义，全部锁上，或者一个都没有
-    c++17 支持scope_lock模板,一个人干了lock的RAII_lock两件事
-    其他的有一些死锁的例子()
    -    线程间循环等待结束，你join我，我join你
    -    多个锁使用，在拿到一锁以后，拿另外一把
    -    避免拿到锁以后，使用user-define 的代码，因为那部分代码是未知的
    -    如果非要获取多个锁，并且无法使用std::lock，那就保证锁的顺序是一致的
-   等级lock：多个锁获得时的防死锁的办法，相当于规定了锁的加锁顺序，**实现可以???选择是一个包含一个**
    -    利用thread_local变量,在每一个线程中存储一个自己的副本，每次加锁验证副本，副本大于类内const属性的值，才可以加锁。
-   线程局部变量：(同线程共存亡)
    -   命名空间内全局变量
    -   类内static变量(记得定义)
    -   局部变量
-   unique_lock的两种模式：一个是adopt_lock和defer_lock，分别是接管锁和延迟加锁,这使得unique_locck更加灵活，同时也cost a little more
    -   考虑到lock_guard也没有lock()与unlock()，try_lock，unique_lock的灵活性高了很多
-   拿锁的时间尽量减少
-   对于比较对象,如果需要比较，最好是在拿到两个对象的锁以后在比较，否则比较的就不是同一时刻的值
    -   有些对象访问可以不加锁，但初始化(费时间)需要加锁，如果使用mutex, 时间消耗比较大，这时可以考虑使用call_once&once_flag，对于可能在多处出现的只需要初始化一次的函数,每个地方都调用

               std::call_once(std::once_flag, function_obj, arguments)  //如果函数需要使用类内的成员的话，就需要把this传进去
               //这两个操作都是move-only
-   c\++11要求对于static变量只初始化一次，那个线程先到，谁初始化，不存在多次的初始化
-   对于读写者问题，c\++14提供了std::shared_timed_mutex, c++17还提供了std::shared_mutex,少了一些功能但性能好一点, 是否这二者真的有用与处理器核数以及读写的相关负载有关
    -   读者可以使用
        std::shared_lock\<std\::shared_mutex>  //  来共享读
    -   写者可以使用
        std::lock_guard\<std\::shared_mutex>  //  来独占写
-   std\::recursive_lock用来解决，在不释放的情况下的多次重锁，**这是一种坏的设计模式**
