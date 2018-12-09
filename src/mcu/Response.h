#ifndef __RESPONSE_H__
#define __RESPONSE_H__

class Response
{	
	private:
		const int MaxLineLength = 512;

	public:
		const char* getContent();
		int status();
		
	private:
		const char* readLine();
};

#endif