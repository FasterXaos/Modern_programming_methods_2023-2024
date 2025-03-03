#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

// ГПСЧ
int grn(int min, int max) {
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// Ширина клетки
int c = 32;

// Длинна и высота сетки
int w = 16;
int h = 8;

// Сетки
int** gridLogic = new int*;
int** gridView = new int*;

// Количество мин
int mines;

// Счетчик мин
int m;

// Сложность
int dificulty;

// Флаги
bool win{ 0 };
bool loos{ 0 };
bool firstClick{ 1 };
bool firstСreation{ 1 };

// Часы (таймер)
Clock clo;
int timeStop;

// Шрифт
sf::Font font;

// Время и количество мин
sf::Text tMines, tTime;

// Открытие окна
RenderWindow app;

// Скрываем сетку
void hideGrid() {
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			gridView[i][j] = 10;
		}
}

// Меняем размер сетки
void setGridSize(int wid, int hei) {
	w = wid;
	h = hei;

	// Определяем количество мин на поле
	mines = w * h / dificulty;

	// Счетчик мин
	m = mines;

	// Освоождаем динамическую память 
	if (!firstСreation) {
		for (int i = 0; i < w + 2; i++) {
			delete[] gridLogic[i];
			delete[] gridView[i];
		}
		delete[] gridLogic;
		delete[] gridView;
		firstСreation = 0;
	}

	// Создаем динамические двумерные массивы
	gridLogic = new int* [w + 2];
	gridView = new int* [w + 2];
	for (int i = 0; i < w + 2; i++) {
		gridLogic[i] = new int[h + 2];
		gridView[i] = new int[h + 2];
	}
	hideGrid();

	// Создаем окно
	app.create(VideoMode((w + 2) * c, (h + 2) * c), "SAPPER");

	// Пытаемся избежать бага
	for (int i = 0; i <= w + 1; i++)
		for (int j = 0; j <= h + 1; j++)
			gridLogic[i][j] = -1;
}

// Чистим Сетку
void clearGrid() {
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			gridLogic[i][j] = 0;
		}
}

// Перезаполняем сетку
void fillGrid(int x = -1, int y = -1) {
	// Скрываем и чистим сетку
	clearGrid();

	// Определяем количество мин на поле
	mines = w * h / dificulty;

	// Счетчик мин
	m = mines;

	// Случайно заполняем поле минами, кроме клеток рялом с первым кликом
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

	// Подсчет мин вокруг каждой клетки	
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			int n = 0;
			// Если клетка и есть мина
			if (gridLogic[i][j] == 9) continue;
			// Перебираем 9 клеток рядом с клеткой (включая ее координаты)
			for (int k = i - 1; k <= i + 1; k++) {
				for (int m = j - 1; m <= j + 1; m++) {
					if (gridLogic[k][m] == 9)
						++n;
				}
			}
			// Присваиваем клетке число мин вокруг
			gridLogic[i][j] = n;
		}
}

// Открытие пустых клеток
void openEmptyCell(int x, int y) {
	gridView[x][y] = gridLogic[x][y];
	// Перебираем 9 клеток рядом с клеткой (включая ее координаты)
	for (int k = x - 1; k <= x + 1; k++) {
		for (int m = y - 1; m <= y + 1; m++) {
			// Если нашли еще одну пустую и не открытую клетку
			if (gridLogic[k][m] == 0 && gridView[k][m] != 0) {
				openEmptyCell(k, m);
				// Клетка с цифрой
			} else if (!(gridView[k][m] >= 1 && gridView[k][m] <= 8)) {
				gridView[k][m] = gridLogic[k][m];
			}
		}
	}
}

// Победа?
bool isWin() {
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++) {
			if (gridView[i][j] == 11)
				if (!(gridLogic[i][j] == 9))
					return false;
		}
	return true;
}

