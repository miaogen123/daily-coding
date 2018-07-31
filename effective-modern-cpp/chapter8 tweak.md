### 读Chapter8的随笔

***
####  Item 41: Consider pass by value for copyable parameters that are cheap to move and always copied

-   对最后一次出现的左值使用move，
-   有时，为了避免使用UR带来的一系列问题，可以简单高效的使用 pass by value
-   但是pass by value 的具体效率的分析是复杂的，同样存在效率并没有改变的可能性
    -   比如 PBV 传了(copy)一个很大的对象，然后又没有用，白白浪费掉，这样性能损失相对于move是很大的
-   PBV(pass by value)可能带来slicing problem.(slicing problem 是指一个派生类的值传递给接受基类的函数，会截掉其中的一些元素)
-   对于左值对象，PBV一般来说更加expensive

####  Item 42:Consider emplacement instead of insertion.

-   一下几种情况更适合使用emplace_back
    -   当被加入的值 是construct into not assigned.
    -   被传入的参数类型与容器承接的参数类型不一致的时候(emplace 不需要去创造临时对象)
    -   容器不可能拒绝一个新值作为一个duplicate(either permits the duplicate or most of the value you insert is unique)
-   Similiarily,emplace_front, emplace_hint, emplace_after,
-   使用emplace_back与push_back相比，如果发生异常更容易出现内存泄露的情况(push_bask生成一个完成的对象在传入，而emplace back是分开的，先new一个，在分配所需要的容器节点的内存，在该内存处构造)
-   emplace_back会进行隐式的类型转换，导致可以在push_back情况下无法通过编译的代码通过，form a  super pit,
    需要注意的是，emplace 是direct initialization，而push_back是copy initialiation
   
***

#### 暂时告一段落，等到7.14号在回过头复习一下这本书的内容
#### 其中item41和item42需要在加强一下
