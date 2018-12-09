#include <request.h>

Request::Request(char* method, char* source)
	:_method(method), _source(source), _body(nullptr)
{
}

void Request::setBody(char* data)
{
	_body = data;
}

void Request::addHeader(char* key, char* value)
{
	auto it = _headers.find(key);
	if(it == _headers.end())
		_headers[key] = value;
	else
		it->second = value;
}

char* Request::getSource()
{
	return _source;
}

char* Request:getBody()
{
	return _body;
}
	
char* Request::getMethod()
{
	return _method;
}

std::map<char*, char*>& Request::getHeaders()
{
	return _headers;
}
