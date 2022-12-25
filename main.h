int logFunc(double base, double argument);

int getRandomSquareOnBoard(const int boardSize);

int getRandomPlayableNumber(const size_t playerScore);

void createBoard(int** board, const int boardSize);

void putFirstNumberOnBoard(int** board, size_t& playerScore, const int boardSize);

void printBoard(int** board, const size_t playerScore, const int boardSize);

void freeBoard(int** board, const int boardSize);

void initializeBoard(int** board, size_t& playerScore, const int boardSize);