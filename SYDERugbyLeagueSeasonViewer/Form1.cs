using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SYDERugbyLeagueSeasonViewer
{
    public partial class Form1 : Form
    {
        // Root myDeserializedClass = JsonConvert.DeserializeObject<Root>(myJsonResponse); 
        public class Ladder
        {
            public int id { get; set; }
            public int lost { get; set; }
            public string name { get; set; }
            public int points { get; set; }
            public int pointsagainst { get; set; }
            public int pointsfor { get; set; }
            public int wins { get; set; }
        }

        public class Game
        {
            public string awayTeam { get; set; }
            public int awayTeamScore { get; set; }
            public string homeTeam { get; set; }
            public int homeTeamScore { get; set; }
            public List<string> summaries { get; set; }
        }

        public class Round
        {
            public List<Game> games { get; set; }
        }

        public class Root
        {
            public List<Ladder> ladder { get; set; }
            public List<Round> rounds { get; set; }
        }
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // read file into a string and deserialize JSON to a type
            string jsonText;
            using (StreamReader sr = File.OpenText("SavedSeasonData\\Season_MonJul261510492021.json"))
            {
                jsonText = sr.ReadToEnd();
                sr.Close();
            }
            Root myDeserializedClass = JsonConvert.DeserializeObject<Root>(jsonText);
            Console.WriteLine(myDeserializedClass.ladder[0].name);
        }

        private void button2_Click(object sender, EventArgs e)
        {
        }
    }
}
