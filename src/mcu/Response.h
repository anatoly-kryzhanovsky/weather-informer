#pragma once

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
