#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <map>
#include <iostream>
#include <fstream>


class hello : public cppcms::application {
public:
    hello(cppcms::service &srv) :
        cppcms::application(srv) 
    {
        dispatcher().assign("/proc",&hello::proc,this);
        mapper().assign("proc","/proc");

        dispatcher().assign("",&hello::main,this);  
        mapper().assign("");
        
        mapper().root("/");  
    }

    virtual void main(std::string url);
    virtual void proc(std::string url);
};

void hello::main(std::string /*url*/)
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

virtual void proc(std::string url)
{
    std::string myString = request().query_string();


    response().out() <<
            "<html>\n"  
        "<body>\n"  
        "  <h1>"<< myString <<  "</h1>\n"  
        "</body>\n"  
        "</html>\n";  

}


int main(int argc,char ** argv)
{
    try {
        cppcms::service srv(argc,argv);
        srv.applications_pool().mount(cppcms::applications_factory<hello>());
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
}
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
