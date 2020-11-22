## CSCI 3761 - Intro To Computer Networks - University of Colorado Denver

## Project Outline 

### PA1 - Server and Client - C

Implementing a server and client

### PA2 - Dijkstra's Algorithm - C/C++

Utilizing Dijkstra's Algorithm to find the most cost-effective paths/routes when traveling between multiple nodes. In this case, we have 5 nodes who can only visibly see the cost to travel to their neighbors.
The goal of this project is to dynamically update our nodes to understand which routes are the most cost-effective and efficient to its desired destination, by creating two structures per node. 

 - The 1st structure(Our DV Table) will hold our current node, destination node, and its cost to get their.

 - The 2nd structure(Our Neighbors Table) will hold the current node's neighbors retaining: neighbor number, the neighbor's IP address, and the neighbor's port number. 
 
 By reading each node's table of neighbors and their cost associated with them, we can paint a better picture of available routes per neighbors and their cost. 
 
 - <b>Note:<b> To run a node under a Linux system/subsystem, the format must be: <NeighborTxtFile> <VectorsTxtFile> <NodeNumToOpen> <PortNumberOfNodeNum> <TotalNumberOfNodes> 
 
 Example of wanting to open node 1: "neighbors1.txt vectors.txt 1 18181 5" - Please ensure to properly compile the program, prior to opening any nodes. Only the corresponding neighbor file and port number will allow the correct node to be ran successfully. Port numbers per node can befound within the neighbor txt files. 

 - There are 3 main functions the user can implement once the node is running:
 
   1. "print" - Prints the node's current distance vector table from itself to any nodes it may see.
   2. "refresh" - Sends the current node's distance vector table to all of its neighboring nodes 
   3. "update" - Format: <FromNode> <ToNode> <NewCost> - Updates the cost from itself to a neighboring node, as long as the new cost is less than its previous. 
   4. "route" - Format: "route <ToNode>" - This will print the node the user should take next from its current node, to get to the desired 'ToNode'
