#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

class State {
public:
  string name;
  int id;
  //FIX:
  vector <vector<State*> > next;
  bool accept = false;

  State(string n) { name = n; }
  State(string n,int iden) {name = n; id = iden;}
  State() {
      name = "";
      id = 1;
      //FIX: initialize next so that bottom layer has size 1
  }

  //Comparison Operators
  bool operator<(const State& s2){return(this->id < s2.id);};
  bool operator>(const State& s2){return(this->id > s2.id);};
  bool operator==(const State& s2){return(this->id == s2.id);};
  bool operator!=(const State& s2){return(this->id != s2.id);};
  bool operator<=(const State& s2){return(this->id <= s2.id);};
  bool operator>=(const State& s2){return(this->id >= s2.id);};


  void printState(vector<char>alphaorder) {
    cout << "State " << name << endl;
    cout << "\tid " << id << endl;
    cout << "\taccept " << accept << endl;
    for (int i=0; i<next.size(); i++) {
      cout <<"\tinput " << alphaorder[i] << endl;
      cout << "\t\t";
      for (int j=0; j<next[i].size(); j++) {
        if (next[i][j]!=NULL) {cout << next[i][j]->name << ", ";}
      }
      cout << endl;
    }
  }
};


//More Comparison Operators
bool operator<(const State& s1,const State& s2){return(s1.id < s2.id);};
bool operator>(const State& s1,const State& s2){return(s1.id > s2.id);};
bool operator==(const State& s1,const State& s2){return(s1.id == s2.id);};
bool operator>=(const State& s1,const State& s2){return(s1.id >= s2.id);};
bool operator<=(const State& s1,const State& s2){return(s1.id <= s2.id);};

//calculates size of array
int arrsize (char * arr) {
  int size = 0;
  int i = 0;
  while (arr[i]!='\0') {
    size++;
    i++;
  }
  return size;
}

// function to print string in sorted order
string sortString(string &str) {
   sort(str.begin(), str.end());
   return str;
}

string * center(int bnum, int spaces, int i, string * display, string** tree) {
  if (tree[i][bnum] != "_") {
    int start = bnum * spaces;
    int loc = floor((spaces-1)/2) + start;
    display[i][loc] = tree[i][bnum][0];
  }
  return display;
}

class FA {
  //Primes for id
  int* primes = new int[100] {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
  43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127,
  131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
  211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
  293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383,
  389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
  479, 487, 491, 499, 503, 509, 521, 523, 541};
  int primetracker = 0;
  int numStates = 0;
  int epsilon = -1;
  vector<State>initFA;
  int numAlpha = 0;
  int numAlphaDFA = 0;
  vector<char> alphaorder;
  vector<State> transFA;
  char * input;
  int startstate;

  public: 
  
  void printDFA(stringstream &o) {
    
    //States
    o << "States: {";
    for (int i=0; i<transFA.size(); i++) {
      o << transFA[i].name << ",";
    }
    o << "}" << endl;

    //Start State
    o << "Start State: " << transFA[0].name << endl;

    //Accept states
    o << "Accept States: {";
    for (int i=0; i<numStates; i++) {
      if (initFA[i].accept == true) {
        for (int j=0; j<transFA.size(); j++) {
          if (transFA[j].id % initFA[i].id == 0) {
            o << transFA[j].name << ",";
          }
        }
      }
    }
    o << "}" << endl;

    //alphabet
    o << "Alphabet: {";
    for (int i=0; i<numAlphaDFA; i++) {
      o << alphaorder[i] << ",";
    }
    o << "}" << endl;

    //Transition Functions
    o << "Transition Functions:" << endl;
    for (int i=0; i<transFA.size(); i++) {
      for (int j=0; j<numAlphaDFA; j++) {
        o << "𝛿(" << transFA[i].name << "," << alphaorder[j] << ") = " << transFA[i].next[j][0]->name << endl;
      }
    }
  }

  public: bool inStateList(vector<State> Func, State cur) {
    //FIX: check if cur is in transFA[i] (binary search)
    for (int i = 0; i < Func.size(); i++)
    {
        if (Func[i].id == cur.id)
        {
            return true;
        }
    }
    return false;
  }

