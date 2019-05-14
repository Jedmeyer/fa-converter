#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include<map>
#include <iostream>
#include <fstream>


class my_hello_world : public cppcms::application {
public:
    my_hello_world(cppcms::service &srv) :
        cppcms::application(srv) 
    {

    }
    virtual void main(std::string url);
};

void my_hello_world::main(std::string /*url*/)
{
    std::string myString = request().query_string();
    std::ifstream webpage;
    std::string line;
    webpage.open("./html-pages/front-page.html");    
    
    if (webpage.is_open())
    {
        while ( getline (webpage,line) )
        {
            response().out() << line << '\n';
        }   
        webpage.close();
    }


}

int main(int argc,char ** argv)
{
    try {
        cppcms::service srv(argc,argv);
        srv.applications_pool().mount(cppcms::applications_factory<my_hello_world>());
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
}
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
