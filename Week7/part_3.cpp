#include <iostream>
#include <iomanip>

int main(){

	int dValue;

	std::cin >> dValue;

	std::cout << std::setbase(16) << dValue << std::endl;

	std::cout << std::dec;

	std::cout << std::setw(10) << std::setfill('0') << dValue << std::endl;

	return 0;
	
}