#ifndef __CSVHPP_
#define __CSVHPP_

#define CONCATENATE(arg1, arg2) CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2

#define FOR_EACH_1(what, x) \
    what[#x] = x

#define FOR_EACH_2(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_1(what, __VA_ARGS__);

#define FOR_EACH_3(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_2(what, __VA_ARGS__);

#define FOR_EACH_4(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_3(what, __VA_ARGS__);

#define FOR_EACH_5(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_4(what, __VA_ARGS__);

#define FOR_EACH_6(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_5(what, __VA_ARGS__);

#define FOR_EACH_7(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_6(what, __VA_ARGS__);

#define FOR_EACH_8(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_7(what, __VA_ARGS__);
#define FOR_EACH_8(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_7(what, __VA_ARGS__);
#define FOR_EACH_9(what, x, ...) \
    what[#x] = x;                \
    FOR_EACH_8(what, __VA_ARGS__);
#define FOR_EACH_10(what, x, ...) \
    what[#x] = x;                 \
    FOR_EACH_9(what, __VA_ARGS__);

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define FOR_EACH_RSEQ_N() 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, ...) \
    CONCATENATE(FOR_EACH_, N)   \
    (what, __VA_ARGS__)
#define REGIESTER(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/locale.hpp>
#include "pystring.h"
using namespace std;
namespace fs = boost::filesystem;

union Data
{
    int iv;
    double dv;
    float fv;
    char *sv;
};
class Val
{
public:
    Data d;
    const char *_type;
    Val()
    {
    }
    Val(int i)
    {
        d.iv = i;
        _type = "int";
    }
    Val(double dv)
    {
        d.dv = dv;
        _type = "double";
    }
    Val(float f)
    {
        d.fv = f;
        _type = "float";
    }
    Val(char *str)
    {
        d.sv = str;
        _type = "string";
    }
    Val(string &str)
    {
        d.sv = (char *)str.c_str();
        _type = "string";
    }
    string Get()
    {
        if (strcmp(_type,"string")==0)
            return d.sv;
        if (strcmp(_type,"int")==0)
            return to_string(d.iv);
        if (strcmp(_type , "float")==0)
            return to_string(d.fv);
        if (strcmp(_type ,"double")==0)
            return to_string(d.dv);
    }
};

class CSV
{
public:
    ofstream _of;
    string _sep = ",";
    unordered_map<string, Val> _vmap;
    CSV(const string &filename, const vector<string> &headers, const string &sep = ",") : _sep(sep)
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
    CSV(const string &filename, const char *header, const string sep = ",") : _sep(sep)
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

    void set_sep(const string &sep)
    {
        _sep = sep;
    }

    void back()
    {
        int here = _of.tellp();
        _of.seekp((here - 1));
    }
    string format_fstring(string &fstring)
    {
        vector<string> vlst;
        pystring::split(fstring, vlst, _sep);
        string row = "";
        for (auto &v : vlst)
        {
            if (v.find("{") != v.npos)
            {
                string key = pystring::strip(v, "{}");
                auto val = _vmap[key];
                row += val.Get();
                row += _sep;
            }
            else
            {
                row += v;
                row += _sep;
            }
        }
        row.pop_back();
        return row;
    }
    template <typename T,typename... Args>
    void write(const T* _format_str, const Args &...param)
    {
        string fstring(_format_str);
        string row;
        if (fstring.find("{") != string::npos && fstring.find("}") != string::npos)
        {
            row = format_fstring(fstring);
        }
        else
        {
            row = format(_format_str, param...);
        }
        _of << boost::locale::conv::between(row, "GBK", "UTF-8");
    }

    template <typename T, typename... Args>
    static string format(const T *format_str, const Args &...param)
    {

        char buf[256];
        sprintf(buf, format_str, param...);
        return buf;
    }
};
#endif