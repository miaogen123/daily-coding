### 读Chapter6的随笔

***
####  Item 31:Avoid default capture modes

-   lamda会默认生成一个closure class，lamda中的可执行代码就相当于class中的mem-func
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
-   并且按值捕获的变量也是不可以被修改的
-   下面的代码中，虽然使用了[=]捕获，但是divisor是static的，这样，如果divisor发生变化，整个lamda的都会发生变化

        filters.emplace_back(
        [=](int value) // captures nothing!
        { return value % divisor == 0; } // refers to above static
        );

***


