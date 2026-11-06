class Board {
    public:
        Board();
        ~Board();
        bool makeMove(int row, int col, char crossOrCircle);
        void clear();
        void checkWinner();
        bool isFull();

    private:
        char ** grid;
}