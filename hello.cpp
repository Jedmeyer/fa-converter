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
#include <unistd.h>


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
    ifstream simulate;
    ifstream dfa;
    string line;
    webpage.open("./html-pages/front-page.html");

    //Here we parse that good ole' query string for preparation
    //Basically use it to figure out what we execute.

    vector<string> qparsed;
    vector<string> qgive;
    map<string,string> qmap;
    stringstream f(qstring);
    // Parse Everything into a vector
    string all; 
    while(getline(f, all, '&'))
    {
        qparsed.push_back(all);
    }
    cout << all << endl;



    // Sepearate variable names and values and throw them into the query map
    string title;
    string content;
    for(int i =0 ; i< qparsed.size(); i++){
        stringstream g(qparsed[i]);
        getline(g, title, '='); //Get the key value
        getline(g, content);    //Get the value... value?

        cout << "found: " << title << " with: " << content << endl;
        qgive.push_back(content);        
        qmap.insert( pair<string,string>(title,content));
    }
        qmap.insert(pair<string, string>("zdumb", "zdumb"));
    for(int i=0; i<qgive.size(); i++)
        cout << qgive[i];
    cout << endl;
    

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
        f.incomingFA(qgive[0],qgive[1],qgive[2],qgive[3],qgive[4],qgive[5],qgive[6]);
        for(int i=0; i<qgive.size(); i++)
            cout << qgive[i] << endl;
        //f.translateFA();
        //f.simulate("010011");
        //f.simulate("010101");
        string send = f.simulate();
        
        system("cat ./txt-files/simulate.txt | ./terminal-to-html -preview > out.html");
        simulate.open("./out.html");
        usleep(500000);
        
        if (simulate.is_open())
        {
            cout << "out.html opened!" << endl;
            while ( getline (simulate,line))
            {
                response().out() << line << '\n';
            }
            simulate.close();
             
        }

       
      }




    // ----------------DFA OUTPUT PAGE----------------------//
    // =====================================================//
    // ----If (type value == DFA) - its the translated page---//
    if(qmap.find("type")->second == "DFA"){
        
        
        cout << "We're gonna CONVERT for a client!\n";
    

        FA f;
        f.incomingFA(qgive[0],qgive[1],qgive[2],qgive[3],qgive[4],qgive[5],qgive[6]);
        //f.incomingFA(qgive[0],qgive[1],qgive[2],qgive[3],qgive[4],qgive[5],qgive[6]);
        f.translateFA();

        system("cat ./txt-files/print.txt | ./terminal-to-html -preview > out.html");
        usleep(500000);

        dfa.open("out.html"); 

        response().out()
        << "<!DOCTYPE html><html>" << endl
        << "<body> <h1>DFA Created: </h1>" << endl;
        if (dfa.is_open())
        {
            while ( getline (dfa,line))
            {
                response().out() << line << '\n';
            }
            dfa.close();
             
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
