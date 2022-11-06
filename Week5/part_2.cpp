#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

enum Red_Headquarter_Soldier {r_iceman = 0, r_lion, r_wolf, r_ninja, r_dragon};

enum Blue_Headquarter_Soldier {b_lion = 0, b_dragon, b_ninja, b_iceman, b_wolf};

enum Weapon {sword = 0, bomb, arrow};

std::string weapons_name[3] = {"sword", "bomb", "arrow"};

class CCreature{

public:

    CCreature(int id = 0, int lifevalue = 0):nId(id), nLifeVlaue(lifevalue){}

    ~CCreature(){}

    int nId;

    int nLifeVlaue;

    virtual void equipped(int serial_number, int total_life_value){ nId = (serial_number + 1); }

};

class Dragon:public CCreature{

public:

	Dragon(float morale = 0.):CCreature(), fMorale(morale){

		weapons[0] = -1;
	}

	float fMorale;

	int weapons[1];

    virtual void equipped(int serial_number, int total_life_value){ 

        nId = (serial_number + 1); 

        fMorale = total_life_value / float(nLifeVlaue);

        weapons[0] = nId % 3;

    }

	void show_status(){

		printf("It has a %s,and it's morale is %.2f\n", weapons_name[weapons[0]].c_str(), fMorale);

	}

};

class Ninja:public CCreature{

public:

	Ninja(float morale = 0):CCreature(){

		weapons[0] = -1;

		weapons[1] = -1;
	}

	int weapons[2];

    virtual void equipped(int serial_number, int total_life_value){ 

        nId = (serial_number + 1);

        weapons[0] = nId % 3;

        weapons[1] = (nId + 1) % 3;

    }

	void show_status(){

		printf("It has a %s and a %s\n", weapons_name[weapons[0]].c_str(),  weapons_name[weapons[1]].c_str());

	}

};

class Iceman:public CCreature{

public:

	Iceman(float morale = 0):CCreature(){

		weapons[0] = -1;

	}

	int weapons[1];

    virtual void equipped(int serial_number, int total_life_value){ 

        nId = (serial_number + 1);

        weapons[0] = nId % 3;

    }

	void show_status(){

		printf("It has a %s\n", weapons_name[weapons[0]].c_str());

	}
	
};

class Lion:public CCreature{

public:

	Lion(float loyalty = 0):CCreature(), nLoyalty(loyalty){}

	int nLoyalty;

    virtual void equipped(int serial_number, int total_life_value){ 

        nId = (serial_number + 1);

        nLoyalty = total_life_value;

    }

	void show_status(){

		printf("It's loyalty is %d\n", nLoyalty);

	}

};

class Wolf:public CCreature{

public:

	Wolf():CCreature(){}

};


class Headquarter{

public:

    Headquarter(int lifevalue, int dragon_lifevalue, int ninja_lifevalue, int iceman_lifevalue, int lion_lifevalue, int wolf_lifevalue): total_life_value(lifevalue){

        dragon.nLifeVlaue = dragon_lifevalue;

        ninja.nLifeVlaue = ninja_lifevalue;

        iceman.nLifeVlaue = iceman_lifevalue;

        lion.nLifeVlaue = lion_lifevalue;

        wolf.nLifeVlaue = wolf_lifevalue;

        memset(nSoliderNUmber, 0, sizeof(nSoliderNUmber[0]) * 5);

    }

    ~Headquarter(){}

    int total_life_value;

    Dragon dragon;

    Ninja ninja;

    Iceman iceman;

    Lion lion;

    Wolf wolf;

    int nSoliderNUmber [5];

    bool is_borned(CCreature &solider){

        if(total_life_value - solider.nLifeVlaue >= 0) return true;

        else return false;

    }

    void born_a_solider(CCreature &solider,int serial_number, int order){

        total_life_value -= solider.nLifeVlaue;

        solider.equipped(serial_number, total_life_value);

        nSoliderNUmber[order] ++;

    }

};

