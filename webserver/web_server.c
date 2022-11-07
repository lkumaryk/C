#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
 
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
        int PORT = atoi(argv[1]);
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
        char output_cmd[1024]={0};
        int ishex(int n)
        {
	return	(n >= '0' && n <= '9')	|| (n >= 'a' && n <= 'f') ||(n >= 'A' && n <= 'F');
        }
        void decode_url(char *url,char *d_url) 
        {
        char *o;
	const char *end = url + strlen(url);
	int c;
	for (o = d_url; url <= end; o++) { 
                
		c = *url++;
		if (c == '+') c = ' ';
		else if (c == '%' && (	!ishex(*url++)	||
					!ishex(*url++)	||
					!sscanf(url - 2, "%2x", &c)))
			
                printf("%d",-1);
		if (d_url) *o = c;
	}
        
        }
       
        const char *d_response = "HTTP/1.1 404 Not Found\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Not Found</title></head>"
"<body><h1>404 Not Found</h1></body></html>\r\n";

	char *response = "HTTP/1.1 200 OK\r\n"

        //\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\n"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
        

	valread = read( new_socket , buffer, 1024);
        char output[strlen(buffer) + 1];
     
        decode_url(buffer,output);
	int pos;
        int i,j;
        if(strstr(output, "exec/") != NULL) {
           printf("%s\n",output );
        char *subs = "exec/";
        for(i=0;output[i]!='\0';i++)
        {
        j=0;
        if(output[i]==subs[j])
        {
            pos=i+1;
            while(output[i]==subs[j])
            {
                i++;
                j++;
            }
 
            if(subs[j]=='\0')
            {
                printf("The substring is present in given string at position %d\n",pos);
                break;
            }
            else
            {
                i=pos;
                pos=0;
            }
}        }

         char *cmd= output+pos+4;
         
         
         printf("%s", cmd);
         strtok(cmd, "\n");
         strtok(cmd, "\r");
         cmd[strlen(cmd)]='\0';
      
        
       
        system(cmd);
        FILE *fpipe;
  
    char b = 0;

    if (0 == (fpipe = (FILE*)popen(cmd, "r")))
    {
        perror("popen() failed.");
        exit(EXIT_FAILURE);
    }
    int i =0;
    while (fread(&b, sizeof b, 1, fpipe))
    {
        output_cmd[i++] = b;
        printf("%c", b);
    }

    pclose(fpipe);
        
        printf("%s\n",output_cmd);
        //strcat(response,output);
        send(new_socket , output_cmd , strlen(output_cmd) , 0 ); 
        //printf("%s\n",response);
        }
        else
        {
	send(new_socket , d_response , strlen(d_response) , 0 ); 
        printf("%s\n",d_response);
        } 
	return 0;
} 

