#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/Reliaquest_daemon.sock"

std::map<int, time_t> numbers;

std::string handle_command(const std::string &cmd) {
    if (cmd.rfind("INSERT ", 0) == 0) {
        int num = std::stoi(cmd.substr(7));
        if (num <= 0) return "ERROR: Only positive integers allowed.\n";
        if (numbers.count(num)) return "ERROR: Number already exists.\n";

        time_t ts = time(nullptr);
        numbers[num] = ts;

        return "INSERTED: " + std::to_string(num) +
               " at timestamp " + std::to_string(ts) + "\n";
    }

    if (cmd.rfind("DELETE ", 0) == 0) {
        int num = std::stoi(cmd.substr(7));
        auto it = numbers.find(num);
        if (it == numbers.end()) return "ERROR: Number does not exist.\n";

        time_t ts = it->second;
        numbers.erase(it);

        return "DELETED: " + std::to_string(num) +
               " (timestamp " + std::to_string(ts) + ")\n";
    }

    if (cmd == "PRINT") {
        if (numbers.empty()) return "EMPTY\n";
        std::string out;
        for (auto &p : numbers) {
            out += std::to_string(p.first) +
                   " (timestamp " + std::to_string(p.second) + ")\n";
        }
        return out;
    }

    if (cmd == "CLEAR") {
        numbers.clear();
        return "CLEARED\n";
    }

    return "ERROR: Invalid command.\n";
}

int main() {
    unlink(SOCKET_PATH);

    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        return 1;
    }

    std::cout << "Daemon running at: " << SOCKET_PATH << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        char buffer[256];
        int n = read(client_fd, buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            std::string response = handle_command(buffer);
            write(client_fd, response.c_str(), response.size());
        }

        close(client_fd);
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}