  public: void incomingFA(string states, string start, string acc, string alpha, string trans, string instring, string type) {
     input = new char[instring.length() + 1];
     strcpy(input,instring.c_str());

    //States
    initFA.resize(0);
    for (int i = 0; i<states.length(); i++)
    {
        if (states[i] != ',' & states[i] != ' ')
        {
            initFA.push_back(string(1,states[i]));
            initFA[numStates].id = primes[primetracker];
            numStates++;
            primetracker++;
        }
    }

    //start and acc
    for (int i = 0; i < acc.length(); i++)
    {
        if (acc[i] != ',' & acc[i] != ' ')
        {
            for (int j=0; j < numStates; j++)
            {
                if (initFA[j].name == string(1,acc[i]))
                {
                    initFA[j].accept = true;
                }
                if (initFA[j].name == start) {
                  startstate = j;
                }
            }
        }
    }

    //alpha
    alphaorder.resize(0);
    for (int i=0; i<alpha.length(); i++)
    {
        if (alpha[i]!=',' & alpha[i]!=' ')
        {
            alphaorder.push_back(alpha[i]);
            if (alpha[i] == 'E') {
              epsilon = numAlpha;
            }
            numAlpha++;
        }
    }

    //Puts epsilon in back of alphaorder if it exists
    if (epsilon != -1) {
      char temp = alphaorder[epsilon];
      alphaorder[epsilon] = alphaorder[numAlpha-1];
      alphaorder[numAlpha-1] = temp;
      epsilon = numAlpha-1;
    }
    numAlphaDFA = numAlpha; //CHANGE LATER IN CODE WHEN GET RID OF EPSILON


    for (int i = 0; i < numStates; i++)
    {
        //initializes each next have size of number of letters in alphabet
        initFA[i].next.resize(numAlpha); //= new vector<vector<State*>>(numAlpha);
    }

    //input
    int curState = -1;
    int curinput = -1;
    for (int i=0; i<trans.length(); i++)
    {
        //find origin state
        for (int j = 0; j < numStates; j++)
        {
            if (initFA[j].name == string(1,trans[i]))
            {
                curState = j;
                break;
            }
        }
        i += 2; //move to input

        //find input value
        for (int j = 0; j < numAlpha; j++)
        {
            if (trans[i] == alphaorder[j])
            {
                curinput = j;
                break;
            }
        }
        i+=2; //move to nextstates

        //find next states
        while(trans[i] != ';' & i<trans.length())
        {
            if (trans[i] != ',' & trans[i] !=' ')
            {
                //find State that matches input[k]
                for (int j = 0; j < numStates; j++)
                {
                    if (initFA[j].name == string(1,trans[i]))
                    {
                        //add to initFA next
                        initFA[curState].next[curinput].push_back(&initFA[j]);
                        break;
                    }
                }
            }
            i++;
        }
    }

    cout << "initFA data:" << endl;
    for (int i=0; i<numStates; i++) {
      initFA[i].printState(alphaorder);
    }
    cout << endl << endl;
  }

