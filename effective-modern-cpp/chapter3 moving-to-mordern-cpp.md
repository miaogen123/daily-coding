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
    
***