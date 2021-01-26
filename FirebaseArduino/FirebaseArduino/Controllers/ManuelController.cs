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
    public class ManuelController : Controller
    {
        string gidecekDegerler;
        int Sicaklik = 0;
        string sicaklik="-9";
        string nem="-8";
        string yemDurumu="-5";
        string suDurumu="-3";
        string alarmDurumu = "-10";
        public ActionResult Index(FirebaseCekilenVeriler veriler)
        {
            IFirebaseConfig ifc = new FirebaseConfig()
            {
                AuthSecret = "Rs1oLkt5fsfBfUKUJA7ZwsOdqcsCBhdn7fN1dlQc",
                BasePath = "https://arduino-afb8e.firebaseio.com/"
            };
            IFirebaseClient client;
            client = new FireSharp.FirebaseClient(ifc);
            FirebaseCekilenVeriler veri = new FirebaseCekilenVeriler();
            //sıcaklık
            if (veriler.GidenSicaklik != null)
            {
                //var sicaklik = client.Set(@"GidenSicaklik/", veriler.GidenSicaklik);
                sicaklik = veriler.GidenSicaklik;
                Sicaklik = Convert.ToInt32(sicaklik)+1000;
                sicaklik = Sicaklik.ToString();
            }
            //nem
            if (veriler.GidenNem != null)
            {
                //var nem = client.Set(@"GidenNem/", veriler.GidenNem);
                nem = veriler.GidenNem;
            }
            //yem
            if (veriler.YemDurumu != null)
            {
                var agirlik = client.Get(@"Agirlik/");
                veri.GelenAgirlik = agirlik.Body;
                if (veriler.YemDurumu == "{ value = 1 }" && veri.GelenAgirlik != "999")
                {
                    yemDurumu = "-6";
                }
                else if (veriler.YemDurumu == "{ value = 0 }")
                {
                    yemDurumu = "-5";

                }
                else
                {
                    yemDurumu = "-5";
                    ViewBag.Mesaj = "Maksimum kapasitede yeminiz vardır!";
                    return View();
                }

                //var yem = client.Set(@"YemDurumu/", yemDurumu);
                var yem = yemDurumu;
            }
            //su
            if (veriler.SuDurumu != null)
            {
                var suseviyesi = client.Get(@"SuSeviyesi/");
                veri.GelenSuSeviyesi = suseviyesi.Body;
                if (veriler.SuDurumu == "{ value = 1 }" && veri.GelenSuSeviyesi != "100")
                {
                    suDurumu = "-4";
                }
                else if (veriler.SuDurumu == "{ value = 0 }")
                {
                    suDurumu = "-3";
                }
                else
                {
                    suDurumu = "-3";
                    ViewBag.Mesaj = "Su Seviyeniz %100'dür. Su ekleme işlemi yapamazsınız!";
                    return View();
                }

                //var su = client.Set(@"SuDurumu/", suDurumu);
                var su = suDurumu;
            }
            //alarm
            if (veriler.Alarm != null)
            {
                if (veriler.Alarm == "{ value = 1 }")
                {
                    alarmDurumu = "-2";
                }
                else
                {
                    alarmDurumu = "-1";
                }
                //var alarm = client.Set(@"Alarm/", alarmDurumu);
                var alarm = alarmDurumu;
            }
            gidecekDegerler = sicaklik + " " + nem + " " + yemDurumu + " " + suDurumu + " " + alarmDurumu+ " ";
            var GidecekDegerler = client.Set(@"GidenDegerler/", gidecekDegerler);
            return View();
        }
    }
}