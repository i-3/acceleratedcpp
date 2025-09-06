#include <fstream>
#include <iostream>
using namespace std;

// int main()
// {
//     ifstream infile("in");
//     ofstream outfile("out");
//     string s;
//     while (getline(infile, s))
//         outfile << s << endl;
//     return 0;
// }

int main(int argc, char **argv)
{
    int fail_count = 0;
    for (int i = 1; i < argc; ++i)
    {
        ifstream in(argv[i]);
        if (in)
        {
            string s;
            while (getline(in, s))
                cout << s << endl;
        }
        else
        {
            cerr << "cannot open file " << argv[i] << endl;
            ++fail_count;
        }
    }
    return fail_count;
}