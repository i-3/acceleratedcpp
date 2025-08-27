#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <list>
using namespace std;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

bool space(char c)
{
    return isspace(c);
}
bool not_space(char c)
{
    return !isspace(c);
}
Rule split(const string &str)
{
    typedef string::const_iterator iter;
    Rule ret;
    iter i = str.begin();
    while (i != str.end())
    {
        i = find_if(i, str.end(), not_space);
        iter j = find_if(i, str.end(), space);
        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }
    return ret;
}
Grammar read_grammar(istream &in)
{
    Grammar ret;
    string line;
    while (getline(in, line))
    {
        Rule entry = split(line);
        if (!entry.empty())
            ret[entry[0]].push_back(
                Rule(entry.begin() + 1, entry.end()));
    }
    return ret;
}
bool bracketed(const string &s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}
int nrand(int n)
{
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");
    const int bucket_size = RAND_MAX / n;
    int r;
    do
        r = rand() / bucket_size;
    while (r >= n);
    return r;
}

void gen_aux(const Grammar &g, const string &word, Rule &ret)
{
    if (!bracketed(word))
        ret.push_back(word);
    else
    {
        Grammar::const_iterator it = g.find(word);
        if (it == g.end())
            throw logic_error("empty rule");
        const Rule_collection &c = it->second;
        const Rule &r = c[nrand(c.size())];
        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
            gen_aux(g, *i, ret);
    }
}
template <class Out>
Out gen_sentence(const Grammar &g, Out out)
{
    Rule ret;
    gen_aux(g, "<sentence>", ret);
    Rule::const_iterator it = ret.begin();
    while (it != ret.end())
        *out++ = *it++;
    return out;
}

// template <class Out>
// Out xref(istream &in, Out out, Rule find_words(const string &) = split)
// {
//     string line;
//     int line_number = 0;
//     map<string, vector<int>> ret;
//     while (getline(in, line))
//     {
//         ++line_number;
//         Rule words = find_words(line);
//         for (Rule::const_iterator it = words.begin(); it != words.end(); ++it)
//             if (find(ret[*it].begin(), ret[*it].end(), line_number) == ret[*it].end())
//                 ret[*it].push_back(line_number);
//     }
//     map<string, vector<int>>::const_iterator it = ret.begin();
//     while (it != ret.end())
//         *out++ = *it++;
//     return out;
// }

int main()
{
    srand(time(0));
    Grammar g = {{"<noun>", {{"cat"}, {"dog"}, {"table"}}},
                 {"<noun-phrase>", {{"<noun>"}, {"<adjective>", "<noun-phrase>"}}},
                 {"<adjective>", {{"large"}, {"brown"}, {"absurd"}}},
                 {"<verb>", {{"jumps"}, {"sits"}}},
                 {"<location>", {{"on", "the", "stairs"}, {"under", "the", "sky"}, {"wherever", "it", "wants"}}},
                 {"<sentence>", {{"the", "<noun-phrase>", "<verb>", "<location>"}}}};
    list<string> l = {"", "", "", "", "", "", "", ""};
    // gen_sentence(g, back_inserter(l));
    gen_sentence(g, l.begin());
    for (auto i : l)
        cout << i << " ";
    cout << endl;

    // map<string, vector<int>> ret;
    // xref(cin, inserter(ret, ret.begin()));
    // for (map<string, vector<int>>::const_iterator it = ret.begin();
    //      it != ret.end(); ++it)
    // {
    //     string str = it->second.size() == 1 ? " occurs on line " : " occurs on lines: ";
    //     cout << it->first << str;
    //     vector<int>::const_iterator line_it = it->second.begin();
    //     cout << *line_it;
    //     ++line_it;
    //     while (line_it != it->second.end())
    //     {
    //         cout << ", " << *line_it;
    //         ++line_it;
    //     }
    //     cout << endl;
    // }

    return 0;
}