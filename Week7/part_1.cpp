#include <iostream>
using namespace std;

template <class T>
class CArray3D{

public:

    CArray3D(int nValue1, int nValue2, int nValue3){

        Length = nValue1;

        TJ = new J[Length];

        for(int i = 0; i < Length; ++i){

            TJ[i].new_TK(nValue2, nValue3);

        }

    }

    ~CArray3D(){

        if(TJ){

            delete []TJ;

            TJ = NULL;

        }

    }

    class J{

    public:

        J(){

            if(!TK) TK = NULL;
        }

        ~J(){

            if(TK){

                delete []TK;

                TK = NULL;

            }

        }

        class K{

        public:

            K(){

                if(!TT) TT = NULL;
                
            }

            ~K(){

                if(TT){

                    delete []TT;

                    TT = NULL;
                }

            }

            T *TT;

            void new_TT(int Length3){

                TT = new T[Length3];

            }

            T &operator[](int val){

                return TT[val];

            }


        };

        K *TK;

        void new_TK(int Length2, int Length3){

            TK = new K[Length2];

            for(int i = 0; i < Length2; ++i){

                TK[i].new_TT(Length3);

            }

        }

        K &operator[](int val){

            return TK[val];

        }

    };


    J *TJ;

    int Length;

    J &operator[](int val){

        return TJ[val];

    }

};

int main()
{

    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
    return 0;

}
