/*
 * TO DO:
 * - do something with all the if() shitty repetitions
 * - i still dont have control over x if it is opened in second while()
 */
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

#include "./conbuf.h"
#include "./servlock.h"
#include "./conbuf.cpp"
#include "./servlock.cpp"

int main(int argc, char* argv[]){
	
	int ctrl_state = -1;
	int client_sock = -1;

	int listening_mode = set_listening_mode(argc, argv);
	
	if(is_locked() == 0)
		return -1;
	
	set_lock();
	
	int main_comm_sock;
	int main_cntl_sock;
	
	socklen_t incoming_addr_len;
	struct sockaddr incoming_addr; 
	
	main_comm_sock = socket(PF_INET, SOCK_STREAM, 0);
	main_cntl_sock = socket(PF_INET, SOCK_STREAM, 0);

	if(main_comm_sock < 0 || main_cntl_sock < 0){
		close(main_cntl_sock);
		close(main_comm_sock);
		unlock();
		exit(-2);
	}
	
	if(set_serv_addr(main_comm_sock, listening_mode, -1) < 0){
		close(main_cntl_sock);
		close(main_comm_sock);
		unlock();
		exit(-3);
	}
	
	if(set_serv_addr(main_cntl_sock, listening_mode, 0) < 0){
		close(main_cntl_sock);
		close(main_comm_sock);
		unlock();
		exit(-4);
	}	
	
	if(listen(main_comm_sock, 10) < 0){
		close(main_cntl_sock);
		close(main_comm_sock);
		unlock();
		exit(-5);
	}
	
	if(listen(main_cntl_sock, 1) < 0){
		close(main_cntl_sock);
		close(main_comm_sock);
		unlock();
		exit(-6);
	}
	
	if((set_nonblock(main_cntl_sock)) < 0){
		close(main_cntl_sock);
		close(main_comm_sock);
		unlock();
		exit(-7);
	}
		
	conversation_buf buf = conversation_buf();
	
	/* locked
	 * buffor enabled
	 * control&communication opened
	 * addresses are assigned
	 * control put into nonlocking mode
	 * */
		
	while((ctrl_state = control_event(main_cntl_sock)) < 0)
	{
		client_sock = accept(main_comm_sock, &incoming_addr, &incoming_addr_len);
		if((ctrl_state = control_event(main_cntl_sock)) >= 0)
			break;
		
		if(client_sock < 0)
			continue;
		
		char main_incoming_buf[256];

		ssize_t rbytes = read(client_sock, (void *)main_incoming_buf, 256);
		
		if((ctrl_state = control_event(main_cntl_sock)) >= 0)
			break;
			
		if(rbytes > 2){

			char* tmp_cstr = new char[rbytes + 1];
				
			for(int i = 0; i < rbytes; i++){
				tmp_cstr[i] = main_incoming_buf[i];
			}
			
			tmp_cstr[rbytes] = '\0' ;
			buf << tmp_cstr;
			buf >> client_sock;
			
		}else if(rbytes <= 2){
			
				buf >> client_sock;	
				
		}
		
		close(client_sock);
		client_sock = -1;
	}
	
	if(client_sock > 0)
		close(client_sock);
		
	close(main_cntl_sock);
	close(main_comm_sock);
	unlock();
	return 0;
}
