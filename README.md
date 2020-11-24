## CSCI 3761 - Intro To Computer Networks - University of Colorado Denver

## Project Outline 

### PA1 - Server and Client - C

Implementing a server and client

### PA2 - Dijkstra's Algorithm - C/C++

<b>Known bug/Error Handling Issue:</b> When attempting to update the cost between two nodes, it will update the DV table for the node the update was attempted on, but the DV tables for the neighboring nodes do not update. This was originally part of the professor's code that was provided to us, may fix at a later date. 

Utilizing Dijkstra's Algorithm to find the most cost-effective paths/routes when traveling between multiple nodes. In this case, we have 5 nodes who can only visibly see the cost to travel to their neighbors.
The goal of this project is to dynamically update our nodes to understand which routes are the most cost-effective and efficient to its desired destination, by creating two structures per node. 

 - The 1st structure(Our DV Table) will hold our current node, destination node, and its cost to get their.

 - The 2nd structure(Our Neighbors Table) will hold the current node's neighbors retaining: neighbor number, the neighbor's IP address, and the neighbor's port number. 
 
 By reading each node's table of neighbors and their cost associated with them, we can paint a better picture of available routes per neighbors and their cost. 
 
<b>Note:</b> The program is set to update automatically every 30 seconds to ensure each node has the most up-to-date information

### Menu-Input Options Available / Functional:
 - <b>print</b> - Prints the Current Node's Distance Vector Table to any nodes it may see
 - <b>refresh</b> - Sends the Current Node's Distance Vector Table its Neighbors
 - <b>update</b> - Updates the Current Node's Distance Vector table
   <p><b>Update Format</b> (Without brackets but include spaces): [FromNode] [ToNode] [NewCost]</p>
 - <b>route</b> - Display's the lowest cost route to desired node and which node to hop to
   <p><b>Route Format</b> (Without brackets but include spaces): route [ToNode]</p>
 
 Note: Menu-input text is not case sensitive, menu will handle any lowercase or uppercase discrepancies. <b> To run a node under a Linux system, the format must be:</b> [NeighborTxtFile] [VectorsTxtFile] [NodeNumToOpen] [PortNumberOfNodeNum] [TotalNumberOfNodes]
 
Example of wanting to open node 1: "neighbors1.txt vectors.txt 1 18181 5"
 
Please ensure to properly compile the program, prior to opening any nodes. Only the corresponding neighbor file and port number will allow the correct node to be ran successfully. Port numbers per node can be found within the neighbor txt files. 
