#include <iostream>
using namespace std;

class CType{

public:

        CType(){}

        ~CType(){}

        int num;

        void setvalue(int n){ num = n; }

        CType &operator ++ (int){

                static CType temp;

                temp.num = num;

                num *= num;

                return temp;

        }

        friend ostream &operator << (ostream &o, CType &obj){

                o << obj.num;

                return o;

        }


};

int main(int argc, char* argv[]) {

        CType obj;

        int n;

        cin>>n;

        while ( n ) {

                obj.setvalue(n);

                cout<<obj++<<" "<<obj<<endl;

                cin>>n;

        }

        return 0;

}
