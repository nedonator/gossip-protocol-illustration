#include "Project.h"
#pragma once
#include "string"
#include "Signal.h"
//#include "SDL_draw.h"

extern const int WIDTH;
extern const int HEIGHT;
extern const int FPS;
extern const double ACC_TIME;
extern const double MAX_SPEED;
extern const double BULLET_SPEED;
extern const int PLAYER_SIZE;
extern const int BULLET_LIFETIME;
extern Image* enemy;
extern Image* bullet;
Unit** units;
//node count
int N = 100;
//number of additional edges
double p = 0.8;
//speed relative deviation
double eps = 0.3;
std::set<std::pair<double, int>> set1;
std::set<std::pair<double, int>> set2;
std::set<Signal*> signals;
extern const double speed;

double dist(int i, int j) {
	return sqrt(pow(units[i]->x - units[j]->x, 2) + pow(units[i]->y - units[j]->y, 2));
}

class TicTacToeScreen : public Screen
{
private:

	Input* input;
	Graphics* graphics;

	// Изображения фона, крестиков и ноликов
	Image** unitpics = new Image*[3];
	Image* back;
	Image* signal;

	// Массив, обозначающий поле, и текущий игрок
	double nextUpdateTime;
	LARGE_INTEGER freq;
	bool** matrix = new bool*[N];
	bool mousePressed;
	

	void StartSettings()
	{
		// Берем объекты Graphics и Input и устанавливаем заголовок окна
		mousePressed = false;
		srand(282);
		QueryPerformanceFrequency(&freq);
		input = game->GetInput();
		graphics = game->GetGraphics();
		//SDL_WM_SetCaption("Tic-Tac-Toe", 0);
		nextUpdateTime = getTime();
		unitpics[0] = graphics->NewImage((char*)"red.bmp", 255, 255, 255);
		unitpics[1] = graphics->NewImage((char*)"green.bmp", 255, 255, 255);
		unitpics[2] = graphics->NewImage((char*)"grey.bmp", 255, 255, 255);
		signal = graphics->NewImage((char*)"signal.bmp", 255, 255, 255);
		back = graphics->NewImage((char*)"intro.bmp");
		units = new Unit*[N];
		for (int i = 0; i < N; i++)
			units[i] = new Unit(unitpics, graphics, rand() % WIDTH, rand() % HEIGHT);
		for (int i = 0; i < N; i++)
			matrix[i] = new bool[N];
		double par = 10;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				matrix[i][j] = 0;
		bool* color = new bool[N];
		for (int i = 1; i < N; i++)
			color[i] = 0;
		color[0] = 1;
		double* d = new double[N];
		int* from = new int[N];
		d[0] = 1e+6;
		for (int i = 1; i < N; i++) {
			d[i] = dist(0, i);
			from[i] = 0;
		}
		while (1) {
			int min = 0;
			for (int i = 1; i < N; i++)
				if (!color[i] && d[i] < d[min])
					min = i;
			if (!min)
				break;
			color[min] = 1;
			matrix[min][from[min]] = 1;
			matrix[from[min]][min] = 1;
			for (int i = 1; i < N; i++)
				if (d[i] > dist(min, i)) {
					d[i] = dist(min, i);
					from[i] = min;
				}
		}
		for (int i = 0; i < N; i++)
			for (int j = i; j < N; j++)
				if (i != j && rand() < RAND_MAX * p / N) {
					matrix[i][j] = 1;
					matrix[j][i] = 1;
				}
		//set1.insert(std::make_pair(nextUpdateTime + 1, 0));
	}

	double getTime() {
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		return 1.*time.QuadPart / freq.QuadPart;
	}

public:
	void Start()
	{
		StartSettings();
	}

	void Update()
	{

		if (input->IsExit())
			game->Exit();

		while (getTime() < nextUpdateTime)
			Sleep(500 / FPS);
		nextUpdateTime += 1. / FPS;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				if (matrix[i][j])
					graphics->DrawLine(units[i]->x, units[i]->y,units[j]->x,units[j]->y,255,0,0);
			units[i]->draw();
		}

		while (set1.begin() != set1.end() && (*set1.begin()).first < nextUpdateTime) {
			int i = (*set1.begin()).second;
			if (units[i]->imageNumber == 0) {
				set2.insert(std::make_pair((*set1.begin()).first + 2, i));
				units[i]->imageNumber = 1;
				for (int j = 0; j < N; j++)
					if (units[j]->imageNumber == 0 && matrix[i][j]) {
						double randSpeed = speed * (1 - eps + 2 * eps * rand() / RAND_MAX);
						set1.insert(std::make_pair((*set1.begin()).first + sqrt(pow(units[i]->x - units[j]->x, 2) + pow(units[i]->y - units[j]->y, 2)) / randSpeed, j));
						signals.insert(new Signal(signal, graphics, units[i]->x, units[i]->y, units[j]->x, units[j]->y, randSpeed));
					}
			}
			set1.erase(set1.begin());
		}
		while (set2.begin() != set2.end() && (*set2.begin()).first < nextUpdateTime) {
			units[(*set2.begin()).second]->imageNumber = 2;
			set2.erase(set2.begin());
		}
		for (auto it = signals.begin(); it != signals.end();) {
			if (!(*it)->isAlive()) {
				signals.erase(it++);
				continue;
			}
			(*it)->update();
			(*it++)->draw();
		}
		graphics->Flip();
		if (input->IsMouseButtonDown() && !mousePressed) {
			mousePressed = true;
			for (int i = 0; i < N; i++) {
				double dist = sqrt(pow(input->GetButtonDownCoords().x - units[i]->x, 2) + pow(input->GetButtonDownCoords().y - units[i]->y, 2));
				if (dist < 10) {
					set1.insert(std::make_pair(nextUpdateTime, i));
				}
			}
		}
		if (input->IsMouseButtonUp()) {
			mousePressed = false;
		}
	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	return game.Execute(new TicTacToeScreen(), WIDTH, HEIGHT);
}