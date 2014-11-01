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
    timeQuantumRR = 4;
    timeQuantumML0 = 8;
    timeQuantumML1 = 16;

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
    averageWaitingTime = (double)totalWait / (double)inputVector.size();
    return output;
}

// Shortest job first
vector< vector<string> > AlgorithmHandler::SJF(vector< vector<int> > inputVector)
{
    // The number of processes
    int numElems = inputVector.size();
    // Every subvector is given a third element, the process number in the order the processes come in(1, 2, 3, ...)

    vector< vector<string> > output;
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


    for (int i = 0; i < numElems * 3; i++)
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
            output.push_back(processVector);

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
                output.push_back(spaceVector);

                trace += earliestArrival - trace;
            }
        }
    }
    // Calculate average waiting time
    averageWaitingTime = (double)totalWait / (double)inputVector.size();

    return output;
}

// Round robin
vector< vector<string> > AlgorithmHandler::RR(vector< vector<int> > inputVector)
{
    // The number of processes
    int numElems = inputVector.size();
    // Every subvector is given a third element, the process number in the order the processes come in(1, 2, 3, ...)

    vector< vector<string> > output;
    // Where the process manager currently is
    int trace = 0;
    int totalWait = 0;
    // Counted from 0 to numElems - 1
    int nextProcess = 0;

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


    for (int i = 0; i < numElems * 4; i++)
    {
        vector< vector<int> > currentWaiting;
        for (int j = 0; j < numElems; j++)
        {
            if (inputVector[j][0] <= trace && inputVector[j][2] != 999)
            {
                currentWaiting.push_back(inputVector[j]);
            }
        }
        // The correct process is determined and started
        if (currentWaiting.size() >= 1)
        {
            // Check whether a full circle has been completed
            if ((unsigned int)(nextProcess + 1) > currentWaiting.size())
            {
                nextProcess = 0;
            }

            int addedProcessNum = currentWaiting[nextProcess][2] - 1;
            vector<string> processVector;
            processVector.push_back("P" + to_string(addedProcessNum + 1));
            // Checking whether the process is longer or equal to the time quantum or not
            totalWait += calculateWaitFromOutputVector(output, addedProcessNum + 1, trace,
                                                       inputVector[addedProcessNum][0]);

            if (inputVector[addedProcessNum][1] > timeQuantumRR)
            {
                processVector.push_back(to_string(timeQuantumRR));
                inputVector[addedProcessNum][1] -= timeQuantumRR;
                trace += timeQuantumRR;
                nextProcess += 1;
            }
            else
            {
                processVector.push_back(to_string(inputVector[addedProcessNum][1]));
                inputVector[addedProcessNum][2] = 999;
                trace += inputVector[addedProcessNum][1];
            }

            output.push_back(processVector);
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
                output.push_back(spaceVector);

                trace += earliestArrival - trace;
            }
        }
    }
    // Calculate average waiting time
    averageWaitingTime = (double)totalWait / (double)inputVector.size();

    return output;
}

