#include <iostream>
#include <cstring>
using namespace std;

class Array2{

private:

    int **spaces;

    int *space;

    int rows;

    int cols;


public:

    Array2(){

        spaces = NULL;

        rows = 0;

        cols = 0;

    }

    Array2(int v1, int v2);

    ~Array2();

    int *operator[](int val){

        space = spaces[val];

        return space;
    }

    int &operator()(int v1, int v2) {return spaces[v1][v2];}

    Array2 &operator=(const Array2 &array){

        if(spaces == array.spaces) return *this;

        if(spaces){

            for(int i = 0; i < rows; ++i) delete spaces[i];        

            delete []spaces;

            spaces = NULL;

        }

        spaces = new int*[array.rows];

        for(int i = 0; i < array.rows; ++i) spaces[i] = new int[array.cols];

        memcpy(spaces, array.spaces, sizeof(int) * array.cols * array.rows);

        return *this;
        
    }


};

Array2::Array2(int v1, int v2){

    rows = v1;

    cols = v2;

    spaces = new int*[rows];

    for(int i = 0; i < rows; ++i) spaces[i] = new int[cols];

}

Array2::~Array2(){

    if(spaces){

        for(int i = 0; i < rows; ++i) delete spaces[i];        

        delete []spaces;

        spaces = NULL;

    } 

}

/*int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;

    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i, j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    
    return 0;
}*/