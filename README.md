<h2> Reliaquest Coding Assessment </h2>
Task: <br>
 Create a daemon and a CLI in C++ that can interact using any IPC of your choice. The CLI, when invoked, presents following choices to the user:

    Insert a number
    Delete a number
    Print all numbers
    Delete all numbers
    Exit

Only positive integers can be accepted as a number. <br>
The daemon holds an in-memory data structure of your choice and depending on the choice between 1 and 2, numbers are accepted from user and added (or removed) into the structure. <br>
When a number is inserted, it should also include the time stamp of its insertion in unix time and also print it on the console but duplicate entries (i.e. same number more than once) is not permitted. <br>
When a number is deleted, it should remove the entire record, including the timestamp, and also print the same on the console. <br>
The choice 3 should ALWAYS print the numbers on the CLI console in a sorted fashion (lowest to highest) along with the timestamp. <br>
The choice 4 should clean all the stored entries. <br>
Simultaneous invocation of multiple CLIs is possible. You can pick any OS of your choice to make this work. All the necessary error conditions should be handled and appropriate messages should be provided to the user. The submission should also include the necessary make files/project files (if using visual studio), build instructions, compiler used and the reasoning behind the choice of your data structure. <br>

OS Chosen: Ubuntu <br>
IPC Chosen: Unix Domain Sockets <br>
Compiler chosen: g++ <br>
Data Structure chosen: std::map <br>
A map is an ordered data structure that can store a key value pair. It was used for these reasons:  <br>
- Easily stores the number (key) and the timestamp (value)  <br>
- Automatically sorted based on the keys, satisfying the condition for choice 3.  <br>
- Does not allow for duplicates, satisfying one of the conditions for choice 1.  <br>

<h3> Build Instructions: </h3>
1. Clone repository from Github into folder <br>
2. Open a terminal in the folder with the cloned files <br>
3. If not already installed, install g++ with the command "sudo apt install g++" <br>
4. Run the command "make" <br>
5. Run the command "./daemon" to invoke the daemon <br>
6. In a new terminal (still located in the same folder as the cloned files), run the command "./cli" <br>

