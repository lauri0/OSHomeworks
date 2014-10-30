#include "AlgorithmHandler.h"

using namespace std;

AlgorithmHandler::AlgorithmHandler()
{
    task1 = "0,10;4,5;12,4";
    task2 = "0,5;1,6;3,4";
    task3 = "5,2;5,7;5,10";
    task4 = "";

    setTaskVector(task1);
}

QString AlgorithmHandler::getTask1()
{
    return QString::fromStdString(task1);
}

QString AlgorithmHandler::getTask2()
{
    return QString::fromStdString(task2);
}

QString AlgorithmHandler::getTask3()
{
    return QString::fromStdString(task3);
}

QString AlgorithmHandler::getTask4()
{
    return QString::fromStdString(task4);
}

vector<string> AlgorithmHandler::split(string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

vector<string> AlgorithmHandler::split(string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

vector< vector<int> > AlgorithmHandler::toVec(string input)
{
    vector<string> parts;
    parts = split(input, ';');
    vector< vector<int> > output;
    for (string part : parts)
    {
        vector<string> smallerParts;
        smallerParts = split(part, ',');
        int arrival = atoi(smallerParts[0].c_str());
        int duration = atoi(smallerParts[1].c_str());

        vector<int> intParts;
        intParts.push_back(arrival);
        intParts.push_back(duration);

        output.push_back(intParts);
    }

    return output;
}

vector< vector<int> > AlgorithmHandler::getTaskVector()
{
    return taskVector;
}

void AlgorithmHandler::setTaskVector(string input)
{
    taskVector = toVec(input);
}
