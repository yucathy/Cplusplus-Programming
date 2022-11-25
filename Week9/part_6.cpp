#include <iostream>
#include <set>
#include <cmath>

class Myless{
	
public:

	bool operator()(int v1, int v2)const{
		
		int nV1Number = get_prime_number(v1);
		
		int nV2Number = get_prime_number(v2);
		
		if(nV1Number == nV2Number){
			
			return v2 < v1;
		}
		
		return nV1Number > nV2Number;
		
	}

private:

	bool is_prime(int number)const{
	
		if(number == 1) return true;
		
		int nDivisibleNumber = 2;
		
		for(int i = 2; i <= sqrt(float(number)); ++i){
			
			if((number % i) == 0){ 
			
				nDivisibleNumber++; 
				
				break; 
			
			}
			
		}
		
		if(nDivisibleNumber == 2) return true;
		
		return false;
	
	}
	
	int get_prime_number(int value)const{
		
		int nDivisibleNumber = 1;
		
		if(value > 1){
			
			for(int i = 2; i <= sqrt(float(value)); ++i){

				if((value % i) == 0){

					int k = value / i;

					if(i != k && is_prime(k)) nDivisibleNumber++;

					if(is_prime(i)) nDivisibleNumber++;
				}

			}

		}

		
		return nDivisibleNumber;
		
	}

};

typedef std::multiset<int, Myless> MYSET;

int main(){
	
	MYSET MySet;

	int nAddtime;
	
	std::cin >> nAddtime;
	
	for(int i = 0; i < nAddtime; ++i){
		
		int nValueArray[10] = {0};
		
		for(int j = 0; j < 10; ++j){ 
		
			std::cin >> nValueArray[j]; 
			
			MySet.insert(nValueArray[j]);	
			
		}

		std::cout << *MySet.begin() << " " << *MySet.rbegin() << std::endl;

		MySet.erase(*MySet.begin());

		MySet.erase(*MySet.rbegin());

	}
	
	MYSET().swap(MySet);

	//system("pause");
	
	return 0;
}