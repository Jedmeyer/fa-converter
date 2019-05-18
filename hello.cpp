#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "FAclassEpsilon.cpp"
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

    
    string qstring = request().query_string();
    ifstream webpage;
    string line;
    webpage.open("./html-pages/front-page.html");

    //Here we parse that good ole' query string for preparation
    //Basically use it to figure out what we execute.
    istringstream f(qstring);
    vector<string> qparsed;
    map<string,string> qmap;
    // Parse Everything into a vector
    string all;  
    while(getline(f, all, '&'))
    {
        qparsed.push_back(all);
    }


    // Sepearate variable names and values and throw them into the query map
    string title;
    string content;
    for(int i =0; i< qparsed.size(); i++){
        istringstream g(qparsed[i]);
        getline(g, title, '='); //Get the key value
        getline(g, content);    //Get the value... value?
        qmap.insert(pair<string,string>(title,content));
    }

    //Inserted to make it easier to be able to find the end
    qmap.insert(pair<string,string>("zdummy", "zdummy"));



    // ------------------LANDING Page-----------------------//
    // ==================================================== //
    // If we don't find a 'type' key - its the landing page.//
    if(qmap.find("type") == qmap.end()){
        cout << "We're gonna LANDING PAGE for a client!\n";

        if (webpage.is_open())
        {
            while ( getline (webpage,line))
            {
                response().out() << line << '\n';
            }
            webpage.close();
        }
    }



    // -----------------NFA OUTPUT PAGE---------------------//
    // ==================================================== //
    // ---If (type key == simulate) - its the output page---//
    if(qmap.find("type")->second == "simulate"){
        cout << "We're gonna SIMULATE for a client!\n";
        FA f;

        f.incomingFA(qmap.find("states")->second,qmap.find("start")->second,qmap.find("acc")->second,qmap.find("alpha")->second,qmap.find("trans")->second,qmap.find("input")->second,qmap.find("type")->second);
        //f.translateFA();
        //f.simulate("010011");
        //f.simulate("010101");
        webpage.open("simulate.txt"); 
        response().out()<< "<!DOCTYPE html><html>" << endl
        << "<body> <h1>Simulate Created: </h1>" << endl ;
        if (webpage.is_open())
        {
            while ( getline (webpage,line))
            {
                response().out() << line << '\n';
            }
            webpage.close();
             
        }

       
      }




    // ----------------DFA OUTPUT PAGE----------------------//
    // =====================================================//
    // ----If (type value == DFA) - its the translated page---//
    if(qmap.find("type")->second == "DFA"){
        cout << "We're gonna CONVERT for a client!\n";
    

        FA f;
        f.incomingFA(qmap.find("states")->second,qmap.find("start")->second,qmap.find("acc")->second,qmap.find("alpha")->second,qmap.find("trans")->second,qmap.find("input")->second,qmap.find("type")->second);
        f.translateFA();

        webpage.open("print.txt"); 

        response().out()
        << "<!DOCTYPE html><html>" << endl
        << "<body> <h1>DFA Created: </h1>" << endl;
        if (webpage.is_open())
        {
            while ( getline (webpage,line))
            {
                response().out() << line << '\n';
            }
            webpage.close();
             
        }

     
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
