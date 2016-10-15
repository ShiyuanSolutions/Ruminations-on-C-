#include "picture.h"
#include <string.h>
#include <iostream>

picture::picture():height(0),width(0),data(0)
{
}


int picture::max(int m, int n)
{
    return m > n ? m :n;
}

void picture::init(int h, int w)
{
    height = h;
    width = w;
    data = new char[height * width];
}

void picture::copyblock(int row, int col, const picture& p)
{
    for(int i = 0;i < p.height; ++i)
    {
        for(int j = 0;j < p.width;j++)
        {
            position(i + row,j + col) =
                    p.position(i, j);
        }
    }
}

void picture::clear(int r1, int c1, int r2, int c2)
{
    for(int r = r1; r < r2;++r)
    {
        for(int c = c1; c < c2; ++c){
            position(r,c) = ' ';
        }
    }
}

picture::picture(const char * const * array, int n)
{
    int w = 0;
    int i;

    for(i = 0;i < n; i++)
        w = picture::max(w,strlen(array[i]));
    init(n, w);
    for(i = 0; i < n; i++)
    {
        const char* src =  array[i];
        int len = strlen(src);
        int j = 0;

        while(j < len)
        {
            position(i,j) = src[j];
            ++j;
        }

        while(j < width)
        {
            position(i, j) = ' ';
            ++j;
        }
    }
}

//copy cons
picture::picture(const picture & p):
    height(p.height),width(p.width),
    data(new char[p.height * p.width])
{
    std::cout << "copyblock" << std::endl;
    copyblock(0, 0, p);
}

picture::~picture()
{
    delete [] data;
}

picture &picture::operator =(const picture &p)
{
    if (this != &p){
        delete[] data;
        init(p.height, p.width);
        copyblock(0,0,p);
    }
    std::cout << "====" << std::endl;
    return *this;
}

//提示编译出错的这段代码是重载输出运算符。问题是出在String::上。
//我是将重载的这个函数定义为友元函数，既然是友元函数，那么就不应该出现picture::，
//因为友元函数并不属于一个类的成员方法，因此将类名和范围解析符删去即可。
std::ostream& operator<<(std::ostream& o, const picture& p)
{
    for(int i = 0;i < p.height; i++){
        for(int j = 0; j < p.width;j++)
        {
            o << p.position(i, j);
        }
        o << std::endl;
    }
    return o;
}

//注意友元函数不是属于该类的
picture frame(const picture &p)
{
    picture r;
    r.init(p.height + 2, p.width + 2);

    for (int i = 1;i < r.height - 1;++i){
        r.position(i, 0) = '|';
        r.position(i, r.width -1) = '|';
    }

    for (int j = 1; j < r.width - 1; ++j){
        r.position(0,j) = '-';
        r.position(r.height - 1, j) = '-';
    }

    r.position(0, 0) = '+';
    r.position(0, r.width -1)= '+';
    r.position(r.height - 1,0) = '+';
    r.position(r.height - 1, r.width - 1) = '+';

    //左上角坐标为(1,1);
    r.copyblock(1, 1, p);
    return r;
}


picture operator &(const picture &p, const picture &q)
{
    picture r;
    r.init(p.height + q.height,
           picture::max(p.width, q.width));

    r.clear(0, p.width, p.height, r.width);
    r.clear(p.height, q.width, r.height, r.width);

    r.copyblock(0, 0, p);
    r.copyblock(p.height, 0, q);

    return r;
}


picture operator |(const picture & p, const picture &q)
{
    picture r;
    r.init(picture::max(p.height, q.height), p.width + q.width);
    r.clear(p.height, 0, r.height, p.width);
    r.clear(q.height,p.width, r.height, r.width);
    r.copyblock(0,0, p);
    r.copyblock(0, p.width, q);

    return r;
}
