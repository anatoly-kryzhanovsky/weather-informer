#include "Response.h"

const char* Response::readLine(Connection* connection)
{
	char buf[MaxLineLength];
	char current = 0;
	int position = 0;
	
	while(connection->read(&current, 1) && current != '\n' && position < MaxLineLength)
	{
		buf[position++] = current;
	}
	
	buf[position] = 0;
}

void Response::readFromConnection(Connection* connection)
{
	bool currentLineIsBlank = true;
	bool httpBody = false;
	bool inStatus = false;

	char statusCode[4];
	int i = 0;
	int code = 0;

	while (_connection->connected()) 
	{
		if (_connection->available()) 
		{
			char c = client.read();
      
			if(c == ' ' && !inStatus)
				inStatus = true;
      
			if(inStatus && i < 3 && c != ' ')
			{
				statusCode[i] = c;
				i++;
			}
      
			if(i == 3)
			{
				statusCode[i] = '\0';
				code = atoi(statusCode);
			}

			if(httpBody)
			{
				if(response != NULL) response->concat(c);
			}
			else
			{
				if (c == '\n' && currentLineIsBlank) 
				{
					httpBody = true;
				}

				if (c == '\n') {
					currentLineIsBlank = true;
				}
				else if (c != '\r') 
				{
					currentLineIsBlank = false;
				}
			}
		}
	}

	return code;
}

const char* Response::getContent()
{
}

int Response::status()
{
}