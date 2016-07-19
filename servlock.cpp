#define LOCK "./s_lock.lock"
#define _PORT_ 25000
#define _CPORT_ 25001

int control_event(int cntl_sock){
	int x = accept(cntl_sock, NULL, NULL);
	if(x > 0)
		close(x);
	
	return x;
}

int is_locked(){
	
	int _STATE_ = -1;
	ifstream if_s(LOCK);
	
	if(if_s.good())
		_STATE_ = 0;
		
	if_s.close();
	return _STATE_;
};

int set_lock(){
	
	ofstream os_s(LOCK);
	
	if(os_s.good()){
		os_s.close();
		return 0;
	} else {
		os_s.close();
		return -1;
	}
};

int unlock(){
	int s = system("unlink ./s_lock.lock");
	return s;
};


int set_nonblock(int filedes){
	int temp_mode;
	temp_mode = fcntl(filedes, F_GETFL, 0);
	
	if(temp_mode < 0)
		return -1;
	
	if(temp_mode > 0)
		temp_mode &= ~O_NONBLOCK;
	
	temp_mode |= O_NONBLOCK;
	return fcntl(filedes, F_SETFL, temp_mode);
};


int set_serv_addr(int filedes, int addr_mode, int which){
	
	struct sockaddr_in serv_addr;
	
	serv_addr.sin_family = AF_INET;
	
	if(which >= 0){
		serv_addr.sin_port = htons(_CPORT_);
		addr_mode = 0;
	}else{
		serv_addr.sin_port = htons(_PORT_);
	}
	
	switch(addr_mode){
		case 0 :
			serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
			break;
		default :
			serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			break;
	}
	
	return bind(filedes, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
};

int set_listening_mode(int argc, char* argv[]){
	
	if(argc <= 1)
		return 0;
		
	if(argc > 1){
		if(*(argv[1]) != '0')
			return 1;
		else
			return 0;
	}
		
};
