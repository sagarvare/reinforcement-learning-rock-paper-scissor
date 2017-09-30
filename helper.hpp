class Game {
	private:
		int old_board[100][100];
		int board[100][100];
	public:
		Game(void);//Constructor for the class
		void run(int num);
		void switchBoards(void);
		void updateBoard(void);
		void display(void);
};