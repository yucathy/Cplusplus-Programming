#include <iostream>
#include <string>
#include <list>
using namespace std;

class A{
private:
        string name;
public:
        A(string n) :name(n){}
        friend bool operator < (const class A& a1, const class A &a2);
        friend bool operator == (const class A &a1, const class A &a2){
                if (a1.name.size() == a2.name.size())
                        return true;
                else
                        return false;
        }
        friend ostream & operator << (ostream &o, const A &a){
                o << a.name;
                return o;
        }
        string get_name() const{
                return name;
        }
        int get_size() const{
                return name.size();
        }
};

bool operator < (const A &elem1, const A &elem2){

        return elem1.get_size() < elem2.get_size();

}

struct Print{

        void operator()(const A &elem1){

                std::cout << elem1 << " ";
        }
};
#if 0
template < typename InputIterator, typename Function >
void Show(InputIterator begin, InputIterator end, Function f){

        while(begin != end){

                f(*begin++);
        }

}

#else
void Show(list<A>::iterator begin, list<A>::iterator end, Print f){

        while(begin != end){

                f(*begin++);
        }

}
#endif

template <class T>
struct MyLarge{

        bool operator () (const T &elem1, const T &elem2){

                return elem1.get_name() < elem2.get_name();

        } 

};

int main(int argc, char* argv[])
{
        list<A> lst;
        int ncase, n, i = 1;
        string s;
        cin >> ncase;
        while (ncase--){
                cout << "Case: "<<i++ << endl;
                cin >> n;
                for (int i = 0; i < n; i++){
                         cin >> s;
                         lst.push_back(A(s));
                }
                lst.sort();
                Show(lst.begin(), lst.end(), Print()); 

                cout << endl;
                lst.sort(MyLarge<A>());
                Show(lst.begin(), lst.end(), Print());
                cout << endl;
                lst.clear();
        }
        return 0;
}

