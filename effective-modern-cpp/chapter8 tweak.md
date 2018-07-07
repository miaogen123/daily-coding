### 读Chapter8的随笔

***
####  Item 41: Consider pass by value for copyable parameters that are cheap to move and always copied

-   对最后一次出现的左值使用move，
-   有时，为了避免使用UR带来的一系列问题，可以简单高效的使用 pass by value
-   但是pass by value 的具体效率的分析是复杂的，同样存在效率并没有改变的可能性
-   PBV(pass by value)可能带来slicing problem.
-   对于左值对象，PBV一般来说更加expensive

####  Item 42:Consider emplacement instead of insertion.

-   一下几种情况更适合使用emplace_back
    -   当被加入的值 是construct into not assigned.
    -   被传入的参数类型与容器承接的参数类型不一致的时候
    -   容器不可能拒绝一个新值作为一个duplicate
-   使用emplace_back与push_back相比，如果发生异常更容易出现内存泄露的情况
-   emplace_back会进行隐式的类型转换，导致可以在push_back情况下无法通过编译的代码通过，form a  super pit
***

#### 暂时告一段落，等到7.14号在回过头复习一下这本书的内容
#### 其中item41和item42需要在加强一下
