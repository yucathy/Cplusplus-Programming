#include <iostream>
#include <cstring>

class BigInt{

private:

	int int_array[200];

	int work_unit;

	bool isnegative;

public:

	BigInt(){

		for(int i = 0; i < 200; ++i) int_array[i] = 0;

		work_unit = 0;

		isnegative = false;

	}

	BigInt(const int array[], int length, bool is_negative = false){

		memcpy(int_array, array, sizeof(int) * 200);

		work_unit = length;

		isnegative = is_negative;

	}

	~BigInt(){}

	void print_big_int_value(){

		if(isnegative) std::cout << "-";

		for(int i = 200 - work_unit; i < 200; ++i) std::cout << int_array[i];

		std::cout << "\n";

	}

	BigInt operator+(const BigInt &big_int);

	BigInt operator-(const BigInt &big_int);

	BigInt operator*(const BigInt &big_int);

	BigInt operator/(const BigInt &big_int);

	BigInt &operator=(const BigInt &big_int){
		
		memcpy(int_array, big_int.int_array, sizeof(int) * 200);

		work_unit = big_int.work_unit;

		isnegative = big_int.isnegative;

		return *this;
	}


};

BigInt BigInt::operator+(const BigInt &big_int){

	if(work_unit == 0 && big_int.work_unit == 0) return BigInt();

	else if(work_unit == 0 && big_int.work_unit != 0) return BigInt(big_int.int_array, big_int.work_unit);

	else if(work_unit != 0 && big_int.work_unit == 0) return BigInt(int_array, work_unit);

	else{

		bool plus_one = false;

		int max_unit = std::max(work_unit, big_int.work_unit);

		int result_array[200] = {0};

		for(int i = 199; i > 199 - max_unit; --i){

			int this_digit = int_array[i] + big_int.int_array[i];

			//std::cout << this_digit << std::endl;

			if(this_digit / 10 >= 1) {

				this_digit -= 10;

				result_array[i - 1] = 1;

				if(i == (200 - max_unit)) plus_one = true;

			}

			result_array[i] += this_digit;

			if(result_array[i] / 10 >= 1){

				result_array[i] -= 10;

				result_array[i - 1] = 1;

				if(i == (200 - max_unit)) plus_one = true;
			}

		}

		if (plus_one) return BigInt(result_array, max_unit + 1);

		else return BigInt(result_array, max_unit);

	}
	
}

BigInt BigInt::operator-(const BigInt &big_int){

	if(work_unit == 0 && big_int.work_unit == 0) return BigInt();

	else if(work_unit == 0 && big_int.work_unit != 0) return BigInt(big_int.int_array, big_int.work_unit);

	else if(work_unit != 0 && big_int.work_unit == 0) return BigInt(int_array, work_unit);

	else{

		bool is_negative = false;

		int result_array[200] = {0};

		bool the_former_bigger = true;

		bool the_same = false;

		int max_unit;

		if(work_unit == big_int.work_unit){

			for(int i = 200 - work_unit; i < 200; ++i){

				if(!(int_array[i] - big_int.int_array[i])){the_same = true; continue; } 

				if((int_array[i] - big_int.int_array[i]) > 0) {the_same = false; break; }

				if((int_array[i] - big_int.int_array[i]) < 0){ the_same = false; the_former_bigger = false; break; }

			}

		}
		else if(work_unit < big_int.work_unit) the_former_bigger = false;

		if(the_same) {

			result_array[199] = 0;

			return BigInt(result_array, 1);
		}

		if(the_former_bigger == false){

			is_negative = true;

			max_unit = big_int.work_unit;

			for(int i = 199; i > 199 - max_unit; --i){

				int this_digit = big_int.int_array[i] - int_array[i];

				if(this_digit < 0) {

					this_digit += 10;

					result_array[i - 1] = -1;

				}

				result_array[i] += this_digit;

				if(result_array[i] < 0){

					result_array[i] += 10;

					result_array[i - 1] = -1;
				} 

			}

		}
		else if(the_former_bigger == true){

			is_negative = false;

			max_unit = work_unit;

			for(int i = 199; i > 199 - max_unit; --i){

				int this_digit = int_array[i] - big_int.int_array[i];

				if(this_digit < 0) {

					this_digit += 10;

					result_array[i - 1] = -1;

				}

				result_array[i] += this_digit;

				if(result_array[i] < 0){

					result_array[i] += 10;

					result_array[i - 1] = -1;
				} 


			}

		}

		int current_unit = max_unit;

		for(int i = 200 - max_unit; i < 200; ++i){

			if(result_array[i] == 0) {

				current_unit = max_unit - 1;

				continue;
			}
			else break;

		}

		return BigInt(result_array, current_unit, is_negative);

	}
	
}

