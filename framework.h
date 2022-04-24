#ifndef frame_

#define frame_
#include<unordered_set>
#include<vector>

#define QFN "./testdata/Question.txt"
#define TFN "./testdata/Total.txt"

class game;

#include"AI.h"

class game{
    private:
        std::vector<std::string> pool;
        std::vector<std::string> q_pool;
        std::unordered_set<std::string> ht;
        std::unordered_set<std::string> q_ht;
        std::string ans;
        int tries;
        int StrLen;
        int correct_index;
    public:
        game();
        void print_status();
        void print_result(int);
        void random_ans();
        void start();
        int test_ans(std::string);
        int guess(std::string);
        void set_ans(int index);
        int check_exist(std::string);
        int q_check_exist(std::string);
};

void read_to_vector(std::vector<std::string>&, std::string);
void make_ht(std::unordered_set<std::string>&, std::vector<std::string>);

#endif
