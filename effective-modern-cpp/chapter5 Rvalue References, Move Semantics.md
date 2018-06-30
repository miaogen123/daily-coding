### 读Chapter4的随笔

***
####  Item 23: Understand std\::move and std::forward 

-   所有的参数的都是左值(有地址的都是左值)
-   move和forward在运行时都不做任何的事情，他是一个模板,在运行期完成自己要做的事
-   如果使用的move的话，对象不能是const，否则会调用他的copy constructor
-   move保证的是，一定会产出一个右值
-   forward是一个conditional cast，只有当传进来的参数是右值的时候，才会进行转换,
    参数是不是右值，这个信息是被编码在模板的参数T里面的

####  Item 24: Understand std\::move and std::forward 

-   作者把**universal reference**称作是如此，但是有些c++ community member 称其为 **forwarding reference**
-   universal reference 和 rvalue reference形式相同，但是意义不同：前者可以承接一切类型，就是需要多加一个std::forward 
-   一般用在函数模板参数，和auto类型推断:共性:类型推断
-   形式一般是T&&,但是不绝对，也有别的如vector中的emplace_back()中的Args同样是一个universal reference

        template<class T, class Allocator = allocator<T>> // still from
        class vector { // C++
        public: // Standards
        template <class... Args>
        void emplace_back(Args&&... args);
        …
        };
-   std\::move在任何时候都会去尝试将参数转换成右值，而std::forward只有在传进来的是右值的时候，才会进行右值的转换

####  Item 25:Use std::move on rvalue references, std\::forward on universal references

-   universal reference
-   对函数的返回对象(local)编译器会默认使用std::move,这就是所谓的 return value optimization(RVO):
    RVO的两个条件：1. 返回值类型与函数声明的类型相同. 2.返回的是一个local object.
-   不要把forward和move用在，满足RVO条件的返回值
-   如果你想对一个对象进行move操作，那么就不要把它声明为const类型。 对一个const对象执行move操作会引起拷贝行为。
   
####  Item 26: Avoid overloading on universal references.
-
***

