#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>


enum Soldier_Input_Order {idragon, ininja, iiceman, ilion, iwolf};

enum Weapons {sword = 0, bomb, arrow};

enum Events {born = 0, lion_ran_away = 5, marched_to = 10, born_citylife = 20, take_away_citylife = 30, \

            shoot_time = 35, bomb_time = 38, fight_time = 40, report_headquarter_lifetime = 50, \

            report_weapons_time = 55};

enum City_Flag {red_flag = -1, no_flag = 0, blue_flag = 1};

std::string weapons_name[3] = {"sword", "bomb", "arrow"};

class Weapon{

public:

    Weapon(){nCategory = -1; nAttackValue = -1; nArrowNumberOfTimes = 3;}

    ~Weapon(){}

    int nCategory;

    int nAttackValue;
	
	int nArrowNumberOfTimes;

    std::string get_the_type_name(){ return weapons_name[nCategory]; }

    bool is_weapon_broken(){

        if(nCategory == arrow){

            nArrowNumberOfTimes--;

            if(nArrowNumberOfTimes == 0) return true;

            else return false;

        }

        if(nCategory == sword){

            nAttackValue = int(nAttackValue * 0.8);

            if(nAttackValue == 0) return true;

            else return false;
        }

        if(nCategory == bomb) return false;

        if(nCategory == -1) return true;

    }
    
private:

    int sword = 0;

    int bomb = 1;

    int arrow = 2;

    std::string weapons_name[3] = {"sword", "bomb", "arrow"};

};

class CCreature{

public:

    CCreature(int currentposition, int id = 0, int lifevalue = 0, int attackpower = 0):\

    nCurrentPositionCity(currentposition), nId(id), nLifeVlaue(lifevalue), nAttackPower(attackpower){}

    virtual ~CCreature(){}

    int nId;

    int nLifeVlaue;

    int nAttackPower;

    int nCurrentPositionCity;

    virtual void move(int currentposition) {nCurrentPositionCity = currentposition;}

    virtual void equipped(int total_life_value, int R){}

    virtual void show_status(){}

    virtual std::string get_the_species() = 0;

    virtual bool check_weapon_status(int &amount){ amount = 0; return false; }

    virtual int& get_and_set_weapon_category(int idx){};

    virtual int& get_and_set_weapon_attackvalue(int idx){};

    virtual int& get_and_set_arrow_times(int idx){};

    virtual bool is_weapon_broken(int idx){ return true; };

    virtual void active_attack(CCreature *enemy){

        int sword_id = -1;

        int sword_attack_value = 0;

        int weapon_amount = 0;

        if(check_weapon_status(weapon_amount)){

            for(int j = 0; j <weapon_amount; j++){

                if(get_and_set_weapon_category(j) == sword){

                    sword_attack_value = get_and_set_weapon_attackvalue(j);

                    sword_id = j;
                }

            }

        }

        enemy->nLifeVlaue -= this->nAttackPower + sword_attack_value;

        if(sword_id != -1){

            if(is_weapon_broken(sword_id)) get_and_set_weapon_category(sword_id) = -1;

        } 

    }

    virtual bool is_killed(CCreature *enemy){

        if(enemy->nLifeVlaue <= 0) return true;

        else return false;

    }

    virtual void fight_back(CCreature *enemy){

        int sword_id = -1;

        int sword_attack_value = 0;

        int weapon_amount = 0;

        if(check_weapon_status(weapon_amount)){

            for(int j = 0; j <weapon_amount; j++){

                if(get_and_set_weapon_category(j) == sword){

                    sword_attack_value = get_and_set_weapon_attackvalue(j);

                    sword_id = j;
                }

            }

        }

        enemy->nLifeVlaue -= (int(this->nAttackPower * 0.5) + sword_attack_value);

        if(sword_id != -1) if(is_weapon_broken(sword_id)) get_and_set_weapon_category(sword_id) = -1;

    }

    void common_reward(int reward_element){ nLifeVlaue += reward_element; }

    virtual void reward(CCreature *enemy){}

    virtual void punished(int K){};

    virtual void get_lion_lifevalue(CCreature *enemy, int enemy_nlifevalue){

        if(enemy) if(enemy->get_the_species() == "lion") nLifeVlaue += enemy_nlifevalue;

    } 

    virtual bool is_celebrated(){return false;}
	
	virtual void show_weapons_status(int amount){};
	

};

class Dragon:public CCreature{

private:

    std::string specie = "dragon";

    Weapon weapons[1];

public:

    Dragon(int currentposition, int id = 0, int lifevalue = 0, int attackpower = 0): \

    CCreature(currentposition, id, lifevalue, attackpower){ fMorale = 0; }

    virtual ~Dragon(){}

    double fMorale;

    virtual void equipped(int total_life_value, int R){

        fMorale = total_life_value / double(nLifeVlaue);

        weapons[0].nCategory = nId % 3;

        if(weapons[0].nCategory == arrow){ weapons[0].nAttackValue = R; } 

        else if(weapons[0].nCategory == sword){

            weapons[0].nAttackValue = int(nAttackPower * 0.2);

            if(weapons[0].nAttackValue == 0) weapons[0].nCategory = -1;

        } 

        else{ weapons[0].nAttackValue = 0; } 

    }

    virtual void show_status(){ printf("Its morale is %.2f\n", fMorale); }

    virtual std::string get_the_species(){ return specie; }

    virtual bool check_weapon_status(int &amount){

        amount = 1;

        return true;
		
	}
	
    virtual int& get_and_set_weapon_category(int idx){ return weapons[idx].nCategory; }

    virtual int& get_and_set_weapon_attackvalue(int idx){ return weapons[idx].nAttackValue; }

    virtual int& get_and_set_arrow_times(int idx){ return weapons[idx].nArrowNumberOfTimes; };

    virtual bool is_weapon_broken(int idx){ return weapons[idx].is_weapon_broken(); }

	virtual void show_weapons_status(int amount){

        if(weapons[0].nCategory == -1) printf("has no weapon\n");

        else if(weapons[0].nCategory == bomb) printf("has bomb\n");
            
        else if(weapons[0].nCategory == arrow) printf("has arrow(%d)\n", weapons[0].nArrowNumberOfTimes);
        
        else if(weapons[0].nCategory == sword) printf("has sword(%d)\n", weapons[0].nAttackValue);
		
	}
	
    virtual void reward(CCreature *enemy){ fMorale += 0.2; }

    virtual void punished(int K){ fMorale -= 0.2; }

    virtual bool is_celebrated(){

        if(fMorale > 0.8) return true;

        return false;
    };


};

class Ninja:public CCreature{

private:

    std::string specie = "ninja";

    Weapon weapons[2];

public:

    Ninja(int currentposition, int id = 0, int lifevalue = 0, int attackpower = 0): \

    CCreature(currentposition, id, lifevalue, attackpower){}

