#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <list>

class MySequence{

public:

	MySequence(){

		Seq.resize(10000);
	}

	~MySequence(){

		//use iterator to free space.

		std::vector< std::list<int> >::iterator vec_iter;

		for(vec_iter = Seq.begin(); vec_iter != Seq.end(); vec_iter++){

			std::list<int>().swap(*vec_iter);

		}

		std::vector< std::list<int> >().swap(Seq);

	}

	void add_data(int idx, int num){

		Seq.at(idx).push_back(num);
	}

	void unique_data(int idx){

		Seq.at(idx).sort();

		Seq.at(idx).unique();
	}

	void out_data(int idx){

		Seq.at(idx).sort();

		std::ostream_iterator<int> o(std::cout," ");

		std::copy(Seq.at(idx).begin(), Seq.at(idx).end(), o);

		std::cout << "\n";

	}

	void merge_data(int idx1, int idx2){

		Seq.at(idx1).merge(Seq.at(idx2));
	}

private:

	std::vector< std::list<int> > Seq;

};

int str2int(std::string str){

	int digital = 0;

	std::istringstream(str) >> digital;

	return digital;

}

int main(){

	MySequence *myseq = new MySequence();

	int nCommandCount;

	std::string operation;

	std::cin >> nCommandCount;

	std::cin.clear();

	std::cin.sync();

	std::string space_delimiter = " ";

	std::vector<std::string> words;

	for(int i = 0; i < nCommandCount; ++i){

		std::getline(std::cin, operation);

		int pos = 0;

		while ((pos = operation.find(space_delimiter)) != std::string::npos) {

	        words.push_back(operation.substr(0, pos));

	        operation.erase(0, pos + space_delimiter.length());

	    }

	    words.push_back(operation);

	    if(words.at(0) == "add"){

	    	myseq->add_data(str2int(words.at(1)), str2int(words.at(2)));

	    }
	    else if(words.at(0) == "out"){

	    	myseq->out_data(str2int(words.at(1)));

	    }
	    else if(words.at(0) == "merge"){

	    	myseq->merge_data(str2int(words.at(1)), str2int(words.at(2)));

	    	
	    }
	    else if(words.at(0) == "unique"){

	    	myseq->unique_data(str2int(words.at(1)));

	    	
	    }

	    std::vector<std::string>().swap(words);

	}

	delete myseq;

	return 0;
}