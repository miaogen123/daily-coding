### 读Chapter2的随笔

-   thread()的参数需要是一个可调用的对象，如果是一个重载()操作符的类，同样可以作为参数(直接传递类名),
    但是这样的定义特别的难看，最好避免或者添加注释
-   下面的声明最好避免:实际意思是定义了一个函数接受参量，返回thread对象
    
        std::thread my_thread(background_task());
        auto my_thread(background_task())->decltype(std::thread);  //这样声明也好
        std::thread my_thread((background_task()));    //这样也行
        std::thread my_thread{background_task()};    //这样也行
-   joinable()：用来判断进程的可join性
-   这里一个join的异常安全性的判断:如果要求必须join，那就必须确保异常的情况下仍然安全
    可以采用try-catch的方法，当然也可以采用RAII的方法，这里就不列try-catch了，看一下RAII的实现
    如果是detach就可以直接进行了

        using namespace std;  
        class thread_guard:boost::noncopyable{  
            public:  
                explicit thread_guard(boost::thread& t):t_(t){}  
                ~thread_guard(){  
                    if(t_.joinable()){//检测是很有必要的，因为thread::join只能调用一次，要防止其它地方意外join了  
                       t_.join();  
                    }  
                }  
                thread_guard(const thread_guard&)=delete;
                thread_guard& operator=(const thread_guard&)=delete;  
            private:  
                boost::thread& t_; 
        };  
-   fire and forget : means 一个启动的任务启动完了就不管了
-   线程搭载的函数如果使用的是引用，则需要小心，如果是指针则是存在在传递未完成的情况下，被指向物离开的
    如果使用右值，可以使用强制转换并且使用std::ref 生成对象引用.
-   当参数不可copy的时候，你可以尝试使用std::move

        std::thread t(process_big_object,std::move(p));   //p是一个unique_ptr
        std::thread t(process_big_object,std::move(std::unique_ptr<DATA>(new DATA()));
-   对于一个线程，要么创建以后就分离，要创建以后就join
-   不要把一个正在运行的线程对象，赋值给另外一个正在运行的线程对象，会出错的
-   std::thread::hardware_concurrency() 获取硬件核心，可能会返回0
-   thread.get_id()只保证对于比较的完全支持，对于一般的标准输出则是平台独立的
