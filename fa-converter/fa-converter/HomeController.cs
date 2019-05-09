using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace faconverter
{
    public class state : IComparable<state>
    {

        public int CompareTo(object obj)
        {
            if (obj == null) return 1;

            state otherState = obj as state;

            if (otherState != null)
                return this.name.CompareTo(otherState.id);
            else
                throw new ArgumentException("Jason has no idea what he's doing.");
        }
        public int CompareTo(state otherState)
        {
            return this.name.CompareTo(otherState.id);
        }

        public string name;
        public int id;
        //FIX: 
        public List<List<state*>> next;
        public bool accept = false;

        public state(string n) { name = n; }
        public state() {
            name = "";
            id = 1;
            //FIX: initialize next so that bottom layer has size 1
        }
    }


    [Route("/")]
    public class HomeController : Controller
    {
        //
        // GET: /Home/
        [HttpGet]
        public ActionResult Index()
        {
            return View();
        }
        // Response to the transition function.

        [HttpGet]
        [Route("/Build")]
        public ActionResult Build(string states, string acc, string alpha, string input, string type)
        {
            string newline = @"
";

            //////////////////////////////////////////////////////////////////////////
            // InitFunc Set up
            //////////////////////////////////////////////////////////////////////////

            //Primes for id
            int[] primes = new int[] {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
            int primetracker = 0;

            //states
            int numStates = 0;
            for (int i = 0; i<states.Length; i++)
            {
                if (states[i] != ',') { numStates++; }
            }
         
            List<state> initFunc = new List<state>(numStates);
            for (int i = 0; i<states.Length; i++)
            {
                if (states[i] != ',')
                {
                    initFunc[i].name = states[i].ToString();
                    initFunc[i].id = primes[primetracker];
                    primetracker++;
                }
            }

            //initFunc.Sort(IComparer<state> IComparable)
            //^^make compare function to pass as argument that specifies that they are sorted by id

            //acc
            for (int i = 0; i < acc.Length; i++)
            {
                if (acc[i] != ',')
                {
                    for (int j=0; j < numStates; j++)
                    {
                        if (initFunc[j].name == acc[i].ToString())
                        {
                            initFunc[j].accept = true;
                            break;
                        }
                    }
                }
            }

            //alpha
            int numAlpha = 0;
            List<char> alphaorder = new List<char>(0);
            for (int i=0; i<alpha.Length; i++)
            {
                if (alpha[i]!=',') 
                {
                    alphaorder.Add(alpha[i]);
                    numAlpha++; 
                }
            }

            for (int i = 0; i < numStates; i++)
            {
                //initializes each next have size of number of letters in alphabet
                initFunc[i].next = new List<List<state*>>(numAlpha);
                for (int j=0; j<numAlpha; j++)
                {
                    initFunc[i].next[j] = new List<state*>(1) { null };
                }
            }


            //input
            int curstate = -1;
            int curinput = -1;
            for (int i=0; i<input.Length; i++)
            {
                for (int j = 0; j < numStates; j++)
                {
                    if (initFunc[j].name == input[i].ToString())
                    {
                        curstate = j;
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
                        //find state that matches input[k]
                        for (int j = 0; j < numStates; j++)
                        {
                            if (initFunc[j].name == input[k].ToString())
                            {
                                //add to initFunc next
                                initFunc[curstate].next[curinput].Add(&initFunc[j]);
                            }
                        }
                    }   
                    k++;
                }
                i = k + 1;
            }


            //////////////////////////////////////////////////////////////////////////
            // Translation: the creation of TransFunc
            //////////////////////////////////////////////////////////////////////////
            //////FIX: NEED TO MAKE RULE WITH FOR WHERE EPSILON STUFF GOES

            PriorityQueue<state> pq = new PriorityQueue<state>();
            List<state> transFunc = new List<state>(0);

            //Add start state to pq
            pq.Enqueue(initFunc[0]);

            //while pq is not empty
            while (pq != null)
            {
                //take state from pq
                state cur = pq.Dequeue();

                bool visit = false;

                //FIX: check if cur is in transFunc[i] (binary search)
                for (int i = 0; i < transFunc.Count; i++)
                {
                    if (transFunc[i].id == cur.id)
                    {
                        visit = true;
                        break;
                    }
                }

                if (visit == false)
                {
                    //for all characters in current state's name
                    for (int i=0; i<cur.name.Length; i++)
                    {
                        state* namechar = null;

                        //find state that matches input[k]
                        for (int j = 0; j < numStates; j++)
                        {
                            if (initFunc[j].name == cur.name[i].ToString())
                            {
                                //add to initFunc next
                                namechar = &initFunc[j];
                            }
                        }

                        //initializes each next have size of number of letters in alphabet
                        cur.next = new List<List<state*>>(numAlpha);

                        //for all inputs possiblities
                        for (int j=0; j<numAlpha; j++)
                        {
                            state curnext = null;

                            cur.next[j] = new List<state*>(1);
                            cur.next[j][0] = &curnext;


                            //for all states that current character state goes to on current input
                            for (int k; k < namechar->next[j].Count; k++)
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
                    transFunc.Add(cur);

                    //add cur's next states to pq if not in transFunc
                    for (int j = 0; j < numAlpha; j++)
                    {
                        bool vis = false;

                        //FIX: check if cur.next[j][0] is in transFunc[k] (binary search)
                        for (int k = 0; k < transFunc.Count; k++)
                        {
                            if (transFunc[k].id == cur.next[j][0]->id)
                            {
                                vis = true;
                                break;
                            }
                        }

                        //not visited => not in transFunc
                        if (vis == false)
                        {
                            pq.Enqueue(*cur.next[j][0]);
                        }
                    }
                }
            }

            return Content(states + newline + acc + newline + alpha + newline + input + newline + type);
        }

        [HttpPost]
        [ActionName("Index")]
        public ActionResult IndexPost()
        {
            return Content("Accepts on index page");

        }
    }
}