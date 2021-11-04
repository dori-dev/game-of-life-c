#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void draw(void *u, int w, int h)
{
    char(*world)[w] = u;
    printf("\033[H");
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            printf(world[x][y] ? "■" : " ");
        }
        printf("\n");
    }
}

void evaluation(void *u, int w, int h)
{
    char(*world)[w] = u;
    char new[w][h];
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int lives = 0;
            for (int xr = x - 1; xr <= x + 1; xr++)
            {
                for (int yr = y - 1; yr <= y + 1; yr++)
                {
                    if (world[(xr + w) % w][(yr + h) % h])
                    {
                        lives++;
                    }
                }
            }
            if (world[x][y])
            {
                lives--;
            }
            if (lives == 3)
            {
                new[x][y] = 1;
            }
            else if (lives == 2 && world[x][y] == 1)
            {
                new[x][y] = 1;
            }
            else
            {
                new[x][y] = 0;
            }
        }
    }
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            world[x][y] = new[x][y];
        }
    }
}

int main()
{
    srand(time(0));
    int w = 30;
    int h = 50;
    int time = 500000;
    char world[w][h];
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            world[x][y] = rand() < RAND_MAX / 5 ? 1 : 0;
        }
    }
    while (1)
    {
        draw(world, w, h);
        evaluation(world, w, h);
        usleep(time);
    }

    return 0;
}
