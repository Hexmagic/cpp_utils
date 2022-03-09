#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include "csv.hpp"
using namespace std;
void func(string &a, const vector<string> &b)
{
    for (auto &e : b)
        cout << e << endl;
}
int main()
{
    vector<string> header = {"name", "age"};
    string name = "test2.csv";
    CSV c1(name, {"name", "age"});
    c1.write("Hello %s yor are %d %s %f", "放辣椒", 2, "fef", 4.8);
    c1.write("Hello %s yor are %d %s %d\n", "放辣椒", 2, "dfj", 4.8);
    c1 << 1 << ","
       << "fef." << 4.3 << std::endl;
    
}