BigInt BigInt::operator*(const BigInt &big_int){

	if(work_unit == 0 && big_int.work_unit == 0) return BigInt();

	else if(work_unit == 0 && big_int.work_unit != 0) return BigInt(big_int.int_array, big_int.work_unit);

	else if(work_unit != 0 && big_int.work_unit == 0) return BigInt(int_array, work_unit);

	else{

		bool previous_on = false;

		int result_array[200] = {0};

		int the_result_work_unit = 200; 

		for(int i = 199; i > 199 - big_int.work_unit; --i){

			int added = 0;

			for(int j = 199; j > 199 - work_unit; --j){

				int this_digit = (big_int.int_array[i] * int_array[j]) + added;

				if(this_digit / 10 >= 1){

					added = this_digit / 10;

					this_digit %= 10;

					if(j == (200 - work_unit)) {previous_on = true; result_array[j + i - 199 - 1] += added;}
				}

				result_array[j + i - 199] += this_digit;

				if(result_array[j + i - 199] / 10 >= 1){

					result_array[j + i - 199 - 1] += 1;

					result_array[j + i - 199] %= 10;

				}

				the_result_work_unit = 200 - (j + i - 199) + previous_on;
			}

		}

		return BigInt(result_array, the_result_work_unit);

	}
	
}

