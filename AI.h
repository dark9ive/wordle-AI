#ifndef AI_

#define AI_

class AI;

#include"framework.h"

class AI_node{
    private:
        std::vector<int> indexlist;
        AI* DS;     //  Data Source
        int ab(int depth);
        int full(int depth);
    public:
        AI_node(std::vector<int> list, AI* ds);
        int solution(int depth, int mode);
};
class AI{
    private:
        std::vector<std::string> pool;
        std::vector<std::string> q_pool;
        std::vector<std::vector<int>> bucket_arr;
        int StrLen;
        int correct_index;
    public:
        AI();
        std::string operator[](int IDX);
        int psize();
        int qsize();
        int getLen();
        int corrIDX();
        int getBucket(int filterIDX, int ansIDX);
        void initBucket();
};

#endif
