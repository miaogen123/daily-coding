### 读Chapter5的随笔

***
####  Item 23: Understand std\::move and std::forward 

-   所有的参数的都是左值(有地址的都是左值)
-   move和forward在运行时都不做任何的事情，他是一个模板,在编译期完成自己要做的事
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
-   universal reference是一个非常**贪婪**(greediest)的推断，在重载时，他几乎会匹配所有的参数类型
-   重载UR引用的函数或者ctor时，可能会过度的匹配导致不想要的结果出现
####  Item 27: Familiarize yourself with alternatives to overloading on universal references.
-   当你需要一个UR同时又非常需要overload的时候，你可以使用一些small trick.
-   abandon overloading
-   pass by const T&
-   pass by value(and use std::move)(意思就是不要使用UR)
-   use tag dispatch
        
        template <typename T>
        void LogAndAddImpl(T&& name, std::false_type){
            cout<<"inside the int"<<endl;
        }

        template <typename T>
        void LogAndAddImpl(T&& name, std::true_type){
            cout<<"inside the string"<<endl;
        }
         
        template <typename T>
        void LogAndAdd(T&& name){
        //	using remove_ref=std::remove_reference<T>;
            LogAndAddImpl(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type>());
        }
-   还有一种办法是利用type_traits中的特性限制模板的使用, 如enable_if来启动编译期对于模板实例化的检查，如果条件满足进行实例化，否则就查找其他符号条件的函数，如果没有，error
   如使用remove_reference移除引用
-   使用UR is effective，但是也有坏处，就是可读性，维护成本都会升高
-   这里插播一个SFINAE: 我的理解是，利用overload 函数的不同匹配在编译期完成一些判断,enable_if就是这样实现的

####  Item 28: Understand reference collapsing
-   引用分解的四种情况，如果其中的一个是lvalue，最后得到的结果就是lvalue,只有两个都是rvalue的时候，结果才是rvalue
-   除了auto&& 和模板推断以外，另外的两种出现引用分解的情况是，generation and use of typedefs and alias declarations 
-   Universal references are rvalue references in contexts where type deduction distinguishes lvalues from rvalues and where reference collapsing occurs.

####  Item 29: Assume that move operations are not present, not cheap, and not used.
-   对于c++98的代码，如果class内声明了copy cotr或者显式抑制了move cotr，编译器不会使用调高性能的move操作的，
-   有一些string 或者其他的实现是采用了SSO(small string optimization)，对于这种情况，move操作不见得就比copy操作快很多
-   接下来的一些情况,No move operations, Move not faster,Move not usable,Source object is lvalue，这些情况下，使用move操作不见得就会快很多
-   写泛型代码的时候，应该注意，以一种保守的方式去进行,如上所述，move 也不一定会起高效率
-   如果确定使用的type支持move 语义，就大胆的用吧 

####  Item 30: Familiarize yourself with perfect forwarding failure cases

-   这里讨论的perfect forward一般是指引用传参
-   以下的几种情况下会出现forwarding failure:当类型推断出错，或者无法推断的情况下
    -   Braced initializers:原因在于在forward给第二个函数的时候，compiler并不会进行隐式转化
    -   0 or NULL as null pointers
    -   Declaration-only integral static const data members:仅声明 static const对象，会在引用时产生指针，这是这里失败的原因，也可能编译器或者linker会自己进行处理
    -   Overloaded function names and template names:当重载函数名和模板名做参数的时候，会失败，然后当时用的时候，可以选择对函数使用声明指针，对模板使用stati_cast
    -   Bitfields:引用bits是不可行的，可以选择使用一个传送copy，来使用forward
    

***