    virtual ~Ninja(){}

    virtual void equipped(int total_life_value, int R){ 

        weapons[0].nCategory = nId % 3;

        if(weapons[0].nCategory == arrow){ weapons[0].nAttackValue = R; } 

        else if(weapons[0].nCategory == sword){

            weapons[0].nAttackValue = int(nAttackPower * 0.2);

            if(weapons[0].nAttackValue == 0) weapons[0].nCategory = -1;

        } 

        else{ weapons[0].nAttackValue = 0;} 

        weapons[1].nCategory = (nId + 1) % 3;

        if(weapons[1].nCategory == arrow){ weapons[1].nAttackValue = R; } 

        else if(weapons[1].nCategory == sword){

            weapons[1].nAttackValue = int(nAttackPower * 0.2);

            if(weapons[1].nAttackValue == 0) weapons[1].nCategory = -1;

        } 

        else{ weapons[1].nAttackValue = 0; }

    }

    virtual std::string get_the_species(){ return specie; }

    virtual bool check_weapon_status(int &amount){

        amount = 2;

        return true;
	
	}

    virtual int& get_and_set_weapon_category(int idx){ return weapons[idx].nCategory; }

    virtual int& get_and_set_weapon_attackvalue(int idx){ return weapons[idx].nAttackValue; }

    virtual int& get_and_set_arrow_times(int idx){ return weapons[idx].nArrowNumberOfTimes; };

    virtual bool is_weapon_broken(int idx){ return weapons[idx].is_weapon_broken(); }

	virtual void show_weapons_status(int amount){

        if((weapons[0].nCategory == -1) && (weapons[1].nCategory == -1)){ printf("has no weapon\n"); } 

        else if((weapons[0].nCategory != -1) && (weapons[1].nCategory != -1)){

            if(weapons[0].nCategory > weapons[1].nCategory){
                
                if(weapons[0].nCategory == arrow){
                    
                    if(weapons[1].nCategory == sword) printf("has arrow(%d),sword(%d)\n", weapons[0].nArrowNumberOfTimes, weapons[1].nAttackValue);
                        
                    else printf("has arrow(%d),bomb\n", weapons[0].nArrowNumberOfTimes);
                    
                }
                else printf("has bomb,sword(%d)\n", weapons[1].nAttackValue);
                
            }
            else{
                
                if(weapons[1].nCategory == arrow){
                    
                    if(weapons[0].nCategory == sword) printf("has arrow(%d),sword(%d)\n", weapons[1].nArrowNumberOfTimes, weapons[0].nAttackValue);
                        
                    else printf("has arrow(%d),bomb\n", weapons[1].nArrowNumberOfTimes);
                    
                }
                else printf("has bomb,sword(%d)\n", weapons[0].nAttackValue);
                
            }

        }

        else{

                int idx = 0;

                if(weapons[0].nCategory == -1) idx = 1;
                
                if(weapons[idx].nCategory == bomb) printf("has bomb\n");
                    
                else if(weapons[idx].nCategory == arrow) printf("has arrow(%d)\n", weapons[idx].nArrowNumberOfTimes);
                
                else if(weapons[idx].nCategory == sword) printf("has sword(%d)\n", weapons[idx].nAttackValue);

        }

	}
};

class Iceman:public CCreature{

private:

    std::string specie = "iceman";

    Weapon weapons[1];

    int two_step;

public:

    Iceman(int currentposition, int id = 0, int lifevalue = 0, int attackpower = 0): \

    CCreature(currentposition, id, lifevalue, attackpower){

        two_step = 0;
    }

    virtual ~Iceman(){}

    virtual void equipped(int total_life_value, int R){ 

        weapons[0].nCategory = nId % 3;

        if(weapons[0].nCategory == arrow){ weapons[0].nAttackValue = R; } 

        else if(weapons[0].nCategory == sword){

            weapons[0].nAttackValue = int(nAttackPower * 0.2);

            if(weapons[0].nAttackValue == 0) weapons[0].nCategory = -1;

        } 

        else{ weapons[0].nAttackValue = 0; } 

    }

    virtual std::string get_the_species(){ return specie; }

    virtual void move(int currentposition) {

        two_step++;

        if((two_step % 2) == 0){

            if(nLifeVlaue - 9 <= 0) nLifeVlaue = 1;

            else nLifeVlaue -= 9;

            nAttackPower += 20;

        }

        nCurrentPositionCity = currentposition;

    }

    virtual bool check_weapon_status(int &amount){

        amount = 1;

        return true;
		
	}

    virtual int& get_and_set_weapon_category(int idx){ return weapons[idx].nCategory; }

    virtual int& get_and_set_weapon_attackvalue(int idx){ return weapons[idx].nAttackValue; }

    virtual int& get_and_set_arrow_times(int idx){ return weapons[idx].nArrowNumberOfTimes; };

    virtual bool is_weapon_broken(int idx){ return weapons[idx].is_weapon_broken(); }

	virtual void show_weapons_status(int amount){
		
        if(weapons[0].nCategory == -1) printf("has no weapon\n");

        else if(weapons[0].nCategory == bomb) printf("has bomb\n");
            
        else if(weapons[0].nCategory == arrow) printf("has arrow(%d)\n", weapons[0].nArrowNumberOfTimes);
        
        else if(weapons[0].nCategory == sword) printf("has sword(%d)\n", weapons[0].nAttackValue);
		
	}
};

class Lion:public CCreature{

private:

    std::string specie = "lion";

public:

    Lion(int currentposition, int id = 0, int lifevalue = 0, int attackpower = 0): \

    CCreature(currentposition, id, lifevalue, attackpower){ nLoyalty = 0; }

    virtual ~Lion(){}

    int nLoyalty;

    virtual void equipped(int total_life_value, int R){ nLoyalty = total_life_value; }

    virtual void show_status(){ printf("Its loyalty is %d\n", nLoyalty); }

    virtual std::string get_the_species(){ return specie; }

    virtual void punished(int K){ nLoyalty -= K; }
	
	virtual void show_weapons_status(int amount){ printf("has no weapon\n"); }
		

};

class Wolf:public CCreature{

private:

    std::string specie = "wolf";

    Weapon weapons[3];

public:

    Wolf(int currentposition, int id = 0, int lifevalue = 0, int attackpower = 0): \

    CCreature(currentposition, id, lifevalue, attackpower){

        for(int i = 0; i < 3; ++i) weapons[i].nCategory = -1;
    }

    virtual ~Wolf(){}

    virtual int& get_and_set_weapon_category(int idx){ return weapons[idx].nCategory; }

    virtual int& get_and_set_weapon_attackvalue(int idx){ return weapons[idx].nAttackValue; }

    virtual int& get_and_set_arrow_times(int idx){ return weapons[idx].nArrowNumberOfTimes; }

    virtual bool is_weapon_broken(int idx){ return weapons[idx].is_weapon_broken(); }

