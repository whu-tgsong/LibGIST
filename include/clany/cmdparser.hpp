#ifndef CMDPARSER_HPP
#define CMDPARSER_HPP

#include <vector>
#include <sstream>
#include <algorithm>
#include "clany_macros.h"

_CLANY_BEGIN
class CmdLineParser
{
public:
    CmdLineParser(int argc, const char* const argv[]) :args(argc - 1, "")
    {
        for (int i = 1; i < argc; ++i) {
            args[i-1] = argv[i];
        }
    }

    template<typename T>
    T parse(const string& name) const
    {
        string arg_name = "--" + name + "=";
        auto iter = find_if(args.begin(), args.end(), [&arg_name](const string& arg) {
            return arg.find(arg_name) != string::npos;
        });

        istringstream ss(iter->substr(iter->find("=") + 1));
        T value;
        ss >> value;
        return value;
    }



private:
    vector<string> args;
};
_CLANY_END

#endif // __CMDPARSER_HPP__