#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <string>
#include <vector>
#include <boost/locale.hpp>
#include "pystring.h"
using namespace std;
namespace fs = boost::filesystem;

class CSV
{
public:
    ofstream _of;

    CSV(const string &filename, const vector<string> &headers)
    {
        if (!fs::exists(fs::path(filename.c_str())))
        {
            _of = ofstream(filename, ios::trunc);
            string line = pystring::join(",", headers);
            line.append("\n");
            _of << boost::locale::conv::between(line, "GBK", "UTF-8");
        }
        else
            _of = ofstream(filename, ios::app);
    }
    CSV(const string &filename, const char *header)
    {
        if (!fs::exists(fs::path(filename.c_str())))
        {
            _of = ofstream(filename, ios::trunc);
            _of << boost::locale::conv::between(header, "GBK", "UTF-8");
            _of << "\n";
        }
        else
            _of = ofstream(filename, ios::app);
    }

    ~CSV()
    {
        _of.close();
    }
    void back()
    {
        int here = _of.tellp();
        _of.seekp((here - 1));
    }
    template <typename T, typename... Args>
    void write(const T *format_str, const Args &...param)
    {
        string row = format(format_str, param...);
        _of << boost::locale::conv::between(row, "GBK", "UTF-8");
    }

    template <typename T>
    ostream &operator<<(T a)
    {
        _of << a;
        return _of;
    }

    template <typename T, typename... Args>
    static string format(const T *format_str, const Args &...param)
    {

        char buf[256];
        sprintf(buf, format_str, param...);
        return buf;
    }
};