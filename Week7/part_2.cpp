#include <iostream>
#include <iomanip>

int main(){

	double dValue;

	std::cin >> dValue;

	std::cout << std::fixed << std::setprecision(5) << dValue << std::endl;

	std::cout << std::scientific << std::setprecision(7) << dValue;

	return 0;
	
}