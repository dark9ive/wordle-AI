#include<iostream>
#include<vector>
#include<ctime>

#include"framework.h"
#include"AI.h"

int human_play(){
//int main(){
    game Game;
    std::string str;
    while(std::cin >> str){
        if(Game.check_exist(str)){
            Game.guess(str);
        }
        else{
            std::cout << "Not in Dictionary!" << std::endl;
        }
    }
    return 0;
}

int ai_solve(){
//int main(){
    while(1){
        std::cout << "Initialize new AI..." << std::endl;
        AI ai;
        clock_t start_clock = clock();
        int solu = ai.solution(1, 1);
        std::cout << "Best start: " << ai[solu] << std::endl;
        std::cout << "Time used: " << ((double)(clock()-start_clock)) / CLOCKS_PER_SEC << std::endl;
        std::string str;
        while(std::cin >> str){
            if(ai.response(str)){
                break;
            }
            start_clock = clock();
            solu = ai.solution(1, 1);
            std::cout << "Best start: " << ai[solu] << std::endl;
            std::cout << "Time used: " << ((double)(clock()-start_clock)) / CLOCKS_PER_SEC << std::endl;
        }
    }
    return 0;
}

//int test(){
int main(){
    game Game;
    int total_guess = 0;
    std::vector<int> dist(11, 0);
    int input; // set input
    std::cin >> input ; // input the number of questions
    for(int a = 0; a < input; a++){
        std::string q; 
        std::cin >> q; 
        Game.start(q);
        //Game.set_ans(a);
        AI ai;
        int count = 0;
        while(1){
            int solu = ai.solution(1, 1);
            std::cout << "Guess: " << ai[solu] << " " << std::endl; // show it
            int res = Game.test_ans(ai[solu]);
            //int res = Game.guess(ai[solu]);
            total_guess++;
            count++;
            std::string resstr;
            for(int b = 0; b < ai.getLen(); b++){
                switch(res&3){
                    case 0:
                        resstr += "0";
                        break;
                    case 1:
                        resstr += "2";
                        break;
                    case 2:
                        resstr += "1";
                        break;
                }
                res >>= 2;
            }
            if(ai.response(resstr)){
                dist[count]++;
                break;
            }
        }
        if(a%100 == 0 && a != 0){
            std::cout << "AVG Guess @ " << a << ": " << ((double)total_guess)/a << std::endl;
        }
    }
    std::cout << "AVG Guess @ 2315: " << ((double)total_guess)/input << std::endl; // change total to input
    for(int a = 0; a < 6; a++){ // change to 6 time
        std::cout << "Words using " << a << " times of guessing: " << dist[a] << std::endl;
    }
    return 0;
}

