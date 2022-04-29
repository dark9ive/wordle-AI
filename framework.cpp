#include<iostream>
#include<fstream>
#include"framework.h"
#include <ctime>


#define MAX_TRIES 6 // change to 6

void read_to_vector(std::vector<std::string>& pool, std::string filename){
    std::ifstream infile(filename);
    std::string bufline;
    while(getline(infile, bufline)){
        pool.push_back(bufline);
    }
    return;
}

void make_ht(std::unordered_set<std::string>& ht, std::vector<std::string> pool){
    for(int a = 0; a < pool.size(); a++){
        ht.insert(pool[a]);
    }
    return;
}

game::game(){
    read_to_vector(q_pool, QFN);
    pool = q_pool;              //  copy question dict to total pool.
    read_to_vector(pool, TFN);
    make_ht(ht, pool);
    make_ht(q_ht, q_pool);
    StrLen = pool[0].size();
    correct_index = 0;
    for(int a = 0; a < StrLen; a++){
        correct_index <<= 2;
        correct_index += 2;
    }
    srand(clock());
    //start(); // not sure
}

void game::print_status(){
    std::cout << "Total pool size: " << pool.size() << std::endl;
    std::cout << "Question pool size: " << q_pool.size() << std::endl;
    std::cout << "Current ans: " << ans << std::endl;
    /*
    for(int a = 0; a < 10; a++){
        std::cout << pool[a] << std::endl;
    }
    for(int a = 0; a < 10; a++){
        std::cout << q_pool[a] << std::endl;
    }
    */
}

void game::print_result(int val){
    for(int a = 0; a < StrLen; a++){
        switch(val & 3){
            case 0:
                std::cout << "_";
                break;
            case 1:
                std::cout << "+";
                break;
            case 2:
                std::cout << "V";
                break;
            default:
                std::cerr << "Error!" << std::endl;
        }
        val >>= 2;
    }
    std::cout << std::endl;
    return;
}

void game::random_ans(){
    ans = q_pool[rand()%q_pool.size()];
    return;
}

void game::start(std::string q){
    //random_ans();  // set ans by human
    ans = q; // set ans
    tries = MAX_TRIES;
    return;
}

int game::test_ans(std::string input){
    int returnval = 0;
    int used[26] = {0};
    for(int a = 0; a < StrLen; a++){
        used[ans[a]-'a'] += 1;
    }
    for(int a = 0; a < StrLen; a++){
        if(input[a] == ans[a]){
            returnval += (2<<(2*a));
            used[input[a]-'a'] -= 1;
        }
    }
    for(int a = 0; a < StrLen; a++){
        if(input[a] != ans[a] && used[input[a]-'a'] != 0){
            returnval += (1<<(2*a));
            used[input[a]-'a'] -= 1;
        }
    }
    return returnval;
}

int game::guess(std::string input){
    tries--;
    int returnval = test_ans(input);
    print_result(returnval);
    if(returnval == correct_index){
        std::cout << "Congratulations, you've got the correct answer!" << std::endl;
        //start(); // no automatics start
    }
    if(returnval != 0 && tries == 0){
        std::cout << "Game Over!\nThe answer is: " << ans << std::endl;
        //start(); // no automatics start
    }
    return returnval;
}

void game::set_ans(int IDX){
    ans = q_pool[IDX];
}

int game::check_exist(std::string input){
    return ht.count(input);
}

int game::q_check_exist(std::string input){
    return q_ht.count(input);
}

