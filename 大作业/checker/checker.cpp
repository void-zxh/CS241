#include "checker.h"

int main(){
    // 用图文件来构造checker
    // 模板参数为边权数据类型,可选int或double
    // 检查输出文件
    try{
        std::fstream fs;
        // fs.open("Hello.txt",std::ios::out);
        ftc::Checker<double> ck("in.txt");
        // ck.check("output.txt",fs);
        ck.check("output.txt",std::cout);
        // fs.close();
    }
    catch(ftc::Error e){
        e.print_error();
    }
    /* 
     * 输出文件格式：
     * 每行一组int， 代表原图对应编号的结点被分割成一张子图
     * 
     */
    return 0;
}