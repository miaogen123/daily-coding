### 读Chapter4的随笔

#### Item 18 Use std::unique_ptr for exclusive-ownership resource management
-   默认的std::unique_ptr<*> 可以认为与raw_pointers的大小是一样的，当你使用自定义的deleter的时候就不一样了
    具体大小取决于你的function state，若是captureless lamda那么对象大小就是没有发生改变，如果是function
    或者是带状态的lamda,unique_prt的大小就会发生改变
-   std::unique_ptr有带[]和不带[]两种形式one for individual objects (std::
unique_ptr<T>) and one for arrays (std::unique_ptr<T[]>). 使用的话就跟单对象和多对象数组的区别一样
-   Pimpl Idiom:指向实现的指针(这种trick用在类的实现中很方便，可以隐藏被指向类的变化，达到封装的效果)
    带状态的lamda比较适合这种,在**Item22**有具体解释，先占个坑，回头再答
-   还有就是unique_ptr可以直接转换为shared_ptr，简直不能在方便了有木有
***
