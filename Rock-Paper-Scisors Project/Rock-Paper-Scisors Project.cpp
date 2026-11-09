# include<iostream>
# include <cstdlib>
using namespace std;

enum enGameChoice { stone = 1, paper = 2, scissors = 3 };
enum enWinner { Player1 = 1, computer = 2, Draw = 3 };

struct stRoundInfo
{
	short GameRound = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner WinnerR;
	string RoundWinnerName = "";


};


struct stGameResults
{
	short GameRounds = 0;
	short Player1WinnerTime = 0;
	short ComputerWinnerTime = 0;
	short DrawTime = 0;
	enWinner WinnerF;
	string FinalWinnerName = "";


};

short ReadHowManyRound() {

	short RoundNumber = 0;

	do {
		cout << "How many Round to play 1 for 10 ?\n";
		cin >> RoundNumber;
	} while (RoundNumber < 1 || RoundNumber>10);

	return RoundNumber;
}

enGameChoice WhatPlayer1Chice() {

	short Choice = 0;
	do {
		cout << "enter please your choice stone[1],paper[2],scssors[3] ?\n";
		cin >> Choice;
	} while (Choice < 1 || Choice>3);
	return (enGameChoice)Choice;

}
short RandomNumber(short From, short To) {

	return rand() % (To - From + 1) + From;
}

enGameChoice WhatComputerChoice() {

	return (enGameChoice)RandomNumber(1, 3);
}

enWinner RoundWinner(stRoundInfo RoundInfo) {

	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice) {

		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice) {

	case enGameChoice::stone:
		if (RoundInfo.ComputerChoice == enGameChoice::paper) {

			return enWinner::computer;


		}
		break;

	case enGameChoice::paper:
		if (RoundInfo.ComputerChoice == enGameChoice::scissors) {

			return enWinner::computer;
		}
		break;

	case enGameChoice::scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::stone) {

			return enWinner::computer;
		}
		break;


	}
	return enWinner::Player1;
}

string WinnerName(enWinner Winner) {

	string winner[3] = { "player1","computer","no winner" };
	return winner[Winner - 1];
}
void setWinnerScreenColor(enWinner Winner) {

	switch (Winner) {

	case enWinner::Player1:
		system("color 2F");
		break;


	case enWinner::computer:
		system("color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

enWinner WhofinalWinner(short Player1WinnerTime, short Computer2WinnerTime) {

	if (Player1WinnerTime == Computer2WinnerTime) {

		return enWinner::Draw;
	}

	if (Player1WinnerTime > Computer2WinnerTime) {

		return enWinner::Player1;
	}
	else
		return enWinner::computer;



}
string ChoiceName(enGameChoice Choice) {
	string Choices[3] = { "stone" , "paper","scissors" };
	return Choices[Choice - 1];
}
void  PrintRoundResult(stRoundInfo RoundInfo) {

	cout << "_______________Round [" << RoundInfo.GameRound << "]____________\n\n";
	cout << "Player1 choice  :" << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer choice :" << ChoiceName(RoundInfo.ComputerChoice) << endl;;
	cout << "Round Winner    :" << RoundInfo.RoundWinnerName << endl;
	cout << "________________________________________\n\n";
	setWinnerScreenColor(RoundInfo.WinnerR);


}

stGameResults FillGameResult(short HowManyRound, short Player1WinnerTime, short  Computer2WinnerTime, short DrawTime)
{
	stGameResults GameResults;
	GameResults.GameRounds = HowManyRound;
	GameResults.Player1WinnerTime = Player1WinnerTime;
	GameResults.ComputerWinnerTime = Computer2WinnerTime;
	GameResults.DrawTime = DrawTime;
	GameResults.WinnerF = WhofinalWinner(Player1WinnerTime, Computer2WinnerTime);
	GameResults.FinalWinnerName = WinnerName(GameResults.WinnerF);

	return GameResults;
}
stGameResults PlayGame(short HowManyRound) {

	stRoundInfo RoundInfo;
	short Player1WinnerTime = 0, Computer2WinnerTime = 0, DrawTime = 0;

	for (int RoundNumber = 1; RoundNumber <= HowManyRound; RoundNumber++) {

		cout << "\n Round[" << RoundNumber << "]begain \n\n";

		RoundInfo.GameRound = RoundNumber;
		RoundInfo.Player1Choice = WhatPlayer1Chice();
		RoundInfo.ComputerChoice = WhatComputerChoice();
		RoundInfo.WinnerR = RoundWinner(RoundInfo);
		RoundInfo.RoundWinnerName = WinnerName(RoundInfo.WinnerR);


		if (RoundInfo.WinnerR == enWinner::Player1) {
			Player1WinnerTime++;
		}

		else if (RoundInfo.WinnerR == enWinner::computer) {
			Computer2WinnerTime++;
		}

		else
			DrawTime++;


		PrintRoundResult(RoundInfo);
	}

	return FillGameResult(HowManyRound, Player1WinnerTime, Computer2WinnerTime, DrawTime);

}

string Tabe(short NumberOfTabe) {

	string t = "";
	for (int i = 1; i <= NumberOfTabe; i++) {

		t = t + "\t";
	}
	return t;
}

void ShowGameOverScreen() {

	cout << Tabe(4) << "----------------------------------------\n\n";
	cout << Tabe(6) << "GAME OVER \n\n";
	cout << Tabe(4) << "----------------------------------------\n\n";

}

void ShowFinalGameResult(stGameResults GameResult) {


	cout << Tabe(2) << "___________________[Game Result]_______________________\n\n";
	cout << Tabe(2) << "Game Round:       :" << GameResult.GameRounds << endl;
	cout << Tabe(2) << "player1 won times :" << GameResult.Player1WinnerTime << endl;
	cout << Tabe(2) << "computer won times:" << GameResult.ComputerWinnerTime << endl;
	cout << Tabe(2) << "Draw times        :" << GameResult.DrawTime << endl;
	cout << Tabe(2) << "Final Winner      :" << GameResult.FinalWinnerName << endl;
	cout << Tabe(2) << "___________________________________________________________\n";

	setWinnerScreenColor(GameResult.WinnerF);

}

void ReseteScreen() {

	system("cls");
	system("color 0F");
}

void StartGame() {

	char PlayAgin = 'y';

	do {

		ReseteScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRound());
		ShowGameOverScreen();
		ShowFinalGameResult(GameResults);

		cout << "Do yu want to play again ? y/n ?\n";
		cin >> PlayAgin;

	} while (PlayAgin == 'y' || PlayAgin == 'Y');

}


int main() {

	srand((unsigned)time(NULL));
	StartGame();

}