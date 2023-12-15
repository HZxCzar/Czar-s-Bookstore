#ifndef IF_FILEWRITING_HPP
#define IF_FILEWRITING_HPP

#include <fstream>
#include <iostream>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

template <class partA> class FileWriting {
private:
  fstream file;
  string file_name;
  long long sizeofA = sizeof(partA);

public:
  FileWriting() = default;
  FileWriting(const string &file_name) : file_name(file_name) {}
  void Setfile(const string &name) { file_name = name; }
  //void Cl(){file.close();}
  void initialise() {
    file.open(file_name, std::ios::out);
    long long beg = 0;
    file.write(reinterpret_cast<char *>(&beg), sizeof(long long));
    file.close();
  }
  void Clear() {
    file.open(file_name, std::ios::out);
    file.close();
  }
  //检查是否是第一次打开
  bool IS_NEW() {
    file.open(file_name, std::ios::in | std::ios::out | std::ios::ate);
    if (!file.is_open()) {
      ofstream file(file_name);
      file.open(file_name, std::ios::in | std::ios::out | std::ios::ate);
      file.close();
      return true;
    }
    if (0 < file.tellp()) {
      long long tmp=0;
      //std::cout<<file.tellp()<<'\n';
      get_info(tmp);
      if(!tmp)
      {
        file.close();
        return true;
      }
      file.close();
      //std::cout<<"tmp"<<tmp<<'\n';
      return false;
    } else {
      file.close();
      return true;
    }
  }
  void get_info(long long &tmp) {
    file.close();
    file.open(file_name, std::ios::in | std::ios::out);
    file.seekg(0);
    file.read(reinterpret_cast<char *>(&tmp), sizeof(long long));
    //std::cout<<tmp<<"GET\n";
    file.close();
  }
  void write_info(long long tmp) {
    file.close();
    file.open(file_name, std::ios::in | std::ios::out);
    file.seekp(0);
    file.write(reinterpret_cast<char *>(&tmp), sizeof(long long));
    file.close();
  }
  //在文件合适位置写入类对象t，并返回写入的位置索引index
  //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  //位置索引index可以取为对象写入的起始位置
  long long writeA(partA &t) {
    file.close();
    file.open(file_name, std::ios::out | std::ios::in | std::ios::ate);
    long long pos = file.tellp();
    file.write(reinterpret_cast<char *>(&t), sizeofA);
    long long num;
    get_info(num);
    write_info(num+1);
    file.close();
    return pos;
  }

  //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void updateA(partA &t, const long long index) {
    file.close();
    file.open(file_name, std::ios::in | std::ios::out);
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofA);
    file.close();
  }

  //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
  void readA(partA &t, const long long index) {
    file.close();
    file.open(file_name, std::ios::in | std::ios::out);
    file.seekg(index);
    //std::cout<<file.tellg()<<"G\n";
    file.read(reinterpret_cast<char *>(&t), sizeofA);
    file.close();
  }
  //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
  void Delete(long long index) { /* your code here */
  }
};
#endif