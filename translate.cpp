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
        cout << next[i][j]->name << ", ";
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





bool inStateList(vector<State> Func, State cur) {
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

void translate(string states, string acc, string alpha, string input, string type) {
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

  //States
  int numStates = 0;
  for (int i = 0; i<states.length(); i++)
  {
      if (states[i] != ',') { numStates++; }
  }

  State* initFunc = new State[numStates];
  for (int i = 0; i<states.length(); i++)
  {
      if (states[i] != ',')
      {
          initFunc[i].name = string(1,states[i]);
          initFunc[i].id = primes[primetracker];
          primetracker++;
      }
  }


  //acc
  for (int i = 0; i < acc.length(); i++)
  {
      if (acc[i] != ',')
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
  int numAlpha = 0;
  vector<char> alphaorder(0);
  for(int i=0; i<alpha.length(); i++)
  {
      if (alpha[i]!=',')
      {
          alphaorder.push_back(alpha[i]);
          numAlpha++;
      }
  }

  for (int i = 0; i < numStates; i++)
  {
      //initializes each next have size of number of letters in alphabet
      initFunc[i].next.resize(numAlpha); //= new vector<vector<State*>>(numAlpha);
      for (int j=0; j<numAlpha; j++)
      {
          initFunc[i].next[j].resize(1);
          initFunc[i].next[j][0] = NULL;
      }
  }

  //input
  int curState = -1;
  int curinput = -1;
  for (int i=0; i<input.length(); i++)
  {
      for (int j = 0; j < numStates; j++)
      {
          if (initFunc[j].name == string(1,input[i]))
          {
              curState = j;
              break;
          }
      }
      i += 2;

      for (int j = 0; j < numAlpha; j++)
      {
          if (input[i] == alphaorder[j])
          {
              curinput = j;
              break;
          }
      }
      i += 2;

      int k = i;
      while(input[k] != ';')
      {
          if (input[k] != ',')
          {
              //find State that matches input[k]
              for (int j = 0; j < numStates; j++)
              {
                  if (initFunc[j].name == string(1,input[k]))
                  {
                      //add to initFunc next
                      initFunc[curState].next[curinput].push_back(&initFunc[j]);
                  }
              }
          }
          k++;
      }
      i = k + 1;
  }

  for (int i=0; i<numStates; i++) {
    initFunc[i].printState(alphaorder);
  }


  //////////////////////////////////////////////////////////////////////////
  // Translation: the creation of TransFunc
  //////////////////////////////////////////////////////////////////////////
  //////FIX: NEED TO MAKE RULE WITH FOR WHERE EPSILON STUFF GOES

  priority_queue<State> pq;
  vector<State> transFunc(0);

  //Add start State to pq
  pq.push(initFunc[0]);

  //while pq is not empty
  while (!pq.empty())
  {
      //take State from pq
      State cur = pq.top();
      pq.pop();
      bool visit = inStateList(transFunc,cur);

      if (visit == false)
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

              //initializes each next to have size of number of letters in alphabet
              cur.next.resize(numAlpha);

              //for all input possiblities
              for (int j=0; j<numAlpha; j++)
              {
                  //State curnext = NULL;
                  cur.next[j].resize(1);
                  cur.next[j][0] = NULL;//&curnext;


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

          //add cur to transFunc
          transFunc.push_back(cur);

          //add cur's next States to pq if not in transFunc
          for (int j = 0; j < numAlpha; j++)
          {
              bool vis = inStateList(transFunc,cur);

              //not visited => not in transFunc
              if (vis == false)
              {
                  pq.push(*cur.next[j][0]);
              }
          }
      }
  }

  for (int i=0; i<transFunc.size(); i++) {
    transFunc[i].printState(alphaorder);
  }

}


int main() {
  translate("A,B,C,D", "D", "0,1", "A;0;A,B;A;1;A,C;B;0;D;C;1;D", "string");
}
