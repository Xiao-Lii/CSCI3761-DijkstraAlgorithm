# CSCI 3761 - Intro to Computer Networks - PA#1

## Implementing a Server and Client 

###   Description of Program
<p>Two programs of a server and client will connect with each other on the port #: 52200 and will 
interact with each other through the menu options of: Previewing the remote server directory,
downloading a file from the server, uploading a file to the server, to view the user's local
directory, and to terminate the program/connection between the two. 

<b>NOTE:</b> 	The max size of the characters to be read/written to & from a file is 1000 characters. 
	The max size of the file name to be uploaded or read from is 50 characters.
	The client is unable to type in any specific linux commands and must abide by menu options.</p>

### Source Files

Name:   main.cpp (Project1_CSocketAndServer)
    This is the main program that reads the player's desired menu commands from the client's 

Name:   temp.txt (Project1_CSocketAndServer)
    This is an empty text file that will be utilized for copying the output of the 'ls' command
for the server's directory. Please refer to SIDE NOTE #3 under 'Circumstances of Programs'

Name:   download.txt (Project1_CSocketServer)
    This is the sample text file used for downloading to the client from the server.

Name:   main.cpp (Project1_CSocketAndClient)
    This is the main program that reads the player's desired menu commands from the client's 
main.cpp

Name:   uploadFile.txt (Project1_CSocketAndClient)
    This is the sample text file used for uploading to the server from the client.

### Circumstances of Programs
Was developed on a Windows 10 Pro OS through CLion v. 2020.2 and tested on a Linux installed
subsystem/termial (Ubunto v 20.04 LTS)

    The server program must be executed prior to the client program, to ensure a proper connection.

<b>SIDE NOTE #1:</b>
    The program runs mostly successful but has some minor bugs. Despite server prompts of successful 
prompts of socket creation, bind, listen, and accepting the client's connection, prompt menu option 1 - 
"Show the remote directory" & if it doesn't show a list of results, the program WILL NOT function. You 
MUST stop the program and attempt to rerun; while attempting to rerun, sometimes the port # may no 
longer work and will need to be incremented by 100 to continue. Quit & recompile until Menu Option
1 proves successful. Only then will the rest of the program be fully functional. 

<b>SIDE NOTE #2:</b> The program will work out of this order, but this is the quickest way to checking/ensuring 
the client and server programs are properly connected. Unsure of why these issues arise and may be purely
dependent on the network's 'mood.'

<b>SIDE NOTE #3:</b> The temp.txt file for the server program must be placed in the main folder with main.cpp 
for the program to write the correcty directory results down for the user. Placing this file in the 
'cmake-build-debug' folder, will result in the incorrect directory to be given to the user.