  public: void translateFA() {
    //////FIX: NEED TO MAKE RULE WITH FOR WHERE EPSILON STUFF GOES

    priority_queue<State> pq;
    transFA.resize(0);

    State cur = initFA[startstate];

    if (epsilon != -1) {
        cout << cur.next[epsilon].size() << endl;
        for (int i=0; i<(cur.next[epsilon].size()); i++) {
          if (cur.id % cur.next[epsilon][i]->id != 0) {
            cur.id *= cur.next[epsilon][i]->id;
            cur.name += cur.next[epsilon][i]->name;
            cur.name = sortString(cur.name);
          }
        }
    }

    //Add start State to pq
    pq.push(cur);

    //while pq is not empty
    while (!pq.empty())
    {
        //take State from pq
        State cur = pq.top();
        pq.pop();
        bool visit = inStateList(transFA,cur);

        //initializes each next to have size of number of letters in alphabet
        cur.next.resize(numAlpha);

        //cout << "Current state " << cur.name << ", visit " << visit << endl;
        if (!visit & cur.name!="" & cur.name!="Ø")
        {
            //for all characters in current State's name
            for (int i=0; i<cur.name.length(); i++)
            {
                State* namechar = NULL;

                //find State that matches input[k]
                for (int j = 0; j < numStates; j++)
                {
                    if (initFA[j].name == string(1,cur.name[i]))
                    {
                        //add to initFA next
                        namechar = &initFA[j];
                    }
                }
                //for all input possiblities
                for (int j=0; j<numAlpha; j++)
                {
                  if (i == 0) {
                    State * curnext = new State;
                    cur.next[j].resize(1);
                    cur.next[j][0] = curnext;
                  }

                  //for all States that current character State goes to on current input
                  for (int k = 0; k < namechar->next[j].size(); k++)
                  {
                      if (cur.next[j][0]->id % namechar->next[j][k]->id != 0)
                      {
                          cur.next[j][0]->id *= namechar->next[j][k]->id;
                          cur.next[j][0]->name += namechar->next[j][k]->name;
                          cur.next[j][0]->name = sortString(cur.next[j][0]->name);
                          /*if (namechar->next[j][k]->accept == true) {
                            cur.next[j][0]->accept = true;
                          }*/
                      }
                  }
               }
             }

          //cout << "Starting Epsilon stuff" << endl;
          //EPSILON stuff
          //for all characters in next on epsilon
          if (epsilon != -1) {
             for (int i=0; i<cur.next[epsilon][0]->name.length(); i++)
             {
                  State* namechar = NULL;

                  //find State that matches input[k]
                 for (int j = 0; j < numStates; j++)
                 {
                     if (initFA[j].name == string(1,cur.next[epsilon][0]->name[i]))
                     {
                         //add to initFA next
                         namechar = &initFA[j];
                     }
                 }

                 //for all input possiblities
                 for (int j=0; j<numAlpha; j++)
                 {
                     //for all States that current character State goes to on current input
                     for (int k = 0; k < namechar->next[j].size(); k++)
                     {
                       if (namechar->next[j][k]->id != 1) {
                           if (cur.next[j][0]->id % namechar->next[j][k]->id != 0)
                           {
                               cur.next[j][0]->id *= namechar->next[j][k]->id;
                               cur.next[j][0]->name += namechar->next[j][k]->name;
                           }
                           if (cur.next[j][0]->id % namechar->id != 0) {
                             cur.next[j][0]->id *= namechar->id;
                             cur.next[j][0]->name += namechar->name;
                           }
                           cur.next[j][0]->name = sortString(cur.next[j][0]->name);
                       }
                     }
                  }
              }
            //Delete epsilon
            cur.next.pop_back();
            numAlphaDFA = numAlpha - 1;
          }

          //add cur to transFA
          transFA.push_back(cur);

          //add cur's next States to pq if not in transFA
          for (int j = 0; j < numAlphaDFA; j++)
          {
              if (cur.next[j][0]->id == 1)
              {
                  cur.next[j][0]->name = "Ø";
                  cur.next[j][0]->id = primes[primetracker];
                  cur.next[j][0]->next.resize(numAlpha);
                  for (int i=0; i<numAlphaDFA; i++) {
                      State * curstate = new State("Ø",primes[primetracker]);
                      cur.next[j][0]->next[i].resize(1);
                      cur.next[j][0]->next[i][0] = curstate;
                  }
                  transFA.push_back(*cur.next[j][0]);
              }
              bool vis = inStateList(transFA,*cur.next[j][0]);

              //not visited => not in transFA
              if (!vis) {pq.push(*cur.next[j][0]);}
          }
       }
    }

    cout << "transFA data: " << endl;
    for (int i=0; i<transFA.size(); i++) {
      transFA[i].printState(alphaorder);
    }
  }

