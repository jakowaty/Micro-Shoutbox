int conversation_buf::index_push(){
	if(index < (limit - 1))
		index = index + 1;
	else
		index = 0;

	return index;	
};

conversation_buf::conversation_buf(int maxsiz){
	limit = maxsiz;
	data = new char*[maxsiz]	;
	index = 0;
	quantity = 0;
	for(int i = 0; i < maxsiz; i++){
		data[i] = 0;
	}
};

conversation_buf::~conversation_buf(){
	for(int i = 0; i < limit; i++){
		delete data[i];
	}
	delete []data;
};

void conversation_buf::operator >> (int filedes){
	for(int i = 0; i < quantity; i++){
		char ** tmpc = &(data[i]);
		write(filedes, (void *)data[i], strlen(tmpc[0]));
	}
};

void conversation_buf::operator << (char* pstr){
	delete data[index];
	data[index] = pstr;
	if(quantity < limit)
		quantity = quantity + 1;
	
	index_push();
};


