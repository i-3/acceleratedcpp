#include <iomanip>
using std::setw;
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main()
{
    double end = 101;
    for (double i = 1; i != end; ++i)
    {
        cout << setw(std::to_string(end).length() - 7)
             << i << ' ' << i * i << endl;
    }
    return 0;
}