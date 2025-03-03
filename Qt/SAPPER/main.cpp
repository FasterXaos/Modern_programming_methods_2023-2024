#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

// ����
int grn(int min, int max) {
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// ������ ������
int c = 32;

// ������ � ������ �����
int w = 16;
int h = 8;

// �����
int** gridLogic = new int*;
int** gridView = new int*;

// ���������� ���
int mines;

// ������� ���
int m;

// ���������
int dificulty;

// �����
bool win{ 0 };
bool loos{ 0 };
bool firstClick{ 1 };
bool first�reation{ 1 };

// ���� (������)
Clock clo;
int timeStop;

// �����
sf::Font font;

// ����� � ���������� ���
sf::Text tMines, tTime;

// �������� ����
RenderWindow app;

// �������� �����
void hideGrid() {
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			gridView[i][j] = 10;
		}
}

// ������ ������ �����
void setGridSize(int wid, int hei) {
	w = wid;
	h = hei;

	// ���������� ���������� ��� �� ����
	mines = w * h / dificulty;

	// ������� ���
	m = mines;

	// ���������� ������������ ������ 
	if (!first�reation) {
		for (int i = 0; i < w + 2; i++) {
			delete[] gridLogic[i];
			delete[] gridView[i];
		}
		delete[] gridLogic;
		delete[] gridView;
		first�reation = 0;
	}

	// ������� ������������ ��������� �������
	gridLogic = new int* [w + 2];
	gridView = new int* [w + 2];
	for (int i = 0; i < w + 2; i++) {
		gridLogic[i] = new int[h + 2];
		gridView[i] = new int[h + 2];
	}
	hideGrid();

	// ������� ����
	app.create(VideoMode((w + 2) * c, (h + 2) * c), "SAPPER");

	// �������� �������� ����
	for (int i = 0; i <= w + 1; i++)
		for (int j = 0; j <= h + 1; j++)
			gridLogic[i][j] = -1;
}

// ������ �����
void clearGrid() {
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			gridLogic[i][j] = 0;
		}
}

// ������������� �����
void fillGrid(int x = -1, int y = -1) {
	// �������� � ������ �����
	clearGrid();

	// ���������� ���������� ��� �� ����
	mines = w * h / dificulty;

	// ������� ���
	m = mines;

	// �������� ��������� ���� ������, ����� ������ ����� � ������ ������
	for (int i{ mines }; i > 0; --i) {
		int xm{ grn(1,w) }, ym{ grn(1,h) };
		if (xm < (x - 1) || xm >(x + 1) || ym < (y - 1) || ym >(y + 1))
			if (gridLogic[xm][ym] != 9)
				gridLogic[xm][ym] = 9;
			else
				++i;
		else
			++i;
	}

	// ������� ��� ������ ������ ������	
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			int n = 0;
			// ���� ������ � ���� ����
			if (gridLogic[i][j] == 9) continue;
			// ���������� 9 ������ ����� � ������� (������� �� ����������)
			for (int k = i - 1; k <= i + 1; k++) {
				for (int m = j - 1; m <= j + 1; m++) {
					if (gridLogic[k][m] == 9)
						++n;
				}
			}
			// ����������� ������ ����� ��� ������
			gridLogic[i][j] = n;
		}
}

// �������� ������ ������
void openEmptyCell(int x, int y) {
	gridView[x][y] = gridLogic[x][y];
	// ���������� 9 ������ ����� � ������� (������� �� ����������)
	for (int k = x - 1; k <= x + 1; k++) {
		for (int m = y - 1; m <= y + 1; m++) {
			// ���� ����� ��� ���� ������ � �� �������� ������
			if (gridLogic[k][m] == 0 && gridView[k][m] != 0) {
				openEmptyCell(k, m);
				// ������ � ������
			} else if (!(gridView[k][m] >= 1 && gridView[k][m] <= 8)) {
				gridView[k][m] = gridLogic[k][m];
			}
		}
	}
}

// ������?
bool isWin() {
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			if (gridView[i][j] == 11)
				if (!(gridLogic[i][j] == 9))
					return false;
		}
	return true;
}

// �������
void restart() {
	win = 0;
	loos = 0;
	firstClick = 1;
	hideGrid();
	clo.restart();
	tTime.setString(std::to_string((int)clo.getElapsedTime().asSeconds()));
	tTime.setFillColor(Color::Red);
	tMines.setFillColor(Color::Red);
	m = mines;
}

