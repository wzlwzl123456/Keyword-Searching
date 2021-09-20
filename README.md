# Keyword-Searching

目标：实现程序对读入的C或C++代码文件进行不同等级的关键字提取<br>

基础要求：输出关键字统计信息<br>
进阶要求：输出有几组switch case结构，同时输出每组对应case个数<br>
拔高要求：输出有几组if else结构<br>
终极要求：输出有几组if，else if，else结构<br>
ddl：2021.9.22.00<br>

time:2021.9.18:源.cpp<br>
已完成功能：关键词检测并计数,输出switch case个数<br>
存在的问题：对于诸如“int if else”这类的字符串以及//switch这类的注释未能正确识别<br>
time: 2021.9.20:源（改）.cpp<br>
改变了读取文件的方式，从按词读取改为按句读取。因而解决了注释和字符串的识别问题。<br>
存在问题：部分关键字从句中以空格为分隔读取后是带有标点符号的（如：break；，default：），将所有标点符号替换成空格或换行就与关键字无法匹配成功，因此就把标点统一替换成其他字符，但是也要在最开始设定匹配的关键字中更改形式。再看看能不能换一种方法。<br>
time:2021.9.20:源（第三版）.cpp<br>
修改了代码，完成了几个特殊的关键字的识别和替换，方便了统计<br>
使用堆栈完成了if_else结构和if_else if_else结构的识别和统计。<br>
完成了按等级输出结果的功能<br>

要求已经基本完成。

注：有可能报C4996错误，其实是可以跑的，直接改设置就行
