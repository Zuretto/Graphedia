#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <chrono>
#include <iostream>

#define AH 184

void outputPredecessorList(std::vector<std::vector<int>> predecessorsList){
    for(int i = 0; i < predecessorsList.size(); ++i){
        if(!predecessorsList[i].empty()){
            std::cout << i << ": ";
            for(auto j : predecessorsList[i]){
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
}

void BFSCheckDistances(int sourceID, std::vector<int> &lengthsVector, std::vector<std::vector<int>> predecessorsList){
    //tuple {page_ID, distance}
    std::queue<std::tuple<int, int>> q;
    std::tuple<int,int> v;
    std::vector<bool> visitedVertexes;
    for (int i = 0; i < 59235; ++i){
        visitedVertexes.push_back(false);
    }
    visitedVertexes[sourceID] = true;
    q.push(std::make_tuple(sourceID, 0));

    while(!q.empty()){
        v = q.front();
        q.pop();
        for (int u: predecessorsList[std::get<0>(v)])
            if (!visitedVertexes[u]){
                lengthsVector[u] = std::get<1>(v) + 1;
                visitedVertexes[u] = true;
                q.push(std::make_tuple(u, std::get<1>(v) + 1));
            }
    }
}

/*
 * arcs.csv has to have format:
 * successor;predecessor
 *
*/

int main(){
    std::fstream arcs;
    arcs.open("arcs.csv", std::ios::in);
    
    std::vector<std::vector<int>> predecessorsList;
    for (int i = 0; i <= 59235; ++i){
        predecessorsList.push_back(std::vector<int>());
    }
    std::string strBuf;
    
    int sepPos;
    int predecessor;
    int successor;

    while(!arcs.eof()){
        arcs >> strBuf;
        sepPos = strBuf.find(';');
        predecessor = std::atoi(strBuf.substr(0, sepPos).c_str());
        successor = std::atoi(strBuf.substr(sepPos + 1, strBuf.length() - sepPos).c_str());
        //std::cout << successor << ";" << predecessor << std::endl;
        predecessorsList[successor].push_back(predecessor);
    }
    arcs.close();

    std::fstream lengthsFile;
    lengthsFile.open("lengths.csv", std::ios::out);
    lengthsFile << "source;destination;distance" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    //for that iterates through every vertex
    //source;destination;distance

    for (int i = 0; i < 59235; ++i){
        std::vector<int> lengthsVector;
        for (int j = 0; j < 59235; ++j){
            //999 simply means no-path from one article to another.
            lengthsVector.push_back(999);
        }
        BFSCheckDistances(AH, lengthsVector, predecessorsList);
        for(int j = 0; j < 59235; ++j){
            lengthsFile << i + 1 << ";" << j + 1 << ";" << lengthsVector[j] << std::endl;;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = finish - start;
    std::cout << elapsed_time.count() << std::endl;

    

    //outputPredecessorList(predecessorsList);
    exit(0);
}