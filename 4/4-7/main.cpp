#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<double> numbers;
    double n;
    cout << "please enter numbers:" << endl;
    while (cin >> n)
    {
        numbers.push_back(n);
    }
    double sum;
    for (vector<double>::size_type i = 0;
         i != numbers.size(); ++i)
    {
        sum += numbers[i];
    }
    cout << "average - " << sum / numbers.size() << endl;

    // double d = f()[n];

    return 0;
}