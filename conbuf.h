class conversation_buf{
	private:
		int limit;
		int index;
		int quantity;
		char** data;
		
		int index_push();
	public:
		conversation_buf(int maxsiz = 100);
		~conversation_buf();
		void operator >> (int filedes);
		void operator << (char * pstr);
};
