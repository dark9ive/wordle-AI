#ifndef AI_

#define AI_

class AI;

#include"framework.h"

class AI_node{
    private:
        std::vector<int> indexlist;
        int StrLen;
        int correct_index;
        AI* DS;     //  Data Source
    public:
        AI_node(std::vector<int> list, AI* ds);
        int ab();
        int get_bucket(int inputIDX, int ansIDX);
};
class AI{
    private:
        std::vector<std::string> pool;
        std::vector<std::string> q_pool;
        int StrLen;
        int correct_index;
    public:
        AI();
        std::string operator[](int IDX);
        friend class AI_node;
};

#endif
