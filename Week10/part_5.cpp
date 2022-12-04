#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#endif
struct CMy_add{

        int *nSum;

        CMy_add(int &sum){

                nSum = &sum;

                *nSum = 0;

        }

        void operator() (int elem){

                *nSum += ( elem ^ 0xfffffff8 ) & 0x00000007;

        }
};
#if 0
int main(int argc, char* argv[]) {

        int v, my_sum=0;

        vector<int> vec;

        cin>>v;

        while ( v ) {

                vec.push_back(v);

                cin>>v;

        }

        for_each(vec.begin(), vec.end(), CMy_add(my_sum));

        cout<< my_sum <<endl;

        return 0;

}
#endif