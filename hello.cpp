#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include<map>
#include <iostream>
#include<sstream>
#include <fstream>
#include<vector>
#include"helper_functions.hpp"

using namespace std;

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
    
    //Here we parse that good ole' query string for preparation
    //Basically use it to figure out what we execute.

    map<string,string> simulate;
    simulate.insert("type", "simulate");
    map<string,string> dfa;
    dfa.insert("type", "DFA");
    
    string qstring = request().query_string();
    ifstream webpage;
    string line;
    webpage.open("./html-pages/front-page.html");    
    map<string,string> *qmap = parseQstring(qstring);
    

    // ------------------LANDING Page-----------------------//
    // ==================================================== //
    // If we don't find a 'type' key - its the landing page.//
    if(qmap->find("type") == qmap->end()){
        if (webpage.is_open())
        {
            while ( getline (webpage,line))
            {
                response().out() << line << '\n';
            }   
            webpage.close();
        }
    }



     // ----------------NFA OUTPUT PAGE---------------------//
    // ==================================================== //
    // ---If (type key == simulate) - its the output page---//
    if(qmap->find("type") == simulate.front()){
        









    }

    // ----------------DFA OUTPUT PAGE----------------------//
    // =====================================================//
    // ----If (type key == DFA) - its the output page-------//
    if(qmap->find("type") == dfa.front()){
        
        response().out() << "<!DOCTYPE html><html>" << endl
        << "<body> <h1>DFA Created: </h1>" << endl
        << "<h2>States: </h2>" << endl
        << /* elaina states*/ << endl
        << "<h2>Alphabet: </h2>" << endl
        << /* Jason  Alphabet*/ << endl 
        << "<h2>Accept States: </h2>" << endl
        << /* Jason Accept State */ << endl
        << "<h2>Transition Functions: </h2>" << endl
        << /* Elaina  Trans function*/ << endl
        << "</body></html>";
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
