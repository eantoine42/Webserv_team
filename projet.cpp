#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

class Route {
public:
    Route() {}
    virtual ~Route() {}

    virtual bool matches(const std::string& method, const std::string& url) const = 0;
    virtual void handle_request(int client_socket) const = 0;
};

class StaticFileRoute : public Route {
public:
    StaticFileRoute(const std::string& root_directory)
        : root_directory_(root_directory)
    {}

    bool matches(const std::string& method, const std::string& url) const {
        return method == "GET" && url.find("..") == std::string::npos;
    }

    void handle_request(int client_socket) const {
        // Extract path from request
        std::string request = read_request(client_socket);
        std::string path = extract_path(request);

        // Open the file for reading
        std::string full_path = root_directory_ + path;
        int file = open(full_path.c_str(), O_RDONLY);
        if (file == -1) {
            send_error(client_socket, 404, "Not Found");
            return;
        }

        // Send the file contents to the client
        send_file(client_socket, file);

        // Close the file descriptor
        close(file);
    }

private:
    std::string root_directory_;

    std::string read_request(int client_socket) const {
        std::string request;

        // Read data from the client until the end of the request is reached
        char buffer[1024];
        int bytes_read;
        do {
            bytes_read = recv(client_socket, buffer, 1024, 0);
            if (bytes_read == -1) {
                throw std::runtime_error("Error reading from client socket");
            }
            request.append(buffer, bytes_read);
        } while (bytes_read == 1024 || (bytes_read > 0 && request.find("\\r\\n\\r\\n") == std::string::npos));

        return request;
    }

    std::string extract_path(const std::string& request) const {
        std::string path;

        // Find the start of the path in the request
        std::string::size_type start = request.find(" ");
        if (start != std::string::npos) {
            start++;
            // Find the end of the path in the request
            std::string::size_type end = request.find(" ", start);
            if (end != std::string::npos) {
                // Extract the path from the request
                path = request.substr(start, end - start);
            }
        }

        return path;
    }

    void send_error(int client_socket, int status_code, const std::string& status_text) const {
        std::string response =
            "HTTP/1.1 " + std::to_string(status_code) + " " + status_text + "\\r\\n"
            "Content-Type: text/html\\r\\n"
            "\\r\\n"
            "<html>\\r\\n"
            "<head><title>" + std::to_string(status_code) + " " + status_text + "</title></head>\\r\\n"
            "<body><h1>" + std::to_string(status_code) + " " + status_text + "</h1></body>\\r\\n"
            "</html>\\r\\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }

    void send_file(int client_socket, int file) const {
        char buffer[1024];
        int bytes_read;
        do {
            bytes_read = read(file, buffer, 1024);
            if (bytes_read == -1) {
                throw std::runtime_error("Error reading file");
            }
            if (bytes_read > 0) {
                send(client_socket, buffer, bytes_read, 0);
            }
        } while (bytes_read == 1024);
    }
};

class HttpServer {
public:
    HttpServer(const std::string& host, int port, size_t client_body_buffer_size,
               const std::map<std::string, Route*>& routes)
        : host_(host), port_(port), client_body_buffer_size_(client_body_buffer_size), routes_(routes)
    {}

    void run() {
        // Create the server socket
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1) {
            throw std::runtime_error("Error creating server socket");
        }

        // Set the server socket to non-blocking mode
        fcntl(server_socket, F_SETFL, O_NONBLOCK);

        // Bind the server socket to the specified address and port
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port_);
        server_address.sin_addr.s_addr = inet_addr(host_.c_str());
        if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            throw std::runtime_error("Error binding server socket");
        }

        // Listen for incoming connections on the server socket
        if (listen(server_socket, 1024) == -1) {
            throw std::runtime_error("Error listening on server socket");
        }

        // Initialize the client socket buffer
        std::vector<char> client_body_buffer(client_body_buffer_size_);

        // Wait for incoming connections
        while (true) {
            // Accept an incoming connection
            struct sockaddr_in client_address;
            socklen_t client_address_size = sizeof(client_address);
            int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
            if (client_socket == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    // No incoming connection, continue waiting
                    continue;
                }
                else {
                    throw std::runtime_error("Error accepting incoming connection");
                }
            }

            // Read the client request
            std::string request = read_request(client_socket);

            // Extract the HTTP method and URL from the request
            std::string method = extract_method(request);
            std::string url = extract_url(request);

            // Find the matching route for the request
            Route* route = find_matching_route(method, url);

            // If no route was found, return a 404 error
            if (!route) {
                send_error(client_socket, 404, "Not Found");
                close(client_socket);
                continue;
            }

            // Handle the request using the matching route
            route->handle_request(client_socket);

            // Close the client socket
            close(client_socket);
        }
    }

private:
    std::string host_;
    int port_;
    size_t client_body_buffer_size_;
    std::map<std::string, Route*> routes_;

    std::string read_request(int client_socket) const {
        std::string request;

        // Read data from the client until the end of the request is reached
        char buffer[1024];
        int bytes_read;
        do {
            bytes_read = recv(client_socket, buffer, 1024, 0);
            if (bytes_read == -1) {
                throw std::runtime_error("Error reading from client socket");
            }
            request.append(buffer, bytes_read);
        } while (bytes_read == 1024 || (bytes_read > 0 && request.find("\\r\\n\\r\\n") == std::string::npos));

        return request;
    }

    std::string extract_method(const std::string& request) const {
        std::string method;

        // Find the end of the method in the request
        std::string::size_type end = request.find(" ");
        if (end != std::string::npos) {
            // Extract the method from the request
            method = request.substr(0, end);
        }

        return method;
    }

    std::string extract_url(const std::string& request) const {
        std::string url;

        // Find the start of the path in the request
        std::string::size_type start = request.find(" ");
        if (start != std::string::npos) {
            start++;
            // Find the end of the path in the request
            std::string::size_type end = request.find(" ", start);
            if (end != std::string::npos) {
                // Extract the path from the request
                url = request.substr(start, end - start);
            }
        }

        return url;
    }

    Route* find_matching_route(const std::string& method, const std::string& url) const {
        for (std::map<std::string, Route*>::const_iterator it = routes_.begin(); it != routes_.end(); ++it) {
            if (it->second->matches(method, url)) {
                return it->second;
            }
        }
        return NULL;
    }

    void send_error(int client_socket, int status_code, const std::string& status_text) const {
        std::string response =
            "HTTP/1.1 " + std::to_string(status_code) + " " + status_text + "\\r\\n"
            "Content-Type: text/html\\r\\n"
            "\\r\\n"
            "<html>\\r\\n"
            "<head><title>" + std::to_string(status_code) + " " + status_text + "</title></head>\\r\\n"
            "<body><h1>" + std::to_string(status_code) + " " + status_text + "</h1></body>\\r\\n"
            "</html>\\r\\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
};

int main() {
    // Define the routes
    std::map<std::string, Route*> routes;
    routes["/static"] = new StaticFileRoute("/var/www/html");

    // Create the HTTP server and run it
    HttpServer server("127.0.0.1", 80, 1024, routes);
    server.run();

    // Cleanup the routes
    for (std::map<std::string, Route*>::iterator it = routes.begin(); it != routes.end(); ++it) {
        delete it->second;
    }

    return 0;
}