BigInt BigInt::operator/(const BigInt &big_int){

	if(work_unit == 0 && big_int.work_unit == 0) return BigInt();

	else if(work_unit == 0 && big_int.work_unit != 0) return BigInt(big_int.int_array, big_int.work_unit);

	else if(work_unit != 0 && big_int.work_unit == 0) return BigInt(int_array, work_unit);

	else{

		int result_array[200] = {0};

		//int iterator_array[200] = {0};

		//memcpy(iterator_array, int_array, sizeof(int) * 200);

		//memcpy(iterator_array, big_int.int_array, sizeof(int) * 200);

		bool the_former_bigger = true;

		bool previous_on = false;

		bool the_same = false;

		if(work_unit == big_int.work_unit){

			for(int i = 200 - work_unit; i < 200; ++i){

				if(!(int_array[i] - big_int.int_array[i])){the_same = true; continue; } 

				if((int_array[i] - big_int.int_array[i]) > 0) {the_same = false; break; }

				if((int_array[i] - big_int.int_array[i]) < 0){ the_same = false; the_former_bigger = false; break; }

			}

		}
		else if(work_unit < big_int.work_unit) the_former_bigger = false;

		if(the_same) {

			result_array[199] = 1;

			return BigInt(result_array, 1);
		}

		if(!the_former_bigger) return BigInt(result_array, 1);

		else{

			int max_unit;

			if(work_unit == big_int.work_unit) max_unit = 1;

			else {

				int F1 = int_array[200 - work_unit];

				int F2 = big_int.int_array[200 - big_int.work_unit];

				if(F1 >= F2) max_unit = work_unit - big_int.work_unit + 1;

				else max_unit = work_unit - big_int.work_unit;
				
			}

			int process = 0;

			int previous_temp_array[200] = {0};

			memcpy(previous_temp_array, int_array, sizeof(int) * 200);

			while(process < max_unit){

				int iterator_array[200] = {0};

				int diff = work_unit - big_int.work_unit - process;

				if(max_unit == diff) memcpy(iterator_array, big_int.int_array, sizeof(int) * 200);

				else{

					for(int i = 200 - big_int.work_unit - diff; i < (200 - diff); ++i) iterator_array[i] = big_int.int_array[i + diff];
				}

				int count = 0;

				bool break_flag = false;

				while(1){

					int temp_array[200] = {0};

					for(int i = 199; i > 199 - work_unit; --i){

						//std::cout << previous_temp_array[i] << std::endl;

						//std::cout << iterator_array[i] << std::endl;

						int this_digit = previous_temp_array[i] - iterator_array[i];

						//std::cout << this_digit << std::endl;

						if(this_digit < 0) {

							this_digit += 10;

							temp_array[i - 1] = -1;

						}

						temp_array[i] += this_digit;

						//std::cout << temp_array[i] << std::endl;

						//std::cout << "---" <<std::endl;

						if(temp_array[i] < 0){

							temp_array[i] += 10;

							temp_array[i - 1] = -1;
						}

					}

					for(int j = 0; j < 200; ++j){

						if(temp_array[j] < 0) {

							break_flag = true;

							break;
						}
					}

					//std::cout << "flag:" << break_flag << std::endl;

					//system("pause");

					if(break_flag) break;

					else memcpy(previous_temp_array, temp_array, sizeof(int) * 200);

					count++;
				}

				if(count == 10){

					result_array[200 - max_unit + process] = 0;

					result_array[200 - max_unit + process - 1] = 0;

				}else{

					result_array[200 - max_unit + process] = count;
				}

				process++;

			}

			return BigInt(result_array, max_unit);
				

			/*static int count = 0;

			int quotient = -1;

			int max_unit = work_unit;

			while(iterator_array[199 - big_int.work_unit] >= 0){

				int temp_array[200] = {0};

				for(int i = 199; i > 199 - max_unit; --i){

					int this_digit = iterator_array[i] - big_int.int_array[i];

					//std::cout << this_digit <<std::endl;

					if(this_digit < 0) {

						this_digit += 10;

						temp_array[i - 1] = -1;

					}

					temp_array[i] += this_digit;

					if(temp_array[i] < 0 && i > 200 - max_unit){

						temp_array[i] += 10;

						temp_array[i - 1] = -1;
					}

					//std::cout << temp_array[i] << std::endl;

				}

				memcpy(iterator_array, temp_array, sizeof(int) * 200);

				quotient++;

				
			}

			return BigInt(result_array, 200 - result_array_index);*/
			
		}

	}

}


int main(){


	int first_int_array[200] = {0};

	int second_int_array[200] = {0};

	std::string first_term, second_term;

	char symbol;

	std::cin >> first_term >> symbol >> second_term;

	const char *first_char_ptr = first_term.c_str();

	const char *second_char_ptr = second_term.c_str();

	int first_term_length = std::strlen(first_char_ptr);

	int second_term_length = std::strlen(second_char_ptr);

	for(int i = 200 - first_term_length; i < 200; ++i) first_int_array[i] = first_char_ptr[i - (200 - first_term_length)] - '0';

	for(int i = 200 - second_term_length; i < 200; ++i) second_int_array[i] = second_char_ptr[i - (200 - second_term_length)] - '0';

	BigInt FirstTerm(first_int_array, first_term_length), SecondTerm(second_int_array, second_term_length), Result;

	switch(symbol){

		case '+':

			Result = FirstTerm + SecondTerm;

			Result.print_big_int_value();

			break;

		case '-':

			Result = FirstTerm - SecondTerm;

			Result.print_big_int_value();

			break;

		case '*':

			Result = FirstTerm * SecondTerm;

			Result.print_big_int_value();

			break;

		case '/':

			Result = FirstTerm / SecondTerm;

			Result.print_big_int_value();

			break;

		default:

			std::cout << "error symbol!" << std::endl;

			break;
	}


	return 0;
}