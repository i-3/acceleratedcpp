#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
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
// void gen_aux(const Grammar &g, const string &word, Rule &ret)
// {
//     if (!bracketed(word))
//     {
//         ret.push_back(word);
//     }
//     else
//     {
//         Grammar::const_iterator it = g.find(word);
//         if (it == g.end())
//             throw logic_error("empty rule");
//         const Rule_collection &c = it->second;
//         const Rule &r = c[nrand(c.size())];
//         for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
//             gen_aux(g, *i, ret);
//     }
// }
Rule gen_sentence(const Grammar &g)
{
    Rule ret;
    Rule stack;
    // gen_aux(g, "<noun-phrase>", ret);
    stack.push_back("<sentence>");

    while (!stack.empty())
    {
        string s = stack.back();
        // cout << s << endl;
        if (!bracketed(s))
        {
            ret.push_back(s);
            stack.pop_back();
            if (bracketed(stack.back()) && stack.back() != "<noun-phrase>")
                stack.pop_back();
            if (stack.back() == "<sentence>")
                stack.pop_back();
        }
        else
        {
            if (s == "<noun-phrase>")
                stack.pop_back();
            Grammar::const_iterator it = g.find(s);
            if (it == g.end())
                throw logic_error("empty rule");
            const Rule_collection &c = it->second;
            const Rule &r = c[nrand(c.size())];
            // for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
            //     gen_aux(g, *i, ret);
            for (auto it = r.rbegin(); it != r.rend(); ++it)
                stack.push_back(*it);
        }
    }
    return ret;
}

int main()
{
    // Rule sentence = gen_sentence(read_grammar(cin));
    srand(time(0));
    Grammar g = {{"<noun>", {{"cat"}, {"dog"}, {"table"}}},
                 {"<noun-phrase>", {{"<noun>"}, {"<adjective>", "<noun-phrase>"}}},
                 {"<adjective>", {{"large"}, {"brown"}, {"absurd"}}},
                 {"<verb>", {{"jumps"}, {"sits"}}},
                 {"<location>", {{"on", "the", "stairs"}, {"under", "the", "sky"}, {"wherever", "it", "wants"}}},
                 {"<sentence>", {{"the", "<noun-phrase>", "<verb>", "<location>"}}}};
    Rule sentence = gen_sentence(g);
    Rule::const_iterator it = sentence.begin();
    if (!sentence.empty())
    {
        cout << *it;
        ++it;
    }
    while (it != sentence.end())
    {
        cout << " " << *it;
        ++it;
    }
    cout << endl;
    return 0;
}