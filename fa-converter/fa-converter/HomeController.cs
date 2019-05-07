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
    public class state : IComparable
    {
        public int CompareTo(object obj)
        {
            if (obj == null) return 1;

            state otherState = obj as state;

            if (otherState != null)
                return this.name.CompareTo(otherState.name);
            else
                throw new ArgumentException("Jason has no idea what he's doing.");
        }
        public string name;
        public bool visited = false;  
        public List <List<string>> next;
        public bool accept = false;
        public state(string n) { name = n; }
        public state() { }
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
            int numStates = 0;
            for (int i = 0; i<states.Length; i++)
            {
                if (input[i] != ',') { numStates++; }
            }

            //states
            List<state> inFunc = new List<state>(numStates);
            for (int i = 0; i<states.Length; i++)
            {
                if (input[i] != ',')
                {
                    inFunc[i].name = states[i].ToString();
                }
            }

            //acc
            for (int i = 0; i < acc.Length; i++)
            {
                if (acc[i] != ',')
                {
                    for (int j=0; j < numStates; j++)
                    {
                        if (inFunc[j].name == acc[i].ToString())
                        {
                            inFunc[j].accept = true;
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
                inFunc[i].next = new List<List<string>>(numAlpha);
            }


            //input
            int curstate = -1;
            int curinput = -1;
            for (int i=0; i<input.Length; i++)
            {
                for (int j = 0; j < numStates; j++)
                {
                    if (inFunc[j].name == input[i].ToString())
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
                        inFunc[curstate].next[curinput].Add(input[k].ToString());
                    }
                    k++;
                }
                i = k + 1;
            }

            PriorityQueue<state> pq;
            
            //Store transition function info


            List<state> transflist;



            //Add start state to pq

            //While(pq not empty):
                //cur = element popped off pq

                //for (i: 0 to cur.name.length):
                //  cur.visited = true
                //  cur.zero += cur.name[i].zero
                //  cur.one = cur.name[i].one

                //Add cur, 0, cur.zero to transflist
                //Add cur, 1, cur.one to transflist

                //if cur.zero not in pq and not visited:
                //  add cur.zero to pq
                //if cur.one not in pq and not visited:
                  //add cur.one to pq

            //return transflist

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