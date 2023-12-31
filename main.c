#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// For Windows
#ifdef _WIN32
#include <windows.h>
#endif

#define HEIGHT 30
#define WIDTH 30

float grid[HEIGHT][WIDTH] = {0};
float nextGrid[HEIGHT][WIDTH] = {0};

char level[] = {'.', '#'};

float rand_float(void) {
    return (float)rand() / (float)RAND_MAX;
}

void initializeGrid(void) {
    for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            float num = rand_float();
            grid[y][x] = (num > 0.5) ? 1 : 0;
        }
    }
}

void display(void) {
    for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            int index = (grid[y][x] > 0.5) ? 1 : 0;
            printf("%c ", level[index]);
        }
        printf("\n");
    }
}

void displayValue(void) {
    for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            printf("%f ", grid[y][x]);
        }
        printf("\n");
    }
}


bool isValid(int x, int y) {
    return x>=0 && x<WIDTH && y>=0 && y<HEIGHT;
}

int countNeighbors(int x, int y) {
    int count = 0;
    for (int dy=-1; dy<=1; ++dy) {
        for (int dx=-1; dx<=1; ++dx) {
            if (dx==0 && dy==0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (isValid(nx, ny) && grid[ny][nx]==1) {
                count++;
            }
        }   
    }
    return count;
}

void nextStep(void) {
    for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            int count = countNeighbors(x, y);
            if (count==2 || count==3) {
                nextGrid[y][x]=1;
            } else if (count>3) {
                nextGrid[y][x]=0;
            } else if (grid[y][x]==0 && count==3) {
                nextGrid[y][x]=1;
            } else if (count<2) {
                nextGrid[y][x]=0;
            }
        }
    }
    // change values loop
    for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            grid[y][x] = nextGrid[y][x];
            nextGrid[y][x] = 0;
        }
    }
}


int main() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    srand(time(0));
    initializeGrid();
    display();
    
    for(;;) {
    
        // Add a delay of 1000 milliseconds (1 second)
        #ifdef _WIN32
            Sleep(1000);
        #else
            // For other platforms, you can use usleep
            usleep(1000000);
        #endif
        
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        nextStep();
        display();
        
    }
    
    // bool res = isValid(0,3);
    // printf("is valid: %d\n", res);
    // int count = countNeighbors(0,0);
    // printf("count: %d\n", count);
    // int count2 = countNeighbors(1,1);
    // printf("count2: %d\n", count2);


    return 0;
}
