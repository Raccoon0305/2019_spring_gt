# DCPM
Directed Chinese Post Man:

Description:
1. This program is for directed graph.
2. This program considers the shortest path, this is presented mainly on finding which edges are going to be walked twice.
   The input graph can have weights on edges, but it also accept unweighted ones, just give every edge an identical weight value.
3. About the standard input of this program: Each line presents an edge,
   format: (head, tail, weight, capability(always be 1 if simple graph))
   a b 100 1 
   example like graph_in.txt
   
Method:
1. Find out vertices whose indegree is not equal to out degree
2. Find the shortest path from each inter to each outer
3. Create a biclique graph whose vertices are all the inter and outer,edges's weights are the value of the shortest path's weight sum
4. Greedy way to find the matching in this biclique
5. Using Hierholzer's algorithm to find the answer

For graph input:
flowval: Present the available walk an edge can be taken.
capability: Present the weight.


