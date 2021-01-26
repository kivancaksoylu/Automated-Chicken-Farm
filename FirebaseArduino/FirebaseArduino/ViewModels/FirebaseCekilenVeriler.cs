using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace FirebaseArduino.ViewModels
{
    public class FirebaseCekilenVeriler
    {
        public string GelenSicaklik { get; set; }
        public string GelenNem { get; set; }
        public string GelenAgirlik { get; set; }
        public string GelenSuSeviyesi { get; set; }
        public string Hareket { get; set; }
        public string Yangin { get; set; }
        public string GidenSicaklik { get; set; }
        public string GidenNem { get; set; }
        public string YemDurumu { get; set; }
        public string SuDurumu { get; set; }
        public string Alarm { get; set; }
    }
}