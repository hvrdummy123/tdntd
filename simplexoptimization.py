import pulp
from pulp import LpMaximize, LpProblem, LpVariable, lpSum, value
#assume start date we take 0
#we also assume that we have enough time for all tasks ensuring that we will not exceed time between deadline and duration
#this program will give me which task to do first
sortedlist = ""
tasks = {
    'Task1': {'duration': 5, 'deadline': 10, 'priority': 4, 'urgency':3},
    'Task2': {'duration': 3, 'deadline': 8, 'priority': 2, 'urgency': 3},
    'Task3': {'duration': 7, 'deadline': 15, 'priority': 5, 'urgency': 3},
    'Task4': {'duration': 7, 'deadline': 25, 'priority': 3, 'urgency': 2},
    'Task5': {'duration': 8, 'deadline': 30, 'priority': 2, 'urgency': 6},
    'Task6': {'duration': 9, 'deadline': 31, 'priority': 5, 'urgency': 6},
}

def optimization(tasks):
    #LP problem
    prob = pulp.LpProblem("Task_Optimization", LpMaximize)

    #decision variables
    x = pulp.LpVariable.dicts("Task", tasks.keys(), cat=pulp.LpBinary)

    #prob += pulp.lpSum([2* tasks[task]['priority']  * x[task] for task in tasks] + [tasks[task]['urgency'] * x[task] for task in tasks])
    prob += pulp.lpSum([
        x[task] * (5 * tasks[task]['priority'] + 1*tasks[task]['urgency'] + 2* 100 / tasks[task]['deadline'])
        for task in tasks
    ])
    #this gives extra weightage to priority and also ensures tasks with closer deadlines are completed first

    #constraints
    prob+= pulp.lpSum([x[task] for task in tasks]) <=1
    prob += pulp.lpSum([tasks[task]['deadline'] -tasks[task]['duration'] * x[task] for task in tasks]) >= 0  

    prob.solve()

    #Printing results (a status of -1 means not feasible)
    if prob.status == 1:
        for task in tasks:
            print(task, "=", int(x[task].varValue))
        print("Total weighted score:", pulp.value(prob.objective))
    else:
        print("Problem is infeasible or unbounded.")
    
    for task in tasks:
        if(int(x[task].varValue==1)):
            optimization.a = task

while(len(tasks)!=0):
    optimization(tasks)
    sortedlist = sortedlist+ optimization.a + " "
    del tasks[optimization.a]

print("\n\n\nThe tasks should be completed as follows : ",sortedlist,"\n")
