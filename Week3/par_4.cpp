#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class CCreature{

public:

    CCreature(int id = 0, int lifevalue = 0, int total = 0):nId(id), nLifeVlaue(lifevalue), nTotoal(total){}

    ~CCreature(){}

    int nId;

    int nLifeVlaue;

    int nTotoal;

};

class Headquarter{

public:

    Headquarter(int lifevalue, int dragon_lifevalue, int ninja_lifevalue, int iceman_lifevalue, int lion_lifevalue, int wolf_lifevalue): total_life_value(lifevalue){

        dragon.nLifeVlaue = dragon_lifevalue;

        ninja.nLifeVlaue = ninja_lifevalue;

        iceman.nLifeVlaue = iceman_lifevalue;

        lion.nLifeVlaue = lion_lifevalue;

        wolf.nLifeVlaue = wolf_lifevalue;

    }

    ~Headquarter(){}

    int total_life_value;

    CCreature dragon;

    CCreature ninja;

    CCreature iceman;

    CCreature lion;

    CCreature wolf;
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

                    case 0:

                        if(red->total_life_value - red->iceman.nLifeVlaue >= 0){

                            red->total_life_value -= red->iceman.nLifeVlaue;

                            red->iceman.nId  = (time + 1);

                            red->iceman.nTotoal ++ ;

                            printf("%03d red iceman %d born with strength %d,%d iceman in red headquarter\n", \

                                    time, red->iceman.nId, red->iceman.nLifeVlaue, red->iceman.nTotoal);

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case 1:

                        if(red->total_life_value - red->lion.nLifeVlaue >= 0){

                            red->total_life_value -= red->lion.nLifeVlaue;

                            red->lion.nId  = (time + 1);

                            red->lion.nTotoal ++ ;

                            printf("%03d red lion %d born with strength %d,%d lion in red headquarter\n", \

                                    time, red->lion.nId, red->lion.nLifeVlaue, red->lion.nTotoal);

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case 2:

                        if(red->total_life_value - red->wolf.nLifeVlaue >= 0){

                            red->total_life_value -= red->wolf.nLifeVlaue;

                            red->wolf.nId  = (time + 1);

                            red->wolf.nTotoal ++ ;

                            printf("%03d red wolf %d born with strength %d,%d wolf in red headquarter\n", \

                                    time, red->wolf.nId, red->wolf.nLifeVlaue, red->wolf.nTotoal);

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case 3:

                        if(red->total_life_value - red->ninja.nLifeVlaue >= 0){

                            red->total_life_value -= red->ninja.nLifeVlaue;

                            red->ninja.nId  = (time + 1);

                            red->ninja.nTotoal ++ ;

                            printf("%03d red ninja %d born with strength %d,%d ninja in red headquarter\n", \

                                    time, red->ninja.nId, red->ninja.nLifeVlaue, red->ninja.nTotoal);

                            red_flag = true;
                        }
                        else red_next_num ++;

                        break;

                    case 4:

                        if(red->total_life_value - red->dragon.nLifeVlaue >= 0){

                            red->total_life_value -= red->dragon.nLifeVlaue;

                            red->dragon.nId  = (time + 1);

                            red->dragon.nTotoal ++ ;

                            printf("%03d red dragon %d born with strength %d,%d dragon in red headquarter\n", \

                                    time, red->dragon.nId, red->dragon.nLifeVlaue, red->dragon.nTotoal);

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

                    case 0:

                        if(blue->total_life_value - blue->lion.nLifeVlaue >= 0){

                            blue->total_life_value -= blue->lion.nLifeVlaue;

                            blue->lion.nId = (time + 1);

                            blue->lion.nTotoal ++ ;

                            printf("%03d blue lion %d born with strength %d,%d lion in blue headquarter\n", \

                                    time, blue->lion.nId, blue->lion.nLifeVlaue, blue->lion.nTotoal);

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case 1:

                        if(blue->total_life_value - blue->dragon.nLifeVlaue >= 0){

                            blue->total_life_value -= blue->dragon.nLifeVlaue;

                            blue->dragon.nId = (time + 1);

                            blue->dragon.nTotoal ++ ;

                            printf("%03d blue dragon %d born with strength %d,%d dragon in blue headquarter\n", \

                                    time, blue->dragon.nId, blue->dragon.nLifeVlaue, blue->dragon.nTotoal);

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case 2:

                        if(blue->total_life_value - blue->ninja.nLifeVlaue >= 0){

                            blue->total_life_value -= blue->ninja.nLifeVlaue;

                            blue->ninja.nId = (time + 1);

                            blue->ninja.nTotoal ++ ;

                            printf("%03d blue ninja %d born with strength %d,%d ninja in blue headquarter\n", \

                                    time, blue->ninja.nId, blue->ninja.nLifeVlaue, blue->ninja.nTotoal);

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case 3:

                        if(blue->total_life_value - blue->iceman.nLifeVlaue >= 0){

                            blue->total_life_value -= blue->iceman.nLifeVlaue;

                            blue->iceman.nId = (time + 1);

                            blue->iceman.nTotoal ++ ;

                            printf("%03d blue iceman %d born with strength %d,%d iceman in blue headquarter\n", \

                                    time, blue->iceman.nId, blue->iceman.nLifeVlaue, blue->iceman.nTotoal);

                            blue_flag = true;
                        }
                        else blue_next_num ++;

                        break;

                    case 4:

                        if(blue->total_life_value - blue->wolf.nLifeVlaue >= 0){

                            blue->total_life_value -= blue->wolf.nLifeVlaue;

                            blue->wolf.nId = (time + 1);

                            blue->wolf.nTotoal ++ ;

                            printf("%03d blue wolf %d born with strength %d,%d wolf in blue headquarter\n", \

                                    time, blue->wolf.nId, blue->wolf.nLifeVlaue, blue->wolf.nTotoal);

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

    system("pause");
    return 0;
}