   /* recursive function that determines determines where the input should go on
  each branch and outputs true if any of the branches end in an accept state */
  public:bool branch(int& t, int i, char * input, State * cur, string** tree, int bnum) {

    string tab = string(i*4,' '); //organizes output based on value of i
    int inputsize = arrsize(input); //size of input
    //tree[i]->curstate = cur;
    tree[i][bnum] = cur->name;

    if (i<inputsize) {
      int size;  //size of next
      int curinput;

      //finds input for cur.next
      for (int j = 0; j<numAlpha; j++) {
        if (alphaorder[j] == input[i]) {
          curinput = j;
          break;
        }
      }

      size = cur->next[curinput].size();

      //if no next state for input, terminate branch
      if (size == 0) {
        tree[i+1][bnum*2] = "x";
        return NULL;
      }

      i++; //increment i to get next character in input
      //call branch for all possible next states
      for(int j = 0; j<size; j++) {
        //bnum = bnum*2+j;

        //if all characters have been inputed, then next state is final state.
        if (i == inputsize) {
          //next[j] = next[j]->e_next[0];
          //cout << tab << "Branch final state: " << cur->next[curinput][j]->name << endl << endl;
          tree[i][bnum*2+j] = cur->next[curinput][j]->name;
          //increment t if final state is an accept state
          if (cur->next[curinput][j]->accept == true) {
            t++;
          }
        }
        //call branch for the next state
        branch(t,i,input,cur->next[curinput][j],tree,bnum*2+j);
      }

      ///EPSILON STUFF -- NOT WORKING
      if (epsilon != -1) {
        for (int k = 0; k<cur->next[epsilon].size(); k++) {
          for (int m=0; m<cur->next[epsilon][k]->next[curinput].size(); m++) {
            branch(t,i,input,cur->next[epsilon][k]->next[curinput][k],tree,bnum*2+k);
          }
        }
      }
    }

    //return true if any branch ends in an accept state
    if (t > 0)
      return true;
    else
      return false;
  }

  public: 
  
  void simulate(ofstream &out) {
    out.open("simulate.txt");

    //call branch function to simulate input moving through states and cout results
    int inputsize = arrsize(input);

    string** tree = new string*[inputsize+1];
    for (int i=0; i<=inputsize; i++) {
      tree[i] = new string[(int)pow(2,i)];
      for (int j=0; j<((int)pow(2,i)); j++) {
        tree[i][j] = "_";
      }
    }
    int bnum = 0;

    int t = 0; //tabs
    out<< "Input: " << input << endl << endl << "Accepted: ";
    if (branch(t,0,input,&initFA[startstate],tree, bnum) == true)
      out<< "Yes" << endl;
    else
      out<< "No"<< endl;
    out<< endl;

    //Printing Tree
    string* display = new string[inputsize+1];
    int rowlen = 2*((int)pow(2,inputsize));
    for (int i=0; i<=inputsize; i++) {
      display[i] = string(rowlen,' ');
    }
    for (int i=0; i<=inputsize; i++) {
      int spaces = rowlen/((int)pow(2,i));
      for(int j=0; j<((int)pow(2,i)); j++) {
        display = center(j,spaces,i,display,tree);
      }
    }

    out<< "Simulation Tree:"<< endl << endl;
    out<< "\tInput " << endl;
    out<< "\t\t" << display[0] << endl;
    for (int i=1; i<=inputsize; i++) {
      out<< "\t" << input[i-1] << ":" << endl;
      out<< "\t\t\t" << display[i] << endl;
    }
  }
};


int main() {
    FA f;
    f.incomingFA("A,B,C,D", "A", "D", "0,1", "A;0;A,B;A;1;A,C;B;0;D;C;1;D,", "010011","string");
    //f.incomingFA("1,2,3", "1", "1", "a,b,E", "1;b;2;1;E;3;2;a;2,3;2;b;3;3;a;1,", "abaa", "string");
    //f.incomingFA("A,B,C,D", "B", "A,D", "0,E,1", "B;E;A,C;C;0;C,D;C;1;C,", "01100", "string");
    f.translateFA();
    //f.simulate("010011");
    //f.simulate("010101");
    ofstream out;
    f.simulate(out);
    f.printDFA();
}
