#include<algorithm>
#include<iostream>
#include<math.h>
#include<unistd.h>
#include"AI.h"


AI_node::AI_node(std::vector<int> list, AI* ds){
    indexlist = list;
    DS = ds;
}

std::pair<int, int> AI_node::full_exp(int depth){
    int psize = DS->psize();
    int qsize = indexlist.size();
    int min_IDX = -1;
    int min_val = 0x7FFFFFFF;
    if(qsize == 0){
        return std::pair<int, int>(min_IDX, -1);
    }
    for(int a = 0; a < psize; a++){
        if(depth == 2){
            std::cout << a << std::endl;
        }
        std::vector<int> bucket[(DS->maxBKT())+1];
        for(int b = 0; b < qsize; b++){
            int bucketIDX = DS->getBucket(a, indexlist[b]);
            bucket[bucketIDX].push_back(indexlist[b]);
        }
        int recuans[(DS->maxBKT())+1] = {0};
        if(depth > 1){
            for(int b = 0; b < ((DS->maxBKT())+1); b++){
                AI_node node(bucket[b], DS);
                recuans[b] = node.full(depth-1).second;
            }
        }
        else{
            for(int b = 0; b < ((DS->maxBKT())+1); b++){
                recuans[b] = bucket[b].size();
            }
        }
        int exp_val = 0;
        for(int b = 0; b < (DS->maxBKT())+1; b++){
            if(recuans[b] == 0){
                continue;
            }
            exp_val += recuans[b]*log2(recuans[b]);
        }
        if (exp_val < min_val){
            min_IDX = a;
            min_val = exp_val;
            /*
            if(depth == 2){
                std::cout << "found better: " << (*DS)[a] << ", val = " << exp_val << std::endl;
            }
            */
        }
        else if(exp_val == min_val && recuans[DS->corrBKT()] == 1){
            min_IDX = a;
            min_val = exp_val;
            /*
            if(depth == 2){
                std::cout << "found better: " << (*DS)[a] << ", val = " << exp_val << std::endl;
            }
            */
        }
    }
    return std::pair<int, int>(min_IDX, min_val);
}

std::pair<int, int> AI_node::full(int depth){
    int psize = DS->psize();
    int qsize = indexlist.size();
    int min_IDX = -1;
    int min_val = 0x7FFFFFFF;
    if(qsize == 0){
        return std::pair<int, int>(min_IDX, -1);
    }
    for(int a = 0; a < psize; a++){
        if(depth == 2){
            std::cout << a << std::endl;
        }
        std::vector<int> bucket[(DS->maxBKT())+1];
        for(int b = 0; b < qsize; b++){
            int bucketIDX = DS->getBucket(a, indexlist[b]);
            bucket[bucketIDX].push_back(indexlist[b]);
        }
        int recuans[(DS->maxIDX())+1] = {0};
        if(depth > 1){
            for(int b = 0; b < ((DS->maxBKT())+1); b++){
                AI_node node(bucket[b], DS);
                recuans[b] = node.full(depth-1).second;
            }
        }
        else{
            for(int b = 0; b < ((DS->maxBKT())+1); b++){
                recuans[b] = bucket[b].size();
            }
        }
        int max_val = *std::max_element(recuans, recuans+((DS->maxBKT())+1));
        if (max_val < min_val){
            min_IDX = a;
            min_val = max_val;
            if(depth == 1){
                std::cout << "found better: " << (*DS)[a] << ", val = " << max_val << std::endl;
            }
        }
        else if(max_val == min_val && recuans[DS->corrBKT()] == 1){
            min_IDX = a;
            min_val = max_val;
            if(depth == 1){
                std::cout << "found better: " << (*DS)[a] << ", val = " << max_val << std::endl;
            }
        }
    }
    return std::pair<int, int>(min_IDX, min_val);
}

