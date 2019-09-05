#include <memory>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <cstring>
#include <evhttp.h>

#define BUFFER_SIZE 1024

int main() {
  if (!event_init()) {
    std::cerr << "Failed to init libevent." << std::endl;
    return -1;
  }
  char const SrvAddress[] = "127.0.0.1";
  std::uint16_t SrvPort = 8083;
  std::unique_ptr<evhttp, decltype(&evhttp_free)> Server(evhttp_start(SrvAddress, SrvPort), &evhttp_free);

  if (!Server) {
    std::cerr << "Failed to init http server." << std::endl;
    return -1;
  }


  void (*OnReq)(evhttp_request *req, void *) = [] (evhttp_request *req, void *) {
    auto *OutBuf = evhttp_request_get_output_buffer(req);
    if (!OutBuf)
      return;

    char filename[100];
    char buffer[BUFFER_SIZE];
    strcpy(filename, "../resource");
    strcat(filename, evhttp_request_uri(req));

    FILE* file = fopen(filename, "r");

    int size = 0;
    if (file != NULL) {
      char c;
      int counter = 0;
      int sz = 0;

      fseek(file, 0, SEEK_END);

      sz = ftell(file);
      fseek(file, 0, SEEK_SET);

      evbuffer_add_printf(OutBuf, "HTTP/1.1 200 OK\n");
      evbuffer_add_printf(OutBuf, "Accept-Ranges: bytes\n");
      evbuffer_add_printf(OutBuf, "Content-Length: %d\n", sz);
      evbuffer_add_printf(OutBuf, "Content-Type: text/html\n\n");

      while ((c = fgetc(file)) != EOF) {
        buffer[counter] = c;
        counter++;

        if (counter >= BUFFER_SIZE - 10) {
          evbuffer_add_printf(OutBuf, "%s", buffer);
          size += counter;
          counter = 0;
        }
      }

      if (counter > 0) {
          evbuffer_add_printf(OutBuf, "%s", buffer);
          size += counter;
      }
      fclose(file);
    }

    evhttp_send_reply(req, HTTP_OK, "", OutBuf);
  };

  evhttp_set_gencb(Server.get(), OnReq, nullptr);
  if (event_dispatch() == -1) {
    std::cerr << "Failed to run messahe loop." << std::endl;
    return -1;
  }

  return 0;
}