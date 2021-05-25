## Homework 1: Rook Jumping Maze (C++)
First homework from AI course, Universidad de Concepción, 2021-1

Solution implemented using BFS

By Fabián Cid
## How to run (in bash):
g++ main.cpp -o maze.exe

./maze.exe < tests/input
## Input
7 integers following the next order:

n

m

row of starting position

column of starting position

row of goal position

column of goal position

0

Note_1: n x m are the dimensions of the matrix, 0 indicates the end of the input

Note_2: You can enter as many matrices as you want, the number 0 indicates the end of the input, you can see the file "input" where are 3 matrix at the time

## Output
Number of steps to reach goal position, if there is no solution, the program prints "No hay solucion"
## Example (of 1 maze only)
Input:

5 5 0 0 1 3

3 4 1 3 1

3 3 3 0 2

3 1 2 2 3

4 2 3 3 3

4 1 4 3 2

0

Output:

13 (steps to reach solution)
## Obs (in JumpingMaze.h)
If you uncomment the line 158, the program will print the Maze

If you uncomment the line 162, the program will print all visited nodes

If you uncomment the line 164, the program will print a Matrix of booleans that shows if the node was visited or not

If you uncomment the line 186, the program will print the path from the start node to goal node



