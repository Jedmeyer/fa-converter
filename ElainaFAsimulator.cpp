//Elaina Brownlee

#include <iostream>
#include <string>
using namespace std;

//state struct with information about where the next input should go
struct state {
  int name;
  state ** a_next;
  state ** b_next;
  state ** e_next;
  int abranch;
  int bbranch;
  int ebranch;
  bool accept;
  //initialize states
  state(int n, bool acc) {
    name = n;
    accept = acc;
    a_next = NULL;
    b_next = NULL;
    e_next = NULL;
  }
  //initialize vectors of pointers of which state next input should go to
  void abe_next(state ** a, state ** b, state ** e,int asize, int bsize, int esize) {
    a_next = a;
    b_next = b;
    e_next = e;
    abranch = asize;
    bbranch = bsize;
    ebranch = esize;
  }
};

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

/* recursive function that determines determines where the input should go on
each branch and outputs true if any of the branches end in an accept state */
bool branch(int& t, int i, char * input, state * cur) {

  string tab = string(i*4,' '); //organizes output based on value of i
  int inputsize = arrsize(input); //size of input

  if (i<inputsize) {
    state ** next; //array of pointers of next states to go to
    int size; //size of next

    //assigns next based on the input
    if (input[i]=='a') {size = cur->abranch; next = cur->a_next;}
    if (input[i]=='b') {size = cur->bbranch; next = cur->b_next;}

    //if no next state for input, terminate branch
    if (size == 0) {
      //output location information
      cout << tab << "Current state: " << cur->name << endl;
      cout << tab << "Input: " << input[i] << endl;
      cout << tab << "i: " << i << endl;
      cout << tab << "Branch terminated." << endl << endl;
      return NULL;
    }

    i++; //increment i to get next character in input
    //call branch for all possible next states
    for(int j = 0; j<size; j++) {
      //output location information
      cout << tab << "Current state: " << cur->name << endl;
      cout << tab << "Input: " << input[i-1] << endl;
      cout << tab << "i: " << i-1 << endl;
      cout << tab << "Branch: " << j+1 << " of " << size << endl;
      cout << tab << "To state: " << next[j]->name << endl << endl;

      //if all characters have been inputed, then next state is final state.
      if (i == inputsize) {
        next[j] = next[j]->e_next[0];
        cout << tab << "Branch final state: " << next[j]->name << endl << endl;
        //increment t if final state is an accept state
        if (next[j]->accept == true) {
          t++;
        }
      }
      //call branch for the next state
      branch(t,i,input,next[j]);
    }
  }
  //return true if any branch ends in an accept state
  if (t > 0)
    return true;
  else
    return false;
}

void simulate(char * input) {
  //init states
  state s1(1,false);
  state s2(2,false);
  state s3(3,true);
  state s4(4,true);

  //connect states
  state ** a1 = new state * {&s2};
  state ** b1 = new state * {&s3};
  state ** e1 = new state * {&s1};
  s1.abe_next(a1,b1,e1,1,1,1);
  state ** a2 = new state * {&s1};
  state ** b2 = new state * [2] {&s3,&s4};
  state ** e2 = new state * {&s3};
  s2.abe_next(a2,b2,e2,1,2,1);
  state ** b3 = new state * [2] {&s3,&s4};
  state ** e3 = new state * {&s3};
  s3.abe_next(NULL,b3,e3,0,2,1);
  state ** a4 = new state * [2] {&s2,&s3};
  state ** e4 = new state * {&s4};
  s4.abe_next(a4,NULL,e4,2,0,1);

  //call branch function to simulate input moving through states and cout results
  int t = 0;
  cout << "INPUT: " << input << endl << endl;
  if (branch(t,0,input,&s1) == true)
    cout << "Input " << input << " accepted." << endl;
  else
    cout << "Input " << input << " not accepted."<< endl;
  cout << endl << endl;
}

int main() {

  simulate("aababba");
  simulate("abba");
  simulate("aa");
  simulate("aabbabba");

  return 0;
}
