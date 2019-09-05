#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

#define PORT 8080

#define MAX_POOL 100
#define BUFFER_SIZE 1024
#define FILENAME_SIZE 120
#define URL_SIZE 100

struct thread_args {
    int socket_fd;
    int connection_counter;
    int* active_socket;
};

void handle_request(struct thread_args* args) {
    int socket_fd = args->socket_fd;
    int connection_counter = args->connection_counter;
    char* buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
    char* url = (char*) malloc(URL_SIZE * sizeof(char));
    char* filename = (char*) malloc(FILENAME_SIZE * sizeof(char));
    int valread;

    valread = read(socket_fd, buffer, BUFFER_SIZE);
    sscanf(buffer, "GET %s HTTP/1.1\n", url);

    strcpy(filename, "../resource");
    strcat(filename, url);

    FILE* file = fopen(filename, "r");

    int size = 0;
    if (file != NULL) {
        char c;
        int counter = 0;
        int sz = 0;
        char content_length[50];

        fseek(file, 0, SEEK_END);

        sz = ftell(file);
        fseek(file, 0, SEEK_SET);

        sprintf(content_length, "Content-Length: %d\n", sz);
        send(socket_fd, "HTTP/1.1 200 OK\n", 16, 0);
        send(socket_fd, "Accept-Ranges: bytes\n", 21, 0);
        send(socket_fd, content_length, strlen(content_length), 0);
        send(socket_fd, "Content-Type: text/html\n\n", 25, 0);

        while ((c = fgetc(file)) != EOF) {
            buffer[counter] = c;
            counter++;

            if (counter >= BUFFER_SIZE - 10) {
                send(socket_fd, buffer, counter, 0);
                size += counter;
                counter = 0;
            }
        }

        if (counter > 0) {
            send(socket_fd, buffer, counter, 0);
            size += counter;
        }
        fclose(file);
    }
    printf("%5d. %d bytes message sent\n", connection_counter, size);
    *(args->active_socket) = *(args->active_socket) - 1;
    // free(args);
    close(socket_fd);
    free(buffer);
    free(filename);
    free(url);
}

int main(int argc, char const *argv[]) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int connection_counter = 0;
    int addrlen = sizeof(address);
    int active_socket = 0;

    while (1) {
        int new_socket;
        long unsigned int thread_id;
        if ((new_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        while (active_socket >= MAX_POOL);
        active_socket++;
        struct thread_args* args = (struct thread_args*) malloc(1 * sizeof(struct thread_args));
        args->connection_counter = connection_counter + 1;
        args->socket_fd = new_socket;
        args->active_socket = &active_socket;
        pthread_create(&thread_id, NULL, (void*) handle_request, args);
        pthread_detach(thread_id);
        ++connection_counter;
    }

    return 0;
}
