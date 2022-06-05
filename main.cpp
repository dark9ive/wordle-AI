#include<iostream>
#include<vector>
#include<ctime>

#include<unistd.h>

#include"framework.h"
#include"AI.h"

#define MainMode 0
/*
int human_play(){
    game Game;
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

int ai_solve(){
//int main(){
    while(1){
        std::cout << "Initialize new AI..." << std::endl;
        AI ai;
        clock_t start_clock = clock();
        int solu = ai.solution(1, 1);
        std::cout << "Best start: " << ai[solu] << std::endl;
        std::cout << "Time used: " << ((double)(clock()-start_clock)) / CLOCKS_PER_SEC << std::endl;
        std::string str;
        while(std::cin >> str){
            if(ai.response(str)){
                break;
            }
            start_clock = clock();
            solu = ai.solution(1, 1);
            std::cout << "Best start: " << ai[solu] << std::endl;
            std::cout << "Time used: " << ((double)(clock()-start_clock)) / CLOCKS_PER_SEC << std::endl;
        }
    }
    return 0;
}
*/
void test(std::string QFN){
    game Game(QFN);
    int total_guess = 0;
    std::vector<int> dist(11, 0);
    for(int a = 0; a < 2315; a++){
        Game.set_ans(a);
        //std::cout << "Answer set." << std::endl;
        AI ai(QFN);
        int count = 0;
        //std::cout << "Start Guessing..." << std::endl;
        while(1){
            std::string AIGuess = ai.solution(1, 1);
            //std::cout << count+1 << ": " << AIGuess << std::endl;
            int res = Game.test_ans(AIGuess);
            total_guess++;
            count++;
            std::string resstr;
            //std::cout << res << " ";
            for(int b = 0; b < ai.getLen(); b++){
                resstr += (char)((res&7) + '0');
                res >>= 3;
            }
            //std::cout << resstr << std::endl;
            if(ai.response(resstr)){
                dist[count]++;
                break;
            }
        }
        if(a%100 == 0 && a != 0){
            std::cout << "AVG Guess @ " << a << ": " << ((double)total_guess)/a << std::endl;
            for(int b = 1; b <= 10; b++){
                std::cout << "Words using " << b << " times of guessing: " << dist[b] << std::endl;
            }
        }
    }
    std::cout << "AVG Guess @ " << 2315 << ": " << ((double)total_guess)/2315 << std::endl;
    for(int a = 1; a <= 10; a++){
        std::cout << "Words using " << a << " times of guessing: " << dist[a] << std::endl;
    }
    return;
}

void HWMain(std::string QFN, std::string IFname, std::string OFname){
    std::vector<std::string> Qs;
    std::ifstream Infile(IFname);
    std::string bufline;
    while(getline(Infile, bufline)){
        Qs.push_back(bufline);
    }
    Infile.close();

    std::ofstream Outfile(OFname);

    for(int a = 0; a < Qs.size(); a++){
        Outfile << Qs[a] << std::endl;
        game Game(QFN);
        AI ai(QFN);
        Game.start(Qs[a]);
        int count = 1;
        while(1){
            std::string AIGuess = ai.solution(1, 1);
            Outfile << count << "; " << AIGuess << "; " ;
            int res = Game.test_ans(AIGuess);
            Outfile << Game.result(res) << std::endl;
            std::string resstr;
            for(int b = 0; b < ai.getLen(); b++){
                resstr += (char)((res&7) + '0');
                res >>= 3;
            }
            //std::cout << resstr << std::endl;
            if(ai.response(resstr)){
                Outfile << count << std::endl;
                break;
            }
            count++;
        }
    }
    Outfile.close();
}

int EZtest(std::string QFN){
    game Game(QFN);
    std::string buf;
    while(std::cin >> buf){
        Game.start(buf);
        std::cin >> buf;
        std::cout << Game.result(Game.test_ans(buf));
    }
    return 0;
}

int main(int argc, char* argv[]){
    switch(MainMode){
        case 0:
            if(argc != 4){
                std::cerr << "Usage: " << argv[0] << " <Wordlist> <Answer_list> <Output_file>" << std::endl;
            }
            else{
                std::string QFN(argv[1]);
                std::string Questions(argv[2]);
                std::string Outfile(argv[3]);
                HWMain(QFN, Questions, Outfile);
            }
            break;
        case 1:
            if(argc != 2){
                std::cerr << "Usage: " << argv[0] << " <Wordlist>" << std::endl;
            }
            else{
                std::string QFN(argv[1]);
                test(QFN);
            }
            break;
        case 2:
            if(argc != 2){
                std::cerr << "Usage: " << argv[0] << " <Wordlist>" << std::endl;
            }
            else{
                std::string QFN(argv[1]);
                EZtest(QFN);
            }
            break;
        default:
            break;
    }
    return 0;
}
