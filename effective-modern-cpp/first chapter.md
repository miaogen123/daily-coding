##### 读Item1 的随笔
##### Item 1  template  type deduce
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