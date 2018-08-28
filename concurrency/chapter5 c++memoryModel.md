### 读Chapter5的随笔

****

-   两个层次：一个是基础结构，另外一个是并发层面
-   c++ 标准把object 定义为 a region of storage
-   连续的位可能具有相同的地址
-   一个程序一处发生了undefined behavior, 整个程序都会变得undefined behavior
-   修改顺序(Modification orders)：每一个对象都有一个修改顺序,**这里对于修改顺序的描述不是很懂**
-   每一个atomic对象都含有一个is_lock_free(),true:使用的是原子操作完成，false:使用的是内部的锁机制, **除了atmoic_flag(不等于std::atomic<bool>), 他一直都是lock-free**
-   使用internal mutex的atmoic<>某种程度上并不如自己写的lock-free
-   C\++17 提供了is_always_lock_free的方法，当且仅当在所有的平台上都是这样的时候才可以
-   有很多的marco可以用来判断lock-free
-   对于 完全支持c\++17的compiler，有很多的 alias来代表相应的atomic, 但尽量还是用atomic\<T>声明，一来简单，二来移植性好
-   atomic不支持copy-c, 也不支持assign-c:两个不同的操作在不同的对象是不可能atomic的
-   每一个操作on atomic都有一个可选的 memory  ordering 参数，
-   **?as such, i'd never expect to see it in use**
-   std::atomic_flag一定是需要以ATOMIC_FLAG_INIT来初始化
-   对于atomic type的操作都有分类，不同的分类对应于不同的memory ordering
-   使用atomic_flag实现自旋锁(spin lock)
-   atomic对象赋值操作返回的值为by value
-   store替换，exchange替换并返回，load返回(或者隐式转换也能完成获取值的操作)
-   c++ 并发中，compare_exchange的出现是一个转折点 **??**, 参数有两个一个expected value, 一个desire value,相等时设置为desire value, 不相等时expected val设置为atomic\<T>的val

        //对于compare_exchange_weak 的spurious failure，的处理
        bool expected =false; extern atomic<bool> b;
        while(!b.compare_exchange_weak(expected, true)&&!expected);
-   对于计算简单的expected值，使用com_exc_weak到没有问题,但如果运算量大，为保证正确最好使用strong版本
-   对于atomic<T*>相对于std::atomic<bool>多出来的操作包括前后++，--， +=， -=， 以及fatch_add(), fatch_sub()
-   fatch_add()与fatch_sub()采用swap的办法, 更新值，然后返回更新之前的值
-   对于user-define-type(UDT),在满足一下条件情况下也可以作为atomic的T
    -   have a trival copy-ass-operator.(**copy-assignment-operator:不能有虚函数，虚基类并且必须使用编译器生成的copy-assignment operator**)
    -   该UDP的每个基类和non-static的data member都必须要有trival copy-ass operator
-   UDP的copy-ass op 是通过直接memcpy来的，直接对bit进行操作，比较也是，只有bit级完全相同的才会是相等的
-   对于float和double在atomic里的exchange是有可能因为表示形式不同而失败的。
-   double-word-compare-and-swap(DWCAS):对于int双倍大小的UDT,同样可以使用atomic指令
-   复杂类型的UDT最好是使用mutex而非atomic,**对方法的支持见table5.3**
-   对于非成员函数的针对atomic的操作，一般以atomic_开头如atomic_load(), 对于加了_explicit的后缀需要加上memory ordering.
-   为了和c兼容，free mem没有采用ref而是使用了指针来作为参数传入
-   stl提供访问shared_ptr实例的atomic操作，比如针对shared_ptr\<T> p的std\::atomic_load(&p)和std::std_atomic_store(&p, local);
-   EXP文件中提供了一个atomic_shared_ptr\<T>,这个类型对原来的shared_ptr没有附加的cost,相较于atomic<shared_ptr>更推荐使用前者

****
**MEAT**

-   synchronizes-with relationship:只发生在atomic type之间
-   六种memory ordering tag：
    -  memory_order_seq_cst 是默认使用的类型
    -  sequentially consistent ordering  (memory_order_seq_cst), acquire release ordering（memory_order_acquire, memory_order_consume, memory_order_release, mem_order_acq_rel),relaxed ordering(memory_order_relaxed)
    -  这些细粒度的memory ordering是为了更高的性能
-  Sequentially consistent ordering
    -  使用memory_order_seq_cst 的进程看到的操作的顺序是一样的，但是需要所有相关的线程都使用这种memory_order_seq_cst  ordering
    -  在所有线程相同的顺序可能是相当的费时间的操作，如果有很多个线程需要同步
-  Non-Sequentially consistent ordering
    -  线程的所有顺序不一定是一致的
    -  **Relaxed ordering**
    -  with relaxed ordering 只有每一个共享变量的修改是被分享
    -  不同变量间的执行顺序是可以reorder的，不想sequentially ordering
    -  一个变量对于不同线程的返回值可以是不一致的，随性的，X读y变量，然后修改y变量，Z再去读y变量，y可能告诉Z读之前的也可能是读之后的
    -  因为relaxed ordering 太过灵活，所以并**不建议使用**
-  Acquire and release
    -  acquire和release 需要成对使用，才能发挥同步的作用
    -  不同线程之间对 Acquire and release的使用会记录相应的信息，不像relax的任意取值返回，load操作对于A-a-R要求返回对应的store的值
    -   对一个变量的读且写操作需要使用memory_order_acq_rel，才能完成同步
    -   pairwise的A-a-R操作是相对于全局mutex的一简单的实现方式
    -  对于memory_order_consume：**建议是不要使用**
-  Release sequence
    -  允许使用memory_order_acquire的R-a-W操作release，对于多个读者可进行序列化的R-a-W操作
-  Fence
   -  又叫memory barrier，加了一道杠类似于锁
-  使用atomic 同步non-atomic
   -  
****