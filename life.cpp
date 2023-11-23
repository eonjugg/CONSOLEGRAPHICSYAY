/*

Conway's game of life printed to console

Program will stop automatically if it detects two identical frames in a row, otherwise
change the max iterations using max_its.

Grid is 'borderless', i.e. a cell on the edge of the grid will observe the cells on the opposite
edge when counting its living neighbors. Visually, this means cells 'moving' past an edge will 
reappear on the opposite edge.

*/

#include <iostream>
#include <thread>

using namespace std;

const int s = 36; // side lengths of grid to print to console
const int max_its = 1000; // max # of generations to print
const bool randgrid = false; // randomize grid (overwrites below declaration)
const bool borderon = true; // true to turn off borderless grid

//bool grid[s][s] = {false};

// below instantiation will paste a glider generator at the top of the grid :o (s must be >36)
bool grid[s][s] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},};

void printgrid() {
    for (int y = 0; y < s; y++) {
        for (int x = 0; x < s; x++) {
            char c = (grid[y][x] ? '#' : '.');
            cout << c << c;
        }
        cout << endl;
    }
}

void progress() {
    bool copy[s][s] = {false};
    for (int y = 0; y < s; y++) {
        for (int x = 0; x < s; x++) {
            int neighbors = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i == 0 && j == 0) continue;
                    if (borderon) {
                        if (x+j < 0) continue;
                        if (x+j > (s-1)) continue;
                        if (y+i < 0) continue;
                        if (y+i > (s-1)) continue;
                    }
                    int px = x + j; // + j
                    int py = y + i; // + i
                    if (px < 0) px = (s-1);
                    if (px > (s-1)) px = 0;
                    if (py < 0) py = (s-1);
                    if (py > (s-1)) py = 0;
                    if (grid[py][px] == true) neighbors++;
                }
            }
            if (grid[y][x]) {
                if (neighbors > 3) {
                    copy[y][x] = false;
                } else if (neighbors < 2) {
                    copy[y][x] = false;
                } else {
                    copy[y][x] = true;
                }
            } else {
                if (neighbors == 3) {
                    copy[y][x] = true;
                }
            }
        }
    }
    for (int y = 0; y < s; y++) {
        for (int x = 0; x < s; x++) {
            grid[y][x] = copy[y][x];
        }
    }
}

int main(int argc, char * argv[]) {

    if (randgrid) {
        srand(time(0));
        for (int y = 0; y < s; y++) {
            for (int x = 0; x < s; x++) {
                grid[y][x] = rand() % 2 == 0;
            }
        }
    }

    printgrid();

    bool check[s][s];
    for (int y = 0; y < s; y++) {
        for (int x = 0; x < s; x++) {
            check[y][x] = grid[y][x];
        }
    }

    for (int i = 0; i < max_its; i++) {
        progress();

        bool duplicate = true;
        for (int y = 0; y < s && duplicate; y++) {
            for (int x = 0; x < s && duplicate; x++) {
                if (check[y][x] != grid[y][x]) duplicate = false;
            }
        }

        if (duplicate) {
            cout << "Grid has frozen!" << endl;
            break;
        } else {
            for (int y = 0; y < s; y++) {
                for (int x = 0; x < s; x++) {
                  check[y][x] = grid[y][x];
                }
            }
        }

        system("clear"); //system("CLS") on windows, clears terminal (easier to watch 'animation')
        cout << "Gen " << i << endl;
        printgrid();
        this_thread::sleep_for(200ms); // time to wait between generations
    }

}