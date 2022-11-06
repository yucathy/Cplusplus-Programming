#include <iostream>
#include <stdio.h>


class A {

public:

    int val;

    A(int n = 0){ val = n; }

    ~A(){}

    int &GetObj(){ return val; }

 
};
int main(){

    std::cout << "this is an apple " << std::endl;

    return 0;
}