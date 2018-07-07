### 读Chapter6的随笔

***
####  Item 31:Avoid default capture modes

-   lambda会默认生成一个closure class，lamda中的可执行代码就相当于class中的mem-func
-   capture 只针对于局部非static变量,对于non-static的成员函数，每一个有一个默认的this指针
-   对于non-static local mem-func，的捕获   

        void Widget::addFilter() const
        {
            auto divisorCopy = divisor; // copy data member
            filters.emplace_back(
                [divisorCopy](int value) // capture the copy
                { return value % divisorCopy == 0; } // use the copy
            );
            //c++14中
            //filters.emplace_back( // C++14:
            //[divisor = divisor](int value) // copy divisor to closure
            //{ return value % divisor == 0; } // use the copy
            //);
        }
-   对于没有加mutable声明的lambda,默认情况下操作符()是**const**:不可修改
-   下面的代码中，虽然使用了[=]捕获，但是divisor是static的，这样，如果divisor发生变化，整个lambda的都会发生变化

        filters.emplace_back(
        [=](int value) // captures nothing!
        { return value % divisor == 0; } // refers to above static
        );
####  Item 32:Use init capture to move objects into closures.

-   c\++11中没有被加入的move capture，在C++14中以更灵活的方式出现init capture
-   下面的捕获方括号中的pw作用域是closure class即lambda表达式，=右边的则是外围的

        auto func = [pw = std::make_unique<Widget>()] // as before,
        { return pw->isValidated() // create pw
        && pw->isArchived(); }; // in closure
-   c++11中没有init capture,但是可以用std::bind来模拟


        auto func=std::bind([](const Widget& data){...}, std::move(data);

####  Item 33:Use decltype on auto&& parameters to std::forward them.

-   as the title is.
-   能这样用的原因是，decltype 对于左值， 产生普通的值，对于右值，则会产生右值
-   这个条款说的是对于forward的参数的使用
   
        auto f=[](auto&& x)
        //{return normalize(std::forward<???>(x));};
        //可以像下面这样  
        {return normalize(std::forward<decltype(x)>(x));};


####  Item 34:Prefer lambdas to std::bind.

-   std::bind 不像lambda 可以内联进代码，它必须经过函数调用，所以代码可能有点多
-   另外一点是代码的可读性
-   std::bind对于传入的参数需要先进行处理(evaluate)，然后才能传入目标函数对象,无法保持参数的类型
-   c++11中可以用std::bind来完成move capture和多态函数对象的绑定，但是在c\++14中以上两个特性都可以有lambda实现

        //polymorphic
        auto boundpw=[pw](const auto& param){pw(param);};



***


