#include <iostream>
#include "MinHeap.h"
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

//calculates heuristic value by checking different characters
int heuristic(string word, string end){
    int result = 0;
    for(size_t i = 0; i < word.length(); i++){
        if(word[i] != end[i]){
            result++;
        }
    }
    return result;
}

//solves doublet problem by traversing through map
void doublet(string start, string end, string file){
    //initualizes visited map, distance map, expansions count, and heap
    map<string, bool> visitedMap;
    map<string, int> gscoreMap;
    MinHeap<string> heap(2);
    int expansionCount = 0;
    
    //changes start and end words to lowercase
    transform(start.begin(), start.end(), start.begin(), ::tolower);
    transform(end.begin(), end.end(), end.begin(), ::tolower);

    //extracts data from words.txt file
    int numberOfWords;
    string word;
    ifstream dataFile(file);
    set<string> wordList;
    dataFile >> numberOfWords;
    while(dataFile >> word){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        wordList.insert(word);
    }

    //initializes start distance and adds start to heap
    heap.add(start, heuristic(start, end));
    gscoreMap[start] = 0;
    
    bool transformation = false;
    //traverses through map to find optimal path
    while(!heap.isEmpty()){
        string currNode = heap.peek();
        heap.remove();
        visitedMap[currNode] = true;

        //outputs answer if goal is reached
        if(currNode == end){
            cout << gscoreMap[currNode] << endl;
            cout << expansionCount << endl;
            transformation = true;
            break;
        }
        expansionCount++;

        //checks if word hasn't been visited
        if (visitedMap.find(currNode) != visitedMap.end()){
            vector<string> wordNeighbors;
            vector<char> letters;


            //creates vector of letters from a to z
            char c = 'a';
            for(size_t i = 0; i < 26; i++){
                letters.push_back(c);
                c++;
            }
            string temp = currNode;
            //generates the neighboring words with only one letter discrepency
            for(size_t i = 0; i < temp.length(); i++){
                //loops through each letter of the alphabet
                for(size_t index = 0; index < 26; index++){
                    temp[i] = letters[index];
                    //adds word if it neighbors
                    if(temp != currNode && wordList.find(temp) != wordList.end()){
                        wordNeighbors.push_back(temp);
                    }
                }
                temp = currNode;
            }
            //loops through word neighbors and adds to heap
            for(size_t i = 0; i < wordNeighbors.size(); i++){
                //checks if neighbor is visited
                if(visitedMap.find(wordNeighbors[i]) == visitedMap.end()){
                    //checks if neighbor is not initialized or the current gscore is worse than the new one
                    if(gscoreMap.find(wordNeighbors[i]) == gscoreMap.end() || gscoreMap[currNode] + 1 < gscoreMap[wordNeighbors[i]]){
                        //updates neighbors gscore
                        gscoreMap[wordNeighbors[i]] = gscoreMap[currNode] + 1;
                        //calculates priority and adds neighbor to heap
                        int hValue = heuristic(wordNeighbors[i], end);
                        int fScore = gscoreMap[wordNeighbors[i]] + hValue;
                        int priority = fScore * (currNode.length() + 1) + hValue;
                        heap.add(wordNeighbors[i], priority);
                    }
                }
            }
        }
      
    }
    if(transformation == false){
        cout << "No transformation" << endl;
        cout << expansionCount << endl;
    }
}


int main(int argc, char* argv[]){
    string start = argv[1];
    string end = argv[2];
    string file = argv[3];
    doublet(start, end, file);
}