#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Task 
{
    string name;
    int priority;
    string startDate;
    string deadline;
    int duration;

    // Constructor to initialize tasks
    Task(string n, int p, string start, string end, int dur) : name(n), priority(p), startDate(start), deadline(end), duration(dur) {}

    // Overloading less than operator to prioritize tasks
    bool operator<(const Task& other) const //for objects of type Task
    {
        //calculate remaining time
        int remainingTime = stoi(deadline) - stoi(startDate) - duration;
        int otherRemainingTime = stoi(other.deadline) - stoi(other.startDate) - other.duration;

        // Determine the quadrant of each task based on its urgency and importance using eisenhower matrix
        int quadrant = 0;
        int otherQuadrant = 0;

        if (priority >= 3 && remainingTime < 1) // Important and Urgent
            quadrant = 1;
        else if (priority >= 3 && remainingTime >= 1) // Important but Not Urgent
            quadrant = 2;
        else if (priority < 3 && remainingTime < 1) // Not Important but Urgent
            quadrant = 3;
        else // Not Important and Not Urgent
            quadrant = 4;

        if (other.priority >= 3 && otherRemainingTime < 1)
            otherQuadrant = 1;
        else if (other.priority >= 3 && otherRemainingTime >= 1)
            otherQuadrant = 2;
        else if (other.priority < 3 && otherRemainingTime < 1)
            otherQuadrant = 3;
        else
            otherQuadrant = 4;

        // Compare tasks based on the Eisenhower Matrix quadrants
        if (quadrant != otherQuadrant)
            return quadrant > otherQuadrant; // Lower quadrant number means higher priority
        else
            return priority < other.priority; // Within the same quadrant, prioritize by importance
    }
};

// Priority based queue class
class PriorityTaskQueue 
{
private:
    priority_queue<Task> tasks;

public:
    // Add task to the queue
    void addTask(const Task& task) 
{
        tasks.push(task);
    }

    // Get the next task in the queue
    Task getNextTask() 
    {
        if (!tasks.empty()) 
        {
            Task nextTask = tasks.top();
            tasks.pop();
            return nextTask;
        } else 
        {
            // Return an empty task if the queue is empty
            return Task("", 0, "", "", 0);
        }
    }

    // Check if the queue is empty
    bool isEmpty() const 
    {
        return tasks.empty();
    }
};

int main() {
    // Create a priority based queue
    PriorityTaskQueue taskQueue;

    // Add some tasks with priorities
    taskQueue.addTask(Task("Task 1", 3, "20240204", "20240210", 5));
    taskQueue.addTask(Task("Task 2", 1, "20240205", "20240212", 7));
    taskQueue.addTask(Task("Task 3", 4, "20240203", "20240208", 6));
    taskQueue.addTask(Task("Task 4", 10, "20240203", "20240208", 10));
    taskQueue.addTask(Task("Task 5", 6, "20240202", "20240218", 2));
    taskQueue.addTask(Task("Task 6", 2, "20240213", "20240218", 9));
    taskQueue.addTask(Task("Task 7", 4, "20240203", "20240205", 1));
    

    // Process tasks in order of priority
    while (!taskQueue.isEmpty()) 
    {
        Task nextTask = taskQueue.getNextTask();
        cout << "Processing task: " << nextTask.name << endl;
        int remainingTime = stoi(nextTask.deadline) - stoi(nextTask.startDate) - nextTask.duration;
        if(remainingTime<=0 && nextTask.priority>=3)
            cout<<"DO THIS TASK URGENTLY !! YOU DON'T HAVE MUCH TIME !!"<<endl;
        else if(remainingTime<=0 && nextTask.priority<3)
            cout<<"even if not important, tick it off early :)"<<endl;
        cout<<endl;
    }

    return 0;
}
