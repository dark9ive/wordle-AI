#include<iostream>
#include<vector>
#include<ctime>

#include <cctype>
#include <string>
#include <algorithm>

#include"framework.h"
#include"AI.h"

#define MainMode 0
#define TOTAL 2500

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

    // seperate lower QFN and original QFN
    std::string original_QFN = QFN;
    //transform(QFN.begin(),QFN.end(),QFN.begin(),tolower);
    //

    game Game(QFN, 1);
    game Original_Game(original_QFN, 0);
    int total_guess = 0;
    std::vector<int> dist(11, 0);
    for(int a = 0; a < TOTAL; a++){
        std::string send = Game.set_ans(a);
        Original_Game.set_original_ans(a, send);
        //std::cout<<send<<std::endl;
        AI ai(QFN, 1);        
        AI original_ai(original_QFN, 0);
        //
        int temp; 
        std::string temp_s;
        // for original_res


        int count = 0;
        while(1){

            int solu = ai.solution(1, 1);
            int res = Game.test_ans(ai[solu]);

            int original_res = Original_Game.test_original_ans(original_ai[solu]);  //use orignial ans for result
            temp = original_res;
            temp_s = original_ai[solu];

            total_guess++;
            count++;
            std::string resstr;
            for(int b = 0; b < ai.getLen(); b++){
                switch(res&3){
                    case 0:
                        resstr += "0";
                        break;
                    case 1:
                        resstr += "2";
                        break;
                    case 2:
                        resstr += "1";
                        break;
                }
                res >>= 2;
            }
            if(ai.response(resstr)){
                //dist[count]++;
                break;
            }
        }
        //
        // last count if we need
        //std::cout<<temp_s<<std::endl;
        int last_count = 0;
        for(int i = 0; i < ai.getLen(); i++){
            switch(temp & 7){
                case 3:
                    //std::cout<<"."<<std::endl;
                    last_count = 1;
                    if( temp_s[i]-'a' >= 0 ){
                        temp_s[i] -= 32;
                    }
                    else{
                        temp_s[i] += 32;
                    }
                    break;
                default:
                    break;
            }
            temp >>= 3;
        }
        //std::cout << temp_s << std::endl;
        if(last_count == 1){
            //std::cout<<"_"<<std::endl;
            total_guess++;
            count++;
            int final = Original_Game.test_original_ans(temp_s);
        }
        dist[count]++;
        //
        if(a%100 == 0 && a != 0){
            std::cout << "AVG Guess @ " << a << ": " << ((double)total_guess)/a << std::endl;
            for(int b = 1; b <= 10; b++){
                std::cout << "Words using " << b << " times of guessing: " << dist[b] << std::endl;
            }
        }
    }
    std::cout << "AVG Guess @ " << TOTAL << ": " << ((double)total_guess)/TOTAL << std::endl;
    for(int a = 1; a <= 10; a++){
        std::cout << "Words using " << a << " times of guessing: " << dist[a] << std::endl;
    }
    return;
}



void HWMain(std::string QFN, std::string IFname, std::string OFname){

    // seperate lower QFN and original QFN
    std::string original_QFN = QFN;
    //transform(QFN.begin(),QFN.end(),QFN.begin(),tolower);
    //

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
        game Game(QFN,1);
        //game Original_Game(original_QFN, 0);
        AI ai(QFN, 1);

        // seperate lower Qs[a] and original Qs[a]
        std::string original_QS = Qs[a];
        transform(Qs[a].begin(),Qs[a].end(),Qs[a].begin(),tolower);
        AI original_ai(original_QFN, 0);
        //
        int temp; 
        std::string temp_s;
        // for original_res

        Game.start(Qs[a], original_QS); // change, input two kinds of ans
        //Original_Game.start(Qs[a], original_QS);
        int count = 1;
        while(1){
            int solu = ai.solution(1, 1);
            Outfile << count << "; " << original_ai[solu] << "; " ;  //show
            int original_res = Game.test_original_ans(original_ai[solu]);  //use orignial ans for result
            temp = original_res;
            temp_s = original_ai[solu];
            int res = Game.test_ans(ai[solu]);
            //
            //std::cout<<original_ai[solu]<<" vs "<<ai[solu]<<std::endl;
            //
            Outfile << Game.result(original_res);  //use orignial ans for result
            std::string resstr;
            for(int b = 0; b < ai.getLen(); b++){
                switch(res&3){
                    case 0:
                        resstr += "0";
                        break;
                    case 1:
                        resstr += "2";
                        break;
                    case 2:
                        resstr += "1";
                        break;
                }
                res >>= 2;
            }
            if(ai.response(resstr)){
                //Outfile << count << std::endl;
                break;
            }
            count++;
        }
        //
        // last count if we need
        int last_count = 0;
        for(int i = 0; i < ai.getLen(); i++){
            switch(temp & 7){
                case 3:
                    last_count = 1;
                    if( temp_s[i]-'a' >= 0 ){
                        temp_s[i] -= 32;
                    }
                    else{
                        temp_s[i] += 32;
                    }
                    break;
                default:
                    break;
            }
            temp >>= 3;
        }
        //std::cout << temp_s << std::endl;
        if(last_count == 1){
            count++;
            Outfile << count << "; " << temp_s << "; ";
            int final = Game.test_original_ans(temp_s);
            Outfile << Game.result(final);
        }
        //
        Outfile << count << std::endl;
    }
    Outfile.close();
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
        default:
            break;
    }
    return 0;
}
