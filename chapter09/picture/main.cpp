#include <iostream>
#include "picture.h"


using namespace std;
char* init[] = {"Paris", "in the", "Spring"};

int main()
{
//    picture p(init, 3);
//    cout << p << endl;

//    picture q = frame(p);
//    cout << q << endl;

//    picture r = p|q;
//    cout << r << endl;

//    picture s = p&q;
//    cout << s << endl<< frame(s)<< endl;

//    picture p(init, 3);
//    picture q = frame(p);
//    cout << frame(q &(p|q)) << endl;

    picture p(init, 3);
    cout << p << endl;
    picture q = p;
    cout << q << endl;
    return 0;
}

