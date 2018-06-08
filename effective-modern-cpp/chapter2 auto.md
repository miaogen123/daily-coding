### 读Chapter2的随笔
#### Item 5  prefer auto to explicit type declaration
-   使用auto避免使用未initialize值
-   **C++14**可以使用auto 来承接lamda表达式的返回值，（不过lamda作用是啥不是很清楚）
-   auto与std::function相比:后者占用更多的内存,调用需要跟多的时间，可以说auto吊打std:;function
-   **Item34** 作者极力劝读者使用lamda而非std::bind
-   如下的代码:在32位下正常，unsigned在32和64位系统下32位，在v.size() 的返回
    值平台而异, **这是为什么选择使用*auto***
-   当你确定使用explicit declaration的时候，程序代码会更加易读，更加方便维护，don't be hesitate to suer

        std::vector<int> v;
        …
        unsigned sz = v.size(); 
-   **Scott在这一个Item中，举了一个例子:**

        std::unordered_map<std::string, int> m;
        …
        for (const std::pair<std::string, int>& p : m)
        {
        … // do something with p
        } 
    作者的意思是这里的p，其实是一个std::pair<const std::string, int>与预期的不一样
    但我试了一下，**跟作者的结论不一样**，如下：
        
        std::unordered_map<std::string, int > m;
        m["hello"]=2;
        m["world"]=3;
        for(const std::pair<std::string, int> &temp:m){
            cout<<temp.first<<endl;
            cout<<typeid(temp.first).name()<<endl;
        }
        const string ss("nihao");
        cout<<"the type of const string "<< typeid(ss).name()<<endl;
        
15j

#### Item 6  prefer auto to explicit type declaration
-   对于bool的特殊处理

        std::vector::operator[] returns reference for every type except bool
-   c++ 禁止reference to bits，可能是为了性能吧？毕竟bits内存占用就很少，但是使用reference
    就很多了，所谓得不偿失 
-   书上的例子是关于一个返回代理对象的东西，(proxy class),这样auto在推断的时候，会发生意外
    当生成一个中间对象，而中间对象又返回引用，中间对象在生成完了就会被摧毁，这种情况下，不知不觉的产生了dangling pointer,
    **当然老先生是为了举例，我用gcc去尝试的时候，发现，跟老先生的又不一样**
        
        auto temp_bool_list=features()[2];
        cout<<temp_bool_list<<endl;
        
    事实上，是可以运行的, **但重要的是这样的问题，需要注意一下**

    **也就是对于存在invisible proxy的时候，auto会推断不想要的值**
-   也可以explicitly invoke static_cast<*>来使auto变成你想的那样
 
***

#### 生词
mandate 授权