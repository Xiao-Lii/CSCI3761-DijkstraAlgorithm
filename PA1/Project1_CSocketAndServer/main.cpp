#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>           // FPR GETTING FILE SIZE USING STAT()
#include<sys/sendfile.h>        // FOR SENDING FILES
#include<fcntl.h>               // FOR 0_RDONLY



using namespace std;

int main(int argc, char *argv[]) {
    int server_sd, connectedServer_sd;
    struct stat obj;
    struct sockaddr_in server_address, from_address;
    int testBind, returnCode, file, size;
    int j, c;
    char buffer[1000], command[10], fileName[50], *filePointer;
    socklen_t fromLength;                                    // Pre-defined length

    // SPECIFIC SET OF FLOW OF COMMANDS TO CREATE A SOCKET - STREAM(TCP)
    // 1. SERVER SIDE - SOCKET(), BIND(), LISTEN(), ACCEPT() - CONNECT(CLIENT-SIDE)
    // 2. CLIENT SIDE - SOCKET(), CONNECT(SERVER-SIDE) - ACCEPT(SERVER-SIDE), SEND(TO SERVER)
    // 3. SERVER SIDE - RECV(FROM CLIENT), SEND(TO CLIENT)
    // 4. CLIENT SIDE - RECV(FROM SERVER)

    // Initialize the socket (Type of Internet Protocol, TCT protocol, flag/protocols)
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    // Error Handling
    if (server_sd < 0) {
        cout << "Socket creation failed" << endl;
        exit(1);
    }
    else
        cout << "Socket successfully binded.\n";

    // Create the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(52300);         // Hold To Network Short (HTONS) - Port # We decided to Use
    server_address.sin_addr.s_addr = INADDR_ANY;            // What's the IP Address we want to bind any? Any IP address on this machine

    memset(server_address.sin_zero, '\0', sizeof(server_address.sin_zero));

    // Bind the Socket
    returnCode = bind(server_sd, (struct sockaddr *) &server_address, sizeof(server_address));
    // Error Handling for Binding the Socket
    if (returnCode < 0) {
        //cout << testBind << endl;
        cout << "Binding socket failed" << endl;
        exit(1);
    }
    else
        cout << "Bind successfully completed.\n";

    // 5 - Represents the # of connections we can have simultaneously but on hold
    int listenReturnVal = listen(server_sd, 5);

    // Error Handing for Listening Return Value
    if (listenReturnVal < 0){
        cout << "Listening for connection failed." << endl;
        exit(1);
    }
    else
        cout << "Listening for connection successful.\n";

    // Accepting the Connection (Server Descriptor, Return Address, Length of Address(How much data))
    connectedServer_sd = accept(server_sd, (struct sockaddr *) &from_address, &fromLength);

    // SPECIFIC SET OF FLOW OF COMMANDS TO CREATE A SOCKET - STREAM(TCP)
    // 1. SERVER SIDE - SOCKET(), BIND(), LISTEN(), ACCEPT() - CONNECT(CLIENT-SIDE)
    // 2. CLIENT SIDE - SOCKET(), CONNECT(SERVER-SIDE) - ACCEPT(SERVER-SIDE), SEND(TO SERVER)
    // 3. SERVER SIDE - RECV(FROM CLIENT), SEND(TO CLIENT)
    // 4. CLIENT SIDE - RECV(FROM SERVER)

    cout << "Welcome to Lee's Server. Ready to receive commands from the client.\n";
    bool run = true;
    while(run == true) {
        memset(buffer, 0, 1000);     // RESETS THE BUFFER

        // RECEIVING COMMANDS FROM CLIENT-SIDE
        recv(connectedServer_sd, buffer, 1000, 0);
        sscanf(buffer, "%s", command);

        // LIST OF POSSIBLE COMMANDS REQUESTED
        // OPTION 1 - CATALOG OPTION - 'LS' COMMAND
        if (!strcmp(command, "ls")) {
            printf("Received the following command: %s\n", buffer);
            system("ls > temp.txt");

            stat("temp.txt", &obj);
            size = obj.st_size;

            // SENDING TO CLIENT-SIDE THE LISTED DIRECTORY
            send(connectedServer_sd, &size, sizeof(int), 0);
            file = open("temp.txt", O_RDONLY, 777);

            sendfile(connectedServer_sd, file, nullptr, size);
            //cout << "Leaving ls Command.\n";
        }

        // OPTION 2 - DOWNLOAD OPTION - 'GET' COMMAND
        else if(!strcmp(command,"get")){
            printf("Received the following command: %s\n", buffer);
            sscanf(buffer, "%s%s", fileName, fileName);
            stat(fileName, &obj);
            file = open(fileName, O_RDONLY, 777); // MAY NEED TO DELETE 777 LATER
            size = obj.st_size;

            // ERROR HANDLING FOR FILE
            if(file == -1)
                size = 0;
            send(connectedServer_sd, &size, sizeof(int), 0);

            // IF SENDING FILE SIZE WAS SUCCESSFUL, PROCEED WITH SENDING FILE CONTENTS
            if(size)
                sendfile(connectedServer_sd, file, nullptr, size);

        }

        // OPTION 3 - UPLOAD OPTION - 'PUT' COMMAND
        else if(!strcmp(command, "put")) {
            // ALREADY RECEIVED INTO BUFFER - 'PUT '
            int n = 0;
            memset(fileName, 50, 0);            // RESETTING FILE NAME CHAR ARRAY

            // RECEIVES AND OVERWRITES BUFFER WITH FILE NAME
            recv(connectedServer_sd, buffer, sizeof(buffer), 0);
            sscanf(buffer, "%s", fileName);
            cout << "\nUploading the following file: " << buffer << endl;
            recv(connectedServer_sd, &size, sizeof(int), 0);

            while(1) {
                file = open(fileName, O_CREAT | O_EXCL | O_WRONLY, 0666);

                // Error Handling for file
                if(file == -1){
                    int i = 1;
                    sprintf(fileName + strlen(fileName), "%d", i);
                }
                else
                    break;
            }
            filePointer = (char *) malloc(size);

            recv(connectedServer_sd, filePointer, size, 0);
            n = write(file, filePointer, size);

            // Error Handling
            if (n < 0){
                printf("Error: The file could not be uploaded to the server.\n");
                break;
            }
            close(file);
            send(connectedServer_sd, &n, sizeof(int), 0);
        }

        // OPTION 5 - QUIT OPTION - CLOSES SERVER & CLIENT
        else if(!strcmp(command, "quit")){
            printf("\nThe server will now quit.\n");
            int i = 1;
            send(connectedServer_sd, &i, sizeof(int), 0);
            exit(0);
        }
    }
    return 0;
}
