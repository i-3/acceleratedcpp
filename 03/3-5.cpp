#include <algorithm>
using std::sort;

#include <vector>
using std::vector;

// #include <ios>
// #include <string>
#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::streamsize;
using std::string;

int main()
{
    cout
        << "Please enter your first name: ";
    string name;
    cin >> name;
    cout << "Enter four your homework grades: ";
    int count = 0;
    double sum = 0;
    double x;
    while (cin >> x && count != 3)
    {
        ++count;
        sum += x;
    }
    if (count == 0)
    {
        cout << endl
             << "You must enter your grades. "
                "Please try again."
             << endl;
        return 1;
    }
    vector<string> names;
    vector<double> grades;
    names.push_back(name);
    grades.push_back(sum / count);

    streamsize prec = cout.precision();
    cout << "Final grade of " << names[0] << " is " << setprecision(3)
         << grades[0]
         << setprecision(prec) << endl;
    return 0;
}