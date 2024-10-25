
#include "Stack.h"
#include "stack.cpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>


using namespace std;

/**
locate function to increment the values in the safematrix whenever a queen is placed somewhere
 */
 void locate(Position p, vector<vector <int>> & matrix){
        long int size = matrix.size();
       int r = p.row;
       int c = p.col;


       for (int i = 0; i < size; i++) {
           matrix[r][i]++;  //increment the values in the same row
           matrix[i][c]++;  //increment the values in the same column
       }

     
     // increment the values in the same diagonal
     for (int i = 1; r - i >= 0 && c - i >= 0; i++){
         matrix[r - i][c - i]++;
     }
     for (int i = 1; r + i < size && c + i < size; i++){
         matrix[r + i][c + i]++;
     }
     for (int i = 1; r - i >= 0 && c + i < size; i++) {
         matrix[r - i][c + i]++;
     }
     for (int i = 1; r + i < size && c - i >= 0; i++) {
         matrix[r + i][c - i]++;
     }
}
/**
remove function to decrement the values in the safematrix whenever a queen is removed from somewhere
 */
void remove(Position p, vector<vector <int>> & matrix){
        long int size = matrix.size();
        int r = p.row;
        int c = p.col;


        for (int i = 0; i < size; i++) {
            matrix[r][i]--;
            matrix[i][c]--;
        }

        for (int i = 1; r - i >= 0 && c - i >= 0; i++) matrix[r - i][c - i]--;
        for (int i = 1; r + i < size && c + i < size; i++) matrix[r + i][c + i]--;
        for (int i = 1; r - i >= 0 && c + i < size; i++) matrix[r - i][c + i]--;
        for (int i = 1; r + i < size && c - i >= 0; i++) matrix[r + i][c - i]--;
}

/**
 the function to print a matrix, useful while debugging
 */
void printmatrix(vector <vector<int>> matrix){
    for (int i=0; i<matrix.size();i++){
        for (int j=0; j<matrix.size();j++){
            cout<<matrix[i][j]<<"\t";
        }
        cout<<"\n";
    }
}
    

int main() {
    cout<<  "Enter the value of N for the N-Queens problem:";
    int N;
    cin>>N;
    if (N<=0){
        cout<<"Invalid input. Please enter a positive integer\n";
        return 0; //terminate the program
    }
    vector <vector <int>> safeMatrix(N, vector <int> (N, 0));
    
    Stack <Position> s;
    vector <vector<int>> solutions;
    vector <int> solution(N, -1);
    int i=0,j=0;
    while (i >= 0) { // when the loop backtracks to negative numbers, it means all solutions are found
        if (i >= N) {
            // found a solution
            solutions.push_back(solution); //record the solution
            i--; //backtrack to find other solutions
            if (!s.isEmpty()) { //remove the element from the stack and update the matrix
                Position p = s.topAndPop();
                remove(p, safeMatrix);
                j = p.col + 1; // try next column
            } else {
                break; // stack is empty, which means all solutions are found
            }
        } 
        else if (j >= N) { // no place in this row, backtrack
            
            if (!s.isEmpty()) {
                Position p = s.topAndPop();
                remove(p, safeMatrix);
                i--;
                j = p.col + 1; // try next column in previous row
            } else {
                break; // stack is empty, which again means all solutions are found
            }
        } 
        else if (safeMatrix[i][j] == 0) { //safe position found, add the column value to the solution
            Position p(i, j);
            s.push(p);
            locate(p, safeMatrix);
            solution[i] = j; // store the position of the queen in this row
            
            i++;
            j = 0; // move to the next row
        } 
        else {
            j++; // try next column in the same row
        }
    }
    string filename= to_string(N) + "queens_solutions.txt"; // write the solutions to a file
    ofstream file(filename);

    file<<"Total solutions for N="<<N<<": "<<solutions.size()<<"\n\n";

    for (int i=0; i<solutions.size();i++){
        file<< "Solution "<<i<<": [";
        for(int j=0;j<solutions[i].size();j++){
            if (j==solutions[i].size()-1){
                file<<solutions[i][j]<<"]\n";
            }
            else{
                file<<solutions[i][j]<<",";
            }
        }
    }
    file.close();
    cout<<"Solutions have been saved to ’"<<filename<<"’\n";
    return 0;
}
