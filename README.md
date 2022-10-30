# GraphRanker

## General Info
This is the final project of the Algorithms and Principles of Computer Science course I have taken in the second year of the bachelor's degree in Computer Science and Engineering at Polytechnic University of Milan.

Professor: Davide Martinenghi

Grade: 30L/30L


## Specifications
The goal of the project is to implement a C (C11) program that manages the ranking of directed weighted graphs.

The ranking keeps track of the k "best" graphs.

The program receives as input:
* Two parameters, only once, at the start, separated by a blank space: d, which is the number of nodes in the graphs, and k, which is the length of the ranking.
* A sequence of commands between AggiungiGrafo [adjacency matrix] and TopK.

d, k and the number of graphs can be represented as 32-bit integers.

AggiungiGrafo adds a new graph to the ones considered to build the ranking. The command is followed by the adjacency matrix, written row by row, with the elements separated by commas. The weights of the edges are integers in the interval [0, 2^32 - 1].

TopK takes in consideration every graph from the start of the program and prints the indexes of the k graphs with the k smallest values of the following metric: sum of the shortest paths between node 0 (first row of the adjacency matrix) and all the other (reachable) nodes of the graph. If there is more than one graph with the same value, the oldest should be prioritized.


## Example of execution
*Input:*
```
3,2
AggiungiGrafo
0,4,3
0,2,0
2,0,0
AggiungiGrafo
0,0,2
7,0,4
0,1,0
AggiungiGrafo
3,1,8
0,0,5
0,9,0
TopK
```

*Output:*
```
0 1 (or 1 0)
```
