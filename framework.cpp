#include<iostream>
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

game::game(std::string QFN, std::string TFN){
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
}

game::game(std::string QFN){
    read_to_vector(q_pool, QFN);
    pool = q_pool;              //  copy question dict to total pool.
    make_ht(ht, pool);
    make_ht(q_ht, q_pool);
    StrLen = pool[0].size();
    correct_index = 0;
    for(int a = 0; a < StrLen; a++){
        correct_index <<= 2;
        correct_index += 2;
    }
    srand(clock());
}

void game::print_status(){
    std::cout << "Total pool size: " << pool.size() << std::endl;
    std::cout << "Question pool size: " << q_pool.size() << std::endl;
    std::cout << "Current ans: " << ans << std::endl;
}

std::string game::result(int val){
    std::string returnval;
    for(int a = 0; a < StrLen; a++){
        if( a==0 )
            returnval += "\"";
        else
            returnval += ","; // print some element
        switch(val & 3){
            case 0:
                returnval += "0"; // change '_' to '0'
                break;
            case 1:
                returnval += "2"; // change '+' to '2'
                break;
            case 2:
                returnval += "1"; // change 'V' to '1'
                break;
            default:
                std::cerr << "Error!" << std::endl;
        }
        val >>= 2;
    }
    returnval += "\"\n";
    return returnval;
}

void game::random_ans(){
    ans = q_pool[rand()%q_pool.size()];
    return;
}

void game::start(){
    random_ans();
    tries = MAX_TRIES;
    return;
}

void game::start(std::string q){
    set_ans(q); // set ans
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
    int returnval = test_ans(input);
    std::cout << result(returnval);
    return returnval;
}

void game::set_ans(int IDX){
    ans = q_pool[IDX];
}

void game::set_ans(std::string Ans){
    ans = Ans;
}

int game::check_exist(std::string input){
    return ht.count(input);
}

int game::q_check_exist(std::string input){
    return q_ht.count(input);
}

