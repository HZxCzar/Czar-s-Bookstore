# 开发文档

## BookStore （Czar）

## 程序功能

### FileWriting

负责文件读写，read获取，write写入并返回写入位置。

### database

数据库处理模板，可以binarysearch单一元素，binarysearchUP和binarysearchBound获取范围元素头尾位置，BREAK支持裂块操作。数据索引与数据块分为两个文件（keyfile|valuefile）存储。以块状链表实现。

### Tool

包括字符串分割Tokenscanner功能，字符字符串转换功能

### Booksystem

负责图书管理系统，通过图书data维护一个图书database，自定义不同data比较方式，数据存储分为四个数据库，分别依照ISBN顺序|主BookName副ISBN顺序|主Author副ISBN顺序|主Keyword副ISBN顺序存储。支持requiremen各种操作。

### Accountsystem

负责账户系统，通过账户data维护一个账户database。

### LOGINsystem

管理登录栈，维护当前用户select操作以及权限等信息。

### Logsystem

负责日志系统，维护一个日志database

### Main

负责程序主要流程控制，检索输入指令通过各system进行指令执行

## 主体逻辑

针对用户输入指令由main中的tokenscanner确认指令类型，选择调用相应的system，一次指令操作中可能回修改多个数据库内容，登录以及select等过程中修改LOGINsystem信息。

## 代码结构

main为主函数，LOGINsystem在运行过程中一直使用，一同调用Book，Account，Log三个数据库内容，剩下FileWriting，Tool，database为内部实现机制，外部不访问。其中Book系统可以调用Log，在购买及进货等操作时同步刷新日志。

## 各个类的接口及成员说明

### Account

**Su：** 实现登录

**Logout：** 实现登出

**Register：** 注册

**Passwd：** 修改密码

**useradd：** 增加用户

**Delete：** 删除用户

**SelectBook：** 选择书本，修改改用户选择情况

**GETID：** 返回当前用户ID

**GetPriv：** 获取当前用户权限等级

**IFSELECT：** 返回当前用户选书情况

**GETSELECT：** 返回当前选择书本ISBN

### Book

**show：** show操作

**Buy：** buy操作

**Select：** select操作

**Modify：** modify操作

**Import：** import操作

### Log

**IN：** 添加进账情况

**OUT：** 添加出账情况

**WORKER：** 添加员工日志

**ShowFinance：** 展示收入支出，show finance操作

**ReportWorker：** 展示员工日志

**UPD：** 更新财务日志

**ReportFinance：** 展示财务日志

**Log：** 展示总员工日志

### Database

**Set：** 设定文件

**BREAK：** 裂块

**BinarySearch：** 二分查找

**Scan：** 判断数据块是否符合

**Scan2：** 在寻找区间时判断数据块是否符合

**FindRange：** 寻找目标数据所在区间

**GetBound：** 获取目标数据所在区间下界

**GetUp：** 获取目标数据所在区间上界

**FindOnly：** 寻找块位置

**GetInPos：** 找特定元素在已知块中具体位置

**Find：** 找到元素具体坐标

**GO：** 查看下一节点位置

**ADD：** 加入元素

**DELETE：** 删除元素

**PRINT：** 输出数据

**Get：** 获取指定位置的数据

**Update：** 更新指定位置数据

 **GetTail：** 获取末尾元素

**PUT：** 针对KEYWORD的将已知元素的ISBN加入set

### Tool

**SetInput：** 设定输入串

**hasMoreToken：** 检查是否有剩余内容

**NextToken：** 返回下一token

**Nextkeyword：** 返回下一keyword

**NextISBN：** 返回下一ISBN

**NextTokenNIC：** 返回下一个token，=也成为分隔符

**NextFollow：** 返回紧接着的token，不跳过前置空格

**AD：** 前往串中下一位置

**ISUSERID：** 检查是否符合USERID

**ISUSERNANE：** 检查是否符合USERNAME

**ISPRIVILEGE：** 检查是否符合PRIVILEGE

**ISISBN：** 检查是否符合ISBN

**ISNAME：** 检查是否符合NAME

**ISQUANTITY：** 检查是否符合QUANTITY

**ISKEYWORD：** 检查是否符合KEYWORD

**ISONEKEYWORD：** 检查是否是单个KEYWORD‘’

**ISPRICE：** 检查是否符合PRICE

**ISCOUNT：** 检查是否是COUNT

**StringToSizeT：** 把stirng转换成sizeT类型

**StringToDouble：** 把string转换成double类型

**BehindToken：** 返回串后续部分

**ISDIGIT：** 检查是否是全数字

**ALLASCILL：** 检查是否全为合法ASCILL字符

**Turn60：** 转换60长字符串为字符数组

**Turn20：** 转换20长字符串为字符数组

**Turn30：** 转换30长字符串为字符数组

**shr：** 修正字符串为标准形式，去除多余空格

## 文件存储

每个文件开头标注是否写入内容

* KeyFile剩下保存索引，标注对应数据块位置、首元素信息（用于查找）、下一索引坐标

* ValueFile剩下保存数据块，块内包含data数据元素，以及目前块内元素数量size

## 其他补充说明

* 实现了网页端，可以实现网页上的指令输入以及输出反馈*127.0.0.1：52237*
