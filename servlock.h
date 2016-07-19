int is_locked();
int set_lock();
int unlock();
int set_nonblock(int filedes);
int set_serv_addr(int filedes, int addr_mode, int which);
int set_listening_mode(int argc, char* argv[]);
int control_event(int main_cntl_sock);
