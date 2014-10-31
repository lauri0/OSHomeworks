#include "AlgorithmHandler.h"

using namespace std;

AlgorithmHandler::AlgorithmHandler()
{
    task1 = "0,10;4,5;12,4";
    task2 = "0,5;7,6;8,4";
    task3 = "6,2;3,7;4,10";
    task4 = "";

    currentAlgorithm = "FCFS";

    averageWaitingTime = 0.0;

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

double AlgorithmHandler::getAverageWaitingTime()
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

// First come first served
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
//    cout << totalWait << "..." << inputVector.size() << "\n";
    averageWaitingTime = (double)totalWait / (double)inputVector.size();
    cout << to_string(totalWait) << " " << to_string(inputVector.size()) << " ";
    cout << to_string(averageWaitingTime) << "\n";
    return output;
}

// Shortest job first
vector< vector<string> > AlgorithmHandler::SJF(vector< vector<int> > inputVector)
{
    // The number of processes
    int numElems = inputVector.size();
    // Every subvector is given a third element, the process number in the order the processes come in(1, 2, 3, ...)

    vector< vector<string> > output1;
    // Where the process manager currently is
    int trace = 0;
    int totalWait = 0;

    // Vector is sorted by start times
    std::sort(inputVector.begin(), inputVector.end(), [](std::vector<int> a, std::vector<int> b)
    {
        return a[0] < b[0];
    });

    // The number of the process is added to every subvector
    for (int i = 0; i < numElems; i++)
    {
        inputVector[i].push_back(i + 1);
    }


    for (int i = 0; i < numElems * 2; i++)
    {
        vector< vector<int> > currentWaiting;
        for (int j = 0; j < numElems; j++)
        {
            if (inputVector[j][0] <= trace && inputVector[j][2] != 999)
            {
                currentWaiting.push_back(inputVector[j]);
            }
        }
        // The shortest process is found from the waiting processes
        if (currentWaiting.size() >= 1){
            std::sort(currentWaiting.begin(), currentWaiting.end(), [](std::vector<int> a, std::vector<int> b)
            {
                return a[1] < b[1];
            });
            int addedProcessNum = currentWaiting[0][2] - 1;
            vector<string> processVector;
            processVector.push_back("P" + to_string(addedProcessNum + 1));
            processVector.push_back(to_string(currentWaiting[0][1]));
            output1.push_back(processVector);

            inputVector[addedProcessNum][2] = 999;

            totalWait += trace - currentWaiting[0][0];
            trace += currentWaiting[0][1];
        }
        // Finds how long the required pause is and adds that to the output vector
        if (currentWaiting.size() == 0)
        {
            int earliestArrival = 1000;
            for (int k = 0; k < numElems; k++)
            {
                if (inputVector[k][0] < earliestArrival && inputVector[k][2] != 999)
                {
                    earliestArrival = inputVector[k][0];
                }
            }
            if (earliestArrival != 1000)
            {
                vector<string> spaceVector;
                spaceVector.push_back(" ");
                spaceVector.push_back(to_string(earliestArrival - trace));
                output1.push_back(spaceVector);

                trace += earliestArrival - trace;
            }
        }
    }
    // Calculate average waiting time
    cout << to_string(totalWait);
    averageWaitingTime = (double)totalWait / (double)output1.size();

    return output1;
}

vector< vector<string> > AlgorithmHandler::getCorrectProcessVector()
{
    vector< vector<string> > correctVector;
    if (currentAlgorithm == "FCFS")
    {
        correctVector = FCFS(taskVector);
    }
    if (currentAlgorithm == "SJF")
    {
        correctVector = SJF(taskVector);
    }
    if (currentAlgorithm == "RR")
    {
        // Placeholder
        correctVector = SJF(taskVector);
    }
    if (currentAlgorithm == "ML")
    {
        // Placeholder
        correctVector = SJF(taskVector);
    }
    return correctVector;
}

string AlgorithmHandler::getCurrentAlgorithm()
{
    return currentAlgorithm;
}

void AlgorithmHandler::setCurrentAlgorithm(string algorithm)
{
    currentAlgorithm = algorithm;
}
