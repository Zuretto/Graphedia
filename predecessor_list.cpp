#include <fstream>
#include <vector>
#include <set>
#include <iostream>

/*
 * arcs.csv has to have format:
 * successor;predecessor
 *
*/

int main(){
    std::fstream arcs;
    arcs.open("arcs.csv", std::ios::in);
    
    std::vector<std::vector<int>> predecessorsList;
    for (int i = 0; i < 59235; ++i){
        predecessorsList.push_back(std::vector<int>());
    }
    std::string strBuf;
    
    int sepPos;
    int predecessor;
    int successor;
    //while(!arcs.eof()){
    /*
        if you change for iterations to 769476 or change it to while eof loop, program will not work.
    */
    while(!arcs.eof()){
        arcs >> strBuf;
        //arcs >> successor;
        //arcs >> predecessor;
        sepPos = strBuf.find(';');
        predecessor = std::atoi(strBuf.substr(0, sepPos).c_str());
        successor = std::atoi(strBuf.substr(sepPos + 1, strBuf.length() - sepPos).c_str());
        //std::cout << successor << ";" << predecessor << std::endl;
        predecessorsList[successor].push_back(predecessor);
    }

    for(int i = 0; i < predecessorsList.size(); ++i){
        if(!predecessorsList[i].empty()){
            std::cout << i << ": ";
            for(auto j : predecessorsList[i]){
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
    exit(0);
}