    virtual bool check_weapon_status(int &amount){

        amount = 3;

        return true;
		
	}

	virtual void show_weapons_status(int amount){

        if((weapons[0].nCategory == -1) && (weapons[1].nCategory == -1) && (weapons[2].nCategory == -1)){ printf("has no weapon\n"); }

        else if((weapons[0].nCategory != -1) && (weapons[1].nCategory != -1) && (weapons[2].nCategory != -1)){

            int max, middle, min;
            
            for(int i = 0; i < amount; ++i){
                
                if(weapons[i].nCategory == 0) min = i;
                
                if(weapons[i].nCategory == 1) middle = i;
                
                if(weapons[i].nCategory == 2) max = i;
                
            }
            
            printf("has arrow(%d),bomb, sword(%d)\n", weapons[max].nArrowNumberOfTimes, weapons[min].nAttackValue);

        }
        else if(((weapons[0].nCategory != -1) && (weapons[1].nCategory != -1) && (weapons[2].nCategory == -1)) || \

                ((weapons[0].nCategory == -1) && (weapons[1].nCategory != -1) && (weapons[2].nCategory != -1)) || \

                ((weapons[0].nCategory != -1) && (weapons[1].nCategory == -1) && (weapons[2].nCategory != -1))){

            int idx1, idx2;

            if(weapons[0].nCategory == -1){ idx1 = 1; idx2 = 2; }

            else if(weapons[1].nCategory == -1){ idx1 = 0; idx2 = 2; }

            else if(weapons[2].nCategory == -1){ idx1 = 0; idx2 = 1; }

            if(weapons[idx1].nCategory > weapons[idx2].nCategory){
                
                if(weapons[idx1].nCategory == arrow){
                    
                    if(weapons[idx2].nCategory == sword) printf("has arrow(%d),sword(%d)\n", weapons[idx1].nArrowNumberOfTimes, weapons[idx2].nAttackValue);
                        
                    else printf("has arrow(%d),bomb\n", weapons[idx1].nArrowNumberOfTimes);
                    
                }
                else printf("has bomb,sword(%d)\n", weapons[idx2].nAttackValue);
                
            }
            else{
                
                if(weapons[idx2].nCategory == arrow){
                    
                    if(weapons[idx1].nCategory == sword) printf("has arrow(%d),sword(%d)\n", weapons[idx2].nArrowNumberOfTimes, weapons[idx1].nAttackValue);
                        
                    else printf("has arrow(%d),bomb\n", weapons[idx2].nArrowNumberOfTimes);
                    
                }
                else printf("has bomb,sword(%d)\n", weapons[idx1].nAttackValue);
                
            }

        }
        else if(((weapons[0].nCategory != -1) && (weapons[1].nCategory == -1) && (weapons[2].nCategory == -1)) || \

                ((weapons[0].nCategory == -1) && (weapons[1].nCategory != -1) && (weapons[2].nCategory == -1)) || \

                ((weapons[0].nCategory == -1) && (weapons[1].nCategory == -1) && (weapons[2].nCategory != -1))){


            int idx;

            if(weapons[0].nCategory != -1) idx = 0;

            else if(weapons[1].nCategory != -1) idx = 1;

            else if(weapons[2].nCategory != -1) idx = 2;

            if(weapons[idx].nCategory == bomb) printf("has bomb\n");
                
            else if(weapons[idx].nCategory == arrow) printf("has arrow(%d)\n", weapons[idx].nArrowNumberOfTimes);
            
            else if(weapons[idx].nCategory == sword) printf("has sword(%d)\n", weapons[idx].nAttackValue);

        }
		
	}

    bool is_picked_already(int category){

        for(int i = 0; i < 3; ++i) if(weapons[i].nCategory == category) return true;

        return false;

    }

    void pciked_up_weapon(int category, int attack_value, int weapon_arrow_times){ 

        for(int i = 0; i < 3; ++i){

            if(weapons[i].nCategory == -1){

                weapons[i].nCategory = category;

                weapons[i].nAttackValue = attack_value;

                if(category == arrow)

                    weapons[i].nArrowNumberOfTimes = weapon_arrow_times;

                break;

            }

        } 

    }

    virtual std::string get_the_species(){ return specie; }

    virtual void reward(CCreature *enemy){

        int amount = 0;

        if(enemy->check_weapon_status(amount)){

            for(int j = 0; j < amount; ++j){

                int loser_weapon_category = enemy->get_and_set_weapon_category(j);

                int loser_weapon_attack_value = enemy->get_and_set_weapon_attackvalue(j);

                int loser_weapon_arrow_times = -1;

                if(loser_weapon_category == arrow)

                    loser_weapon_arrow_times = enemy->get_and_set_arrow_times(j);

                if(is_picked_already(loser_weapon_category)) continue;

                pciked_up_weapon(loser_weapon_category, loser_weapon_attack_value, loser_weapon_arrow_times);

            }

        }

    }

};


class Headquarter{

private:

    std::string team;

public:

    Headquarter(std::string name ,int headquarterid, int lifevalue, int species_lifevalue[5], int attackpower[5], int v1, int v2, int v3, int v4, int v5){

        team = name;

        nHeadquarterId = headquarterid;

        total_life_value = lifevalue;

        LION = v1;

        ICEMAN = v2;

        DRAGON = v3;

        WOLF = v4;

        NINJA = v5;

        nSpeciesLifeValue[ICEMAN] = species_lifevalue[iiceman];

        nSpeciesLifeValue[NINJA] = species_lifevalue[ininja];

        nSpeciesLifeValue[DRAGON] = species_lifevalue[idragon];

        nSpeciesLifeValue[LION] = species_lifevalue[ilion];

        nSpeciesLifeValue[WOLF] = species_lifevalue[iwolf];

        nSpeciesAttackPower[ICEMAN] = attackpower[iiceman];

        nSpeciesAttackPower[NINJA] = attackpower[ininja];

        nSpeciesAttackPower[DRAGON] = attackpower[idragon];

        nSpeciesAttackPower[LION] = attackpower[ilion];

        nSpeciesAttackPower[WOLF] = attackpower[iwolf];

        memset(nSoliderNUmber, 0, sizeof(nSoliderNUmber[0]) * 5);

        waiting_number = 0;

        for(int i = 0; i < 84; ++i) pCreature[i] = NULL;
		
		take_over_times = 0;

    }

    virtual ~Headquarter(){

        for(int i = 0; i < 84; ++i){

            if(pCreature[i]){

                delete pCreature[i];

                pCreature[i] = NULL;

            } 

        }

    }

    CCreature *pCreature[84];

    int total_life_value;

    int nSoliderNUmber[5];

    int nSpeciesLifeValue[5];

    int nSpeciesAttackPower[5];

    int nHeadquarterId;

    int nRedHqId;

    int nBlueHqId;

