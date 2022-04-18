#include"AI.h"

AI::AI(){
    read_to_vector(q_pool, QFN);
    pool = q_pool;
    read_to_vector(pool, TFN);
    StrLen = pool[0].size();
    correct_index = 0;
    for(int a = 0; a < StrLen; a++){
        correct_index <<= 2;
        correct_index += 2;
    }
    return;
}

std::string AI::operator[](int IDX){
    return pool[IDX];
}

AI_node::AI_node(std::vector<int> list, AI* ds){
    indexlist = list;
    DS = ds;
    StrLen = DS->StrLen;
    correct_index = DS->correct_index;
}

int AI_node::get_bucket(int inputIDX, int ansIDX){
    int returnval = 0;
    int used[26] = {0};
    for(int a = 0; a < StrLen; a++){
        used[(*DS)[ansIDX][a]-'a'] += 1;
    }
    for(int a = 0; a < StrLen; a++){
        if((*DS)[inputIDX][a] == (*DS)[ansIDX][a]){
            returnval += (2<<(2*a));
            used[(*DS)[ansIDX][a]-'a'] -= 1;
        }
    }
    for(int a = 0; a < StrLen; a++){
        if(used[(*DS)[inputIDX][a]-'a'] != 0){
            used[(*DS)[inputIDX][a]-'a'] -= 1;
            returnval += (1<<(2*a));
        }
    }
    return returnval;
}
