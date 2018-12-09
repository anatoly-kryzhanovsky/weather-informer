#include <Arduino.h>
#include "Connectionc.h"
#include "Response.h"

class RestClient {

  public:
    RestClient(Connection* connection, const char* host);
    RestClient(Connection* connection, const char* _host, int _port);

    Response* request(const char* method, const char* path, const char* body);
    void setHeader(const char*);
    void setContentType(const char*);

    Response* get(const char*);
    Response* post(const char* path, const char* body);
    Response* put(const char* path, const char* body);
    Response* del(const char*);    

  private:
	Connection* _connection;
};
