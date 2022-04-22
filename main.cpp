#include<iostream>
#include<vector>
#include<ctime>

#include"framework.h"
#include"AI.h"

int main(){
    AI ai;
    std::vector<int> buf;
    for(int a = 0; a < ai.qsize(); a++){
        buf.push_back(a);
    }
    AI_node node(buf, &ai);
    clock_t start_clock = clock();
    int solu = node.solution(1, 1);
    std::cout << "Best start: " << ai[solu] << std::endl;
    std::cout << "Time used: " << ((double)(clock()-start_clock)) / CLOCKS_PER_SEC << std::endl;
    start_clock = clock();
    solu = node.solution(1, 0);
    std::cout << "Best start: " << ai[solu] << std::endl;
    std::cout << "Time used: " << ((double)(clock()-start_clock)) / CLOCKS_PER_SEC << std::endl;
    game Game;
    Game.print_status();
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
