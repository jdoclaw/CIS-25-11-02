// deals with game logic
class Game {
    public:
        void run(); // runs the game
        void switchPlayer(); // switches player from x to o or o to x
        void readInput(); // reads input from user and makes corresponding move on board

    private:
        Board board;
        char crossOrCircle;
};