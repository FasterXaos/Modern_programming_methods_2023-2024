#include <QDialog>
#include <QFontDatabase>
#include <QFormLayout>
#include <QIntValidator>
#include <QLineEdit>
#include <QRandomGenerator>
#include <QTime>

#include "cell.h"
#include "customdialog.h"
#include "game.h"
#include "menu.h"
#include "records.h"

namespace AED {
	Game::Game(QWidget *parent): QMainWindow(parent){
		centralWidget = new QWidget(this);
		mainVLayout = new QVBoxLayout(centralWidget);
		mainVLayout->setContentsMargins(0, 0, 0, 0);
		mainVLayout->setSpacing(0);


		int fontId = QFontDatabase::addApplicationFont(":/fonts/digital_numbers.ttf");
		QString fontFamilyName = QFontDatabase::applicationFontFamilies(fontId).at(0);
		QFont digitalFont = QFont(fontFamilyName, 14);


		QWidget* topPanel = new QWidget(this);
		topHLayout = new QHBoxLayout(topPanel);
		topPanel->setContentsMargins(0, 0, 0, 0);
		topPanel->setStyleSheet("background-color: #c0c0c0;");

		minesCounter = new QLabel("Mines:" + QString::number(mineCount), this);
		minesCounter->setFont(digitalFont);
		minesCounter->setStyleSheet("color: red;");
		topHLayout->addWidget(minesCounter);

		resetButton = new QPushButton(this);
		resetButton->setFixedSize(48, 48);
		resetButton->setIcon(QIcon(":/images/minesweeper_button.png"));
		resetButton->setIconSize(QSize(48, 48));
		topHLayout->addStretch();
		topHLayout->addWidget(resetButton);
		topHLayout->addStretch();

		timerLabel = new QLabel("Time:000", this);
		timerLabel->setFont(digitalFont);
		timerLabel->setStyleSheet("color: red;");
		gameTimer = new Timer(timerLabel, this);
		gameTimer->start();
		topHLayout->addWidget(timerLabel);


		QWidget* fieldWidget = new QWidget(this);
		fieldGLayout = new QGridLayout(fieldWidget);
		fieldGLayout->setContentsMargins(0, 0, 0, 0);
		fieldGLayout->setSpacing(0);


		mainVLayout->addWidget(topPanel);
		mainVLayout->addWidget(fieldWidget);

		setCentralWidget(centralWidget);

		createField();
		createMenu();


		connect(resetButton, &QPushButton::pressed, this, &Game::onResetButtonPressed);
		connect(resetButton, &QPushButton::released, this, &Game::onResetButtonReleased);
		connect(gameTimer, &Timer::timeIsUp, this, &Game::onGameLost);
		connect(this, &Game::gameLost, this, &Game::onGameLost);
	}

