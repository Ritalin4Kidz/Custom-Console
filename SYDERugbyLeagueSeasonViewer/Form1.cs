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
        enum ViewerState
        {
            MatchupsState = 0,
            LadderState = 1,
            LeaderboardState = 2,
        }
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
            public bool playersent { get; set; }
            public IList<string> plays { get; set; }
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
        ViewerState _viewState = ViewerState.MatchupsState;
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

        private void LoadMatchupsForTeam(int team)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    if (_MainSeason.rounds[i].games[ii].awayTeam == _MainSeason.ladder[team].name || _MainSeason.rounds[i].games[ii].homeTeam == _MainSeason.ladder[team].name)
                    {
                        bool won = false;
                        if (_MainSeason.rounds[i].games[ii].awayTeam == _MainSeason.ladder[team].name)
                        {
                            if (_MainSeason.rounds[i].games[ii].awayTeamScore > _MainSeason.rounds[i].games[ii].homeTeamScore)
                            {
                                won = true;
                            }
                        }
                        else
                        {
                            if (_MainSeason.rounds[i].games[ii].homeTeamScore > _MainSeason.rounds[i].games[ii].awayTeamScore)
                            {
                                won = true;
                            }
                        }
                        Panel p = new Panel();
                        p.Name = $"";
                        if (won)
                        {
                            p.BackColor = Color.FromArgb(95, 64, 210, 41);
                        }
                        else if (_MainSeason.rounds[i].games[ii].awayTeamScore == _MainSeason.rounds[i].games[ii].homeTeamScore)
                        {
                            p.BackColor = Color.FromArgb(95, 239, 239, 77);
                        }
                        else
                        {
                            p.BackColor = Color.FromArgb(95, 242, 51, 51);
                        }
                        Label lbl = new Label();
                        lbl.Tag = i.ToString();
                        lbl.Name = "lbl" + i;
                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        lbl.Text = $"Round {i+1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}";
                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        p.Controls.Add(lbl);
                        mainBackPanel.Controls.Add(p);
                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                     // this is just for fun:
                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                        mainBackPanel.Invalidate();
                    }
                }
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

        void ladderPanel_Click(object sender, EventArgs e)
        {
            // do click stuff
            Label l = sender as Label;
            int gameNumber = int.Parse(l.Tag.ToString());
            LoadMatchupsForTeam(gameNumber);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // read file into a string and deserialize JSON to a type
            string jsonText;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.InitialDirectory = Directory.GetCurrentDirectory() + "\\SavedSeasonData\\"; ;
            openFileDialog1.Filter = "Json files (*.json)|*.json|Text files (*.txt)|*.txt";
            openFileDialog1.FilterIndex = 0;
            openFileDialog1.RestoreDirectory = true;
            string selectedFileName = "";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                selectedFileName = openFileDialog1.FileName;
            }
            else
            {
                return;
            }
            using (StreamReader sr = File.OpenText(selectedFileName))
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
            if (_viewState == ViewerState.MatchupsState)
            {
                if (currentRound < 0)
                {
                    currentRound = maxRounds - 1;
                }
                RoundLabel.Text = (currentRound + 1).ToString();
                LoadRoundMatchups(currentRound);
            }
            else if (_viewState == ViewerState.LeaderboardState)
            {
                if (currentRound < 0)
                {
                    currentRound = _MainSeason.leaderboards.Count - 1;
                }
                RoundLabel.Text = (currentRound + 1).ToString();
                LoadLeaderboard(currentRound);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            currentRound++;
            if (_viewState == ViewerState.LeaderboardState)
            {
                if (currentRound >= _MainSeason.leaderboards.Count)
                {
                    currentRound = 0;
                }
                RoundLabel.Text = (currentRound + 1).ToString();
                LoadLeaderboard(currentRound);
            }
            if (_viewState == ViewerState.MatchupsState)
            {
                if (currentRound >= maxRounds)
                {
                    currentRound = 0;
                }
                RoundLabel.Text = (currentRound + 1).ToString();
                LoadRoundMatchups(currentRound);
            }
        }

        private void hmePage_Click(object sender, EventArgs e)
        {
            _viewState = ViewerState.MatchupsState;
            currentRound = 0;
            RoundLabel.Text = (currentRound + 1).ToString();
            LoadRoundMatchups(currentRound);
        }

        private void LoadLeaderboard(int leaderboard)
        {
            mainBackPanel.Controls.Clear();
            int leaderboardCount = 24;
            if (_MainSeason.leaderboards[leaderboard].positions.Count - 1 < 24)
            {
                leaderboardCount = _MainSeason.leaderboards[leaderboard].positions.Count - 1;
            }
            for (int i = leaderboardCount; i >= 0; i--)
            {
                Panel p = new Panel();
                p.Name = $"";
                p.BackColor = Color.FromArgb(95, 73, 243, 132);
                Label lbl = new Label();
                lbl.Name = "lbl" + i;
                lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                lbl.Text = $"{i + 1}. {_MainSeason.leaderboards[leaderboard].positions[i].playerName}\n{_MainSeason.leaderboards[leaderboard].positions[i].points}\n{_MainSeason.leaderboards[leaderboard].positions[i].teamName}";
                p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                p.Controls.Add(lbl);
                mainBackPanel.Controls.Add(p);
                mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                             // this is just for fun:
                p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                mainBackPanel.Invalidate();
            }
            Panel p2 = new Panel();
            p2.Name = $"";
            p2.BackColor = Color.FromArgb(95, 73, 243, 132);
            Label lbl2 = new Label();
            lbl2.Name = "lbl";
            lbl2.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
            lbl2.Text = $"{_MainSeason.leaderboards[leaderboard].name}";
            p2.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
            p2.Controls.Add(lbl2);
            mainBackPanel.Controls.Add(p2);
            mainBackPanel.Controls.SetChildIndex(p2, 0);  // this moves the new one to the top!
            p2.Paint += (ss, ee) => { ee.Graphics.DrawString(p2.Name, Font, Brushes.White, 22, 11); };
            mainBackPanel.Invalidate();
        }

        private void LadderBtn_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            _viewState = ViewerState.LadderState;
            for (int i = _MainSeason.ladder.Count - 1; i >= 0; i--)
            {
                Panel p = new Panel();
                p.Name = $"";
                p.BackColor = Color.FromArgb(95, 173, 43, 200);
                Label lbl = new Label();
                lbl.Name = "lbl" + i;
                lbl.Tag = i.ToString();
                lbl.Click += ladderPanel_Click;
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

        private void LdrBoardBtn_Click(object sender, EventArgs e)
        {
            currentRound = 0;
            RoundLabel.Text = (currentRound + 1).ToString();
            _viewState = ViewerState.LeaderboardState;
            LoadLeaderboard(currentRound);
        }

        private void ComebackSrch_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    bool AddGame = false;
                    string ComebackText = "";
                    if (_MainSeason.rounds[i].games[ii].awayTeamTopLead >= 12 && _MainSeason.rounds[i].games[ii].homeTeamScore >= _MainSeason.rounds[i].games[ii].awayTeamScore)
                    {
                        AddGame = true;
                        ComebackText = $"Comeback from {_MainSeason.rounds[i].games[ii].awayTeamTopLead} points";
                    }
                    else if (_MainSeason.rounds[i].games[ii].homeTeamTopLead >= 12 && _MainSeason.rounds[i].games[ii].awayTeamScore >= _MainSeason.rounds[i].games[ii].homeTeamScore)
                    {
                        AddGame = true;
                        ComebackText = $"Comeback from {_MainSeason.rounds[i].games[ii].homeTeamTopLead} points";
                    }
                    if (AddGame)
                    {
                        Panel p = new Panel();
                        p.Name = $"";
                        p.BackColor = Color.FromArgb(95, 64, 210, 41);
                        Label lbl = new Label();
                        lbl.Tag = i.ToString();
                        lbl.Name = "lbl" + i;
                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        lbl.Text = $"Round {i + 1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}\n{ComebackText}";
                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        p.Controls.Add(lbl);
                        mainBackPanel.Controls.Add(p);
                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                     // this is just for fun:
                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                        mainBackPanel.Invalidate();
                    }
                }
            }
        }

        private void ThrashingsButton_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    int diff = _MainSeason.rounds[i].games[ii].homeTeamScore - _MainSeason.rounds[i].games[ii].awayTeamScore;
                    if (diff < 0)
                    {
                        diff *= -1;
                    }
                    bool AddGame = false;
                    string DifferenceText = "";
                    if (diff >= 30)
                    {
                        AddGame = true;
                        DifferenceText = $"Difference was {diff} points";
                    }
                    if (AddGame)
                    {
                        Panel p = new Panel();
                        p.Name = $"";
                        p.BackColor = Color.FromArgb(95, 64, 210, 41);
                        Label lbl = new Label();
                        lbl.Tag = i.ToString();
                        lbl.Name = "lbl" + i;
                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        lbl.Text = $"Round {i + 1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}\n{DifferenceText}";
                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        p.Controls.Add(lbl);
                        mainBackPanel.Controls.Add(p);
                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                     // this is just for fun:
                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                        mainBackPanel.Invalidate();
                    }
                }
            }
        }

        private void NailBiters_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    int diff = _MainSeason.rounds[i].games[ii].homeTeamScore - _MainSeason.rounds[i].games[ii].awayTeamScore;
                    if (diff < 0)
                    {
                        diff *= -1;
                    }
                    bool AddGame = false;
                    string DifferenceText = "";
                    if (diff == 1)
                    {
                        AddGame = true;
                        DifferenceText = $"Difference was 1 point";
                    }
                    else if (diff <= 3)
                    {
                        AddGame = true;
                        DifferenceText = $"Difference was {diff} points";
                    }
                    if (AddGame)
                    {
                        Panel p = new Panel();
                        p.Name = $"";
                        p.BackColor = Color.FromArgb(95, 64, 210, 41);
                        Label lbl = new Label();
                        lbl.Tag = i.ToString();
                        lbl.Name = "lbl" + i;
                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        lbl.Text = $"Round {i + 1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}\n{DifferenceText}";
                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        p.Controls.Add(lbl);
                        mainBackPanel.Controls.Add(p);
                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                     // this is just for fun:
                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                        mainBackPanel.Invalidate();
                    }
                }
            }
        }

        private void plyerSentGme_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    if (_MainSeason.rounds[i].games[ii].playersent)
                    {
                        Panel p = new Panel();
                        p.Name = $"";
                        p.BackColor = Color.FromArgb(95, 64, 210, 41);
                        Label lbl = new Label();
                        lbl.Tag = i.ToString();
                        lbl.Name = "lbl" + i;
                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        lbl.Text = $"Round {i + 1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}";
                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                        p.Controls.Add(lbl);
                        mainBackPanel.Controls.Add(p);
                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                     // this is just for fun:
                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                        mainBackPanel.Invalidate();
                    }
                }
            }
        }

        private void hattricksBtn_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    for (int iii = _MainSeason.rounds[i].games[ii].plays.Count - 1; iii >= 0; iii--)
                    {
                        //Tries: 1
                        if (_MainSeason.rounds[i].games[ii].plays[iii].Contains("|Tries: "))
                        {
                            List<String> stats = _MainSeason.rounds[i].games[ii].plays[iii].Split("|").ToList<string>();
                            for (int j = 0; j < stats.Count; j++)
                            {
                                if (stats[j].Contains("Tries: "))
                                {
                                    string value = stats[j].Replace("Tries: ","");
                                    value = value.Trim();
                                    int tries = Int16.Parse(value);
                                    if (tries >= 3)
                                    {
                                        Panel p = new Panel();
                                        p.Name = $"";
                                        p.BackColor = Color.FromArgb(95, 64, 210, 41);
                                        Label lbl = new Label();
                                        lbl.Tag = i.ToString();
                                        lbl.Name = "lbl" + i;
                                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                                        lbl.Text = $"Round {i + 1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}\n{stats[0].Split(":")[1].Trim()}\n{tries} Tries";
                                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                                        p.Controls.Add(lbl);
                                        mainBackPanel.Controls.Add(p);
                                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                                     // this is just for fun:
                                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                                        mainBackPanel.Invalidate();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void highScorers_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    for (int iii = _MainSeason.rounds[i].games[ii].plays.Count - 1; iii >= 0; iii--)
                    {
                        //Tries: 1
                        if (_MainSeason.rounds[i].games[ii].plays[iii].Contains("|Total Points: "))
                        {
                            List<String> stats = _MainSeason.rounds[i].games[ii].plays[iii].Split("|").ToList<string>();
                            for (int j = 0; j < stats.Count; j++)
                            {
                                if (stats[j].Contains("Total Points: "))
                                {
                                    string value = stats[j].Replace("Total Points: ", "");
                                    value = value.Trim();
                                    int points = Int16.Parse(value);
                                    if (points >= 20)
                                    {
                                        Panel p = new Panel();
                                        p.Name = $"";
                                        p.BackColor = Color.FromArgb(95, 64, 210, 41);
                                        Label lbl = new Label();
                                        lbl.Tag = i.ToString();
                                        lbl.Name = "lbl" + i;
                                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                                        lbl.Text = $"Round {i + 1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}\n{stats[0].Split(":")[1].Trim()}\n{points} Points";
                                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                                        p.Controls.Add(lbl);
                                        mainBackPanel.Controls.Add(p);
                                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                                     // this is just for fun:
                                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                                        mainBackPanel.Invalidate();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void highFantasy_Click(object sender, EventArgs e)
        {
            mainBackPanel.Controls.Clear();
            for (int i = _MainSeason.rounds.Count - 1; i >= 0; i--)
            {
                for (int ii = _MainSeason.rounds[i].games.Count - 1; ii >= 0; ii--)
                {
                    for (int iii = _MainSeason.rounds[i].games[ii].plays.Count - 1; iii >= 0; iii--)
                    {
                        //Tries: 1
                        if (_MainSeason.rounds[i].games[ii].plays[iii].Contains("|Fantasy Points: "))
                        {
                            List<String> stats = _MainSeason.rounds[i].games[ii].plays[iii].Split("|").ToList<string>();
                            for (int j = 0; j < stats.Count; j++)
                            {
                                if (stats[j].Contains("Fantasy Points: "))
                                {
                                    string value = stats[j].Replace("Fantasy Points: ", "");
                                    value = value.Trim();
                                    int points = Int16.Parse(value);
                                    if (points >= 90)
                                    {
                                        Panel p = new Panel();
                                        p.Name = $"";
                                        p.BackColor = Color.FromArgb(95, 64, 210, 41);
                                        Label lbl = new Label();
                                        lbl.Tag = i.ToString();
                                        lbl.Name = "lbl" + i;
                                        lbl.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                                        lbl.Text = $"Round {i + 1}:\n{_MainSeason.rounds[i].games[ii].homeTeam} {_MainSeason.rounds[i].games[ii].homeTeamScore} v {_MainSeason.rounds[i].games[ii].awayTeamScore} {_MainSeason.rounds[i].games[ii].awayTeam}\n{stats[0].Split(":")[1].Trim()}\n{points} FP";
                                        p.Size = new Size(mainBackPanel.ClientSize.Width - 40, 65);
                                        p.Controls.Add(lbl);
                                        mainBackPanel.Controls.Add(p);
                                        mainBackPanel.Controls.SetChildIndex(p, 0);  // this moves the new one to the top!
                                                                                     // this is just for fun:
                                        p.Paint += (ss, ee) => { ee.Graphics.DrawString(p.Name, Font, Brushes.White, 22, 11); };
                                        mainBackPanel.Invalidate();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