// Рестарт
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
	// Для ГПСЧ
	srand(time(0));

	// Загружаем шрифт
	font.loadFromFile("img/Samson.ttf");

	// Настраиваем вывод текста
	tMines.setFont(font);
	tMines.setCharacterSize(32);
	tMines.setFillColor(sf::Color::Red);
	tTime.setFont(font);
	tTime.setCharacterSize(32);
	tTime.setFillColor(sf::Color::Red);

	// Параметры первого появления окна
	dificulty = 8;
	setGridSize(w, h);
	tTime.setString(std::to_string((int)clo.getElapsedTime().asSeconds()));

	// Инициализация необходимых значений
	sf::Vector2u size = app.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	double ratioW{ 1 };
	double ratioH{ 1 };

	// Загрузка текстуры и создание спрайта
	Texture t;
	t.loadFromFile("img/pix.png");
	Sprite s(t);

	while (app.isOpen()) {
		// События
		Event e;

		// Получаем координаты курсора мышки относительно окна нашего приложения
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / ratioW / c;
		int y = pos.y / ratioH / c;

		while (app.pollEvent(e)) {
			// Закрытие окна
			if (e.type == Event::Closed)
				app.close();

			// При изменениии размера, получаем коэффициенты
			else if (e.type == sf::Event::Resized) {
				size = app.getSize();
				ratioW = size.x * 1.0 / width;
				ratioH = size.y * 1.0 / height;
			}

			// Определяем, была ли нажата кнопка мыши?
			else if (e.type == Event::MouseButtonPressed)
				// Если была нажата левая кнопка мыши, то открываем клетку
				if (e.key.code == Mouse::Left) {
					// Нажатие на закрытую клетку
					if (gridView[x][y] == 10) {
						// Обработка первого клика
						if (firstClick) {
							fillGrid(x, y);
							firstClick = 0;
							clo.restart();
						}
						// Если мина
						if (gridLogic[x][y] == 9) {
							loos = true;
							timeStop = clo.getElapsedTime().asSeconds();
						}
						// Если пустая клетка
						else if (gridLogic[x][y] == 0)
							openEmptyCell(x, y);
						// В любом случае открываем клетку
						gridView[x][y] = gridLogic[x][y];


					}
					// Нажатие на клетку 1-8
					else if (gridView[x][y] >= 1 && gridView[x][y] <= 8) {
						// Подсчет флажков
						int n{ 0 };
						for (int k = x - 1; k <= x + 1; k++) {
							for (int m = y - 1; m <= y + 1; m++) {
								if (gridView[k][m] == 11)
									++n;
							}
						}
						// Если совпал с цифрой
						if (n == gridView[x][y]) {
							for (int k = x - 1; k <= x + 1; k++) {
								for (int m = y - 1; m <= y + 1; m++) {
									if (gridView[k][m] == 10) {
										// Если пустая клетка открыта
										if (gridLogic[k][m] == 0)
											openEmptyCell(k, m);
										// Если открыта мина
										if (gridLogic[k][m] == 9) {
											loos = true;
											timeStop = clo.getElapsedTime().asSeconds();
										}
										// В любом случае открываем клетку
										gridView[k][m] = gridLogic[k][m];
									}
								}
							}
						}


					}
					// Нажатие на кнопку изменения сложности
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
					// Нажатие на верхнюю панель
					else {
						// При четной длинне поля
						if (w % 2 == 0) {
							// Уменьшение поля
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
								// Рестарт
							else if (pos.x / ratioW > (w / 2 + 1) * c - c / 2 && pos.x / ratioW <= (w / 2 + 1) * c + c / 2 && y == 0)
								restart();
							// Увеличение поля
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
								// При нечетности
						} else {
							// Уменьшение поля
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
								// Рестарт
							else if (pos.x / ratioW > (w / 2 + 1) * c && pos.x / ratioW <= (w / 2 + 2) * c && y == 0)
								restart();
							// Увеличение поля
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

			// Если была нажата правая кнопка мыши, то отображаем флажок
				else if (e.key.code == Mouse::Right && !win) {
					if (gridView[x][y] == 10) {
						gridView[x][y] = 11;
						--m;
					} else if (gridView[x][y] == 11) {
						gridView[x][y] = 10;
						++m;
					}
					// И проверяем на победу
					if (m == 0 && isWin()) {
						win = true;
						tTime.setFillColor(Color::Green);
						tMines.setFillColor(Color::Green);
						timeStop = clo.getElapsedTime().asSeconds();
					}
				}
		}

		// Отрисовываем видимую сетку
		for (int i = 1; i <= w; i++)
			for (int j = 1; j <= h; j++) {
				if (loos) gridView[i][j] = gridLogic[i][j];
				s.setTextureRect(IntRect(gridView[i][j] * c, 0, c, c));
				s.setPosition(i * c, j * c);
				app.draw(s);
			}

		// Рисуем рамку
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

		// Отрисовка кнопок рестарта и смены размера
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

		// Отрисовка кнопок изменения сложности
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

		// Замараживаем время при проигрише, выйгрыше и до первого клика
		if (loos || win)
			tTime.setString(std::to_string(timeStop));
		else if (!firstClick)
			tTime.setString(std::to_string((int)clo.getElapsedTime().asSeconds()));

		// Отрисовка количества мин
		tMines.setString(std::to_string(m));
		tMines.setPosition(c * 2, -5);
		app.draw(tMines);

		// Отрисовка времени
		tTime.setPosition(c * (w - 1), -5);
		app.draw(tTime);

		// Отображаем всю композицию на экране
		app.display();
	}
	return 0;
}