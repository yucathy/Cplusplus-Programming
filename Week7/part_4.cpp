#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

class StringOperation{

public:

	StringOperation(){

		StringArray = NULL;
	}

	StringOperation(int length){

		StringArray = new std::string[length];

		nArrayLength = length;
	}

	~StringOperation(){

		delete []StringArray;

		StringArray = NULL;
	}

	std::string *StringArray;

	void set_string_array(int idx, std::string str){ StringArray[idx] = str; }

	void print_string_array(int idx){ 

		std::cout << StringArray[idx] << std::endl;

	}

	std::string insert(std::string S, std::string N, std::string X){

		int nN = str2int(N);

		int nX = str2int(X);

		StringArray[nN - 1].insert(nX, S);

		return StringArray[nN - 1];

	}

	std::string copy(std::string N, std::string X, std::string L){

		int nN = str2int(N);

		int nX = str2int(X);

		int nL = str2int(L);

		return StringArray[nN - 1].substr(nX, nL);

	}

	std::string find(std::string S, std::string N){

		int nN = str2int(N);

		int pos = StringArray[nN - 1].find(S);

		if(pos == std::string::npos) pos = S.length();

		return int2str(pos);

	}

	std::string rfind(std::string S, std::string N){

		int nN = str2int(N);

		int pos = StringArray[nN - 1].rfind(S);

		if(pos == std::string::npos) pos = S.length();

		return int2str(pos);

	}

	std::string reset(std::string S, std::string N){

		int nN = str2int(N);

		StringArray[nN - 1] = S;

		return StringArray[nN - 1];

	}

	std::string add(std::string S1, std::string S2){

		if(isNumeric(S1) == true && isNumeric(S2) == true){

			long nS1 = str2int(S1);

			long nS2 = str2int(S2);

			if( (nS1 <= 999999 && nS1 >= 0) &&
				(nS2 <= 999999 && nS2 >= 0) ){

				return int2str(nS1 + nS2);
			
			}
			else{

				return S1 + S2;
			}

		}
		else{

			return S1 + S2;

		}


	}

	void print(std::string idx){

		int nidx = str2int(idx);

		std::cout << StringArray[nidx - 1] << std::endl;
	}

	void printall(){

		for(int i = 0; i < nArrayLength; ++i){

			std::cout << StringArray[i] << std::endl;

		}

	}

	bool isNumeric(std::string const &str){

		return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;

	}
    
private:

	int nArrayLength;

	long str2int(std::string str){

		long digital = 0;

		std::istringstream(str) >> digital;

		return digital;
	
	}

	std::string int2str(long value){

		std::stringstream ss;

		ss << value;
		
		return ss.str();

	}

};



int main(){

	int nStringLength;

	std::cin >> nStringLength;

	StringOperation *cStrOp = new StringOperation(nStringLength);

	for(int i = 0; i < nStringLength; ++i){

		std::string str;

		std::cin >> str;

		cStrOp->set_string_array(i, str);

	}

	std::cin.clear();

	std::cin.sync();

	std::string operation;

	std::string space_delimiter = " ";

	std::vector<std::string> words;

	while(std::getline(std::cin, operation)){

		if(operation == "over") break;

		int pos = 0;

		while ((pos = operation.find(space_delimiter)) != std::string::npos) {

	        words.push_back(operation.substr(0, pos));

	        operation.erase(0, pos + space_delimiter.length());

	    }

	    words.push_back(operation);

	    bool isDigintal[words.size()] = {true};

	    for(int i = words.size() - 1; i >= 0; --i) isDigintal[i] = cStrOp->isNumeric(words.at(i));

	    for(int i = (sizeof(isDigintal)/sizeof(*isDigintal)) - 1; i >= 0; --i){

	    	if(isDigintal[i] == false){

	    		std::string op = words.at(i);

	    		std::string result;

	    		if(op == "insert"){

	    			result = cStrOp->insert(words.at(i + 1), words.at(i + 2), words.at(i + 3));

		    		words.at(i) = result;

		    		words.erase(words.begin() + (i + 1), words.begin() + (i + 4));

	    		}
	    		else if(op == "copy"){

	    			result = cStrOp->copy(words.at(i + 1), words.at(i + 2), words.at(i + 3));

		    		words.at(i) = result;

		    		words.erase(words.begin() + (i + 1), words.begin() + (i + 4));

	    		}
	    		else if(op == "find"){

	    			result = cStrOp->find(words.at(i + 1), words.at(i + 2));

		    		words.at(i) = result;

		    		words.erase(words.begin() + (i + 1), words.begin() + (i + 3));

	    		}
	    		else if(op == "rfind"){

	    			result = cStrOp->rfind(words.at(i + 1), words.at(i + 2));

		    		words.at(i) = result;

		    		words.erase(words.begin() + (i + 1), words.begin() + (i + 3));

	    		}
	    		else if(op == "add"){

					result = cStrOp->add(words.at(i + 1), words.at(i + 2));

		    		words.at(i) = result;

		    		words.erase(words.begin() + (i + 1), words.begin() + (i + 3));

	    		}
	    		else if(op == "reset"){

					result = cStrOp->reset(words.at(i + 1), words.at(i + 2));

		    		words.at(i) = result;

		    		words.erase(words.begin() + (i + 1), words.begin() + (i + 3));

	    		}
	    		else if(op == "print"){

	    			cStrOp->print(words.at(i + 1));

	    		}
	    		else if(op == "printall"){

	    			cStrOp->printall();
	    		}

	    	}

	    }

	    std::vector<std::string>().swap(words);

	}
	
    std::vector<std::string>().swap(words);

	delete cStrOp;

	return 0;
	
}

