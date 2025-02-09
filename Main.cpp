#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

const int WIDTH = 21;
const int HEIGHT = 21;
const char WALL = '#';
const char PATH = '.';
const char START = 'S';
const char GOAL = 'G';
const char SOLUTION = '*';

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

vector<vector<char>> maze(HEIGHT, vector<char>(WIDTH, WALL));
vector<vector<int>> wave(HEIGHT, vector<int>(WIDTH, -1));

bool isValid(int x, int y) {
    return x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1;
}

void generateMaze(int x, int y) {
    maze[y][x] = PATH;
    vector<int> order = {0, 1, 2, 3};
    random_device rd;
    mt19937 g(rd());
    shuffle(order.begin(), order.end(), g);
    for (int i : order) {
        int nx = x + dx[i] * 2, ny = y + dy[i] * 2;
        int mx = x + dx[i], my = y + dy[i];
        if (isValid(nx, ny) && maze[ny][nx] == WALL) {
            maze[my][mx] = PATH;
            generateMaze(nx, ny);
        }
    }
}

void wavefrontSearch(int goalX, int goalY) {
    queue<pair<int, int>> q;
    q.push({goalX, goalY});
    wave[goalY][goalX] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny) && maze[ny][nx] != WALL && wave[ny][nx] == -1) {
                wave[ny][nx] = wave[y][x] + 1;
                q.push({nx, ny});
            }
        }
    }
}

vector<pair<int, int>> reconstructPath(int startX, int startY) {
    vector<pair<int, int>> path;
    int x = startX, y = startY;
    while (wave[y][x] != 0) {
        path.emplace_back(x, y);
        int minWave = wave[y][x];
        int nextX = x, nextY = y;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny) && wave[ny][nx] >= 0 && wave[ny][nx] < minWave) {
                minWave = wave[ny][nx];
                nextX = nx;
                nextY = ny;
            }
        }
        x = nextX;
        y = nextY;
    }
    path.emplace_back(x, y);
    reverse(path.begin(), path.end());
    return path;
}

void printMaze() {
    for (const auto& row : maze) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    generateMaze(1, 1);
    maze[1][1] = START;
    maze[HEIGHT - 2][WIDTH - 2] = GOAL;
    wavefrontSearch(WIDTH - 2, HEIGHT - 2);
    vector<pair<int, int>> path = reconstructPath(1, 1);
    for (const auto& [x, y] : path) {
        if (maze[y][x] == PATH) maze[y][x] = SOLUTION;
    }
    printMaze();
    return 0;
}