	Game::~Game() {
		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < columns; ++col) {
				delete cells[row][col];
			}
			delete[] cells[row];
		}
		delete[] cells;

		delete centralWidget;

		delete mainVLayout;
		delete topHLayout;
		delete fieldGLayout;

		delete minesCounter;
		delete resetButton;
		delete timerLabel;
		delete gameTimer;
	}


	void Game::createField() {
		cells = new Cell**[rows];
		for (int row = 0; row < rows; ++row) {
			cells[row] = new Cell*[columns];
			for (int column = 0; column < columns; ++column) {
				cells[row][column] = new Cell(row, column, this);
				fieldGLayout->addWidget(cells[row][column], row, column);

				connect(cells[row][column], &Cell::checkForWin, this, &Game::onCheckForWin);
				connect(cells[row][column], &Cell::emptyCellOpened, this, &Game::openAdjacentCells);
				connect(cells[row][column], &Cell::flagAdded, this, &Game::onFlagAdded);
				connect(cells[row][column], &Cell::flagRemoved, this, &Game::onFlagRemoved);
				connect(cells[row][column], &Cell::mineClicked, this, &Game::onGameLost);
				connect(cells[row][column], &Cell::openedCellClicked, this, &Game::onOpenedCellClicked);
			}
		}

		int placedMines = 0;
		while (placedMines < mineCount) {
			int randomRow = QRandomGenerator::global()->bounded(rows);
			int randomColumn = QRandomGenerator::global()->bounded(columns);

			Cell* cell = cells[randomRow][randomColumn];

			if (!cell->hasMine) {
				cell->setMine();
				++placedMines;
			}
		}

		for (int row = 0; row < rows; ++row) {
			for (int column = 0; column < columns; ++column) {
				if (cells[row][column]->hasMine) {
					continue;
				}

				int adjacentMines = 0;
				for (int i = -1; i <= 1; ++i) {
					for (int j = -1; j <= 1; ++j) {
						int newRow = row + i;
						int newColumn = column + j;

						if (newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns) {
							if (cells[newRow][newColumn]->hasMine) {
								++adjacentMines;
							}
						}
					}
				}

				cells[row][column]->surroundingMinesCount = adjacentMines;
				QString iconPath = ":/images/cell_" + QString::number(adjacentMines) + ".png";
				cells[row][column]->openedIcon = QPixmap(iconPath);
			}
		}
	}

	void Game::createMenu() {
		QMenuBar* menuBar = new QMenuBar(this);
		menuBar->setStyleSheet("QMenuBar {spacing: 0px;}");
		setMenuBar(menuBar);

		QMenu* gameMenu = new QMenu("Game", this);
		gameMenu->setStyleSheet("QMenu::item {padding: 5px 5px;}");
		menuBar->addMenu(gameMenu);


		QAction* restartAction = new QAction("Restart", this);
		connect(restartAction, &QAction::triggered, this, &Game::onRestartGame);
		gameMenu->addAction(restartAction);

		gameMenu->addSeparator();

		QAction* beginnerAction = new QAction("Beginner", this);
		QAction* intermediateAction = new QAction("Intermediate", this);
		QAction* expertAction = new QAction("Expert", this);
		QAction* customAction = new QAction("Custom", this);

		connect(beginnerAction, &QAction::triggered, this, &Game::onBeginnerSelected);
		connect(intermediateAction, &QAction::triggered, this, &Game::onIntermediateSelected);
		connect(expertAction, &QAction::triggered, this, &Game::onExpertSelected);
		connect(customAction, &QAction::triggered, this, &Game::onCustomSelected);

		gameMenu->addAction(beginnerAction);
		gameMenu->addAction(intermediateAction);
		gameMenu->addAction(expertAction);
		gameMenu->addAction(customAction);

		gameMenu->addSeparator();

		QAction* recordsAction = new QAction("Records", this);
		connect(recordsAction, &QAction::triggered, this, &Game::onRecordsSelected);
		gameMenu->addAction(recordsAction);

		gameMenu->addSeparator();

		QAction* menuAction = new QAction("Menu", this);
		QAction* quitAction = new QAction("Quit", this);

		connect(menuAction, &QAction::triggered, this, &Game::onReturnToStartMenu);
		connect(quitAction, &QAction::triggered, this, &Game::close);

		gameMenu->addAction(menuAction);
		gameMenu->addAction(quitAction);
	}

	void Game::openAdjacentCells(int row, int col) {
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				int newRow = row + i;
				int newColumn = col + j;

				if (newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns) {
					cells[newRow][newColumn]->openCell();
				}
			}
		}
	}

	void Game::restartGame(int newRows, int newColumns, int newMineCount) {
		for (int row = 0; row < rows; ++row) {
			for (int col = 0; col < columns; ++col) {
				delete cells[row][col];
			}
			delete[] cells[row];
		}
		delete[] cells;

		rows = newRows;
		columns = newColumns;
		mineCount = newMineCount;
		createField();

		minesCounter->setText("Mines:" + QString::number(mineCount));
		minesCounter->setStyleSheet("color: red;");

		resetButton->setIcon(QIcon(":/images/minesweeper_button.png"));

		timerLabel->setStyleSheet("color: red;");
		gameTimer->reset();
		gameTimer->start();
	}

	void Game::showMines() {
		for (int row = 0; row < rows; ++row) {
			for (int column = 0; column < columns; ++column) {
				Cell* cell = cells[row][column];
				if (cell->hasMine) {
					if (cell->isFlagged) {
						continue;
					}
					cell->showCell();
				}
				else if (cell->isFlagged) {
					cell->hidenIcon = QPixmap(":/images/cell_12.png");
					QPixmap scaledPixmap = cell->hidenIcon.scaled(cell->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
					cell->setIcon(QIcon(scaledPixmap));
				}
			}
		}
	}


	void Game::onBeginnerSelected() {
		restartGame(9, 12, 14);
	}

	void Game::onCheckForWin() {
		bool won = true;
		for (int row = 0; row < rows; ++row) {
			for (int column = 0; column < columns; ++column) {
				Cell* cell = cells[row][column];
				if ((cell->hasMine && !cell->isFlagged) || (!cell->hasMine && cell->isFlagged)) {
					won = false;
					break;
				}
			}
			if (!won) break;
		}

		if (won) {
			gameTimer->stop();
			minesCounter->setStyleSheet("color: green;");
			timerLabel->setStyleSheet("color: green;");

			for (int row = 0; row < rows; ++row) {
				for (int column = 0; column < columns; ++column) {
					Cell* cell = cells[row][column];
					if (!cell->isFlagged && !cell->isOpened) {
						cell->showCell();
					}
					cell->isBlocked = true;
				}
			}

			int elapsedTime = gameTimer->getElapsedTime();
			QString timeStr = QString::number(elapsedTime) + "s";
			Records records;
			QString difficulty;

			if (rows == 9 && columns == 12 && mineCount == 14) {
				difficulty = "Beginner";
			}
			else if (rows == 16 && columns == 16 && mineCount == 40) {
				difficulty = "Intermediate";
			}
			else if (rows == 16 && columns == 30 && mineCount == 99) {
				difficulty = "Expert";
			}
			else {
				difficulty = "Custom";
			}

			QString recordData = records.getRecordData();
			QStringList lines = recordData.split('\n');
			QString currentRecordTime = lines[difficulty == "Beginner" ? 0 :
											difficulty == "Intermediate" ? 1 :
											difficulty == "Expert" ? 2 : 0].split('\t').at(1).trimmed();

			QString timeStrWithoutS = timeStr.left(timeStr.length() - 1);
			QString recordTimeWithoutS = currentRecordTime.left(currentRecordTime.length() - 1);

			if (timeStrWithoutS.toInt() < recordTimeWithoutS.toInt()) {
				records.setRecordData(difficulty, timeStr);
			}
		}
	}

	void Game::onCustomSelected(){
		CustomDialog dialog(this);

		if (dialog.exec() == QDialog::Accepted) {
			int newRows = std::clamp(dialog.getRows(), 9, 24);
			int newColumns = std::clamp(dialog.getColumns(), 9, 36);
			int newMines = std::clamp(dialog.getMines(), 1, newRows * newColumns - 1);

			restartGame(newRows, newColumns, newMines);
		}
	}

	void Game::onExpertSelected() {
		restartGame(16, 30, 99);
	}

	void Game::onFlagAdded() {
		int remainingMines = minesCounter->text().mid(6).toInt();
		minesCounter->setText("Mines:" + QString::number(--remainingMines));
	}

	void Game::onFlagRemoved() {
		int remainingMines = minesCounter->text().mid(6).toInt();
		minesCounter->setText("Mines:" + QString::number(++remainingMines));
	}

	void Game::onGameLost(){
		showMines();
		resetButton->setIcon(QIcon(":/images/minesweeper_game_over.png"));
		gameTimer->stop();

		for (int row = 0; row < rows; ++row) {
			for (int column = 0; column < columns; ++column) {
				cells[row][column]->isBlocked = true;
			}
		}
	}

	void Game::onIntermediateSelected() {
		restartGame(16, 16, 40);
	}

	void Game::onOpenedCellClicked(int row, int column){
		int flaggedCount = 0;

		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0) {
					continue;
				}

				int newRow = row + i;
				int newColumn = column + j;
				if (newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns && cells[newRow][newColumn]->isFlagged) {
						++flaggedCount;
				}
			}
		}

		if (flaggedCount == cells[row][column]->surroundingMinesCount) {
			openAdjacentCells(row, column);
		}
	}

	void Game::onRecordsSelected() {
		Records records;
		QString recordData = records.getRecordData();

		QDialog* recordsDialog = new QDialog(this);
		recordsDialog->setWindowIcon(QIcon(":/images/minesweeper_icon.png"));
		recordsDialog->setWindowTitle("Records");
		recordsDialog->setFixedSize(190, 120);

		QLabel* recordsLabel = new QLabel(recordData, recordsDialog);

		QPushButton* closeButton = new QPushButton("Close", recordsDialog);
		connect(closeButton, &QPushButton::clicked, recordsDialog, &QDialog::accept);

		QVBoxLayout* dialogLayout = new QVBoxLayout(recordsDialog);
		dialogLayout->addWidget(recordsLabel);
		dialogLayout->addWidget(closeButton);

		recordsDialog->setLayout(dialogLayout);
		recordsDialog->exec();
	}

	void Game::onResetButtonPressed() {
		resetButton->setIcon(QIcon(":/images/minesweeper_button_pressed.png"));
	}

	void Game::onResetButtonReleased() {
		resetButton->setIcon(QIcon(":/images/minesweeper_button.png"));
		restartGame(rows, columns, mineCount);
	}

	void Game::onRestartGame(){
		restartGame(rows, columns, mineCount);
	}

	void Game::onReturnToStartMenu() {
		Menu* menu = new Menu();
		menu->resize(150, 200);
		menu->setWindowIcon(QIcon(":images/minesweeper_icon.png"));
		menu->setWindowTitle("Minesweeper");
		menu->show();

		this->close();
	}
}
