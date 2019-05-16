#include <iostream>
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
  vector<vector<State*>> next;
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
    std::cout << "State " << name << endl;
    std::cout << "\tid " << id << endl;
    std::cout << "\taccept " << accept << endl;
    for (int i=0; i<next.size(); i++) {
      std::cout <<"\tinput " << alphaorder[i] << endl;
      std::cout << "\t\t";
      for (int j=0; j<next[i].size(); j++) {
        if (next[i][j]!=NULL) {std::cout << next[i][j]->name << ", ";}
      }
      std::cout << endl;
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
  int* primes = new int[100] {2, 3, 5, 7, 11, 13, 17, 19,
  23, 29, 31, 37, 41, 43, 47, 53,
  59, 61, 67, 71, 73, 79, 83, 89,
  97, 101, 103, 107, 109, 113, 127,
  131, 137, 139, 149, 151, 157, 163,
  167, 173, 179, 181, 191, 193, 197,
  199, 211, 223, 227, 229, 233, 239,
  241, 251, 257, 263, 269, 271, 277,
  281, 283, 293, 307, 311, 313, 317,
  331, 337, 347, 349, 353, 359, 367, 373,
  379, 383, 389, 397, 401, 409, 419, 421,
  431, 433, 439, 443, 449, 457, 461, 463,
  467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
  int primetracker = 0;
  int numStates = 0;
  vector<State>initFA;
  int numAlpha = 0;
  vector<char> alphaorder;
  vector<State> transFA;
  char * input;
  int startstate;

  public: printDFA(string alpha) {
    //States
    std::cout << "States: {";
    for (int i=0; i<transFA.size(); i++) {
      std::cout << transFA.name << ","
    }
    std::cout << "}" << endl;

    //Start State
    std::cout << "Start State: " transFA[0].name << endl;

    //Accept states
    std::cout << "Accept States: {"};
    for (int i=0; i<numStates; i++) {
      if (initFA[i].accept == true) {
        for (int j=0; j<transFA.size(); j++) {
          if (transFA[j].id % initFA[i].id) {
            std::cout << transFA[j].name << ",";
          }
        }
      }
      std::cout << "}" << endl;
    }

    //alphabet
    std::cout << "Alphabet: {" << alpha << "}" << endl;
    
    //Transition Functions

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
            numAlpha++;
        }
    }

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

    std::cout << "initFA data:" << endl;
    for (int i=0; i<numStates; i++) {
      initFA[i].printState(alphaorder);
    }
    std::cout << endl << endl;
  }

  public: void translateFA() {
    //////FIX: NEED TO MAKE RULE WITH FOR WHERE EPSILON STUFF GOES

    priority_queue<State> pq;
    transFA.resize(0);

    //Add start State to pq
    pq.push(initFA[0]);

    //while pq is not empty
    while (!pq.empty())
    {
        //take State from pq
        State cur = pq.top();
        pq.pop();
        bool visit = inStateList(transFA,cur);

        //initializes each next to have size of number of letters in alphabet
        cur.next.resize(numAlpha);

        //std::cout << "Current state " << cur.name << ", visit " << visit << endl;

        if (!visit & cur.name!="")
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
                        }
                    }
                }
            }

            //add cur to transFA
            transFA.push_back(cur);

            //add cur's next States to pq if not in transFA
            for (int j = 0; j < numAlpha; j++)
            {
                bool vis = inStateList(transFA,*cur.next[j][0]);

                //not visited => not in transFA
                if (!vis) {pq.push(*cur.next[j][0]);}
            }
        }
    }

    std::cout << "transFA data: " << endl;
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
        bnum = bnum*2+j;

        //if all characters have been inputed, then next state is final state.
        if (i == inputsize) {
          //next[j] = next[j]->e_next[0];
          //std::cout << tab << "Branch final state: " << cur->next[curinput][j]->name << endl << endl;
          tree[i][bnum] = cur->next[curinput][j]->name;
          //increment t if final state is an accept state
          if (cur->next[curinput][j]->accept == true) {
            t++;
          }
        }
        //call branch for the next state
        branch(t,i,input,cur->next[curinput][j],tree,bnum);
      }
    }
    //return true if any branch ends in an accept state
    if (t > 0)
      return true;
    else
      return false;
  }


  public: void simulate() {
    //call branch function to simulate input moving through states and std::cout results
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
    std::cout << "INPUT: " << input << endl << endl;
    if (branch(t,0,input,&initFA[startstate],tree, bnum) == true)
      std::cout << "Input " << input << " accepted." << endl;
    else
      std::cout << "Input " << input << " not accepted."<< endl;
    std::cout << endl << endl;

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

    std::cout << "Tree for input " << input << endl;
    std::cout << "Input";
    std::cout << "\t" << display[0] << endl;
    for (int i=1; i<=inputsize; i++) {
      std::cout << input[i-1] << ":" << endl;
      std::cout << "\t" << display[i] << endl;
    }
  }
};
