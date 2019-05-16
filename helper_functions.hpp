#include<sstream>
#include<map>
#include<vector>
using namespace std;

map<string, string> parseQstring(string qstring){
    istringstream *f = new istringstream(qstring);
    vector<string> qparsed;

    map<string,string> qmap;

    // Parse Everything into a vector
    string all;  
    while(getline(*f, all, '&'))
    {
        qparsed.push_back(all);
    }


    // Sepearate variable names and values and throw them into the query map
    string title;
    string content;
    for(int i =0; i< qparsed.size(); i++){
        delete f;
        f = new istringstream(qparsed[i]);
        getline(*f, title, '='); //Get the key value
        getline(*f, content);    //Get the value... value?
        qmap.insert(pair<string,string>(title,content));
    }
    delete f;
    return qmap;
}

