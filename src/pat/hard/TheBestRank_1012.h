//
// Created by guojm on 2021/2/19.
//

#ifndef ALGORITHM_THEBESTRANK_1012_H
#define ALGORITHM_THEBESTRANK_1012_H
#include <string>
#include <cstdio>
#include <unordered_map>
#include <cmath>
using namespace std;

namespace PAT_TheBestRank_1012 {
    /**
     * notice that grades range from 0 to 100
     * so we can use an array of length 101 (index from 0 to 100)
     * to count the amount of each grade and then to calculate the rank of students
     */
    namespace CountRank{

        constexpr char cs[]{'C','M','E','A'};
        constexpr int priorities[]{3,0,1,2};

        int main(){
            int M=0,N=0;
            //key student-id value score
            unordered_map<string,int*> students;
            //store ranks
            int* ranks[4];
            for (int i = 0; i < 4; ++i) {
                ranks[i] = new int[101];
                for (int j = 0; j < 101; ++j) {
                    ranks[i][j] = -1;
                }
            }
            //read data from input
            scanf("%d %d",&N,&M);
            for(int i = 0;i < N;i++){
                int* score = new int[4];
                char* id = new char[6];
                scanf("%s %d %d %d", id, score, score + 1, score + 2);
                students[id] = score;
                score[3] = (int)round((score[0] + score[1] + score[2]) / 3.0);
                for (int j = 0; j < 4; ++j) {
                    ranks[j][score[j]] = 0;
                }
            }
            //calculate rank
            for (int i = 0; i < 4; ++i) {
                int* array = ranks[i];
                int lastRank = 0;
                for (int j = 100;j >= 0;j--){
                    if (array[j] != -1){
                        array[j] = ++lastRank;
                    }
                }
            }
            //find
            char fid[6];
            for(int i = 0;i < M;i++){
                scanf("%s",fid);
                auto fs = students.find(fid);
                if(fs != students.end()){
                    int* score = fs->second;
                    int p = priorities[0];
                    int maxRank = ranks[p][score[p]];
                    int index = p;
                    //traverse by priority
                    for (int j = 1;j < 4; j++){
                        int r = ranks[priorities[j]][score[priorities[j]]];
                        if (r < maxRank){
                            maxRank = r;
                            index = priorities[j];
                        }
                    }
                    printf("%d %c",maxRank,cs[index]);
                } else {
                    printf("N/A");
                }
                if (i < M-1){
                    printf("\n");
                }
            }
            return 0;
        }
    }


};


#endif //ALGORITHM_THEBESTRANK_1012_H
