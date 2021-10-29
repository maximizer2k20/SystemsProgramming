int main(int argc, char **argv)
{
  int server_socket = setup_server(SERVERPORT, SERVER_BACKLOG);
  
  while (true) {
    
    printf("Waiting for connections...\n");
    
    int client_socket = accept_new_connection(server_socket);
    
    
    handle_connection(client_socket);
    
  }
  
  return 0;
}

int setup_server(short port, int backlog) {
  int server_socket, client_socket, addr_size;
  SA_IN server_addr;
  
  check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create socket");
  
  // initialize the address struct
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);
  
  check(bind(server_socket, (SA*)&server_addr, sizeof(server_addr)), "Bind failed");
  check(listen(server_socket, backlog), "Listen failed"); 
  return server_socket;
}

int accept_new_connection(int server_socket) {
  int addr_size = sizeof(SA_IN);
  int client_socket;
  SA_IN client_addr;
  check(client_socket = 
          accept(server_socket, 
                  (SA*)&client_addr, 
                  (socklen_t*)&addr_size),
        "accept failed");
  return client_socket;
}

int check(int exp, const char *msg) {
    if (exp == SOCKETERROR) {
      perror(msg);
      exit(1);
    }
  return exp;
}

void * handle_connection(int client_socket) {
  char buffer[BUFSIZE];
  size_t bytesRead;
  int msgsize = 0;
  char actualpath[PATH_MAX+1];
  
  //read the client's message- the name of file to read
  while((bytesRead = read(client_socket, buffer+msgsize, sizeof(buffer)-msgsize-1) {
                          msgsize +- bytesRead;
            if (msgsize > BUFSIZE-1 || buffer[msgsize-1] == '\n') break;
  }
  check(bytesRead, "recv error:);
        buffer[msgsize-1] =0; // null terminate the message and remove \n
        
        printf("REQUEST: %s\n", buffer);
        fflush(stdout);
        
        //validity check
        if (realpath(buffer, actualpath) == NULL) {
          printf("ERROR(bad path): %s\n", buffer);
          close(client_socket);
          return NULL;
        }
        
        //read file and send its content to client
        FILE *fp = fopen(actualpath, "r");
        if (fp == NULL) {
          printf("ERROR(open): %s\n", buffer);
          close(client_socket);
          return NULL;
        }
        
        while(bytesRead = fread(buffer, 1, BUFSIZE, fp)) >0) {
    //printf("sending %zu bytes\n", bytesRead);
    write(client_socket, buffer, bytesRead);
  }
         close(client_socket);
         fclose(fp);
         printf("closing connection\n");
         return NULL;
        }
         
          
         
  
  
