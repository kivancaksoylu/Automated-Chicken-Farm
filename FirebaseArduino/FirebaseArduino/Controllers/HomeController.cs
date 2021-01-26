using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FireSharp.Config;
using FireSharp.Response;
using FireSharp.Interfaces;
using FirebaseArduino.ViewModels;


namespace FirebaseArduino.Controllers
{
    public class HomeController : Controller
    {
        
        public ActionResult Index()
        {
            IFirebaseConfig ifc = new FirebaseConfig()
            {
                AuthSecret = "Rs1oLkt5fsfBfUKUJA7ZwsOdqcsCBhdn7fN1dlQc",
                BasePath = "https://arduino-afb8e.firebaseio.com/"
            };
            IFirebaseClient client;
            client = new FireSharp.FirebaseClient(ifc);
            FirebaseCekilenVeriler veri = new FirebaseCekilenVeriler();
            var sicaklik = client.Get(@"Sicaklik/");
            veri.GelenSicaklik = sicaklik.Body;
            var nem = client.Get(@"Nem/");
            veri.GelenNem = nem.Body;
            var agirlik = client.Get(@"Agirlik/");
            veri.GelenAgirlik = agirlik.Body;
            //double gelenAgirlik = double.Parse(veri.GelenAgirlik, System.Globalization.CultureInfo.InvariantCulture);
            //if (gelenAgirlik >= 0.90)
            //{
            //    var su = client.Set(@"YemDurumu/", "0");
            //}
            var suseviyesi = client.Get(@"SuSeviyesi/");
            veri.GelenSuSeviyesi = suseviyesi.Body;
            //decimal gelenSuSeviyesi = Convert.ToDecimal(veri.GelenSuSeviyesi.Replace(".", ","));
            //if (gelenSuSeviyesi >=80)
            //{
            //    var su = client.Set(@"SuDurumu/", "0");
            //}
            var hareket = client.Get(@"Hareket/");
            veri.Hareket = hareket.Body;
            var yangin = client.Get(@"Yangin/");
            veri.Yangin = yangin.Body;
            ViewBag.Sicaklik = veri.GelenSicaklik;
            ViewBag.Nem = veri.GelenNem;
            ViewBag.Agirlik = veri.GelenAgirlik;
            ViewBag.SuSeviyesi = veri.GelenSuSeviyesi;
            if (veri.Yangin == "0")
            {
                ViewBag.Yangin = "Stabil";
            }
            else
            {
                ViewBag.Yangin = "Olumsuz bir durum oluştu!";
            }
            if (veri.Hareket == "0")
            {
                ViewBag.Hareket = "Hareket gözlemlenmedi.";
            }
            else
            {
                ViewBag.Hareket = "Hareketli bir cisim/nesne algılandı!";
            }
            return View();
        }
    }
}