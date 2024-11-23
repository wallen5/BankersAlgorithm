#include <iostream>
#include <fstream>
#include <string>

using namespace std;
 
int main()
{
    // Open input file
    ifstream inFile;
    inFile.open("input.txt");
    
    const int resources = 3;
    const int processes = 5;

    int alloc[processes][resources];
    int max[processes][resources];
    int avail[resources];

    // Read the allocation matrix from file
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            inFile >> alloc[i][j]; // Store input file into allocations
        }
    }

    // Read the maximum matrix from file
    for (int i = 0; i < processes; ++i){
        for (int j = 0; j < resources; ++j){
            inFile >> max[i][j];
        }
    }    

    // Read the available resources from file
    for (int i = 0; i < resources; ++i){
        inFile >> avail[i];
    }
    inFile.close(); // Close the input file

    // store[i] == 1 means finished
    int store[processes]; 
    int safeseq[processes];    
    int index = 0;

    for (int k = 0; k < processes; k++) {
        store[k] = 0;
    }


    int need[processes][resources];
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    // Bankers Algorithm to find a safe sequence
    for (int k = 0; k < processes; k++) {  
        for (int i = 0; i < processes; i++) {
            if (store[i] == 0) {
                int flag = 0;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > avail[j]) { 
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {

                    safeseq[index++] = i;

                    for (int d = 0; d < resources; d++)
                        avail[d] += alloc[i][d];
                        store[i] = 1;
                }
            }
        }
    }


  int flag = 1; 
  for (int i = 0; i < processes; i++){
    if(store[i] == 0) {
        flag = 0;
        cout << "Sequence is not safe\n";
        break;
    }
  }
 
  if(flag == 1) {
    cout << "Sequence is safe:" << endl;
    for (int i = 0; i < processes - 1; i++)
        cout << " P" << safeseq[i] << ", ";

    cout << " P" << safeseq[processes - 1] << endl;
  }
}