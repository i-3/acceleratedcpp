#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    cout
        << "Please enter your first name: ";
    string name;
    cin >> name;
    const string greeting = "Hello, " + name + "!";

    cout
        << "Please enter the number of blanks: ";
    int pad;
    cin >> pad;

    const int rows = pad * 2 + 3;
    const string::size_type cols = greeting.size() + pad * 2 + 2;
    cout << endl;

    for (int r = 0; r != rows; ++r)
    {
        {
            if (r == pad + 1)
            {
                string spaces(pad, ' ');
                cout
                    << "*" + spaces + greeting + spaces + "*";
            }
            else
            {
                if (r == 0 || r == rows - 1)
                {
                    string stars(cols, '*');
                    cout << stars;
                }
                else
                {
                    string spaces(cols - 2, ' ');
                    cout << "*" + spaces + "*";
                }
            }
        }
        cout << endl;
    }
    return 0;
}