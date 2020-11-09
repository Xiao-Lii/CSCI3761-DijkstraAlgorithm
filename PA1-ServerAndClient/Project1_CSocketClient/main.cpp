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

    int client_sd;
    struct sockaddr_in server;
    struct stat obj;
    int sock, choice, k, size, file, status;
    char buffer[1000], command[10], fileName[50], *filePointer;
    char key_press;
    int ascii_value;
    socklen_t fromLength;
    int returnCode;

    // SPECIFIC SET OF FLOW OF COMMANDS TO CREATE A SOCKET - STREAM(TCP)
    // 1. SERVER SIDE - SOCKET(), BIND(), LISTEN(), ACCEPT() - CONNECT(CLIENT-SIDE)
    // 2. CLIENT SIDE - SOCKET(), CONNECT(SERVER-SIDE) - ACCEPT(SERVER-SIDE), SEND(TO SERVER)
    // 3. SERVER SIDE - RECV(FROM CLIENT), SEND(TO CLIENT)
    // 4. CLIENT SIDE - RECV(FROM SERVER)

    // INITIALIZE THE SOCKET
    client_sd = socket(AF_INET, SOCK_STREAM, 0);
    // ERROR-HANDLING - INITIALIZING THE SOCKET
    if (client_sd < 0) {
        cout << "Socket creation failed" << endl;
        exit(1);
    }
    else
        cout << "Socket created successfully.\n";

    // CREATING THE SOCKET
    server.sin_family = AF_INET;
    server.sin_port = htons(52300);             // Port # from Server Side
    server.sin_addr.s_addr = INADDR_ANY;                // inet_addr(serverIP)

    // Handling a "Busy Signal"
    returnCode = connect(client_sd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
    // Error Handling - Connection
    if (returnCode < 0){
        close(client_sd);
        perror("Error connecting to the server socket");
        exit(1);
    }
    else
        cout << "Connection successful.\n";


    // SPECIFIC SET OF FLOW OF COMMANDS TO CREATE A SOCKET - STREAM(TCP)
    // 1. SERVER SIDE - SOCKET(), BIND(), LISTEN(), ACCEPT() - CONNECT(CLIENT-SIDE)
    // 2. CLIENT SIDE - SOCKET(), CONNECT(SERVER-SIDE) - ACCEPT(SERVER-SIDE), SEND(TO SERVER)
    // 3. SERVER SIDE - RECV(FROM CLIENT), SEND(TO CLIENT)
    // 4. CLIENT SIDE - RECV(FROM SERVER)
    memset(buffer, 0, 1000);         // RESET THE BUFFER

    // BEGINNING OF DISPLAYING REPEATABLE MENU OPTIONS
    bool run = true;
    while(run == true){
        memset(buffer, 0, 1000);         // THIS WILL RESET THE BUFFER EVERYTIME WE RETURN TO MENU OPTIONS

        //printf("Enter a choice:\n1- get\n2- put\n3- pwd\n4- ls\n5- cd\n6- quit\n");
        printf("Menu Options:\n1: Show Remote Directory\n2: Download a File\n3: Upload a File\n"
               "4: Show Local Directory\n5: Quit\n");
        scanf("%d", &choice);
        switch(choice){
            // OPTION 1 - CATALOG - LS COMMAND
            case 1:
                strcpy(buffer, "ls");
                send(client_sd, buffer, 1000, 0);

                // Displays the server directory to Client
                recv(client_sd, &size, sizeof(int), 0);
                filePointer = (char *) malloc(size);

                // Receiving 'temp.txt' file from Client
                recv(client_sd, filePointer, size, 0);

                // Creating 'tempFile.txt' on Client's local directory to write/read remote directory into
                file = creat("tempFile.txt", O_WRONLY);
                write(file, filePointer, size);
                close(file);
                system("clear");            // Clear's screen for cleanliness

                // PRINTING THE DIRECTORY
                printf("The remote directory:\n");
                system("chmod 777 tempFile.txt");
                system("cat tempFile.txt");
                system("rm tempFile.txt");
                cout << endl;
                break;

            // OPTION 2 - DOWNLOAD
            case 2:
                // BEGIN DOWNLOAD
                printf("Enter the file you'd like to download:\n");
                scanf("%s", fileName);
                strcpy(buffer, "get ");
                strcat(buffer, fileName);

                // SENDS TO CLIENT - 'GET ' + USER-INPUT FILENAME
                send (client_sd, buffer, 1000, 0);

                // RECEIVES FROM CLIENT - SIZE OF FILE TO BE DOWNLOADED
                recv(client_sd, &size, sizeof(int), 0);

                // ERROR HANDLING - IF FILE DOESN'T EXIST = NO SIZE
                if(!size){
                    printf("Error: File can't be found on directory.\n\n");
                    break;
                }

                filePointer = (char *) malloc(size);
                recv(client_sd, filePointer, size, 0);

                // FILE LOOP CHECK
                while(true){
                    int i = 1;
                    file = open(fileName, O_CREAT | O_EXCL | O_WRONLY, 0666);
                    // NEEDED ONLY IF THE FILES ARE IN THE SAME DIRECTORY FOR BOTH SERVER AND CLIENT
                    if (file == -1) {
                        sprintf(fileName + strlen(fileName), "%d", i);
                    }
                    else
                        break;
                }
                system("clear");
                write(file, filePointer, size);
                cout << "The file has been successfully downloaded. Below is a preview:\n";
                close(file);
                strcpy(buffer, "cat ");
                strcat(buffer, fileName);
                system(buffer);
                cout << endl << endl;
                break;
                // END DOWNLOAD

            // OPTION 3 - UPLOAD
            case 3:
                // BEGIN UPLOAD - BACKWARDS PROCESS OF DOWNLOAD
                strcpy(buffer, "put ");

                // SENDS TO SERVER 'PUT' COMMAND, TO TRIGGER ELSE IF STATEMENT ON SERVER-SIDE
                send(client_sd, buffer, 1000, 0);

                // BOOL/VAR FOR LOOP DOESN'T WORK HERE
                while (1){
                    system("clear");                 // CLEARING CLIENT SCREEN FOR CLEANLINESS
                    memset(fileName, 50, 0);            // RESETTING THE FILENAME CHAR ARRAY
                    printf("Please enter the file you'd like to upload:\n");
                    scanf("%s", fileName);
                    file = open(fileName, O_RDONLY, 777);

                    if(file == -1){
                        printf("\nError: No such file on the local directory. Please try again after"
                               " this prompt disappears.\n");
                        sleep(3);
                    }
                    else break;
                }

                // COPIES FILENAME TO BUFFER
                strcpy(buffer, fileName);

                // SENDS BUFFER TO CLIENT WITH UPLOAD COMMAND + FILENAME
                send(client_sd, buffer, 1000, 0);
                stat(fileName, &obj);
                size = obj.st_size;
                send(client_sd, &size, sizeof(int), 0);
                sendfile(client_sd, file, nullptr, size);
                recv(client_sd, &status, sizeof(int), 0);

                // ERROR HANDLING - FILE STORAGE UPLOAD
                if(status > 0) {
                    printf("File stored successfully. Below is a preview of the file uploaded.\n");
                    memset(buffer, 100, 0);
                    strcpy(buffer, "cat ");
                    strcat(buffer, fileName);
                    system(buffer);
                    cout << endl << endl;
                }
                else
                    printf("File failed to be stored to remote machine\n");
                break;
                // END UPLOAD

            // OPTION 4 - SHOW LOCAL DIRECTORY
            case 4:
                system("clear");                    // CLEARS THE SCREEN
                cout << "The current local directory:\n";
                system("ls");                       // LINUX-CMD FOR DISPLAYING THE DIRECTORY
                cout << endl;
                break;

            // OPTION 5 - QUIT
            case 5:
                strcpy(buffer, "quit");
                send(client_sd, buffer, 1000, 0);
                recv(client_sd, &status, 1000, 0);
                close(client_sd);
                if(status){
                    printf("The server will now be closed.\n\n");
                    exit(0);
                }
                printf("Server failed to close connection\n");
                //memset(buffer, 0, 100);     // RESET THE BUFFER
                break;
        }       // END OF SWITCH CASE MENU - MENU OPTIONS
    }           // END OF REPEATABLE DISPLAY OF MENU CHOICES
    return 0;
}               // END OF MAIN