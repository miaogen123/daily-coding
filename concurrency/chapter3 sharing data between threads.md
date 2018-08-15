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