#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

class A{

public:

        A(){c = 'A';}

        A(int k):nAge(k){c = 'A';}

        ~A(){}

        int nAge;

        char c;

};

class B:public A{

public:
        B(){c = 'B';}

        B(int k):A(k){ c = 'B'; }

        ~B(){}
};

struct Comp{

        bool operator() (const A *a, const A *b){

                return a->nAge < b->nAge;
        }

};

void Print(const A *a){

        std::cout << a->c << " " << a->nAge << std::endl;

}

int main()
{

        int t;
        cin >> t;
        set<A*,Comp> ct;

        while( t -- ) {
                int n;
                cin >> n;
                ct.clear();
                for( int i = 0;i < n; ++i){
                        char c; int k;
                        cin >> c >> k;
                        if( c == 'A')
                                ct.insert(new A(k));
                        else
                                ct.insert(new B(k));
                }
                for_each(ct.begin(),ct.end(),Print);
                cout << "****" << endl;
        }

}
