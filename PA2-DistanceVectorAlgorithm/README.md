# CSCI 3761 - Intro to Computer Networks - PA#2
## Dijkstra's Algorithm - Multi-node Pathway
### Please note that Professor Dave Ogle of UC Denver is responsible for 90% of this code. The goal of this project was to be able to read someone else's code, add functional implementations such as reading/creating the neighbor/vector tables and adding additional menu functions regarding: update, refresh, print, and route.

Utilizing the Distance Vector Algorithm to find the most cost-efficient path between multiple nodes. Ability to view 
that node's neighbors, update the cost to travel to its neighbors, and refresh it's information to all the nodes involved. 

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
