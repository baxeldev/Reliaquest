# Reliaquest
Reliaquest Coding Assessment
Task:
 Create a daemon and a CLI in C++ that can interact using any IPC of your choice. The CLI, when invoked, presents following choices to the user:

    Insert a number
    Delete a number
    Print all numbers
    Delete all numbers
    Exit

Only positive integers can be accepted as a number. 
The daemon holds an in-memory data structure of your choice and depending on the choice between 1 and 2, numbers are accepted from user and added (or removed) into the structure.
When a number is inserted, it should also include the time stamp of its insertion in unix time and also print it on the console but duplicate entries (i.e. same number more than once) is not permitted. 
When a number is deleted, it should remove the entire record, including the timestamp, and also print the same on the console.
The choice 3 should ALWAYS print the numbers on the CLI console in a sorted fashion (lowest to highest) along with the timestamp.
The choice 4 should clean all the stored entries.
Simultaneous invocation of multiple CLIs is possible. You can pick any OS of your choice to make this work. All the necessary error conditions should be handled and appropriate messages should be provided to the user. The submission should also include the necessary make files/project files (if using visual studio), build instructions, compiler used and the reasoning behind the choice of your data structure.

OS Chosen: Ubuntu
Compiler chosen: g++

Build Instructions:
1. Clone repository from Github into folder
2. Open a terminal in the folder with the cloned files
3. Run the command "make"
4. Run the command "./daemon" to invoke the daemon
5. In a new terminal (still located in the same folder as the cloned files), run the command "./cli"

