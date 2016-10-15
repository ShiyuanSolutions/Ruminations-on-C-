#ifndef PICTURE_H
#define PICTURE_H
#include <iostream>

class picture
{
    friend std::ostream& operator<<(std::ostream &, const picture &);
    friend picture frame(const picture&);
    friend picture operator&(const picture&, const picture&);
    friend picture operator|(const picture&, const picture&);

public:
    picture();
    picture(const char* const*, int);

    picture(const picture&);
    ~picture();
    //本质上是将当前对象的数据抛弃（但并不是删除），然后
    //从源端复制数据
    picture& operator=(const picture&);

private:
    char* data;
    int height,width;
    //在const picture上操作，返回副本
    char& position(int row,int col){
        return data[row * width + col];
    }
    //直接读给定字符的左值
    char position(int row, int col)const{
        return data[row * width + col];
    }
    static int max(int, int);
    void init(int, int);
    void copyblock(int, int, const picture&);
    void clear(int, int, int, int);
};

#endif // PICTURE_H
