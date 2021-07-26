using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
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
        public class Positions
        {
            public string playerName { get; set; }
            public int points { get; set; }
            public string teamName { get; set; }

        }
        public class Leaderboards
        {
            public string name { get; set; }
            public IList<Positions> positions { get; set; }

        }
        public class Games
        {
            public string awayTeam { get; set; }
            public string awayTeamOdds { get; set; }
            public int awayTeamScore { get; set; }
            public int awayTeamTopLead { get; set; }
            public string homeTeam { get; set; }
            public string homeTeamOdds { get; set; }
            public int homeTeamScore { get; set; }
            public int homeTeamTopLead { get; set; }
            public IList<string> summaries { get; set; }

        }
        public class Rounds
        {
            public IList<Games> games { get; set; }

        }
        public class Season
        {
            public IList<Ladder> ladder { get; set; }
            public IList<Leaderboards> leaderboards { get; set; }
            public IList<Rounds> rounds { get; set; }

        }

        Season _MainSeason;


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
            using (StreamReader sr = File.OpenText("SavedSeasonData\\Season_MonJul261803122021.json"))
            {
                jsonText = sr.ReadToEnd();
                sr.Close();
            }
            _MainSeason = JsonSerializer.Deserialize<Season>(jsonText);
        }

        private void button2_Click(object sender, EventArgs e)
        {
        }
    }
}
