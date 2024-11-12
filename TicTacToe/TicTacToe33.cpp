#include<bits/stdc++.h>
using namespace std;

const int n=3;
const char AI = 'X', HUMAN = 'O', EMT = ' ';

vector <vector<char>>board= {
    {EMT,EMT,EMT},
    {EMT,EMT,EMT},
    {EMT,EMT,EMT},
};

bool isWinner(char player){
    //row,clmn chck
    for(int i=0; i<n; i++){
          if(board[i][0]==player && board[i][1]==player && board[i][2]==player) return true;
          if(board[0][i]==player && board[1][i]==player && board[2][i]==player) return true;

    }

    //diagonal check
    if(board[0][0]==player && board[1][1] == player && board[2][2]==player) return true;
    if(board[0][2]==player && board[1][1] == player && board[2][0]==player) return true;
    return false;
}

bool isDraw(){
   for(int i=0; i<n; i++ ){
    for(int j=0; j<n; j++){
        if(board[i][j] == EMT) return false;
    }
   }

   return true;
}


int evaluate(){
    if(isWinner(AI)) return 1;
    else if(isWinner(HUMAN)) return -1;
    else return 0;
}

void printBoard(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cout<< board[i][j] << " ";
        cout<< endl;
    }
}


int MiniMax(bool isMaximizing){
    int score = evaluate();
    if(score == 1 || score== -1) return score;
    if(isDraw()) return 0;
    
    //So, it's AI's turn
    if(isMaximizing){
        int bestScore = INT_MIN;

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(board[i][j]==EMT){
                    board[i][j]=AI;
                    bestScore= max(bestScore, MiniMax(false));
                    board[i][j] = EMT;
                }
            }
        }

        return bestScore;
    }
    

    //So, it's Human's's turn
     else{
        int bestScore = INT_MAX;

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(board[i][j]==EMT){
                    board[i][j]=HUMAN;
                    bestScore= min(bestScore, MiniMax(true));
                    board[i][j] = EMT;
                }
            }
        }

        return bestScore;
    }

}

pair<int, int> findBestMove(){
    int bestScore = INT_MIN;
    pair<int,int>bestMove = {-1,-1};
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(board[i][j]==EMT){
                board[i][j]=AI;

                int moveScore = MiniMax(false);

                board[i][j]= EMT;

                if(moveScore > bestScore){
                    bestScore = moveScore;
                    bestMove= {i,j};
                }


            }
        }
    }

    return bestMove;
}

int main() {
    while (true) {
        // Player's turn
        int row, col;
        cout << "Enter your move (row and col): ";
        cin >> row >> col;
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMT) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row][col] = HUMAN;
        printBoard();
        if (isWinner(HUMAN)) {
            cout << "You win!" << endl;
            break;
        }
        if (isDraw()) {
            cout << "It's a draw!" << endl;
            break;
        }

        // AI's turn
        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = AI;
        cout << "AI played at (" << bestMove.first << ", " << bestMove.second << "):" << endl;
        printBoard();
        if (isWinner(AI)) {
            cout << "AI wins!" << endl;
            break;
        }
        if (isDraw()) {
            cout << "It's a draw!" << endl;
            break;
        }
    }
    return 0;
}
