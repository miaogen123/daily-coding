### 读Chapter4的随笔

***
#### Item 18 Use std::unique_ptr for exclusive-ownership resource management
-   默认的std::unique_ptr<*> 可以认为与raw_pointers的大小是一样的，当你使用自定义的deleter的时候就不一样了
    具体大小取决于你的function state，若是captureless lamda那么对象大小就是没有发生改变，如果是function
    或者是带状态的lamda,unique_prt的大小就会发生改变
-   std::unique_ptr有带[]和不带[]两种形式one for individual objects (std::
unique_ptr<T>) and one for arrays (std::unique_ptr<T[]>). 使用的话就跟单对象和多对象数组的区别一样
-   Pimpl Idiom:指向实现的指针(这种trick用在类的实现中很方便，可以隐藏被指向类的变化，达到封装的效果)
    带状态的lamda比较适合这种,在**Item22**有具体解释，先占个坑，回头再答
-   还有就是unique_ptr可以直接转换为shared_ptr，简直不能在方便了有木有

#### Item 19 Use std::shared_ptr for shared-ownership resource management
-   shared_ptr 的大小是raw pointer的2倍，他还额外包括了一个指向control block的对象，之中包括引用计数,weak_number, 以及自定义的deleter和alloctor if have.
-   shared_ptr一般情况下只能指向动态分配的内存，但是make_shared可以避免这样的存储开销
-   因为shared_ptr在进行reference count的修改的时候，需要是原子操作，**也就意味着，如果系统是时间要求很高的，就不能使用该指针或者说需要注意该指针带来的性能消耗**
-   如果使用move进行shared_ptr的ownership tranferring，这个过程不涉及引用计数的修改(原子操作),性能损耗会小很多
-   **不像unique_ptr，自定义的deleter不用放在模板参数里面，这样给了shared_ptr相当大的灵活性，所有的shared_ptr都是可以互换共享的**
-   AS for control block(CB),make_shared保证会产生一个CB，当从unique_ptr构造shared_ptr时也会创造一个CB, shared_ptr从一个raw pointer构造时会产生CB,
    如果想要把一个已经存在CB的对象传给shared_ptr，可以直接传送一个weak_ptr或shared_ptr.
-   **尽可能的不要把一个raw pointer 传给一个shared_ptr, multi-control-block 会出现，你的头会变大**
-   Curiously Recurring Template Pattern (CRTP) 用法：CRTP的出现是为了兼顾多态性以及效率，短的继承对于效率来讲，
    不是大的影响，关键是长的多重继承会影响效率，CRTP的出现兼顾二者，具体看这篇文章![C++ 惯用法 CRTP 简介 ](https://liam0205.me/2016/11/26/Introduction-to-CRTP-in-Cpp/)
-   std::enable_shared_from_this:给予一个有shared_ptr管理的对象，以用this 生成一个shared_ptr对象的能力.也就是提供了将this这个raw pointer 转变成shared_ptr的能力。最主要的是防止多个shared_ptr对象的生成. 
-   shared_ptr里面甚至存在virtual function用来释放对象，好在只有在对象释放的时候才调用
-   shared_ptr和unique_ptr不同的地方是：**unique_ptr提供指向原始数组的能力，而shared_ptr不提供，如果你需要的话可以选择使用std\::array,std\::vector**

#### Item 20  Use std\::weak_ptr for std::shared_ptr like pointers that can dangle. 
-   weak_ptr不能解引，也不能测试是否为空，他不是一个人，一般来说，他会与shared_ptr配合
-   weak_ptr可以用在缓存中，weak_ptr.lock()返回一个shared_ptr对象，如果指针之前是空的,即weak_ptr指向的对象已经被消除，那么得到的shared_ptr对象是nullptr
-   weak_ptr可以用在观察者模式中，因为被观察者只是想要知道观察者是否存在，而不会想去操作观察者，weak_ptr是一个相当匹配的选择
-   当然weak_ptr可以用来解决循环引用的问题，这个自然是不能被忘掉的
-   有一点需要注意的是在shared_ptr的CB中，含有一个与weak_ptr有关的计数，see next item.

***

