### sha256 算法

**功能描述：生成对内容(string)的sha256 哈希**
**使用指南**：只要包含sha256.h 和sha256.cpp就可以进行调用sha256,输入为string，输出为含有8个32位uint32_5的 vector (**测试文件test.cpp中使用了windows的计时函数，如果在linux下测试的话，删掉计时那部分的代码就可以运行**)
运行时间：
计时部件使用了windows的高精度计时器：QueryPerformance
对10m大小文件的hash，平均每文件用了0.451s

对100m大小的文件进行hash，平均每文件用了4.514s:

***

#### TO stress in the end：

以后CodeReview的时候不能简单的看逻辑，还得看有没有typo之类的混过了语法检查。立个flag, 再犯这样的错误我就是个XX.