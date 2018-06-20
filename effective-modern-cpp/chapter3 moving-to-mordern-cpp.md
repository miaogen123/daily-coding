### 读Chapter3的随笔
#### Item 7 distinguish between () and{} 
-   {}是一个几乎是万能的创造对象的方法(uniform initialization)，他可以胜任大部分情况下的工作。
-   还有避免narrow conversions:避免在创造对象的时候发生转义,
        
        double x, y, z;
        int sum1{ x + y + z }; // error! sum of doubles may not be expressible as int 
    **在g\++上尝试实现的时候，发现其实g\++编译器,只会在编译的时候，waring一下，并不会报错**
-    avoid c++'s most vex parse : 使用空的构造函数生成对象与调用函数

         Widget w2(); // most vexing parse! declares a function named w2 that returns a Widget! 
         Widget w3{}; // calls Widget ctor with no args
-    **缺点也是有的**: {}会造成语义上的不清晰，特别是对于构造函数中含有 std::initializer_list的类来说
     使用{1,2}会默认调用std::initializer_list的调用，不论是否是最佳匹配
-    还有一个调用默认函数的问题，生成一个空对象还是调用一个包含空地._list的对象，**见page55**
-    再有就是在使用函数模板的情况下的判断，()和{}两种方式是不同的,比如std::vector<*> something\
     (20, 10)   //10个20， 如果是{10， 20} 那就是两个值
-    总的来说，择其善者而从之，一般情况下 **\{}** 还是比较舒服的 

-    **ATTENTION**, 以下代码在功能上是相同:两个都是进行了copy constructor

         Widget small_widget();
         Widget middle_widget=small_widget;
         Widget middle_widget(small_widget);
-    **这里有一个细节问题**，
            
          Widget(std::initializer_list<long double> init_list){
                cout<<"inside init_list"<<endl;
                for(const auto& temp:init_list ){
                    cout<<temp<<endl;
                }
            }
         //Widget middle_widget{{}};   //输出为0
         Widget middle_widget{};     //没有输出
         也就是说，在gnu的编译器实现上，其实他对{{}}样的初始值，是给了一个默认的0值的
         注意一下，免的以后被坑

#### Item 8 prefer nullptr to NULL and 0
-    **骚操作一枚:  这样可以返回不确定的值，厉害呢，scott**

         auto lockAndCall(FuncType func,
         MuxType& mutex,
         PtrType ptr) -> decltype(func(ptr))
-    avoid overload on integral and pointer types;
     或者说，如果真的这样重载的话，就可能出现相应的调用混乱
-    在模板中，使用更多的 nullptr 然后主要是NULL和0 的语义不清晰
-    以下是一个调用之间的比较

            void f(int ){
                cout<<" int";
            }
            void f(bool){
                cout<<" bool";
            }
            void f(int *){
                cout<<" void *";
            }
            int main(void)
            {
                cout<<"call f(null)"<<endl;
                //f(NULL);   //error
                cout<<"call f(0)"<<endl;
                //f(0);   //output:int
                f((void *)0);   //output bool
                cout<<"call f(nullptr)"<<endl;
                f(nullptr);   //output: void *
                return 0;
                }
#### Item 9  prefer alias declaration to typedef 
-    书中举的例子代码很长，这里就不贴了，主要的意思是\
     **使用using 在模板中会有很大的作用可以避免，过多的影响理解的代码的出现，同时可以在template内使用独立的type 而不用加上typename**
-    C++14 offers alias templates for all the C++11 type traits transformations , 
     更加sleek的类型是如：std::remove_const_t

#### Item 10 Prefer scoped enums to unscoped enums 
-   C++98-style enums are now known as unscoped enums.
-   Enumerators of scoped enums are visible only within the enum. They convert
to other types only with a cast.\
   **以上两条就是说，之前的enums是没有域的，enums的命名会污染外部的命名空间**\
   **而新的enum class 则不会**
-   Both scoped and unscoped enums support specification of the underlying type.
The default underlying type for scoped enums is int. Unscoped enums have no
default underlying type.\
    **enum class 的另个好处是他可以避免隐式的类型转换,因为enum的**
    **默认类型是int,可以当做int来使用**
-   Scoped enums may always be forward-declared. Unscoped enums may be
forward-declared only if their declaration specifies an underlying type.
    **enum class 可以声明而不被定义，so-called forward-declaration**\
    *书上还举了一个方便不一样文件夹下的tuple引用的例子，但是比较繁琐, 代码写起来也不很漂亮就不是很注意*
    
#### Item 11 Prefer deleted functions to private undefined ones.
-   书上的一个例子是使用delete来拒绝隐式转换，但是这样其实可以使用explicit来完成，并不能作为一个充分的理由\
    **其实可以通过将特定的constructor声明为delete来拒绝一些特定的实例化**
-   还有另外的一个理由：使用delete来使模板拒绝一些特定参数的 实例化，这个到时挺好用的

#### Item 12 Declare overriding functions override
-   在子类显示的声明override的话，如果父类中没有相应的函数，compiler会报错
    这样方便排错，在编译器发现错误
-   在这个Item下，作者讲了另外的一个知识点，是类内成员函数的引用修饰符
    这个意思，如果在对应的工厂设计模式下面，如果生成工厂生成了一个类以后，类暂时是右值，\
    如果，只是利用了这个临时类的一些数据，然后这个类就被销毁了，这样如果使用正常的非引用修饰符的话\
    是一种浪费性能的方式，而使用右值引用修饰符修饰函数以后，这个函数的返回的就会变成\
    该临时类的右值返回，这个时候就不用进行另外一次的copy-constructor