    int LION;

    int ICEMAN;

    int DRAGON;

    int WOLF;

    int NINJA;

    int waiting_number;
	
	int take_over_times;

    void waiting_for_next_time(){ waiting_number ++; }

    bool is_borned(int hour){

        int current_soilder_idx = ((hour - waiting_number) % 5);

        int current_LifeVlaue = nSpeciesLifeValue[current_soilder_idx];

        if(total_life_value - current_LifeVlaue >= 0) return true;

        else{

            waiting_for_next_time();

            return false;
        } 

    }

    void born_a_solider(int hour, int minute, int R){

        int current_soilder_idx = ((hour - waiting_number) % 5);

        int soilder_lifeValue = nSpeciesLifeValue[current_soilder_idx];

        int soilder_attackpower = nSpeciesAttackPower[current_soilder_idx];

        total_life_value -= soilder_lifeValue;

        if(current_soilder_idx == ICEMAN) pCreature[hour - waiting_number] = new Iceman(nHeadquarterId, (hour + 1 - waiting_number), soilder_lifeValue, soilder_attackpower);

        else if(current_soilder_idx == NINJA) pCreature[hour - waiting_number] = new Ninja(nHeadquarterId, (hour + 1 - waiting_number), soilder_lifeValue, soilder_attackpower);

        else if(current_soilder_idx == DRAGON) pCreature[hour - waiting_number] = new Dragon(nHeadquarterId, (hour + 1 - waiting_number), soilder_lifeValue, soilder_attackpower);

        else if(current_soilder_idx == LION) pCreature[hour - waiting_number] = new Lion(nHeadquarterId, (hour + 1 - waiting_number), soilder_lifeValue, soilder_attackpower);

        else if(current_soilder_idx == WOLF) pCreature[hour - waiting_number] = new Wolf(nHeadquarterId, (hour + 1 - waiting_number), soilder_lifeValue, soilder_attackpower);

        CCreature *solider = pCreature[hour - waiting_number];

        solider->equipped(total_life_value, R);

        printf("%03d:%02d %s %s %d born\n", \

                hour, minute, team.c_str(), solider->get_the_species().c_str(), solider->nId);

        solider->show_status();

        nSoliderNUmber[current_soilder_idx] ++;

    }

    void check_lion_ran_away(int hour, int minute){

        if(nSoliderNUmber[LION] > 0){

            for(int i = 0; i < nSoliderNUmber[LION]; ++i){

                if(pCreature[i * 5 + LION]){

                    Lion *lion = (Lion*)pCreature[i * 5 + LION];

                    if(lion->nLoyalty <= 0){

                        printf("%03d:%02d %s %s %d ran away\n", \

                        hour, minute, team.c_str(), lion->get_the_species().c_str(), lion->nId);

                        delete pCreature[i * 5 + LION];

                        pCreature[i * 5 + LION] = NULL;

                    }

                }

            }

        }

    }

    void killed(CCreature *loser){

        for(int i = 0; i < 84; ++i){

            if((pCreature[i] != NULL) && (loser->nId == pCreature[i]->nId)){

                delete pCreature[i]; 

                pCreature[i] = NULL;

                break;

            } 

        }

    }

    virtual void soliders_marched_to() = 0;

    void report_headquarter_lifetime(int hour, int minute){

        printf("%03d:%02d %d elements in %s headquarter\n", hour, minute, total_life_value, team.c_str());

    }

};

class RedHeadquarter:public Headquarter{

public:

    RedHeadquarter(int lifevalue, int cityid, int species_lifevalue[5], int attackpower[5]): \

    Headquarter("red", 0, lifevalue, species_lifevalue, attackpower, 1, 0, 4, 2, 3){

        nRedHqId = 0;
    }

    virtual ~RedHeadquarter(){}

    virtual void soliders_marched_to(){

        for(int i = 0; i < 84; ++i){

            if(pCreature[i]){

                pCreature[i]->move(pCreature[i]->nCurrentPositionCity + 1);

            }

        } 

    }

};

class BlueHeadquarter:public Headquarter{

public:

    BlueHeadquarter(int lifevalue, int cityid, int species_lifevalue[5], int attackpower[5]):\

    Headquarter("blue", cityid + 1, lifevalue, species_lifevalue, attackpower, 0, 3, 1, 4, 2) {

        nBlueHqId = cityid + 1;

    }

    virtual ~BlueHeadquarter(){}

    virtual void soliders_marched_to(){

        for(int i = 0; i < 84; ++i){

            if(pCreature[i]){

                pCreature[i]->move(pCreature[i]->nCurrentPositionCity - 1);

            }

        } 

    }


};

class Cities{

public:

    Cities(){ 

        memset(nCitiesOrder, 0, sizeof(nCitiesOrder[0]) * 20);

        memset(nCitiesFlag, 0, sizeof(nCitiesFlag[0]) * 20);

        memset(nCountSuccess, 0, sizeof(nCountSuccess[0]) * 20);

        for(int i = 0; i < 20; ++i) for(int j = 0; j < 2; ++j) CitySoliders[i][j] = NULL;

        for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j) HQSolider[i][j] = NULL;

        red_invade_times = 0;

