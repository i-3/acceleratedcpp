#include <iostream>
using namespace std;

int nrand(int n)
{
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");
    const int bucket_size = RAND_MAX / n;
    int r;
    do
    {
        r = rand() / bucket_size;
    } while (r >= n);
    return r;
}

int main()
{
    srand(time(0));
    int n = 2147483647;
    int r = nrand(n);
    cout << RAND_MAX << endl
         << r << endl;
    return 0;
}