# CSCI 3761 - Intro To Computer Networks - University of Colorado Denver

## Project Outline 

### PA1 - Server and Client - C

Implementing a server and client

### PA2 - Dijkstra's Algorithm - C/C++

Utilizing Dijkstra's Algorithm to find the most cost-effective paths/routes when traveling between multiple nodes. In this case, we have 5 nodes who can only visibly see the cost to travel to their neighbors.
The goal of this project is to dynamically update our nodes to understand which routes are the most cost-effective and efficient to its desired destination, by creating two structions per node. 

 - The 1st structure(Our DV Table) will hold our current node, destination node, and its cost to get their.

 - The 2nd structure(Our Neighbors Table) will hold the current node's neighbors retaining: neighbor number, the neighbor's IP address, and the neighbor's port number. 
 
 By reading each node's table of neighbors and their cost associated with them, we can paint a better picture of available routes per neighbors and their cost. 