        blue_invade_times = 0;

    }

    int nCitiesOrder[20];

    int nCitiesFlag[20];

    int nCountSuccess[20];

    int red_invade_times;

    int blue_invade_times;

    CCreature *CitySoliders[20][2];

    CCreature *HQSolider[2][2];

    void check_cities_status(Headquarter *red, Headquarter *blue, int N){

        for(int i = 0; i < N; ++i){

            CitySoliders[i][0] = NULL;

            CitySoliders[i][1] = NULL;

			for(int j = 0; j < 84; ++j){

				if((red->pCreature[j] != NULL) && (red->pCreature[j]->nCurrentPositionCity == (i + 1))){

					CitySoliders[i][0] = red->pCreature[j];

				} 

				if((blue->pCreature[j] != NULL) && (blue->pCreature[j]->nCurrentPositionCity == (i + 1))){

					CitySoliders[i][1] = blue->pCreature[j];

				}

			}

        }

        for(int j = 0; j < 84; ++j){

            if((red->pCreature[j] != NULL) && (red->pCreature[j]->nCurrentPositionCity == blue->nBlueHqId)){

                HQSolider[1][red_invade_times] = red->pCreature[j];

                red_invade_times++;

            }

            if((blue->pCreature[j] != NULL) && (blue->pCreature[j]->nCurrentPositionCity == red->nRedHqId)){

                HQSolider[0][blue_invade_times] = blue->pCreature[j];

                blue_invade_times++;

            }

        }

    }

    void lifevalue_take_away_from_soliders(int hour, int minute, Headquarter *red, Headquarter *blue){

        for(int i = 0; i < 20; ++i){

            if(nCitiesOrder[i] != 0){

                if((CitySoliders[i][0] != NULL) && (CitySoliders[i][1] == NULL)){

                    red->total_life_value += nCitiesOrder[i];

                    printf("%03d:%02d red %s %d earned %d elements for his headquarter\n", \

                    hour, minute, CitySoliders[i][0]->get_the_species().c_str(), \

                    CitySoliders[i][0]->nId, nCitiesOrder[i]);
					
					nCitiesOrder[i] = 0;

                }

                if((CitySoliders[i][0] == NULL) && (CitySoliders[i][1] != NULL)){

                    blue->total_life_value += nCitiesOrder[i];

                    printf("%03d:%02d blue %s %d earned %d elements for his headquarter\n", \

                    hour, minute, CitySoliders[i][1]->get_the_species().c_str(), \

                    CitySoliders[i][1]->nId, nCitiesOrder[i]);
					
					nCitiesOrder[i] = 0;

                }
                
            }

        }

    }

	void cities_marched_to(int hour, int minute, Headquarter *red, Headquarter *blue, bool &is_red_ended, bool &is_blue_ended){
		
        if(HQSolider[0][blue->take_over_times] != NULL){

            printf("%03d:%02d blue %s %d reached red headquarter with %d elements and force %d\n", \

            hour, minute, HQSolider[0][blue->take_over_times]->get_the_species().c_str(), \

            HQSolider[0][blue->take_over_times]->nId, HQSolider[0][blue->take_over_times]->nLifeVlaue, HQSolider[0][blue->take_over_times]->nAttackPower);

            blue->take_over_times++;

            if(blue->take_over_times == 2){

                printf("%03d:%02d red headquarter was taken\n", hour, minute);

                is_red_ended = true;

            } 

        }

		for(int i = 0; i < 20; ++i){
			
			if(CitySoliders[i][0] != NULL){

				printf("%03d:%02d red %s %d marched to city %d with %d elements and force %d\n", \

				hour, minute, CitySoliders[i][0]->get_the_species().c_str(), \

				CitySoliders[i][0]->nId, CitySoliders[i][0]->nCurrentPositionCity, CitySoliders[i][0]->nLifeVlaue, CitySoliders[i][0]->nAttackPower);				
					
			}
			
			if(CitySoliders[i][1] != NULL){
				
				printf("%03d:%02d blue %s %d marched to city %d with %d elements and force %d\n", \

				hour, minute, CitySoliders[i][1]->get_the_species().c_str(), \

				CitySoliders[i][1]->nId, CitySoliders[i][1]->nCurrentPositionCity, CitySoliders[i][1]->nLifeVlaue, CitySoliders[i][1]->nAttackPower);
					
			}

		}

        if(HQSolider[1][red->take_over_times] != NULL){

            printf("%03d:%02d red %s %d reached blue headquarter with %d elements and force %d\n", \

            hour, minute, HQSolider[1][red->take_over_times]->get_the_species().c_str(), \

            HQSolider[1][red->take_over_times]->nId, HQSolider[1][red->take_over_times]->nLifeVlaue, HQSolider[1][red->take_over_times]->nAttackPower);

            red->take_over_times++;

            if(red->take_over_times == 2){

                printf("%03d:%02d blue headquarter was taken\n", hour, minute);

                is_blue_ended = true;

            }

        }
	
	}

    void cities_shoot_time(int hour, int minute){

        for(int i = 0; i < 20; ++i){

            if((CitySoliders[i][0] != NULL) && (CitySoliders[i + 1][1] != NULL)){

                int weapon_amount = 0;

                if(CitySoliders[i][0]->check_weapon_status(weapon_amount)){

                    for(int j = 0; j < weapon_amount; ++j){

                        if(CitySoliders[i][0]->get_and_set_weapon_category(j) == arrow){

                            CitySoliders[i + 1][1]->nLifeVlaue -= CitySoliders[i][0]->get_and_set_weapon_attackvalue(j);

                            if(CitySoliders[i][0]->is_weapon_broken(j)) CitySoliders[i][0]->get_and_set_weapon_category(j) = -1;

                            if(CitySoliders[i + 1][1]->nLifeVlaue <= 0){

                                printf("%03d:%02d red %s %d shot and killed blue %s %d\n", \

                                hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, \

                                CitySoliders[i + 1][1]->get_the_species().c_str(), CitySoliders[i + 1][1]->nId);


                            }
                            else{

                                printf("%03d:%02d red %s %d shot\n", \

                                hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId);

                            }

                        }

                    }

                }

            }

            if(i == 0) continue;

            if((CitySoliders[i][1] != NULL) && (CitySoliders[i - 1][0] != NULL)){

                int weapon_amount = 0;

                if(CitySoliders[i][1]->check_weapon_status(weapon_amount)){

                    for(int j = 0; j < weapon_amount; ++j){

                        if(CitySoliders[i][1]->get_and_set_weapon_category(j) == arrow){

                            CitySoliders[i - 1][0]->nLifeVlaue -= CitySoliders[i][1]->get_and_set_weapon_attackvalue(j);

                            if(CitySoliders[i][1]->is_weapon_broken(j)) CitySoliders[i][1]->get_and_set_weapon_category(j) = -1;

                            if(CitySoliders[i - 1][0]->nLifeVlaue <= 0){ 

                                printf("%03d:%02d blue %s %d shot and killed red %s %d\n", \

                                hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, \

                                CitySoliders[i - 1][0]->get_the_species().c_str(), CitySoliders[i - 1][0]->nId);


                            }
                            else{

                                printf("%03d:%02d blue %s %d shot\n", \

                                hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId);

                            }

                        }

                    }

                }

            }

        }

    }

    void cities_bomb_time(int hour, int minute, Headquarter *red, Headquarter *blue){

        for(int i = 0; i < 20; ++i){

            if(((CitySoliders[i][0] != NULL) && (CitySoliders[i][1] != NULL)) && ((CitySoliders[i][0]->nLifeVlaue > 0) && (CitySoliders[i][1]->nLifeVlaue > 0))){

                int weapon_amount1 = 0;

                int weapon_amount2 = 0;

                int bomb_id_of_blue = -1;

                int bomb_id_of_red = -1;

                int sword_id_of_blue = -1;

                int sword_id_of_red = -1;

                if(CitySoliders[i][0]->check_weapon_status(weapon_amount1)){

                    for(int j = 0; j < weapon_amount1; ++j){

                        if(CitySoliders[i][0]->get_and_set_weapon_category(j) == bomb) bomb_id_of_red = j;

                        if(CitySoliders[i][0]->get_and_set_weapon_category(j) == sword) sword_id_of_red = j;                        

                    }

                }

                if(CitySoliders[i][1]->check_weapon_status(weapon_amount2)){

                    for(int j = 0; j < weapon_amount2; ++j){

                        if(CitySoliders[i][1]->get_and_set_weapon_category(j) == bomb) bomb_id_of_blue = j;

                        if(CitySoliders[i][1]->get_and_set_weapon_category(j) == sword) sword_id_of_blue = j;                        

                    }

                }

                if(bomb_id_of_red >= 0){

                    bool is_die_together = false;

                    int blue_attack_power = -1;

                    int red_sword_attackvalue = 0;

                    if(sword_id_of_red >= 0) red_sword_attackvalue = CitySoliders[i][0]->get_and_set_weapon_attackvalue(sword_id_of_red);

                    if((nCitiesFlag[i] == red_flag) || (nCitiesFlag[i] == no_flag && ((i+1) % 2) != 0)){

                        if(((CitySoliders[i][0]->nAttackPower + red_sword_attackvalue) < CitySoliders[i][1]->nLifeVlaue)){

                            if(CitySoliders[i][1]->get_the_species() == "ninja" )

                                blue_attack_power = 0;

                            else

                                blue_attack_power = int(CitySoliders[i][1]->nAttackPower * 0.5);

                        }
                        else{ blue_attack_power = 0;}   

                    }
                    else{

                        blue_attack_power = CitySoliders[i][1]->nAttackPower;
                        
                    }

                    //printf("blue_attack_power:%d\n", blue_attack_power);

                    //printf("sword_id_of_blue:%d\n", sword_id_of_blue);

                    //printf("CitySoliders[i][0]->nLifeVlaue:%d\n", CitySoliders[i][0]->nLifeVlaue);

                    if((sword_id_of_blue < 0) && (blue_attack_power >= CitySoliders[i][0]->nLifeVlaue) && (blue_attack_power > 0)) is_die_together = true;

                    if((sword_id_of_blue >= 0) && ((blue_attack_power + CitySoliders[i][1]->get_and_set_weapon_attackvalue(sword_id_of_blue)) \

                        >= CitySoliders[i][0]->nLifeVlaue) && (blue_attack_power > 0)) is_die_together = true;

                    if(is_die_together){

                        printf("%03d:%02d red %s %d used a bomb and killed blue %s %d\n", \

                        hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, \

                        CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId);

                        CitySoliders[i][0]->nLifeVlaue = 0;

                        CitySoliders[i][1]->nLifeVlaue = 0;

                        red->killed(CitySoliders[i][0]);

                        CitySoliders[i][0] = NULL;

                        blue->killed(CitySoliders[i][1]);

                        CitySoliders[i][1] = NULL;

                        continue;

                    }

                }

                if(bomb_id_of_blue >= 0){

                    bool is_die_together = false;

                    int red_attack_power = -1;

                    int blue_sword_attackvalue = 0;

                    if(sword_id_of_blue >= 0) blue_sword_attackvalue = CitySoliders[i][1]->get_and_set_weapon_attackvalue(sword_id_of_blue);

                    if((nCitiesFlag[i] == blue_flag) || (nCitiesFlag[i] == no_flag && ((i+1) % 2) == 0)){

                        if((CitySoliders[i][1]->nAttackPower + blue_sword_attackvalue) < CitySoliders[i][0]->nLifeVlaue){

                            if(CitySoliders[i][0]->get_the_species() == "ninja" )

                                red_attack_power = 0;

                            else

                                red_attack_power = int(CitySoliders[i][0]->nAttackPower * 0.5);

                        }
                        else{ red_attack_power = 0; }

                    }
                    else{

                        red_attack_power = CitySoliders[i][0]->nAttackPower;

                    }

                    if((sword_id_of_red < 0) && (red_attack_power >= CitySoliders[i][1]->nLifeVlaue) && (red_attack_power > 0)) is_die_together = true;

                    if((sword_id_of_red >= 0) && ((red_attack_power + CitySoliders[i][0]->get_and_set_weapon_attackvalue(sword_id_of_red)) 

                     >= CitySoliders[i][1]->nLifeVlaue) && (red_attack_power > 0)) is_die_together = true;

                    if(is_die_together){

                        printf("%03d:%02d blue %s %d used a bomb and killed red %s %d\n", \

                        hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, \

                        CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId);

                        CitySoliders[i][0]->nLifeVlaue = 0;

                        CitySoliders[i][1]->nLifeVlaue = 0;

                        red->killed(CitySoliders[i][0]);

                        CitySoliders[i][0] = NULL;

                        blue->killed(CitySoliders[i][1]);

                        CitySoliders[i][1] = NULL;

                        continue;

                    }

                }

            }
        }

    }

    void cities_fight_time(int hour, int minute, Headquarter *red, Headquarter *blue, int K){

        for(int i = 0; i < 20; ++i){

            if((CitySoliders[i][0] != NULL) && (CitySoliders[i][1] != NULL)){

                int red_lion_nlifevalue = 0;

                int blue_lion_nlifevalue = 0;

                if(CitySoliders[i][0]->get_the_species() == "lion") red_lion_nlifevalue = CitySoliders[i][0]->nLifeVlaue < 0 ? 0 : CitySoliders[i][0]->nLifeVlaue;

                if(CitySoliders[i][1]->get_the_species() == "lion") blue_lion_nlifevalue = CitySoliders[i][1]->nLifeVlaue < 0 ? 0 : CitySoliders[i][1]->nLifeVlaue;

                if((nCitiesFlag[i] == red_flag) || (nCitiesFlag[i] == no_flag && (i % 2) == 0)){

					if(CitySoliders[i][0]->nLifeVlaue > 0 && CitySoliders[i][1]->nLifeVlaue > 0){
						
						printf("%03d:%02d red %s %d attacked blue %s %d in city %d with %d elements and force %d\n", \

						hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, \

						CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, (i + 1), \

						CitySoliders[i][0]->nLifeVlaue, CitySoliders[i][0]->nAttackPower);

						CitySoliders[i][0]->active_attack(CitySoliders[i][1]);

						if(CitySoliders[i][0]->is_killed(CitySoliders[i][1])){

							printf("%03d:%02d blue %s %d was killed in city %d\n", \

							hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, (i + 1));

							CitySoliders[i][0]->reward(CitySoliders[i][1]);

							CitySoliders[i][0]->get_lion_lifevalue(CitySoliders[i][1], blue_lion_nlifevalue);

                            blue->killed(CitySoliders[i][1]);

                            CitySoliders[i][1] = NULL;

						}
						else{

							CitySoliders[i][0]->punished(K);

							if(CitySoliders[i][1]->get_the_species() != "ninja"){

								CitySoliders[i][1]->fight_back(CitySoliders[i][0]);

								printf("%03d:%02d blue %s %d fought back against red %s %d in city %d\n", \

								hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, \

								CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, (i + 1));

								if(CitySoliders[i][1]->is_killed(CitySoliders[i][0])){

									printf("%03d:%02d red %s %d was killed in city %d\n", \

									hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, (i + 1));

									CitySoliders[i][1]->reward(CitySoliders[i][0]);

									CitySoliders[i][1]->get_lion_lifevalue(CitySoliders[i][0], red_lion_nlifevalue);

                                    red->killed(CitySoliders[i][0]);

                                    CitySoliders[i][0] = NULL;

								}
								else CitySoliders[i][1]->punished(K);

							}

						}
						
					}
					else{
						
                        if((CitySoliders[i][0]->nLifeVlaue <= 0) && (CitySoliders[i][1]->nLifeVlaue > 0)){

                            CitySoliders[i][1]->reward(CitySoliders[i][0]);

                            CitySoliders[i][1]->get_lion_lifevalue(CitySoliders[i][0], red_lion_nlifevalue);

                            red->killed(CitySoliders[i][0]);

                            CitySoliders[i][0] = NULL;

                        }

                        else if((CitySoliders[i][1]->nLifeVlaue <= 0) && (CitySoliders[i][0]->nLifeVlaue > 0)){

                            CitySoliders[i][0]->reward(CitySoliders[i][1]);

                            CitySoliders[i][0]->get_lion_lifevalue(CitySoliders[i][1], blue_lion_nlifevalue);

                            blue->killed(CitySoliders[i][1]);

                            CitySoliders[i][1] = NULL;

                        }

                        else if((CitySoliders[i][0]->nLifeVlaue <= 0) && (CitySoliders[i][1]->nLifeVlaue <= 0)){

                            red->killed(CitySoliders[i][0]);

                            CitySoliders[i][0] = NULL;

                            blue->killed(CitySoliders[i][1]);

                            CitySoliders[i][1] = NULL;

                        }

					}

                    if((CitySoliders[i][0] != NULL) && (CitySoliders[i][0]->is_celebrated() == true)){

                        printf("%03d:%02d red %s %d yelled in city %d\n", \

                        hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, (i + 1));

                    }

                }
                else{
					
					if(CitySoliders[i][0]->nLifeVlaue > 0 && CitySoliders[i][1]->nLifeVlaue > 0){
					
						printf("%03d:%02d blue %s %d attacked red %s %d in city %d with %d elements and force %d\n", \

						hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, \

						CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, (i + 1), \

						CitySoliders[i][1]->nLifeVlaue, CitySoliders[i][1]->nAttackPower);

						CitySoliders[i][1]->active_attack(CitySoliders[i][0]);

                        //printf("CitySoliders[i][0]:%d\n", CitySoliders[i][0]->nLifeVlaue);

						if(CitySoliders[i][1]->is_killed(CitySoliders[i][0])){

							printf("%03d:%02d red %s %d was killed in city %d\n", \

							hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, (i + 1));

							CitySoliders[i][1]->reward(CitySoliders[i][0]);

							CitySoliders[i][1]->get_lion_lifevalue(CitySoliders[i][0], red_lion_nlifevalue);

                            red->killed(CitySoliders[i][0]);

                            CitySoliders[i][0] = NULL;


						}
						else{

							CitySoliders[i][1]->punished(K);

							if(CitySoliders[i][0]->get_the_species() != "ninja"){

								CitySoliders[i][0]->fight_back(CitySoliders[i][1]);

								printf("%03d:%02d red %s %d fought back against blue %s %d in city %d\n", \

								hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, \

								CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, (i + 1));

								if(CitySoliders[i][0]->is_killed(CitySoliders[i][1])){

									printf("%03d:%02d blue %s %d was killed in city %d\n", \

									hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, (i + 1));

									CitySoliders[i][0]->reward(CitySoliders[i][1]);

									CitySoliders[i][0]->get_lion_lifevalue(CitySoliders[i][1], blue_lion_nlifevalue);

                                    blue->killed(CitySoliders[i][1]);

                                    CitySoliders[i][1] = NULL;

								}
								else CitySoliders[i][0]->punished(K);

							}

						}
						
					}
					else{

                        if( (CitySoliders[i][0]->nLifeVlaue <= 0) && (CitySoliders[i][1]->nLifeVlaue > 0) ){

                            CitySoliders[i][1]->reward(CitySoliders[i][0]);

                            CitySoliders[i][1]->get_lion_lifevalue(CitySoliders[i][0], red_lion_nlifevalue);

                            red->killed(CitySoliders[i][0]);

                            CitySoliders[i][0] = NULL;

                        }

                        else if( (CitySoliders[i][1]->nLifeVlaue <= 0) && (CitySoliders[i][0]->nLifeVlaue > 0) ){

                            CitySoliders[i][0]->reward(CitySoliders[i][1]);

                            CitySoliders[i][0]->get_lion_lifevalue(CitySoliders[i][1], blue_lion_nlifevalue);

                            blue->killed(CitySoliders[i][1]);

                            CitySoliders[i][1] = NULL;

                        }
                        else if( (CitySoliders[i][0]->nLifeVlaue <= 0) && (CitySoliders[i][1]->nLifeVlaue <= 0) ){

                            red->killed(CitySoliders[i][0]);

                            CitySoliders[i][0] = NULL;

                            blue->killed(CitySoliders[i][1]);

                            CitySoliders[i][1] = NULL;

                        }
						
					}

                    if((CitySoliders[i][1] != NULL) &&(CitySoliders[i][1]->is_celebrated() == true)){

                        printf("%03d:%02d blue %s %d yelled in city %d\n", \

                        hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, (i + 1));

                    }

                }

                if((CitySoliders[i][0] != NULL) && (CitySoliders[i][1] == NULL)){

                    if(red->total_life_value - 8 > 0){

                        red->total_life_value -= 8;

                        CitySoliders[i][0]->common_reward(8);

                    }

                    printf("%03d:%02d red %s %d earned %d elements for his headquarter\n", \

                    hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId, nCitiesOrder[i]);

                    red->total_life_value += nCitiesOrder[i];

                    nCitiesOrder[i] = 0;

                    if(nCountSuccess[i] <= 0) nCountSuccess[i] -= 1;

                    else nCountSuccess[i] = -1;

                } 

                if((CitySoliders[i][0] == NULL) && (CitySoliders[i][1] != NULL)){

                    if(blue->total_life_value - 8 > 0){

                        blue->total_life_value -= 8;

                        CitySoliders[i][1]->common_reward(8);

                    }

                    printf("%03d:%02d blue %s %d earned %d elements for his headquarter\n", \

                    hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId, nCitiesOrder[i]);

                    blue->total_life_value += nCitiesOrder[i];

                    nCitiesOrder[i] = 0;

                    if(nCountSuccess[i] >= 0) nCountSuccess[i] += 1;

                    else nCountSuccess[i] = 1;
                } 

                if((CitySoliders[i][0] != NULL) && (CitySoliders[i][1] != NULL)){

                    nCountSuccess[i] = 0;
                }

                if(nCountSuccess[i] == -2){

                    if(nCitiesFlag[i] != red_flag){

                        nCitiesFlag[i] = red_flag;

                        printf("%03d:%02d red flag raised in city %d\n", hour, minute, (i + 1));


                    }

                } 

                if(nCountSuccess[i] == 2){

                    if(nCitiesFlag[i] != blue_flag){

                        nCitiesFlag[i] = blue_flag;

                        printf("%03d:%02d blue flag raised in city %d\n", hour, minute, (i + 1));

                    }

                }

            }

            if((CitySoliders[i][0] == NULL && CitySoliders[i][1] != NULL) || (CitySoliders[i][0] != NULL && CitySoliders[i][1] == NULL)){

                if(CitySoliders[i][0]){

                    if(CitySoliders[i][0]->nLifeVlaue <= 0){

                        red->killed(CitySoliders[i][0]);

                        CitySoliders[i][0] = NULL;

                    } 

                }
                else{

                    if(CitySoliders[i][1]->nLifeVlaue <= 0){

                        blue->killed(CitySoliders[i][1]);

                        CitySoliders[i][1] = NULL;

                    } 

                }

            }

        }

    }

	void cities_report_weapons_status(int hour, int minute){
		
		for(int i = 0; i < 20; ++i){
			
			if(CitySoliders[i][0]){
				
				printf("%03d:%02d red %s %d ", hour, minute, CitySoliders[i][0]->get_the_species().c_str(), CitySoliders[i][0]->nId);
				
				int amount = 0;
				
				CitySoliders[i][0]->check_weapon_status(amount);
				
				CitySoliders[i][0]->show_weapons_status(amount);
				
			}
			
		}

        for(int i = 0; i < 2; ++i){

            if(HQSolider[1][i]){

                printf("%03d:%02d red %s %d ", hour, minute, HQSolider[1][i]->get_the_species().c_str(), HQSolider[1][i]->nId);

                int amount = 0;
                
                HQSolider[1][i]->check_weapon_status(amount);
                
                HQSolider[1][i]->show_weapons_status(amount);

            }
        }

        for(int i = 0; i < 2; ++i){

            if(HQSolider[0][i]){

                printf("%03d:%02d blue %s %d ", hour, minute, HQSolider[0][i]->get_the_species().c_str(), HQSolider[0][i]->nId);

                int amount = 0;
                
                HQSolider[0][i]->check_weapon_status(amount);
                
                HQSolider[0][i]->show_weapons_status(amount);
                
            }
        }
		
		for(int i = 0; i < 20; ++i){
			
			if(CitySoliders[i][1]){
				
				printf("%03d:%02d blue %s %d ", hour, minute, CitySoliders[i][1]->get_the_species().c_str(), CitySoliders[i][1]->nId);
				
				int amount = 0;
				
				CitySoliders[i][1]->check_weapon_status(amount);

				CitySoliders[i][1]->show_weapons_status(amount);
				
			}
			
		}

	}
	
};

