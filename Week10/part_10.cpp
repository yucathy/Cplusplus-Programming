#include <iostream>
#include <map>
using namespace std;

class A{
	
public:

	A(){count++;}
	
	A(int value){count++;}
	
	virtual ~A(){
		
		std::cout << "A::destructor" << std::endl;
	
	}
	
	void operator delete(void *a){
		
		count--;
	}

	static int count;
	
private:

	
};

class B:public A{
	
public:	

	B():A(){}
	
	B(int value):A(){}
	
	virtual ~B(){
		
		std::cout << "B::destructor" << std::endl;
		
	}
	
};

int A::count = 0;

void func(B b) { }

int main()
{
        A a1(5),a2;
        cout << A::count << endl;
        B b1(4);
        cout << A::count << endl;
        func(b1);
        cout << A::count << endl;
        A * pa = new B(4);
        cout << A::count << endl;
        delete pa;
        cout << A::count << endl;

        return 0;
}
