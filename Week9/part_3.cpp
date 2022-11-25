#include <iostream>
#include <string>
#include <map>

typedef std::multimap<unsigned int, unsigned int> MAP_GYM;

class MyMultiMap{

public:

	MyMultiMap(){

		map_gym.insert(std::make_pair(1000000000, 1));
	}

	~MyMultiMap(){

		std::multimap<unsigned int, unsigned int>().swap(map_gym);

	}

	void add_data(unsigned int id, unsigned int str){

		map_gym.insert(std::make_pair(str, id));

	}

	void show_opponent(unsigned int id, unsigned int str){

		int nLowerDiff, nUpperDiff;

		std::pair<MAP_GYM::iterator, MAP_GYM::iterator> p;

		p = map_gym.equal_range(str);

		if(p.first == map_gym.begin()) {

			nLowerDiff = -1;
		} 
		else {

			p.first--;

			nLowerDiff = str - p.first->first;

		} 

		if(p.second == map_gym.end()) nUpperDiff = -1;

		else nUpperDiff = p.second->first - str;

		unsigned int opponent_id;

		if(nLowerDiff != -1)

			opponent_id = nLowerDiff <= nUpperDiff ? p.first->second : p.second->second;

		else 

			opponent_id = p.first->second;

		std::cout << id << " " << opponent_id << std::endl;

	}


private:

	MAP_GYM map_gym;

};

int main(){

	MyMultiMap *mymultimap = new MyMultiMap();

	int nNewbiesCount;

	std::string operation;

	std::cin >> nNewbiesCount;

	std::cin.clear();

	std::cin.sync();

	for(int i = 0; i < nNewbiesCount; ++i){

		unsigned int nId, nStr;

		std::cin >> nId >> nStr;

		mymultimap->show_opponent(nId, nStr);

		mymultimap->add_data(nId, nStr);

	}

	delete mymultimap;

	return 0;
}