int main(){

    int case_id = 0, headquarter_life_points = 0;

    int dragon_life_points = 0, ninja_life_points = 0, iceman_life_points = 0, lion_life_points = 0, wolf_life_points = 0;

    std::cin >> case_id;

    static bool red_stop_flag = false;

    static bool blue_stop_flag = false;

    static int red_next_num = 0;

    static int blue_next_num = 0;

    for(int i = 0; i < case_id ; ++i){

        red_stop_flag = false;

        blue_stop_flag = false;

        red_next_num = 0;

        blue_next_num = 0;

        std::cin >> headquarter_life_points;

        std::cin >> dragon_life_points >> ninja_life_points >> iceman_life_points >> lion_life_points >> wolf_life_points;

        Headquarter *red = new Headquarter(headquarter_life_points, dragon_life_points, ninja_life_points, iceman_life_points, lion_life_points, wolf_life_points);

        Headquarter *blue = new Headquarter(headquarter_life_points, dragon_life_points, ninja_life_points, iceman_life_points, lion_life_points, wolf_life_points);

        int time = 0;

        std::cout << "Case:" << (i + 1) << std::endl;

        do{

            int red_loop = 0;

            int blue_loop = 0;

            bool red_flag = false;

            bool blue_flag = false;

            while(red_loop < 5 && red_flag == false && red_stop_flag == false){

                switch((time + red_next_num) % 5){

                    case r_iceman:

                        if(red->is_borned(red->iceman)){

                            red->born_a_solider(red->iceman, time, r_iceman);

                            printf("%03d red iceman %d born with strength %d,%d iceman in red headquarter\n", \

                                    time, red->iceman.nId, red->iceman.nLifeVlaue, red->nSoliderNUmber[r_iceman]);

                            red->iceman.show_status();

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case r_lion:

                        if(red->is_borned(red->lion)){

                            red->born_a_solider(red->lion, time, r_lion);

                            printf("%03d red lion %d born with strength %d,%d lion in red headquarter\n", \

                                    time, red->lion.nId, red->lion.nLifeVlaue, red->nSoliderNUmber[r_lion]);

                            red->lion.show_status();

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case r_wolf:

                        if(red->is_borned(red->wolf)){

                            red->born_a_solider(red->wolf, time, r_wolf);

                            printf("%03d red wolf %d born with strength %d,%d wolf in red headquarter\n", \

                                    time, red->wolf.nId, red->wolf.nLifeVlaue, red->nSoliderNUmber[r_wolf]);

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case r_ninja:

                        if(red->is_borned(red->ninja)){

                            red->born_a_solider(red->ninja, time, r_ninja);


                            printf("%03d red ninja %d born with strength %d,%d ninja in red headquarter\n", \

                                    time, red->ninja.nId, red->ninja.nLifeVlaue, red->nSoliderNUmber[r_ninja]);

                            red->ninja.show_status();

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case r_dragon:

                        if(red->is_borned(red->dragon)){

                            red->born_a_solider(red->dragon, time, r_dragon);

                            printf("%03d red dragon %d born with strength %d,%d dragon in red headquarter\n", \

                                    time, red->dragon.nId, red->dragon.nLifeVlaue, red->nSoliderNUmber[r_dragon]);

                            red->dragon.show_status();

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                }

                red_loop++;

            }

            if(red_flag == false && red_stop_flag == false) {

                red_stop_flag = true;

                red->total_life_value = 0;

                printf("%03d red headquarter stops making warriors\n", time);
            }

            while(blue_loop < 5 && blue_flag == false && blue_stop_flag == false){

                switch((time + blue_next_num) % 5){

                    case b_lion:

                        if(blue->is_borned(red->lion)){

                            blue->born_a_solider(blue->lion, time, b_lion);

                            printf("%03d blue lion %d born with strength %d,%d lion in blue headquarter\n", \

                                    time, blue->lion.nId, blue->lion.nLifeVlaue, blue->nSoliderNUmber[b_lion]);

                            blue->lion.show_status();

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case b_dragon:

                        if(blue->is_borned(red->dragon)){

                            blue->born_a_solider(blue->dragon, time, b_dragon);

                            printf("%03d blue dragon %d born with strength %d,%d dragon in blue headquarter\n", \

                                    time, blue->dragon.nId, blue->dragon.nLifeVlaue, blue->nSoliderNUmber[b_dragon]);

                            blue->dragon.show_status();

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case b_ninja:

                        if(blue->is_borned(red->ninja)){

                            blue->born_a_solider(blue->ninja, time, b_ninja);

                            printf("%03d blue ninja %d born with strength %d,%d ninja in blue headquarter\n", \

                                    time, blue->ninja.nId, blue->ninja.nLifeVlaue, blue->nSoliderNUmber[b_ninja]);

                            blue->ninja.show_status();

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case b_iceman:

                        if(blue->is_borned(red->iceman)){

                            blue->born_a_solider(blue->iceman, time, b_iceman);

                            printf("%03d blue iceman %d born with strength %d,%d iceman in blue headquarter\n", \

                                    time, blue->iceman.nId, blue->iceman.nLifeVlaue, blue->nSoliderNUmber[b_iceman]);

                            blue->iceman.show_status();

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case b_wolf:

                        if(blue->is_borned(red->wolf)){

                            blue->born_a_solider(blue->wolf, time, b_wolf);

                            printf("%03d blue wolf %d born with strength %d,%d wolf in blue headquarter\n", \

                                    time, blue->wolf.nId, blue->wolf.nLifeVlaue, blue->nSoliderNUmber[b_wolf]);

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                }

                blue_loop++;

            }

            if(blue_flag == false && blue_stop_flag == false){

                blue_stop_flag = true;

                blue->total_life_value = 0;

                printf("%03d blue headquarter stops making warriors\n", time);
            }

            time++;

        }while(red_stop_flag == false || blue_stop_flag == false);

        delete red;

        delete blue;

    }

    return 0;
}