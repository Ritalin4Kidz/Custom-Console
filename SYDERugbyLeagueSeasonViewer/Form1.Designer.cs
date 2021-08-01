
namespace SYDERugbyLeagueSeasonViewer
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.mainBackPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.button2 = new System.Windows.Forms.Button();
            this.RoundLabel = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.MainPanel = new System.Windows.Forms.Panel();
            this.NailBiters = new System.Windows.Forms.Button();
            this.ThrashingsButton = new System.Windows.Forms.Button();
            this.ComebackSrch = new System.Windows.Forms.Button();
            this.LdrBoardBtn = new System.Windows.Forms.Button();
            this.LadderBtn = new System.Windows.Forms.Button();
            this.hmePage = new System.Windows.Forms.Button();
            this.plyerSentGme = new System.Windows.Forms.Button();
            this.MainPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(121, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Load Season";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // mainBackPanel
            // 
            this.mainBackPanel.AutoScroll = true;
            this.mainBackPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.mainBackPanel.Location = new System.Drawing.Point(13, 42);
            this.mainBackPanel.Name = "mainBackPanel";
            this.mainBackPanel.Size = new System.Drawing.Size(1020, 474);
            this.mainBackPanel.TabIndex = 1;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(929, 12);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(32, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "<<";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click_1);
            // 
            // RoundLabel
            // 
            this.RoundLabel.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.RoundLabel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RoundLabel.Location = new System.Drawing.Point(968, 12);
            this.RoundLabel.Name = "RoundLabel";
            this.RoundLabel.Size = new System.Drawing.Size(25, 23);
            this.RoundLabel.TabIndex = 3;
            this.RoundLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(999, 12);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(32, 23);
            this.button3.TabIndex = 4;
            this.button3.Text = ">>";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // MainPanel
            // 
            this.MainPanel.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.MainPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MainPanel.Controls.Add(this.plyerSentGme);
            this.MainPanel.Controls.Add(this.NailBiters);
            this.MainPanel.Controls.Add(this.ThrashingsButton);
            this.MainPanel.Controls.Add(this.ComebackSrch);
            this.MainPanel.Controls.Add(this.LdrBoardBtn);
            this.MainPanel.Controls.Add(this.LadderBtn);
            this.MainPanel.Controls.Add(this.hmePage);
            this.MainPanel.Location = new System.Drawing.Point(13, 522);
            this.MainPanel.Name = "MainPanel";
            this.MainPanel.Size = new System.Drawing.Size(1020, 74);
            this.MainPanel.TabIndex = 5;
            // 
            // NailBiters
            // 
            this.NailBiters.Location = new System.Drawing.Point(694, 0);
            this.NailBiters.Name = "NailBiters";
            this.NailBiters.Size = new System.Drawing.Size(133, 34);
            this.NailBiters.TabIndex = 5;
            this.NailBiters.Text = "Nail-Biters";
            this.NailBiters.UseVisualStyleBackColor = true;
            this.NailBiters.Click += new System.EventHandler(this.NailBiters_Click);
            // 
            // ThrashingsButton
            // 
            this.ThrashingsButton.Location = new System.Drawing.Point(555, 0);
            this.ThrashingsButton.Name = "ThrashingsButton";
            this.ThrashingsButton.Size = new System.Drawing.Size(133, 34);
            this.ThrashingsButton.TabIndex = 4;
            this.ThrashingsButton.Text = "Thrashings";
            this.ThrashingsButton.UseVisualStyleBackColor = true;
            this.ThrashingsButton.Click += new System.EventHandler(this.ThrashingsButton_Click);
            // 
            // ComebackSrch
            // 
            this.ComebackSrch.Location = new System.Drawing.Point(416, 0);
            this.ComebackSrch.Name = "ComebackSrch";
            this.ComebackSrch.Size = new System.Drawing.Size(133, 34);
            this.ComebackSrch.TabIndex = 3;
            this.ComebackSrch.Text = "Comebacks";
            this.ComebackSrch.UseVisualStyleBackColor = true;
            this.ComebackSrch.Click += new System.EventHandler(this.ComebackSrch_Click);
            // 
            // LdrBoardBtn
            // 
            this.LdrBoardBtn.Location = new System.Drawing.Point(277, 0);
            this.LdrBoardBtn.Name = "LdrBoardBtn";
            this.LdrBoardBtn.Size = new System.Drawing.Size(133, 34);
            this.LdrBoardBtn.TabIndex = 2;
            this.LdrBoardBtn.Text = "Leaderboards";
            this.LdrBoardBtn.UseVisualStyleBackColor = true;
            this.LdrBoardBtn.Click += new System.EventHandler(this.LdrBoardBtn_Click);
            // 
            // LadderBtn
            // 
            this.LadderBtn.Location = new System.Drawing.Point(138, 0);
            this.LadderBtn.Name = "LadderBtn";
            this.LadderBtn.Size = new System.Drawing.Size(133, 34);
            this.LadderBtn.TabIndex = 1;
            this.LadderBtn.Text = "Ladder";
            this.LadderBtn.UseVisualStyleBackColor = true;
            this.LadderBtn.Click += new System.EventHandler(this.LadderBtn_Click);
            // 
            // hmePage
            // 
            this.hmePage.Location = new System.Drawing.Point(-1, 0);
            this.hmePage.Name = "hmePage";
            this.hmePage.Size = new System.Drawing.Size(133, 34);
            this.hmePage.TabIndex = 0;
            this.hmePage.Text = "Home Page";
            this.hmePage.UseVisualStyleBackColor = true;
            this.hmePage.Click += new System.EventHandler(this.hmePage_Click);
            // 
            // plyerSentGme
            // 
            this.plyerSentGme.Location = new System.Drawing.Point(-1, 35);
            this.plyerSentGme.Name = "plyerSentGme";
            this.plyerSentGme.Size = new System.Drawing.Size(133, 34);
            this.plyerSentGme.TabIndex = 6;
            this.plyerSentGme.Text = "Player Sent In Game";
            this.plyerSentGme.UseVisualStyleBackColor = true;
            this.plyerSentGme.Click += new System.EventHandler(this.plyerSentGme_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1045, 608);
            this.Controls.Add(this.MainPanel);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.RoundLabel);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.mainBackPanel);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "SYDE Rugby League Season Viewer";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MainPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.FlowLayoutPanel mainBackPanel;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label RoundLabel;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Panel MainPanel;
        private System.Windows.Forms.Button hmePage;
        private System.Windows.Forms.Button LadderBtn;
        private System.Windows.Forms.Button LdrBoardBtn;
        private System.Windows.Forms.Button ComebackSrch;
        private System.Windows.Forms.Button ThrashingsButton;
        private System.Windows.Forms.Button NailBiters;
        private System.Windows.Forms.Button plyerSentGme;
    }
}

