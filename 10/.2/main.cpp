#include <iostream>
using namespace std;

const char hello[] = {'H', 'e', 'l', 'l', 'o', '\0'};
size_t strlen(const char *p)
{
    size_t size = 0;
    while (*p++ != '\0')
        ++size;
    return size;
}
// string s(hello);
// string s("Hello");
string s(hello, hello + strlen(hello));

int main()
{

    cout << "strlen('Hello') = " << strlen("Hello") << endl;

    return 0;
}