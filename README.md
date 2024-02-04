This is a project based on task prioritization using Eisenhower matrix method and a simplex Linear Programming
I have used a priority based queue system in c++ to enter tasks with parameters like start date, deadlines and duration along with urgency and priority. 
Eisenhower matrix method works on a 2x2 matrix defining urgency and priority and segregating on its variations.
The simplex linear programming optimization uses PuLP which is an LP modeler written in python, making use of a problem statement where we can add constraints on deadlines, urgency and priority.'
The program gives us which task must be performed first for maximum optimization, after which we delete that task and re-enter the dictionary for the next task to be done.
Thus we get a sorted list of prioritized tasks to perform.
