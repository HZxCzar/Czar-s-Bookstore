#ifndef _DATABASE_HPP
#define _DATABASE_HPP
#include "FileWriting.hpp"
#include <set>
#include <string>
constexpr int BLOCKSIZE =600;
const string ACCOUNTKEY = "ACCOUNTKEY", ACCOUNTVAL = "ACCOUNTVAL",
             ISBNKEY = "ISBNKEY", ISBNVAL = "ISBNVAL", NAMEKEY = "NAMEKEY",
             NAMEVAL = "NAMEVAL", AUTHORKEY = "AUTHORKEY",
             AUTHORVAL = "AUTHORVAL", KEYWORDKEY = "KEYWORDKEY",
             KEYWORDVAL = "KEYWORDVAL", LOGKEY = "LOGKEY", LOGVAL = "LOGVAL";
template <class data> struct A {
  long long next;
  long long pos;
  data first;
};
template <class data> struct B {
  data elem[BLOCKSIZE+20];
  long long size = 0;
};
template <class data> class database {
public:
  //设定文件
  void Set(const string &Aname, const string &Bname);
  //裂块
  void BREAK(const long long &p, B<data> &);
  //寻找元素在块中位置
  long long BinarySearch(const B<data> &, const data &);
  //判断位置
  bool Scan(const A<data> &, const data &);
  bool Scan2(const A<data> &, const data &);
  //寻找块区间,end取不到
  void FindRange(const data &, long long &beg, long long &end);
  //寻找元素下界
  long long GetBound(const data &, const long long &);
  //寻找元素上界
  long long GetUp(const data &, const long long &);
  //寻找块位置
  void FindOnly(const data &, long long &p, long long &lastp);
  //寻找元素在块中位置
  long long GetInPos(const data &, const long long &);
  //找到元素具体坐标
  void Find(const data &, long long &p, long long &pos);
  //下一节点
  long long GO(const long long &p);
  //加入元素
  void ADD(const data &);
  //删除元素
  void DELETE(const data &);
  //输出数据
  // endpos为下一个(输出块),end为下一个（不输出位置）
  void PRINT(const long long &begpos = -1, const long long &endpos = -1,
             const long long &beg = -1, const long long &end = -1);
  //获取指定数据
  data Get(const long long &p, const long long &pos);
  //更新指定位置数据
  void Update(const data &elem, const long long &p, const long long &pos);
  //获取末尾元素
  data GetTail();
  //是否找到元素
  bool if_find = false;
  //针对KEYWORD的putinset
  void PUT(const long long& p,const long long& start,const long long& end,std::set<string>& u);
  //索引数据库
  FileWriting<A<data>> Afile;
  //元素数据库
  FileWriting<B<data>> Bfile;
  //确保关闭
  //void CL(){Afile.Cl();Bfile.Cl();}
  //是否为空
  bool empt = true;
  //是否执行
  bool excute = false;
};
#endif