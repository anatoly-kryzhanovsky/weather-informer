#include <Arduino.h>
#include "restclient.h"

RestClient:: RestClient(Connection* connection, const char* host)
    :_host(host), _port(80), _connection(connection)
{
}

RestClient:: RestClient(Connection* connection, const char* host, int port)
    :_host(host), _port(port), _connection(connection)
{
}

Response* RestClient::execute(Request* request)
{
    
}

Response* RestClient::get(const char* path)
{
    return request("GET", path, nullptr);
}

Response* RestClient::post(const char* path, const char* body)
{
    return request("POST", path, body);
}

Response* RestClient::put(const char* path, const char* body)
{
    return request("PUT", path, body);
}

Response* RestClient::delete(const char* path)
{
    return request("DELETE", path, nulltpr);
}

    Response* request(const char* method, const char* path, const char* body);
    void setHeader(const char*);
    void setContentType(const char*);