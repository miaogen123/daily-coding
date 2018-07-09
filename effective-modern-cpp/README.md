#### 这里是在读effective modern c++时写的代码 以及一些随笔
#### 似乎图书馆没有这本书的中译版，就拿英文版凑活一下吧。
#### 所以会有很多的随笔名词都是英文，never mind
##### enjoy~

<br>
<br>
<br>
<br>

***
实验书上的代码时，为了方便就使用了GNU的g++ v4.9.2编译器, 以下是版本的输出信息
        
        g++.exe (tdm-1) 4.9.2
        Copyright (C) 2014 Free Software Foundation, Inc.
        This is free software; see the source for copying conditions.  There is NO
        warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
        
为了能够不每次都敲 --std=c++ 14，我投奔了g++ v8.1, 从**chapter4**开始

        g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
        Copyright (C) 2018 Free Software Foundation, Inc.
        This is free software; see the source for copying conditions.  There is NO
        warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