std::pair<int, int> AI_node::ab(int depth, int max_val_glob){
    int psize = DS->psize();
    int qsize = indexlist.size();
    int min_IDX = -1;
    int min_val = 0x7FFFFFFF;
    std::cout << psize << " " << qsize << std::endl;
    if(qsize == 0){
        return std::pair<int, int>(min_IDX, -1);
    }
    for(int a = 0; a < psize; a++){
        /*
        if(depth == 2 && a%100 == 0){
            std::cout << a << std::endl;
        }
        */
        std::vector<int> bucket[(DS->maxBKT())+1];
        for(int b = 0; b < qsize; b++){
            int bucketIDX = DS->getBucket(a, indexlist[b]);
            bucket[bucketIDX].push_back(indexlist[b]);
        }

        int recuans[(DS->maxBKT())+1] = {0};
        int max_val = 0x80000000;

        for(int b = 0; b < ((DS->maxBKT())+1); b++){
            if(depth > 1){
                AI_node node(bucket[b], DS);
                recuans[b] = node.ab(depth-1, max_val).second;
            }
            else{
                recuans[b] = bucket[b].size();
            }
            if(recuans[b] > max_val){
                max_val = recuans[b];
            }
            if(recuans[b] > min_val){
                break;
            }
        }

        if (max_val < min_val){
            min_IDX = a;
            min_val = max_val;
            /*
            if(depth == 2){
                std::cout << "found better: " << (*DS)[a] << ", val = " << max_val << std::endl;
            }
            */
        }
        else if(max_val == min_val && recuans[DS->corrBKT()] == 1){
            min_IDX = a;
            min_val = max_val;
            /*
            if(depth == 2){
                std::cout << "found better: " << (*DS)[a] << ", val = " << max_val << std::endl;
            }
            */
        }
        if(min_val < max_val_glob){
            return std::pair<int, int>(-1, -1);
        }
    }
    return std::pair<int, int>(min_IDX, min_val);
}

int AI_node::operator[](int IDX){
    return indexlist[IDX];
}

int AI_node::size(){
    return indexlist.size();
}

AI::AI(std::string QFN){
    read_to_vector(q_pool, QFN);
    pool = q_pool;
    StrLen = pool[0].size();

    correct_index = 0;
    max_index = 0;
    correct_bucket = 0;
    max_bucket = 0;
    for(int a = 0; a < StrLen; a++){
        correct_index <<= 3;
        correct_index += 1;
        max_index <<= 3;
        max_index += 4;
        correct_bucket <<= 2;
        correct_bucket += 1;
        max_bucket <<= 2;
        max_bucket += 2;
    }

    initTable();
    caps.resize(StrLen, 0);

    std::vector<int> buf;
    for(int a = 0; a < qsize(); a++){
        buf.push_back(a);
    }
    node = new AI_node(buf, this);
    return;
}

std::string AI::operator[](int IDX){
    return pool[IDX];
}

int AI::psize(){
    return pool.size();
}

int AI::qsize(){
    return q_pool.size();
}

int AI::getLen(){
    return StrLen;
}

int AI::corrIDX(){
    return correct_index;
}

int AI::maxIDX(){
    return max_index;
}

int AI::corrBKT(){
    return correct_bucket;
}

int AI::maxBKT(){
    return max_bucket;
}

int AI::getBucket(int filter, int ans){
    return bucket_arr[filter][ans];
}

void AI::initTable(){
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
                    val += (1<<(2*c));
                    used[pool[b][c]-'a'] -= 1;
                }
            }
            for(int c = 0; c < StrLen; c++){
                if(pool[a][c] != pool[b][c] && used[pool[a][c]-'a'] != 0){
                    used[pool[a][c]-'a'] -= 1;
                    val += (2<<(2*c));
                }
            }
            buf[b] = val;
        }
        bucket_arr[a] = buf;
    }
    return;
}

std::string AI::solution(int depth, int mode){
    int returnval = -1;
    switch(mode){
        case 0:
            returnval = node->ab(depth, 0x80000000).first;
            break;
        case 1:
            returnval = node->full_exp(depth).first;
            break;
        default:
            returnval = node->full(depth).first;
            break;
    }
    Mask = returnval;
    std::string Ans = pool[returnval];
    for(int a = 0; a < StrLen; a++){
        if(caps[a]){
            Ans[a] = Ans[a] - 'a' + 'A';
        }
    }
    return Ans;
}

bool AI::response(std::string str){
    int bucket_IDX = 0;
    int IDX = 0;
    for(int a = 0; a < StrLen; a++){
        IDX += ((str[a]-'0') << (3*a));
        switch(str[a]){
            case '0':
                break;
            case '3':
                caps[a] = 1-caps[a];
            case '1':
                bucket_IDX += (1 << (2*a));
                break;
            case '4':
                caps[a] = 1-caps[a];
            case '2':
                bucket_IDX += (2 << (2*a));
                break;
            default:
                std::cerr << "Error!" << std::endl;
                break;
        }
    }
    //std::cout << bucket_IDX << " " << IDX << std::endl;
    if(IDX == correct_index){
        return true;
    }
    std::vector<int> newlist;
    for(int a = 0; a < node->size(); a++){
        if(getBucket(Mask, (*node)[a]) == bucket_IDX){
            newlist.push_back((*node)[a]);
            //std::cout << pool[newlist.back()] << std::endl;
        }
    }
    delete node;
    node = new AI_node(newlist, this);
    Mask = -1;
    return false;
}
