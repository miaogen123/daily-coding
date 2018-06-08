### 读Chapter1的随笔
#### Item 1  template  type deduce
-   reference  is discarded during .
-   it's normal when Paramtype is pointer or reference 
-   Universal reference means rvalue reference .
    -   **lvalue is deduced as lvalue reference .**
    -   rvalue  is still a rvalue reference .
-   ParamType is neither pointer nor reference , namely by value.
      -   all the constness and reference -ness are discarded.
      -   An exceptional case is that when the arguments passed in is an\
          const pointer  to const type, the ParmType will become non-const\ 
          pointer to const type

-   对于T&， if you pass an array type, the ParamType will be deduced as\
    actual type of array
    -   声明为constexpr的表达式 在**编译期**可以使用,**如下：**
    
            template <typename T, std::size_t N> 
            constexpr std::size_t arraySize(T (&)N) noexcept
            {return N;}

            int value[]={1, 2,3};
            int mappedavalue[arraySize(value)];
            //of course, 最好使用内置的array
    -  参数是函数的时候，与是array的情况相同

            void someFunc(int, double); // someFunc is a function;
            // type is void(int, double)

            template<typename T>
            void f1(T param); // in f1, param passed by value

            template<typename T>
            void f2(T& param); // in f2, param passed by ref

            f1(someFunc); // param deduced as ptr-to-func;
            // type is void (*)(int, double)
            f2(someFunc); // param deduced as ref-to-func;
            // type is void (&)(int, double)

***

#### Item 2  auto type deduction

-   This is exactly the same as the cases in Item 1
-   auto can get different types by different declaration  forms

        auto x1 = 27; // type is int, value is 27
        auto x2(27); // ditto
        auto x3 = { 27 }; // type is std::initializer_list<int>,
        // value is { 27 }
        auto x4{ 27 }; // ditto 
-   there are two dedection happened, one is auto, another is std::initializer_list<T>

        auto x3 = { 27 }; // type is std::initializer_list<int>,
-   下面的代码用的**模板推断**而非auto推断

        auto createInitList()
        {
        return { 1, 2, 3 }; // error: can't deduce type
        } // for { 1, 2, 3 }
***
#### Item 3 understand decltype  

-   c++中的container一般返回的是引用，但也存在返回value 的情况
-   **universal reference ==右值引用**，主要使用用来处理，接受的参数可能既是\
    左值，又可能是右值，同时也想保持这两种情况(同时处理),而不用写重载
-   decltype 对于**表达式**以及decltype((x))类型的，总是产生左值引用
-   **(c++14)** decltype(auto) 在推导返回值的时候，是为了进行处理返回引用的情况
-   decltype 不修改表达式的类型，不想auto会omit reference

//注释：mayer老先生很幽默啊：
**That’s the kind of code that puts you on the express train
to undefined behavior—a train you certainly don’t want to be on.**



***

#### Item 4 How to view the deduction of type

-   By IDE, compilers diagnose , or by boost libraries.
-   **NOTE**, the type name coming from  standard library maybe not right \
    as you think, Be caution.
-   boost 库会好一点

***

#### 生词
derision  嘲笑
admonition 警告
nag 唠叨
trivial adj. 不重要的，琐碎的；琐细的