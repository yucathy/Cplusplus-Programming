#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class A {

public:

    int val;

    A(int n = 0){ val = n; }

    ~A(){}

    int &GetObj(){ return val; }

 
};
int main(){

    A a;

    std::cout << a.val << std::endl;

    a.GetObj() = 5;

    std::cout << a.val << std::endl;

    system("pause");

    return 0;
}