#include "util.h"

vector<string> Util::splitString(string buffer, char delim)
{
    vector<string> split;

    size_t begin, end;
    begin = buffer.find_first_not_of(delim);
    end = buffer.find_first_of(delim, begin);

    while (begin != end) {
        split.push_back(buffer.substr(begin, end - begin));
        begin = buffer.find_first_not_of(delim, end);
        end = buffer.find_first_of(delim, begin);
    }

    return split;
}
