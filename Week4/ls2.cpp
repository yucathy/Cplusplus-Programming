#include <iostream>
#include <cmath>

class CArray{

	int size;

	int *ptr;

	const int basic_space_size = 32;

public:

	CArray(int s = 0);

	CArray(CArray &a);

	~CArray();

	void push_back(int v);

	int length(){ return size; }

	CArray & operator=(const CArray &a);

	int & operator[](int i){ return ptr[i]; }

};

CArray::CArray(int s):size(s){

	if (s == 0) ptr = NULL;

	else ptr = new int[s];
}

CArray::CArray(CArray &a){

	if(! a.ptr){

		ptr = NULL;

		size = 0;

		return;
	}

	int multiple = floor((a.size + 1) / basic_space_size) + 1;

	ptr = new int(multiple * basic_space_size);

	memcpy(ptr, a.ptr, sizeof(int) * a.size);

	size = a.size;

}

CArray::~CArray(){

	if(ptr) delete []ptr;
}

CArray & CArray::operator=(const CArray &a){

	if(ptr == a.ptr) return *this;

	if(a.ptr == NULL){

		if(ptr) delete []ptr;

		ptr = NULL;

		size = 0;

		return *this;

	}

	if(size == 0){

		if(ptr) delete []ptr;

		int multiple = floor((a.size + 1) / basic_space_size) + 1;

		ptr = new int[multiple * basic_space_size];


	}
	else if(size < a.size){

		if(floor(size / basic_space_size) != floor(a.size / basic_space_size)){

			if(ptr) delete []ptr;

			int multiple = floor((a.size + 1) / basic_space_size) + 1;

			ptr = new int[multiple * basic_space_size];

		}

	}

	memcpy(ptr, a.ptr, sizeof(int) * a.size);

	size = a.size;

	return *this;
}

void CArray::push_back(int v){

	if(!ptr){

		ptr = new int[basic_space_size];

		size = 1;

		ptr[0] = v;

	}
	else{

		if ((size + 1) > basic_space_size){

			int multiple = floor((size + 1) / basic_space_size) + 1;

			int *temp_ptr = new int[multiple * basic_space_size];

			memcpy(temp_ptr, ptr, sizeof(int) * size);

			delete []ptr;

			ptr = temp_ptr;

		}

		ptr[size++] = v;

	}


}

int main(){

	CArray a; //構造函數初始化

	for(int i = 0; i < 5; ++i) a.push_back(i); // 成員函數

	CArray a2, a3; //構造函數初始化

	a2 = a; // =符號重載

	for(int i = 0; i < 5; ++i) std::cout << a2[i] << ", "; // []符號重載

	std::cout << "\n";

	a2 = a3; // =符號重載

	for(int i = 0; i < a2.length(); ++i) std::cout << a2[i] << ", "; // []符號重載
	
	std::cout << "\n";

	a[3] = 100; // =符號重載

	CArray a4(a); //複製構造函數重寫

	for(int i = 0; i < a4.length(); ++i) std::cout << a4[i] << ", ";

	std::cout << "\n";

	return 0;
}