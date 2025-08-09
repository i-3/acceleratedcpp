#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
int main()
{
    const int rows = 4;
    for (int r = 0; r != rows; ++r)
    {
        string row(rows * 2.25, '*');
        cout << row << endl;
    }
    cout << endl;
    for (int r = 0; r != rows; ++r)
    {
        string row(rows * 5, '*');
        cout << row << endl;
    }
    cout << endl;
    for (int r = 0; r != rows; ++r)
    {
        string spaces((rows - r - 1) * 2, ' ');
        string stars(r * 4 + 1, '*');
        cout << spaces + stars << endl;
    }
    return 0;
}