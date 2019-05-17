#include <iostream>
#include <string>
#include <queue>
#include <vector>
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
  vector<State>initFunc;
  int numAlpha = 0;
  vector<char> alphaorder;
  vector<State> transFunc;

  public: bool inStateList(vector<State> Func, State cur) {
    //FIX: check if cur is in transFunc[i] (binary search)
    for (int i = 0; i < Func.size(); i++)
    {
        if (Func[i].id == cur.id)
        {
            return true;
        }
    }
    return false;
  }

   public: void incomingFA(string states, string acc, string alpha, string input, string type) {
    //States
    initFunc.resize(0);
    for (int i = 0; i<states.length(); i++)
    {
        if (states[i] != ',' & states[i] != ' ')
        {
            initFunc.push_back(string(1,states[i]));
            initFunc[numStates].id = primes[primetracker];
            numStates++;
            primetracker++;
        }
    }

    //acc
    for (int i = 0; i < acc.length(); i++)
    {
        if (acc[i] != ',' & acc[i] != ' ')
        {
            for (int j=0; j < numStates; j++)
            {
                if (initFunc[j].name == string(1,acc[i]))
                {
                    initFunc[j].accept = true;
                    break;
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
        initFunc[i].next.resize(numAlpha); //= new vector<vector<State*>>(numAlpha);
    }

    //input
    int curState = -1;
    int curinput = -1;
    for (int i=0; i<input.length(); i++)
    {
        //find origin state
        for (int j = 0; j < numStates; j++)
        {
            if (initFunc[j].name == string(1,input[i]))
            {
                curState = j;
                break;
            }
        }
        i += 2; //move to input

        //find input value
        for (int j = 0; j < numAlpha; j++)
        {
            if (input[i] == alphaorder[j])
            {
                curinput = j;
                break;
            }
        }
        i+=2; //move to nextstates

        //find next states
        while(input[i] != ';' & i<input.length())
        {
            if (input[i] != ',' & input[i] !=' ')
            {
                //find State that matches input[k]
                for (int j = 0; j < numStates; j++)
                {
                    if (initFunc[j].name == string(1,input[i]))
                    {
                        //add to initFunc next
                        initFunc[curState].next[curinput].push_back(&initFunc[j]);
                        break;
                    }
                }
            }
            i++;
        }
    }

    cout << "initFunc data:" << endl;
    for (int i=0; i<numStates; i++) {
      initFunc[i].printState(alphaorder);
    }
    cout << endl << endl;
  }


  public: void translateFA() {
    //////FIX: NEED TO MAKE RULE WITH FOR WHERE EPSILON STUFF GOES

    priority_queue<State> pq;
    transFunc.resize(0);

    //Add start State to pq
    pq.push(initFunc[0]);

    //while pq is not empty
    while (!pq.empty())
    {
        //take State from pq
        State cur = pq.top();
        pq.pop();
        bool visit = inStateList(transFunc,cur);

        //initializes each next to have size of number of letters in alphabet
        cur.next.resize(numAlpha);

        //cout << "Current state " << cur.name << ", visit " << visit << endl;

        if (!visit & cur.name!="")
        {
            //for all characters in current State's name
            for (int i=0; i<cur.name.length(); i++)
            {
                State* namechar = NULL;

                //find State that matches input[k]
                for (int j = 0; j < numStates; j++)
                {
                    if (initFunc[j].name == string(1,cur.name[i]))
                    {
                        //add to initFunc next
                        namechar = &initFunc[j];
                    }
                }

                //cout << "\tCurrent char state: " << namechar->name << endl;

                //for all input possiblities
                for (int j=0; j<numAlpha; j++)
                {

                  if (i == 0) {
                    State * curnext = new State;
                    cur.next[j].resize(1);
                    cur.next[j][0] = curnext;
                  }

                    //cout << "\t\tCurrent input: " << j << endl;

                    //for all States that current character State goes to on current input
                    for (int k = 0; k < namechar->next[j].size(); k++)
                    {
                        if (cur.next[j][0]->id % namechar->next[j][k]->id != 0)
                        {
                            //cout << "\t\t\tadding to nextstate ";
                            cur.next[j][0]->id *= namechar->next[j][k]->id;
                            cur.next[j][0]->name += namechar->next[j][k]->name;
                            //cout << "name: " << cur.next[j][0]->name << " id " << cur.next[j][0]->id << endl;
                        }
                    }
                    //cout << "\tFinal next state" << "name: " << cur.next[j][0]->name << " id " << cur.next[j][0]->id << endl;
                }
            }

            //add cur to transFunc
            transFunc.push_back(cur);

            //add cur's next States to pq if not in transFunc
            for (int j = 0; j < numAlpha; j++)
            {
                bool vis = inStateList(transFunc,*cur.next[j][0]);

                //not visited => not in transFunc
                if (!vis)
                {
                    //cout << "Adding " << cur.next[j][0]->name << " to pq" << endl;
                    pq.push(*cur.next[j][0]);
                }
            }
        }
    }

    cout << "TransFunc data: " << endl;
    for (int i=0; i<transFunc.size(); i++) {
      transFunc[i].printState(alphaorder);
    }
  }
};


int main() {
  FA f;
  f.incomingFA("A,B,C,D", "D", "0,1", "A;0;A,B;A;1;A,C;B;0;D;C;1;D;", "string");
  f.translateFA();
}
