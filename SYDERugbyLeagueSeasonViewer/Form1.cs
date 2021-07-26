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
        int maxRounds = 0;
        int currentRound = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void LoadMatchupInDepth(int round, int game)
        {
            mainBackPanel.Controls.Clear();
            List<GameSummaryStruct> gameSummaries =  new List<GameSummaryStruct>();
            for (int i = _MainSeason.rounds[round].games[game].summaries.Count - 1; i >= 0; i--)
            {
                string[] temp = _MainSeason.rounds[round].games[game].summaries[i].Split('#');
                gameSummaries.Add(new GameSummaryStruct(temp[0], temp[2], temp[1], temp[3]));
            }
            for (int i = gameSummaries.Count - 1; i >= 0; i--)
            {
                Panel p = new Panel();
                p.Name = $"";
                p.BackColor = Color.FromArgb(95, 205, 189, 146);

                Label lbl = new Label();
                lbl.Name = "lbl" + i;
                lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                lbl.Text = gameSummaries[i].asLblStr();
                p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                p.Controls.Add(lbl);

                mainBackPanel.Controls.Add(p);
                mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                             // this is just for fun:
                p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                mainBackPanel.Invalidate();
            }
        }

        private void LoadRoundMatchups(int round)
        {
            try
            {
                mainBackPanel.Controls.Clear();
                for (int i = _MainSeason.rounds[round].games.Count - 1; i >= 0; i--)
                {
                    Panel p = new Panel();
                    p.Name = $"";
                    p.BackColor = Color.FromArgb(95, 105, 109, 246);
                    Label lbl = new Label();
                    lbl.Tag = i.ToString();
                    lbl.Click += matchPanel_Click;
                    lbl.Name = "lbl" + i;
                    lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                    lbl.Text = $"{_MainSeason.rounds[round].games[i].homeTeam} {_MainSeason.rounds[round].games[i].homeTeamScore} v {_MainSeason.rounds[round].games[i].awayTeamScore} {_MainSeason.rounds[round].games[i].awayTeam}";
                    p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                    p.Controls.Add(lbl);
                    mainBackPanel.Controls.Add(p);
                    mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                 // this is just for fun:
                    p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                    mainBackPanel.Invalidate();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            RoundLabel.Text = (currentRound + 1).ToString();
        }

        void matchPanel_Click(object sender, EventArgs e)
        {
            // do click stuff
            Label l = sender as Label;
            int gameNumber = int.Parse(l.Tag.ToString());
            LoadMatchupInDepth(currentRound, gameNumber);
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
            maxRounds = _MainSeason.rounds.Count;
            currentRound = 0;
            RoundLabel.Text = (currentRound + 1).ToString();
            LoadRoundMatchups(currentRound);
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            currentRound--;
            if (currentRound < 0)
            {
                currentRound = maxRounds - 1;
            }
            RoundLabel.Text = (currentRound + 1).ToString();
            LoadRoundMatchups(currentRound);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            currentRound++;
            if (currentRound >= maxRounds)
            {
                currentRound = 0;
            }
            RoundLabel.Text = (currentRound + 1).ToString();
            LoadRoundMatchups(currentRound);
        }

        private void hmePage_Click(object sender, EventArgs e)
        {
            LoadRoundMatchups(currentRound);
        }

        private void LadderBtn_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.ladder.Count - 1; i >= 0; i--)
            {
                Panel p = new Panel();
                p.Name = $"";
                p.BackColor = Color.FromArgb(95, 173, 43, 200);
                p.Tag = i.ToString();
                Label lbl = new Label();
                lbl.Name = "lbl" + i;
                lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                lbl.Text = $"{i + 1}. {_MainSeason.ladder[i].name}\nWins: {_MainSeason.ladder[i].wins} | Lost: {_MainSeason.ladder[i].lost}\nPoints: {_MainSeason.ladder[i].points}\nPoints Difference: {_MainSeason.ladder[i].pointsfor - _MainSeason.ladder[i].pointsagainst}";
                p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                p.Controls.Add(lbl);
                mainBackPanel.Controls.Add(p);
                mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                             // this is just for fun:
                p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                p.Click += matchPanel_Click;
                mainBackPanel.Invalidate();
            }
        }
    }
}
