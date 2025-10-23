#include <iostream>
int main()
{
    std::string str = "\n#include <iostream>;\nint main()\n{\nstd::string str = \"%s\";\nprintf(str.c_str(), str.c_str());\nreturn 0;\n}\n";
    printf(str.c_str(), str.c_str());
    return 0;
}