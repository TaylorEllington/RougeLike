class coordinate{
public:
	coordinate();
	coordinate(int, int, int, int);
	void up();
	void down();
	void left();
	void right();
	int get_x();
	int get_y();
	void teleport(int, int);
	void bounce();

private:
	int x;
	int y;
	int max_X;
	int max_Y;
	int prev_x;
	int prev_y;

};