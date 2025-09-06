#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout
        << "Please enter first number: ";
    int num1;
    cin >> num1;

    cout
        << "Please enter second number: ";
    int num2;
    cin >> num2;
    cout << endl;
    if (num1 < num2)
        std::cout << "Second number is larger than the first!" << std::endl;
    if (num1 == num2)
        std::cout << "The numbers are equal!" << std::endl;
    if (num1 > num2)
        std::cout << "First number is larger than the second!" << std::endl;
    return 0;
}