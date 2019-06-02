# DCPM
Directed Chinese Post Man:
Method:
1. Find out vertices whose indegree is not equal to out degree
2. Find the shortest path from each inter to each outer
3. Create a biclique graph whose vertices are all the inter and outer,edges's weights are the value of the shortest path's weight sum
4. Greedy way to find the matching in this biclique
5. Using Hierholzer's algorithm to find the answer

For graph input:
flowval: Present the available walk an edge can be taken.
capability: Present the weight.

recently:
1. Complete the final part of the program.

