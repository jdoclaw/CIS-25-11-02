// Contains board on which game is played

class Board {
    public:
        Board(); // constructs board
        ~Board(); // destructs board
        bool makeMove(int row, int col, char crossOrCircle); // makes move on board, returns true if move can be made, false otherwise
        void clear(); // clears board of x's and o's
        void checkWinner(); // checks if there is a winner and prints out their symbol (x or o)
        bool isFull(); // checks if board is full

    private:
        char ** grid;
};