#pragma once

#include <Arduino.h>
#include "Connection.h"
#include "Response.h"
#include "Request.h"

class RestClient 
{
private:
    const char* host;
    int _port;
    Connection* _connection;

public:
    RestClient(Connection* connection, const char* host);
    RestClient(Connection* connection, const char* host, int port);

    Response* request(const char* method, const char* path, const char* body);
    void setHeader(const char*);
    void setContentType(const char*);

    Response* get(const char* path);
    Response* post(const char* path, const char* body);
    Response* put(const char* path, const char* body);
    Response* delete(const char* path);

private:
    Response* execute(Request* request);
};
