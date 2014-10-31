#ifndef ALGORITHMHANDLER_H
#define ALGORITHMHANDLER_H

#include <string>
#include <vector>
#include <QString>
#include <sstream>
#include <iostream>

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

    vector< vector<int> > getTaskVector();
    void setTaskVector(string input);
    double getAverageWaitingTime();
    string getCurrentAlgorithm();
    void setCurrentAlgorithm(string algorithm);

    vector<string> split(string &s, char delim, vector<string> &elems);
    vector<string> split(string &s, char delim);
    vector< vector<int> > toVec(string input);

    vector< vector<string> > FCFS(vector< vector<int> > inputVector);
    vector< vector<string> > SJF(vector< vector<int> > inputVector);

    vector< vector<string> > getCorrectProcessVector();

private:
    string task1;
    string task2;
    string task3;
    string task4;
    string currentAlgorithm;

    double averageWaitingTime;

    vector< vector<int> > taskVector;

};

#endif // ALGORITHMHANDLER_H
