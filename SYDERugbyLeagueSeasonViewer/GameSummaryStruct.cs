using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SYDERugbyLeagueSeasonViewer
{
	enum GameSummaryTextType
	{
		GSTType_Error = 0,
		GSTType_Points = 1,
		GSTType_Penalty = 2,
		GSTType_Sent = 3,
		GSTType_Interchange_Injury = 4,
	};
	public struct GameSummaryStruct
	{
		public GameSummaryStruct(string t, string p, string player, string s)
		{
			summaryTextType = GameSummaryTextType.GSTType_Error;
			Time = t; Play = p; Player = player; ScoreText = s;
			if (Play == "TRY" || Play == "GOAL" || Play == "FIELD GOAL" || Play == "PENALTY GOAL")
			{
				summaryTextType = GameSummaryTextType.GSTType_Points;
			}
			else if (Play == "SEND OFF" || Play == "SIN BIN")
			{
				summaryTextType = GameSummaryTextType.GSTType_Sent;
			}
			else if (Play == "INJURY" || Play == "INTERCHANGE")
			{
				summaryTextType = GameSummaryTextType.GSTType_Interchange_Injury;
			}
			else if (Play == "KNOCK ON" || Play == "FORWARD PASS" || Play == "RUCK INFRINGEMENT")
			{
				summaryTextType = GameSummaryTextType.GSTType_Error;
			}
			else if (Play == "PENALTY")
			{
				summaryTextType = GameSummaryTextType.GSTType_Penalty;
			}
		}
		public string Time;
		public string Play;
		public string Player;
		public string ScoreText;

		public string asLblStr()
        {
			string temp = "";
			if (Time != "!")
			{
				temp += $"{Time}\n";
			}
			temp += $"{Play}\n";
			if (Player != "!")
			{
				temp += $"{Player}\n";
			}
			if (ScoreText != "!")
			{
				temp += $"{ScoreText}\n";
			}
			return temp;
		}

		GameSummaryTextType summaryTextType;
	};
}