vector< vector<string> > AlgorithmHandler::ML(vector< vector<int> > inputVector)
{
    // Three vectors representing the queues are created
    vector < vector<int> > q0;
    vector < vector<int> > q1;
    vector < vector<int> > q2;

    q0 = inputVector;

    // Output vector is qreated
    vector < vector<string> > output;

    // Incoming processes are sorted by their arrival times
    std::sort(q0.begin(), q0.end(), [](std::vector<int> a, std::vector<int> b)
    {
        return a[0] < b[0];
    });

    int numElems = q0.size();

    // Every process is given a process id
    for (int i = 0; i < numElems; i++)
    {
        q0[i].push_back(i + 1);
    }

    // Total waiting time
    int totalWait = 0;
    int trace0 = 0;

    // Queue 0
    for (vector<int> task : q0)
    {
        int arrival = task[0];
        int duration = task[1];
        int pid = task[2];

        // If there is a hole between two processes a space with the right length will be added to the vector
        if (arrival > trace0)
        {
            // Check if there are processes in queue 1
/*            if (q1.size() > 0)
            {
                vector<string> fromQ1;
                fromQ1.push_back()
            }*/
            vector<string> spaceVector;
            spaceVector.push_back(" ");
            spaceVector.push_back(to_string(arrival - trace0));
            output.push_back(spaceVector);

            // Check whether the process has to be sent to queue 1
            if (task[1] > timeQuantumML0)
            {
                vector<int> remainingTask;
                remainingTask.push_back(arrival);
                remainingTask.push_back(duration - timeQuantumML0);
                // Remainingtask is also given the process id
                remainingTask.push_back(pid);
                q1.push_back(remainingTask);
                duration = timeQuantumML0;
            }

            vector<string> processVector;
            processVector.push_back("P" + to_string(pid));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace0 = arrival + duration;
        }
        else
        {
            // Check whether the process has to be sent to queue 1
            if (task[1] > timeQuantumML0)
            {
                vector<int> remainingTask;
                remainingTask.push_back(arrival);
                remainingTask.push_back(duration - timeQuantumML0);
                // Remainingtask is also given the process id
                remainingTask.push_back(pid);
                q1.push_back(remainingTask);
                duration = timeQuantumML0;
            }
            // Check for how long the process had to wait
            if (arrival < trace0)
            {
                totalWait += trace0 - arrival;
            }
            vector<string> processVector;
            processVector.push_back("P" + to_string(pid));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace0 += duration;

        }
    }

    // Queue 1
    for (vector<int> task : q1)
    {
        int arrival = task[0];
        int duration = task[1];
        int pid = task[2];

        // If there is a hole between two processes a space with the right length will be added to the vector
        if (arrival > trace0)
        {
            vector<string> spaceVector;
            spaceVector.push_back(" ");
            spaceVector.push_back(to_string(arrival - trace0));
            output.push_back(spaceVector);

            // Check whether the process has to be sent to queue 2
            if (task[1] > timeQuantumML1)
            {
                vector<int> remainingTask;
                remainingTask.push_back(arrival);
                remainingTask.push_back(duration - timeQuantumML1);
                // Remainingtask is also given the process id
                remainingTask.push_back(pid);
                q2.push_back(remainingTask);
                duration = timeQuantumML1;
            }
            vector<string> processVector;
            processVector.push_back("P" + to_string(pid));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace0 = arrival + duration;
        }
        else
        {
            // Check whether the process has to be sent to queue 2
            if (task[1] > timeQuantumML1)
            {
                vector<int> remainingTask;
                remainingTask.push_back(arrival);
                remainingTask.push_back(duration - timeQuantumML1);
                // Remainingtask is also given the process id
                remainingTask.push_back(pid);
                q2.push_back(remainingTask);
                duration = timeQuantumML1;
            }
            // Check for how long the process had to wait
            if (arrival < trace0)
            {
                totalWait += calculateWaitFromOutputVector(output, pid, trace0, arrival);
            }
            vector<string> processVector;
            processVector.push_back("P" + to_string(pid));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace0 += duration;

        }
    }

    // Queue 2
    for (vector<int> task : q2)
    {
        int arrival = task[0];
        int duration = task[1];
        int pid = task[2];

        // If there is a hole between two processes a space with the right length will be added to the vector
        if (arrival > trace0)
        {
            vector<string> spaceVector;
            spaceVector.push_back(" ");
            spaceVector.push_back(to_string(arrival - trace0));
            output.push_back(spaceVector);

            vector<string> processVector;
            processVector.push_back("P" + to_string(pid));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace0 = arrival + duration;
        }
        else
        {
        // Check for how long the process had to wait
            if (arrival < trace0)
            {
                totalWait += calculateWaitFromOutputVector(output, pid, trace0, arrival);
            }
            vector<string> processVector;
            processVector.push_back("P" + to_string(pid));
            processVector.push_back(to_string(duration));
            output.push_back(processVector);

            trace0 += duration;

        }
    }

    averageWaitingTime = (double) totalWait / (double) inputVector.size();

    return output;
}

vector< vector<string> > AlgorithmHandler::getCorrectProcessVector()
{
    vector< vector<string> > correctVector;
    if (currentAlgorithm == "FCFS")
    {
        correctVector = FCFS(taskVector);
    }
    else if (currentAlgorithm == "SJF")
    {
        correctVector = SJF(taskVector);
    }
    else if (currentAlgorithm == "RR")
    {
        correctVector = RR(taskVector);
    }
    else if (currentAlgorithm == "ML")
    {
        correctVector = ML(taskVector);
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

int AlgorithmHandler::calculateWaitFromOutputVector(vector< vector<string> > oVector, int pid, int trace,
                                                    int arrival)
{
    if (oVector.size() == 0)
    {
        return 0;
    }

    int wait = 0;
    int lastRunning = -1;
    // Trace used for wait time calculations
    int waitTrace = 0;
    string pidString = "P" + to_string(pid);

    for (vector<string> vec : oVector)
    {
        waitTrace += atoi(vec[1].c_str());
        if (pidString == vec[0])
        {
            lastRunning = waitTrace;
            cout << to_string(lastRunning) << "\n";
            //cout << to_string(oVector.size()) << "\n";
        }
    }

    if (lastRunning != -1)
    {
        wait = trace - lastRunning;
    }
    else
    {
        wait = trace - arrival;
    }

    return wait;
}
