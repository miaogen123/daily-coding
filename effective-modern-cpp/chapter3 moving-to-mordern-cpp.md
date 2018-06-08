### 读Chapter3的随笔
#### Item 7 distinguish between () and{} 
-   {}是一个几乎是万能的创造对象的方法(uniform initialization)，他可以胜任大部分情况下的工作。
-   还有避免narrow conversions:避免在创造对象的时候发生转义
        
        double x, y, z;
        …
        int sum1{ x + y + z }; // error! sum of doubles may not be expressible as int 
-    avoid c++'s most vex parse : 使用空的构造函数生成对象与调用函数

         Widget w2(); // most vexing parse! declares a function named w2 that returns a Widget! 
         Widget w3{}; // calls Widget ctor with no args
-    **缺点也是有的**: {}会造成语义上的不清晰，特别是对于构造函数中含有 std::initializer_list的类来说
     使用{1,2}会默认调用std::initializer_list的调用，不论是否是最佳匹配
-    还有一个调用默认函数的问题，生成一个空对象还是调用一个包含空地._list的对象，**见page55**
-    再有就是在使用函数模板的情况下的判断，()和{}两种方式是不同的,比如std::vector<*> something\
     (20, 10)   //10个20， 如果是{10， 20} 那就是两个值
-    总的来说，择其善者而从之，一般情况下**{}**还是比较舒服的 


***

#### 生词
mandate 授权
