/*#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }*/

    Complex &operator = (char *s){

        if(!strlen(s)) return *this;

        r = atof(&s[0]);

        i = atof(&s[2]);

        return *this;
    }
/*};
int main() {

    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();

    system("pause");
    return 0;
}*/