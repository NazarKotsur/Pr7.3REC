#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Input(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex);
void Print(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex);
int Part1_Count(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex);
void Part2_SaddlePoint(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex);
bool IsMaxInRowN(int** a, const int n, const int k, const int colCount, int currentMax, int colIndex);
bool IsMinInColK(int** a, const int n, const int k, const int rowCount, int currentMin, int rowIndex);

int main()
{
    srand((unsigned)time(NULL));

    int Low = -17;
    int High = 15;
    int rowCount, colCount;

    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    //Input(a, rowCount, colCount, 0, 0);
    Print(a, rowCount, colCount, 0, 0);

    int sum = Part1_Count(a, rowCount, colCount, 0, 0);
    if (sum > 0)
        cout << "Sum = " << sum << endl;
    else
        cout << "There are no negative elements" << endl;
    cout << endl;

    Part2_SaddlePoint(a, rowCount, colCount, 0, 0);
    cout << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High)
{
    if (rowCount <= 0 || colCount <= 0)
        return;

    a[rowCount - 1][colCount - 1] = Low + rand() % (High - Low + 1);
    Create(a, rowCount, colCount - 1, Low, High);
    Create(a, rowCount - 1, colCount, Low, High);
}

void Input(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex)
{
    if (rowIndex >= rowCount)
        return;

    if (colIndex < colCount)
    {
        cout << "a[" << rowIndex << "][" << colIndex << "] = ";
        cin >> a[rowIndex][colIndex];
        Input(a, rowCount, colCount, rowIndex, colIndex + 1);
    }
    else
    {
        Input(a, rowCount, colCount, rowIndex + 1, 0);
    }
}

void Print(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex)
{
    if (rowIndex >= rowCount)
        return;

    if (colIndex < colCount)
    {
        cout << setw(4) << a[rowIndex][colIndex];
        Print(a, rowCount, colCount, rowIndex, colIndex + 1);
    }
    else
    {
        cout << endl;
        Print(a, rowCount, colCount, rowIndex + 1, 0);
    }
}

int Part1_Count(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex)
{
    if (rowIndex >= rowCount)
        return 0;

    if (colIndex < colCount)
    {
        if (a[rowIndex][colIndex] < 0)
            return Part1_Count(a, rowCount, colCount, rowIndex, colIndex + 1);
        else
            return a[rowIndex][colIndex] + Part1_Count(a, rowCount, colCount, rowIndex, colIndex + 1);
    }
    else
    {
        return Part1_Count(a, rowCount, colCount, rowIndex + 1, 0);
    }
}

void Part2_SaddlePoint(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex)
{
    if (rowIndex >= rowCount)
        return;

    if (colIndex < colCount)
    {
        if (IsMaxInRowN(a, rowIndex, colIndex, colCount, a[rowIndex][colIndex], colIndex) &&
            IsMinInColK(a, rowIndex, colIndex, rowCount, a[rowIndex][colIndex], rowIndex))
        {
            cout << setw(4) << "(" << rowIndex << ", " << colIndex << ")" << endl;
        }
        Part2_SaddlePoint(a, rowCount, colCount, rowIndex, colIndex + 1);
    }
    else
    {
        Part2_SaddlePoint(a, rowCount, colCount, rowIndex + 1, 0);
    }
}

bool IsMaxInRowN(int** a, const int n, const int k, const int colCount, int currentMax, int colIndex)
{
    if (colIndex >= colCount)
        return true;

    if (a[n][colIndex] > currentMax)
        currentMax = a[n][colIndex];

    return IsMaxInRowN(a, n, k, colCount, currentMax, colIndex + 1);
}

bool IsMinInColK(int** a, const int n, const int k, const int rowCount, int currentMin, int rowIndex)
{
    if (rowIndex >= rowCount)
        return true;

    if (a[rowIndex][k] < currentMin)
        currentMin = a[rowIndex][k];

    return IsMinInColK(a, n, k, rowCount, currentMin, rowIndex + 1);
}