int main() {
	// ��� ����
	srand(time(0));

	// ��������� �����
	font.loadFromFile("img/Samson.ttf");

	// ����������� ����� ������
	tMines.setFont(font);
	tMines.setCharacterSize(32);
	tMines.setFillColor(sf::Color::Red);
	tTime.setFont(font);
	tTime.setCharacterSize(32);
	tTime.setFillColor(sf::Color::Red);

	// ��������� ������� ��������� ����
	dificulty = 8;
	setGridSize(w, h);
	tTime.setString(std::to_string((int)clo.getElapsedTime().asSeconds()));

	// ������������� ����������� ��������
	sf::Vector2u size = app.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	double ratioW{ 1 };
	double ratioH{ 1 };

	// �������� �������� � �������� �������
	Texture t;
	t.loadFromFile("img/pix.png");
	Sprite s(t);

	while (app.isOpen()) {
		// �������
		Event e;

		// �������� ���������� ������� ����� ������������ ���� ������ ����������
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / ratioW / c;
		int y = pos.y / ratioH / c;

		while (app.pollEvent(e)) {
			// �������� ����
			if (e.type == Event::Closed)
				app.close();

			// ��� ���������� �������, �������� ������������
			else if (e.type == sf::Event::Resized) {
				size = app.getSize();
				ratioW = size.x * 1.0 / width;
				ratioH = size.y * 1.0 / height;
			}

			// ����������, ���� �� ������ ������ ����?
			else if (e.type == Event::MouseButtonPressed)
				// ���� ���� ������ ����� ������ ����, �� ��������� ������
				if (e.key.code == Mouse::Left) {
					// ������� �� �������� ������
					if (gridView[x][y] == 10) {
						// ��������� ������� �����
						if (firstClick) {
							fillGrid(x, y);
							firstClick = 0;
							clo.restart();
						}
						// ���� ����
						if (gridLogic[x][y] == 9) {
							loos = true;
							timeStop = clo.getElapsedTime().asSeconds();
						}
						// ���� ������ ������
						else if (gridLogic[x][y] == 0)
							openEmptyCell(x, y);
						// � ����� ������ ��������� ������
						gridView[x][y] = gridLogic[x][y];


					}
					// ������� �� ������ 1-8
					else if (gridView[x][y] >= 1 && gridView[x][y] <= 8) {
						// ������� �������
						int n{ 0 };
						for (int k = x - 1; k <= x + 1; k++) {
							for (int m = y - 1; m <= y + 1; m++) {
								if (gridView[k][m] == 11)
									++n;
							}
						}
						// ���� ������ � ������
						if (n == gridView[x][y]) {
							for (int k = x - 1; k <= x + 1; k++) {
								for (int m = y - 1; m <= y + 1; m++) {
									if (gridView[k][m] == 10) {
										// ���� ������ ������ �������
										if (gridLogic[k][m] == 0)
											openEmptyCell(k, m);
										// ���� ������� ����
										if (gridLogic[k][m] == 9) {
											loos = true;
											timeStop = clo.getElapsedTime().asSeconds();
										}
										// � ����� ������ ��������� ������
										gridView[k][m] = gridLogic[k][m];
									}
								}
							}
						}


					}
					// ������� �� ������ ��������� ���������
					else if (x == w + 1 && y == 0) {
						dificulty = 7;
						restart();
						fillGrid();
					} else if (x == w + 1 && y == 1) {
						dificulty = 8;
						restart();
						fillGrid();
					} else if (x == w + 1 && y == 2) {
						dificulty = 9;
						restart();
						fillGrid();
					}
					// ������� �� ������� ������
					else {
						// ��� ������ ������ ����
						if (w % 2 == 0) {
							// ���������� ����
							if (pos.x / ratioW > (w / 2) * c - c / 2 && pos.x / ratioW <= (w / 2) * c + c / 2 && y == 0)
								if (!(w <= 16 || h <= 8)) {
									restart();
									setGridSize(w / 1.5, h / 1.5);
									ratioW = 1;
									ratioH = 1;
									size = app.getSize();
									width = size.x;
									height = size.y;
								} else
									restart();
								// �������
							else if (pos.x / ratioW > (w / 2 + 1) * c - c / 2 && pos.x / ratioW <= (w / 2 + 1) * c + c / 2 && y == 0)
								restart();
							// ���������� ����
							else if (pos.x / ratioW > (w / 2 + 2) * c - c / 2 && pos.x / ratioW <= (w / 2 + 2) * c + c / 2 && y == 0)
								if (VideoMode::getDesktopMode().width / 32 > w * 1.5 && VideoMode::getDesktopMode().height > h * 1.5) {
									restart();
									setGridSize(w * 1.5, h * 1.5);
									ratioW = 1;
									ratioH = 1;
									size = app.getSize();
									width = size.x;
									height = size.y;
								} else
									restart();
								// ��� ����������
						} else {
							// ���������� ����
							if (pos.x / ratioW > (w / 2) * c && pos.x / ratioW <= (w / 2 + 1) * c && y == 0)
								if (!(w <= 16 || h <= 8)) {
									restart();
									setGridSize(w / 1.5, h / 1.5);
									ratioW = 1;
									ratioH = 1;
									size = app.getSize();
									width = size.x;
									height = size.y;
								} else
									restart();
								// �������
							else if (pos.x / ratioW > (w / 2 + 1) * c && pos.x / ratioW <= (w / 2 + 2) * c && y == 0)
								restart();
							// ���������� ����
							else if (pos.x / ratioW > (w / 2 + 2) * c && pos.x / ratioW <= (w / 2 + 3) * c && y == 0)
								if (VideoMode::getDesktopMode().width / 32 > w * 1.5 && VideoMode::getDesktopMode().height > h * 1.5) {
									restart();
									setGridSize(w * 1.5, h * 1.5);
									ratioW = 1;
									ratioH = 1;
									size = app.getSize();
									width = size.x;
									height = size.y;
								} else
									restart();
						}
					}
				}

			// ���� ���� ������ ������ ������ ����, �� ���������� ������
				else if (e.key.code == Mouse::Right && !win) {
					if (gridView[x][y] == 10) {
						gridView[x][y] = 11;
						--m;
					} else if (gridView[x][y] == 11) {
						gridView[x][y] = 10;
						++m;
					}
					// � ��������� �� ������
					if (m == 0 && isWin()) {
						win = true;
						tTime.setFillColor(Color::Green);
						tMines.setFillColor(Color::Green);
						timeStop = clo.getElapsedTime().asSeconds();
					}
				}
		}

		// ������������ ������� �����
		for (int i = 1; i <= w; i++)
			for (int j = 1; j <= h; j++) {
				if (loos) gridView[i][j] = gridLogic[i][j];
				s.setTextureRect(IntRect(gridView[i][j] * c, 0, c, c));
				s.setPosition(i * c, j * c);
				app.draw(s);
			}

		// ������ �����
		{
			s.setTextureRect(IntRect(13 * c, 0, c, c));
			s.setPosition(0, 0);
			app.draw(s);

			s.setTextureRect(IntRect(15 * c, 0, c, c));
			s.setPosition((w + 1) * c, 0);
			app.draw(s);

			s.setTextureRect(IntRect(19 * c, 0, c, c));
			s.setPosition(0, (h + 1) * c);
			app.draw(s);

			s.setTextureRect(IntRect(17 * c, 0, c, c));
			s.setPosition((w + 1) * c, (h + 1) * c);
			app.draw(s);

			for (int i(1); i <= w; ++i) {
				s.setTextureRect(IntRect(14 * c, 0, c, c));
				s.setPosition(i * c, 0);
				app.draw(s);

				s.setTextureRect(IntRect(18 * c, 0, c, c));
				s.setPosition(i * c, (h + 1) * c);
				app.draw(s);
			}

			for (int i(1); i <= h; ++i) {
				s.setTextureRect(IntRect(20 * c, 0, c, c));
				s.setPosition(0, i * c);
				app.draw(s);

				s.setTextureRect(IntRect(16 * c, 0, c, c));
				s.setPosition((w + 1) * c, i * c);
				app.draw(s);
			}}

		// ��������� ������ �������� � ����� �������
		if (w % 2 == 0) {
			s.setTextureRect(IntRect(12 * c, 0, c, c));
			s.setPosition((w / 2) * c + c / 2, 0 * c);
			app.draw(s);
			s.setTextureRect(IntRect(0 * c, 1 * c, c, c));
			s.setPosition((w / 2 - 1) * c + c / 2, 0 * c);
			app.draw(s);
			s.setTextureRect(IntRect(1 * c, 1 * c, c, c));
			s.setPosition((w / 2 + 1) * c + c / 2, 0 * c);
			app.draw(s);
		} else {
			s.setTextureRect(IntRect(12 * c, 0, c, c));
			s.setPosition((w / 2 + 1) * c, 0 * c);
			app.draw(s);
			s.setTextureRect(IntRect(0 * c, 1 * c, c, c));
			s.setPosition((w / 2) * c, 0 * c);
			app.draw(s);
			s.setTextureRect(IntRect(1 * c, 1 * c, c, c));
			s.setPosition((w / 2 + 2) * c, 0 * c);
			app.draw(s);
		}

		// ��������� ������ ��������� ���������
		{
			s.setTextureRect(IntRect(2 * c, 1 * c, c, c));
			s.setPosition((w + 1) * c, 0 * c);
			app.draw(s);
			s.setTextureRect(IntRect(3 * c, 1 * c, c, c));
			s.setPosition((w + 1) * c, 1 * c);
			app.draw(s);
			s.setTextureRect(IntRect(4 * c, 1 * c, c, c));
			s.setPosition((w + 1) * c, 2 * c);
			app.draw(s);
		}

		// ������������ ����� ��� ���������, �������� � �� ������� �����
		if (loos || win)
			tTime.setString(std::to_string(timeStop));
		else if (!firstClick)
			tTime.setString(std::to_string((int)clo.getElapsedTime().asSeconds()));

		// ��������� ���������� ���
		tMines.setString(std::to_string(m));
		tMines.setPosition(c * 2, -5);
		app.draw(tMines);

		// ��������� �������
		tTime.setPosition(c * (w - 1), -5);
		app.draw(tTime);

		// ���������� ��� ���������� �� ������
		app.display();
	}
	return 0;
}