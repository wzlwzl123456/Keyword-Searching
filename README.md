# Keyword-Searching

目标：实现程序对读入的C或C++代码文件进行不同等级的关键字提取<br>

基础要求：输出关键字统计信息<br>
进阶要求：输出有几组switch case结构，同时输出每组对应case个数<br>
拔高要求：输出有几组if else结构<br>
终极要求：输出有几组if，else if，else结构<br>

time:2021.9.18:<br>
已完成功能：关键词检测并计数,输出switch case个数<br>
存在的问题：对于诸如“int if else”这类的字符串以及//switch这类的注释未能正确识别<br>
