// Developed by Kushal Pathak
#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#define pixel '*'
#define height 49
#define width 105
#define pi 3.1415926
using namespace std;

struct Point
{
    int x, y, z;
};

struct Cube
{
    Point p[8];
};

char matrix[height][width];

void maximizeWindow();                                 // maximizes console window
void init();                                           // initializes matrix with whitespace character
void display();                                        // displays matrix content in the console window
void putpixel(int, int);                               // puts a pixel in the matrix
void putpixelo(int, int);                              // to put a brighter pixel at a given point (vertex)
void line(int, int, int, int);                         // puts pixels of a line in the matrix
Point projection(Point);                               // for projection, not really useful here
Point rotateX(Point, int, int, float);                 // rotates a vector3 along x axis
Point rotateY(Point, int, int, float);                 // rotates a vector3 along y axis
Point rotateZ(Point, int, int, float);                 // rotates a vector3 along z axis
Point rotate(int, int, int, int, float);               // rotates (x,y) about (h,k) by a given angle
Cube make_cube(int, int, int, int);                    // returns a cube and takes in starting point (x1,y1,z1) and its length l as parameters
void connect_points(Point, Point);                     // connects two vector3 points to create a line
void render_cube(Cube);                                // connects all the vetrices of the cube by creating edges
void delay(float);                                     // to create time delay
Point compound_rotation(Point, int, int, int, double); // does rotation along all 3 axes

int main()
{
    // maximize the console window
    maximizeWindow();
    cout << "3D CUBE ANIMATION BY KUSHAL PATHAK\nPress any key to start";
    getch();

    Cube c = make_cube(42, 14, 10, 23); // make a cube starting at (x1,y1,z1) with length l
    Cube c1 = c;                        // copy c into c1

    // starting angle
    int angle = 0;

    // Loop to draw cube
    while (1)
    {
        init(); // reset matrix before each render
        render_cube(c);
        display();
        // delay(10); // to slow down animation
        for (int j = 0; j < 8; j++)
            c.p[j] = compound_rotation(c1.p[j], 52, 24, 24, angle); // performing rotation on cube c1 and updating cube c

        // increment angle in each iteration
        angle += 5;
    }
    return 0;
}

Cube make_cube(int x1, int y1, int z1, int l)
{
    Cube c;
    c.p[0].x = x1;
    c.p[0].y = y1;
    c.p[0].z = z1;
    c.p[1].x = x1 + l;
    c.p[1].y = y1;
    c.p[1].z = z1;
    c.p[2].x = c.p[1].x;
    c.p[2].y = y1 + l;
    c.p[2].z = z1;
    c.p[3].x = x1;
    c.p[3].y = c.p[2].y;
    c.p[3].z = z1;
    c.p[4].x = x1;
    c.p[4].y = y1;
    c.p[4].z = z1 + l;
    c.p[5].x = c.p[1].x;
    c.p[5].y = y1;
    c.p[5].z = c.p[4].z;
    c.p[6].x = c.p[1].x;
    c.p[6].y = c.p[2].y;
    c.p[6].z = c.p[4].z;
    c.p[7].x = x1;
    c.p[7].y = c.p[2].y;
    c.p[7].z = c.p[4].z;
    return c;
}
void render_cube(Cube c)
{
    connect_points(c.p[0], c.p[1]);
    connect_points(c.p[1], c.p[2]);
    connect_points(c.p[2], c.p[3]);
    connect_points(c.p[3], c.p[0]);
    connect_points(c.p[4], c.p[5]);
    connect_points(c.p[5], c.p[6]);
    connect_points(c.p[6], c.p[7]);
    connect_points(c.p[7], c.p[4]);
    connect_points(c.p[0], c.p[4]);
    connect_points(c.p[1], c.p[5]);
    connect_points(c.p[2], c.p[6]);
    connect_points(c.p[3], c.p[7]);
}

Point compound_rotation(Point p, int h, int k, int w, double a)
{
    a = (pi / 180) * a;
    double s = sin(a), c = cos(a), s2 = s * s, c2 = c * c;
    int dx = p.x - h, dy = p.y - k, dz = p.z - w;
    p.x = round(dx * c2 + dy * s2 * c - dy * c * s + dz * c2 * s + dz * s2) + h;
    p.y = round(dx * c * s + dy * s2 * s + dy * c2 + dz * c * s2 - dz * s * c) + k;
    p.z = round(-dx * s + dy * s * c + dz * c2) + w;
    return p;
}

void connect_points(Point p1, Point p2)
{
    line(p1.x, p1.y, p2.x, p2.y);
}

Point rotateZ(Point p, int h, int k, float angle)
{
    angle = (pi / 180) * angle;
    int dx = p.x - h, dy = p.y - k;
    p.x = round(dx * cos(angle) - dy * sin(angle) + h);
    p.y = round(dx * sin(angle) + dy * cos(angle) + k);
    return p;
}
Point rotateX(Point p, int h, int k, float angle)
{
    angle = (pi / 180) * angle;
    int dy = p.y - h, dz = p.z - k;
    p.y = round(dy * cos(angle) - dz * sin(angle) + h);
    p.z = round(dy * sin(angle) + dz * cos(angle) + k);
    return p;
}
Point rotateY(Point p, int h, int k, float angle)
{
    angle = (pi / 180) * angle;
    int dx = p.x - h, dz = p.z - k;
    p.x = round(dx * cos(angle) + dz * sin(angle) + h);
    p.z = round(-dx * sin(angle) + dz * cos(angle) + k);
    return p;
}
Point rotate(int x, int y, int h, int k, float a)
{
    Point p;
    int dx = x - h, dy = y - k;
    a = (pi / 180) * a;
    p.x = round(dx * cos(a) - dy * sin(a)) + h;
    p.y = round(dx * sin(a) + dy * cos(a)) + k;
    p.z = 0;
    return p;
}

void line(int x1, int y1, int x2, int y2) // Bresenham's line drawing algorithm
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int e1 = dx - dy;
    while (true)
    {
        putpixel(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * e1;
        if (e2 > -dy)
        {
            e1 -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            e1 += dx;
            y1 += sy;
        }
    }
}

void putpixel(int x, int y)
{
    if (x > width - 1)
        x = x % width;
    if (x < 0)
        x = (x % width) + width;
    if (y > height - 1)
        y = y % height;
    if (y < 0)
        y = (y % height) + height;
    matrix[y][x] = pixel;
}

void putpixelo(int x, int y)
{
    if (x > width - 1)
        x = x % width;
    if (x < 0)
        x = (x % width) + width;
    if (y > height - 1)
        y = y % height;
    if (y < 0)
        y = (y % height) + height;
    matrix[y][x] = '@';
}

void maximizeWindow()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

void display()
{
    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
}

void init()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            matrix[i][j] = ' ';
    }
}

Point projection(Point p)
{
    p.z = 0;
    return p;
}

void delay(float n)
{
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
            for (int k = 0; k < n * 100; k++)
                ;
    }
}
