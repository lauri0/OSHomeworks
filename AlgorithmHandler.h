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
    vector< vector<string> > getCorrectProcessVector();

    vector<string> split(string &s, char delim, vector<string> &elems);
    vector<string> split(string &s, char delim);
    vector< vector<int> > toVec(string input);

    vector< vector<string> > FCFS(vector< vector<int> > inputVector);
    vector< vector<string> > SJF(vector< vector<int> > inputVector);
    vector< vector<string> > RR(vector< vector<int> > inputVector);
    vector< vector<string> > ML(vector< vector<int> > inputVector);

    int calculateWaitFromOutputVector(vector< vector<string> > oVector, int pid, int trace, int arrival);


private:
    string task1;
    string task2;
    string task3;
    string task4;
    string currentAlgorithm;

    double averageWaitingTime;
    int timeQuantumRR;
    int timeQuantumML0;
    int timeQuantumML1;

    vector< vector<int> > taskVector;

};

#endif // ALGORITHMHANDLER_H
