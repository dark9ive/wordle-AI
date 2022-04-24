#ifndef AI_

#define AI_

class AI;

#include<utility>
#include<string>
#include"framework.h"

class AI_node{
    private:
        std::vector<int> indexlist;
        AI* DS;     //  Data Source
    public:
        AI_node(std::vector<int> list, AI* ds);
        int operator[](int IDX);
        int size();
        std::pair<int, int> ab(int depth, int max_val_glob);
        std::pair<int, int> full(int depth);
        std::pair<int, int> full_exp(int depth);
};
class AI{
    private:
        std::vector<std::string> pool;
        std::vector<std::string> q_pool;
        std::vector<std::vector<int>> bucket_arr;
        int StrLen;
        int correct_index;
        AI_node* node;
        int Mask;
    public:
        AI();
        std::string operator[](int IDX);
        int psize();
        int qsize();
        int getLen();
        int corrIDX();
        int getBucket(int filterIDX, int ansIDX);
        void initTable();
        bool response(std::string str);
        int solution(int depth, int mode);
};

#endif
