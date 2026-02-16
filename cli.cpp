#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/Reliaquest_daemon.sock"

std::string send_command(const std::string &cmd) {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) return "ERROR: Could not create socket\n";

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    if (connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        close(fd);
        return "ERROR: Could not connect to daemon. Is it running?\n";
    }

    write(fd, cmd.c_str(), cmd.size());

    char buffer[512];
    int n = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    if (n <= 0) return "ERROR: No response from daemon.\n";

    buffer[n] = '\0';
    return std::string(buffer);
}

int cleanInput() {
    int cleanedInteger;
    bool running = true;

    while (running) {
        std::cout << "Enter a positive integer: ";
        std::string input;
        std::getline(std::cin, input);

        try {
        size_t position; //create an integer for the position of any non-integer characters
        cleanedInteger = std::stoi(input, &position);
        if (position != input.size()) {
            std::cout << "ERROR: Number entered was not an integer.\n";
            continue;
        }

        if (cleanedInteger < 0) {
            std::cout << "ERROR: Number entered was negative.\n";
            continue;
        }

        running = false; // valid positive integer was entered
        }

        catch  (std::invalid_argument&) {
            std::cout << "ERROR: Invalid input.\n";
        }

        catch (std::out_of_range&) {
            std::cout << "ERROR: Number was too large.\n";
        }
    }

    return cleanedInteger;
}

int main() {
    int choice;
    bool running = true;
    while (running) {
        std::cout << "\n Please choose an option below by entering the associated number\n"
                     "1. Insert a number\n"
                     "2. Delete a number\n"
                     "3. Print all numbers\n"
                     "4. Delete all numbers\n"
                     "5. Exit\n"
                     "Enter choice: ";
        std::string choiceString;
        std::getline(std::cin, choiceString);

        try {
            choice = std::stoi(choiceString);
        }
        catch(...){
            std::cout << "Invalid choice.\n";
        }

        if (choice == 1) {
            int cleanedInput = cleanInput();
            std::cout << send_command("INSERT " + std::to_string(cleanedInput));
        }
        
        else if (choice == 2) {
            int cleanedInput = cleanInput();
            std::cout << send_command("DELETE " + std::to_string(cleanedInput));
        }

        else if (choice == 3) {
            std::cout << send_command("PRINT");
        }

        else if (choice == 4) {
            std::cout << send_command("CLEAR");
        }

        else if (choice == 5) {
            running = false;
        }

        else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}