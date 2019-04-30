using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace fa_converter
{
    [Route("/")]
    public class HomeController : Controller
    {
        //
        // GET: /Home/
        [HttpGet]
        public ActionResult Index()
        {
            return Content(@"<!DOCTYPE html>
<html>
    <form action=""/action_page.php"">
        𝛿(<input type=""text"" name=""curstate"" value="""" maxlength=""1"" size=""1"">,<input type=""text"" name=""input"" value="""" maxlength=""1"" size=""1""> ) = {<input type=""text"" name=""nextstate"" value="""" maxlength=""20"">}<br>


        <script>function myFunction() {
                var div = document.getElementById('myItems'),
                    clone = div.cloneNode(true);
                document.body.appendChild(clone);
            }</script>
        <div id=""myItems"">
            <form action=""/action_page.php"">
                𝛿(<input type=""text"" name=""curstate"" value="""" maxlength=""1"" size=""1"">,<input type=""text"" name=""input"" value="""" maxlength=""1"" size=""1""> ) = {<input type=""text"" name=""nextstate"" value="""" maxlength=""20"">}<br>
            </form>
        </div>

        <p id=""demo"">Click the button to clone the above items</p>
        <button onclick=""myFunction()"">+</button> <br>
        <input type=""submit"" value=""Submit"">
    </form>

    <p>Click the ""Submit"" button and the form-data will be sent to a page on the server called ""/action_page.php"".</p>
</html>","text/html");
        }


        [HttpPost]
        [ActionName("Index")]
        public ActionResult IndexPost()
        {
            return Content("Accepts on index page");

        }
    }
}