#### Item 13 Prefer const_iterators to iterators
-   c\++98中的const是不很好用的，在c\++11中进行了很大的优化, 
-   新标准中容器操作都是用的const_iterators, 
-   c++14引入了对于std::cbegin(container &C)和对应的cend的支持
-   日常代码中尽量用const_iterator 就想scott的effective c++ 中的提到的 use const as far as possible.
    
#### Item 14  Declare functions noexcept if they won’t emit exceptions.
-   使用noexcept 可以在程序发生异常的时候，保证所有的对象都被销毁
-   noexcept只应该在少数确定是non-except的函数中使用，否则
-   在98标准库的实现中，多数push_back都有强的异常安全保证，然后可以保证如果出现异常，原来的对象不会出现问题\
    在c++11中出现了move语义，如果直接使用move替代原来的copy，如果出现错误，将无法返回最初的状态。所以对于这种情况\
    只有在move不会抛出异常的手，这样也就是说，只有当相应的最底层的实现是nonexcept的时候，container才会使用move版本的
    push_back.(STL一般情况下, 是有两种分别使用copy和move的push_back)

            template <class T, size_t N>
            void swap(T (&a)[N], // see
            T (&b)[N]) noexcept(noexcept(swap(*a, *b))); // below
            template <class T1, class T2>
            struct pair {
            …
            void swap(pair& p) noexcept(noexcept(swap(first, p.first)) &&
            noexcept(swap(second, p.second)));
            …
            };
            //这实现看起来有点蛋疼啊
-   c++11中所有的内存分配函数默认都是noexcept，无论是否进行声明。因为内存分配时候出现exception会很难受\
    除了这些类中含有的data member 含有一些对象可能会抛except的时候
-   functions with **wide contracts** 意思是他没有先决条件，对于传入的参数没有限制，这样的函数不会显示未定义行为
-   有的library designer 会区分 wide contracts and narrow contract，对于wide *作者可能会使用noexcept版本的实现
-   noexcept是一种函数接口，caller may depend on it.
-   noexcept对于swap，move，memory deallocation function and destructors 用处很大
-   **这一节，有点难啊, 不是很理解**
    
#### Item 15  Use constexpr whenever possible
-   constexpr 的值必须是在编译期可知的，这会让constexpr表达式能够在使用常量的位置使用
-   c\++11对于constexpr的限制比较多，但在c++14中大多都取消了。比如c\++11要求使用constexpr function
    必须是一个statement的return 语句，c\++14则取消了这样要求(**虽然我测试用的gcc编译器还是不支持, vs2017可以的**)
-   constexpr函数对于常量输入，可以产生编译时常量，对于runtime variable 参数就会产生，runtime variable
-   书上说**c++11中constexpr 成员函数implicitly是const的，在c\++14中取消了这样的限制**(但我测试的gcc加--std=c++14 仍然不可用, vs2017可以的)
-   **声明constexpr 函数或者变量，会减少一些运行时的开销，但是会增加编译时间**
-   **constexpr is part of function interface.** 也就是客户端调用你的代码的依赖，如果你的constexpr发生了改动，
    客户机的很多代码都会无法使用
#### Item 16: Make const member functions thread safe 
-   mutable 在const函数中，使用改变局部的constness. 含有mutable变量这样的const 成员函数就需要考虑线程安全性。
-   内含锁的mutex的class对于move-only的处理，mutex 是不可以copy的
-   **std::atomic 成本要比使用mutex要小一点，所以需要熟练使用atmoic**, 但是话又说回来， 
    如果是多个atmoic变量的话，在多个atomic之间会形成空隙，造成非原子性，这样就需要使用mutex了，没有办法的
#### Item 17: Understand special member function generation.
-   对于可以move的对象 move and move-assigning 使用move，如果不可以的话，就是使用copy来完成
-   与c++中copy constructor和copy-assignment 不同(当自定义其中的一个时，另外的一个没有定义的会有编译器来生成)， move与他的partner move-assignment 
    则不是这样，当自定义其中一个的时候，另外一个则不会有编译器代劳，**原因在于，你自定义了其中任意一个，你都应该去定义其中一个**
-   声明 copy operation(constructor or assignment) 会默认停止 move operation (constructor or assignment)的生成，原因是**当你自定义一个copy operation 时候,**
    **就已经认定对于这个class 默认的 copy不适合这个类的使用，那么copy也可能不合适，反过来也是这样，如果定义了copy operation相应的copy operation也不会默认的生成**
-   *the rule of three*: 是关于copy constructor and copy assignment and destructor
    **当你自定义其中的任何一个的时候，都意味着有自己的内存/对象管理，那么另外的两个也是需要的**
-   用户自定义的destructor 会抑制编译器生成move operation
-   当你需要默认的move 而destructor又是必须要求的时候，可以用"=default"来使用默认的,
    这里的一个问题是，当你无意中添加了一个 destructor的时候，原来的move语义可能不在生效，如果该类之前大量使用了move语义，这样简单的修改很可能造成性能的巨大损失
-   move operation和copy operation 默认是互斥的，如果定义了前者，编译器不会默认生成后者，但是前者是被 overload的，其中有move和copy两个版本，可以完成后者的任务
    这可能是为什么生成前者以后就不会默认生成后者的原因之一
-   一个特殊情况是当你的constructor和destructor是模板函数的时候，compilers会为你生成默认的copy and move operation.
-   这里有一个链接![Rule-of-Three becomes Rule-of-Five with C++11?](https://stackoverflow.com/questions/4782757/rule-of-three-becomes-rule-of-five-with-c11) 高赞答案Philipp的
***
