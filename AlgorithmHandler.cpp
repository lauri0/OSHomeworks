#include "AlgorithmHandler.h"

using namespace std;

AlgorithmHandler::AlgorithmHandler()
{
    task1 = "0,10;4,5;12,4";
    task2 = "0,5;7,6;8,4";
    task3 = "6,2;3,7;4,10";
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

vector< vector<int> > AlgorithmHandler::getTaskVector()
{
    return taskVector;
}

void AlgorithmHandler::setTaskVector(string input)
{
    taskVector = toVec(input);
}

int AlgorithmHandler::getAverageWaitingTime()
{
    return averageWaitingTime;
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

vector< vector<string> > AlgorithmHandler::FCFS(vector< vector<int> > inputVector)
{
    vector< vector<string> > output;
    // The number of the current process
    int counter = 1;
    // Where the process manager currently is
    int trace = 0;
    int totalWait = 0;

    // Vector is sorted
    std::sort(inputVector.begin(), inputVector.end(), [](std::vector<int> a, std::vector<int> b)
    {
        return a[0] < b[0];
    });

//    cout << inputVector[0][0];
//    cout << "\n";

    for (vector<int> task : inputVector)
    {
        int arrival = task[0];
        int duration = task[1];

        // If there is a hole between two processes a space with the right length will be added to the vector
        if (arrival > trace)
        {
            vector<string> spaceVector;
            spaceVector.push_back(" ");
            spaceVector.push_back(to_string(arrival - trace));
            output.push_back(spaceVector);

            vector<string> processVector;
            processVector.push_back("P" + to_string(counter));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace = arrival + duration;

            counter += 1;
        }
        else
        {
            // Check for how long the process had to wait
            if (arrival < trace)
            {
                totalWait += trace - arrival;
            }
            vector<string> processVector;
            processVector.push_back("P" + to_string(counter));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace += duration;

            counter += 1;
        }
    }
    // Calculate average waiting time
    averageWaitingTime = totalWait / output.size();
    cout << averageWaitingTime;
    cout << "\n";

    return output;
}
