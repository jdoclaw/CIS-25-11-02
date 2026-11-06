class Game {
    public:
        void run();
        void switchPlayer();
        void readInput();

    private:
        Board board;
        char crossOrCircle;
}