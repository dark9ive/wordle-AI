#include"AI.h"


AI_node::AI_node(std::vector<int> list, AI* ds){
    indexlist = list;
    DS = ds;
    StrLen = DS->getLen();
    correct_index = DS->corrIDX();
}

AI::AI(){
    read_to_vector(q_pool, QFN);
    //
    //  finish processing question pool.
    //
    pool = q_pool;
    read_to_vector(pool, TFN);
    //
    //  finish processing total pool.
    //
    StrLen = pool[0].size();
    //  
    //  count length of each question.
    //
    correct_index = 0;
    for(int a = 0; a < StrLen; a++){
        correct_index <<= 2;
        correct_index += 2;
    }
    //
    //  finish calculating correct bucket index.
    //
    initBucket();
    return;
}

std::string AI::operator[](int IDX){
    return pool[IDX];
}

int AI::getLen(){
    return StrLen;
}

int AI::corrIDX(){
    return correct_index;
}

void AI::initBucket(){
    int qsize = q_pool.size();
    int psize = pool.size();
    bucket_arr.resize(psize);
    for(int a = 0; a < psize; a++){
        std::vector<int> buf(qsize);
        for(int b = 0; b < qsize; b++){
            int val = 0;
            int used[26] = {0};
            for(int c = 0; c < StrLen; c++){
                used[pool[b][c]-'a'] += 1;
            }
            for(int c = 0; c < StrLen; c++){
                if(pool[a][c] == pool[b][c]){
                    val += (2<<(2*c));
                    used[pool[b][c]-'a'] -= 1;
                }
            }
            for(int c = 0; c < StrLen; c++){
                if(pool[a][c] != pool[b][c] && used[pool[a][c]-'a'] != 0){
                    used[pool[a][c]-'a'] -= 1;
                    val += (1<<(2*c));
                }
            }
            buf[b] = val;
        }
        bucket_arr[a] = buf;
    }
    return;
}
int AI::getBucket(int filter, int ans){
    return bucket_arr[filter][ans];
}
