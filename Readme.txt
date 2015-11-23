Problem statement:

The CNF-SAT problem

Before defining the problem we need to define logical expressions in conjunctive normal form. Note the similarity to Boolean algebra.
Conjunctive normal form (CNF) of a logical expression
A logical (Boolean) variable is a variable that may be assigned the value true or false (for example p is true, while q is false). A literal is a logical variable or the negation of a logical variable (For example p and ?q are literals). A clause is a disjunction of literals (for example (p?q?s) and (?q ? r) are clauses). A logical expression is in Conjunctive Normal Form if it is a conjunction of clauses. Forexample the expression:
(p??q?s) ?(?q ? r)?(?p ? r) ?(?r ? s)?(?p??s??q)
The CNF-SAT problem is:Given a logical expression in Conjunctive Normal Form, is there a truth assignment for the variables which causes the CNF expression to be true?
Answer is yes, if there is an assignment that makes all the clausesevaluate to T (true). For example, p=T, q=F, r=T and s=T is a truth assignment for
(p??q?s) ?(?q ? r)? (?p ? r) ? (?r ? s)? (?p??s??q)
Note that if q=F then ?q=T
The answer is no, if there is no such an assignment. This means that for each assignment some clauses will evaluate to false.
The CNF-SAT problem is an important problem in logic. It is also the first problem shown to be NP-Complete by Cook
The Program
In this program you will use backtracking to find solutions. At each state of the solution (node in the state space tree) you will check that it is promising. For this assignment a node is promising if the current solution does not result in clauses that evaluates to false. Note that in this programit is possible that all clauses are satisfied and there may still be unassigned variables.
This program will read from the command line the following two parameters: <input file name><output file name>.
The input file has the following structure:
Line 1: n m sizeC// where n is the number of variables, and m the number of clauses and sizeC the number of literals in the clauses
Line 2 to m+1: a list of sizeC positive and negative numbers in the range 1 to n. If the number is negative the literal is negated.

The output file:

Case 1: There was no satisfying assignment:
Line 1: No satisfying assignment
Line 2: Run time is <x> milliseconds.


Case 2: n<=5 and there are solutions
Print all solutions
Last line: Run time is <x> milliseconds.

Case 3: n>5 and m>30 and there are solutions
Line 1: There is a satisfying assignment”
Line 2: Run time is <x> milliseconds.

Case 4; n>5, m<=30 and there are solutions:
Print a solution
Last line: Run time is <x> milliseconds

Example 1
(?x1??x2) ?(?x2??x3)? (?x1? x3) 
The input file:
Line 1: 3 3 2
Line 2: -1 2
Line 3: -2 -3
Line 4: -1 3 
The output file:
The solution is 
x[1]= 0
x[2]= 1
x[3]= 0
 The solution is 
x[1]= 0
x[2]= 0
Run time is 1 milliseconds
Example 2
(?x1???x2) ?(?x1?x2)? (x1??x2)? (x1? x2) 
The input is:
2 4 2
-1 -2
-1  2
 1 -2
1	2
The output is:

No satisfying assignment
Run time is <x> milliseconds.


	backTrackCompute(depth) {
		if (all clauses are satisfied)	
			write to file the appropriate output

		return;
				
	if (promising(depth)){
		x[depth]=1;
		backTrackCompute(depth+1);
		x[depth]=0;
		backTrackCompute(depth +1);
	}
		}
		
	


Programmed in C


How to Execute?

1> make clean
	will clean the existing output files

2> make
	will execute the program and generate output files for the specific input files 


I am using many arrays in my code

1> n variables
2> m clauses
3> expression for n*m size