int main(){
#if 0
    int input[82][5] = {0};

    std::ifstream in_file("in.txt");

    if(!in_file.is_open()) printf("can not open this file\n");
    
    for(int i = 0; i < 82; ++i){

        for(int j = 0; j < 5; ++j){

            in_file >> input[i][j];

        }

    }

    in_file.close();
#endif

    int case_id = 0;

    int M = 0, N = 0, R = 0, K = 0, T = 0;

    int life_points[5] = {0};

    int attackpower[5] = {0};

#if 0
    case_id = input[0][0];
#else

    std::cin >> case_id;

#endif

    for(int i = 0; i < case_id ; ++i){
#if 0
        M = input[i * 3 + 1][0], N = input[i * 3 + 1][1], R = input[i * 3 + 1][2], K = input[i * 3 + 1][3], T = input[i * 3 + 1][4];

        life_points[idragon] = input[i * 3 + 2][0], life_points[ininja] = input[i * 3 + 2][1], life_points[iiceman] = input[i * 3 + 2][2], life_points[ilion] = input[i * 3 + 2][3], life_points[iwolf] = input[i * 3 + 2][4];

        attackpower[idragon] = input[i * 3 + 3][0], attackpower[ininja] = input[i * 3 + 3][1], attackpower[iiceman] = input[i * 3 + 3][2], attackpower[ilion] = input[i * 3 + 3][3], attackpower[iwolf] = input[i * 3 + 3][4];
#else
        std::cin >> M >> N >> R >> K >> T;

        std::cin >> life_points[idragon] >> life_points[ininja] >> life_points[iiceman] >> life_points[ilion] >> life_points[iwolf];
        
        std::cin >> attackpower[idragon] >> attackpower[ininja] >> attackpower[iiceman] >> attackpower[ilion] >> attackpower[iwolf];
#endif
        Headquarter *red = new RedHeadquarter(M, N, life_points, attackpower); 

        Headquarter *blue = new BlueHeadquarter(M, N, life_points, attackpower);

        Cities *cities = new Cities();

        std::cout << "Case " << (i + 1) << ":" << std::endl;

        bool is_red_ended = false;

        bool is_blue_ended = false;

        for(int j = 0; j <= T; ++j){

            if((is_red_ended == true) || (is_blue_ended == true)) break;

            int current_hour = j / 60;

            int current_minute = j % 60;

            switch(current_minute){

                case born:

                    if(red->is_borned(current_hour)) red->born_a_solider(current_hour, current_minute, R);

                    if(blue->is_borned(current_hour)) blue->born_a_solider(current_hour, current_minute, R);

                    break;

                case lion_ran_away:

                    red->check_lion_ran_away(current_hour, current_minute);

                    blue->check_lion_ran_away(current_hour, current_minute);

                    break;

                case marched_to:

					red->soliders_marched_to();
					
					blue->soliders_marched_to();
				
                    cities->check_cities_status(red, blue, N);

					cities->cities_marched_to(current_hour, current_minute, red, blue, is_red_ended, is_blue_ended);

                    break;

                case born_citylife:

                    for(int k = 0; k < N; ++k) cities->nCitiesOrder[k] += 10;

                    break;

                case take_away_citylife:

                    cities->lifevalue_take_away_from_soliders(current_hour, current_minute, red, blue);

                    break;

                case shoot_time:

                    cities->cities_shoot_time(current_hour, current_minute);

                    break;

                case bomb_time:

                    cities->cities_bomb_time(current_hour, current_minute, red, blue);

                    break;

                case fight_time:

                    cities->cities_fight_time(current_hour, current_minute, red, blue, K);

                    break;

                case report_headquarter_lifetime:

                    red->report_headquarter_lifetime(current_hour, current_minute);

                    blue->report_headquarter_lifetime(current_hour, current_minute);

                    break;

                case report_weapons_time:
				
					cities->cities_report_weapons_status(current_hour, current_minute);

                    break;

            }

        }
        
        delete red;

        delete blue;

        delete cities;

    }

    return 0;
}