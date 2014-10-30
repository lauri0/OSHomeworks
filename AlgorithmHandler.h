#ifndef ALGORITHMHANDLER_H
#define ALGORITHMHANDLER_H

#include <string>
#include <vector>
#include <QString>
#include <sstream>

using std::string;
using std::vector;

class AlgorithmHandler
{
public:
    AlgorithmHandler();

    QString getTask1();
    QString getTask2();
    QString getTask3();
    QString getTask4();

    vector<string> split(string &s, char delim, vector<string> &elems);
    vector<string> split(string &s, char delim);
    vector< vector<int> > toVec(string input);
    vector< vector<int> > getTaskVector();
    void setTaskVector(string input);

private:
    string task1;
    string task2;
    string task3;
    string task4;

    vector< vector<int> > taskVector;

};

#endif // ALGORITHMHANDLER_H
