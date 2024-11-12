#include<bits/stdc++.h>
using namespace std;

const int n = 4;  // Changed board size to 4x4
const char AI = 'X', HUMAN = 'O', EMT = ' ';
vector<vector<char>> board = {
    {EMT, EMT, EMT, EMT},
    {EMT, EMT, EMT, EMT},
    {EMT, EMT, EMT, EMT},
    {EMT, EMT, EMT, EMT}
};

bool isWinner(char player) {
    // Row and column check
    for(int i = 0; i < n; i++) {
        // Check rows
        if(board[i][0] == player && board[i][1] == player && 
           board[i][2] == player && board[i][3] == player) 
            return true;
        // Check columns
        if(board[0][i] == player && board[1][i] == player && 
           board[2][i] == player && board[3][i] == player) 
            return true;
    }
    
    // Diagonal checks
    if(board[0][0] == player && board[1][1] == player && 
       board[2][2] == player && board[3][3] == player) 
        return true;
    
    if(board[0][3] == player && board[1][2] == player && 
       board[2][1] == player && board[3][0] == player) 
        return true;
    
    return false;
}

bool isDraw() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == EMT) 
                return false;
        }
    }
    return true;
}

int evaluate() {
    if(isWinner(AI)) return 1;
    else if(isWinner(HUMAN)) return -1;
    else return 0;
}

void printBoard() {
    cout << "---------------\n";  // Added longer separator for 4x4 board
    for(int i = 0; i < n; i++) {
        cout << "| ";
        for(int j = 0; j < n; j++) 
            cout << board[i][j] << " | ";
        cout << "\n---------------\n";  // Added longer separator for 4x4 board
    }
}

// Modified MiniMax to use alpha-beta pruning for better performance with larger board
int MiniMax(bool isMaximizing, int alpha, int beta, int depth = 0) {
    int score = evaluate();
    if(score == 1 || score == -1) return score;
    if(isDraw() || depth > 5) return 0;  // Added depth limit for performance
    
    if(isMaximizing) {
        int bestScore = INT_MIN;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == EMT) {
                    board[i][j] = AI;
                    bestScore = max(bestScore, MiniMax(false, alpha, beta, depth + 1));
                    board[i][j] = EMT;
                    alpha = max(alpha, bestScore);
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == EMT) {
                    board[i][j] = HUMAN;
                    bestScore = min(bestScore, MiniMax(true, alpha, beta, depth + 1));
                    board[i][j] = EMT;
                    beta = min(beta, bestScore);
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return bestScore;
    }
}

pair<int, int> findBestMove() {
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == EMT) {
                board[i][j] = AI;
                int moveScore = MiniMax(false, INT_MIN, INT_MAX);
                board[i][j] = EMT;
                if(moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

int main() {
    cout << "4x4 Tic-tac-toe\n";
    cout << "Enter row and column numbers between 0 and 3\n";
    
    while(true) {
        // Player's turn
        int row, col;
        cout << "Enter your move (row and col): ";
        cin >> row >> col;
        
        if(row < 0 || row >= n || col < 0 || col >= n || board[row][col] != EMT) {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        
        board[row][col] = HUMAN;
        printBoard();
        cout<<endl <<endl;
        
        if(isWinner(HUMAN)) {
            cout << "You win!\n";
            break;
        }
        if(isDraw()) {
            cout << "It's a draw!\n";
            break;
        }
        
        // AI's turn
        cout << "AI is thinking...\n";
        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = AI;
        cout << "AI played at (" << bestMove.first << ", " << bestMove.second << "):\n";
        printBoard();
        cout<<endl<<endl;
        
        if(isWinner(AI)) {
            cout << "AI wins!\n";
            break;
        }
        if(isDraw()) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}