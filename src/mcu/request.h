#pragma once

#include <StandardCplusplus.h>
#include <map>

class Request
{	
private:
	std::map<char*, char*> _headers;
	char* _source;
	char* _body;
	char* _method;

public:
	Request(char* method, char* source);

	void setBody(char* data);
	void addHeader(char* key, char* value);

	char* getSource();
	char* getBody();
	char* getMethod();

	std::map<char*, char*>& getHeaders();
};
