#include <iostream>
#include <cstdlib> 
#include <ctime>    
#include <string>   
using namespace std;

// This project made by Eng.Hazem Hamada 
// Stone-paper-scissors-GAME-version-2.0

enum enGameChoise { Stone = 1, Paper = 2, Scissors = 3 };
enum enGameWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoise Player1Choice; 
    enGameChoise ComputerChoice;
    enGameWinner Winner;
    string WinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enGameWinner Winner;
    string WinnerName = "";
};


int RandomNumber(int From, int To)
{
    int RandNumber = rand() % (To - From + 1) + From;
    return RandNumber;
}


short ReadHowManyRounds()
{
    short numberOfRounds = 0;
    do
    {
        cout << "\nEnter how many round you want from [1] to [10] ? ";
        cin >> numberOfRounds;

    } while (numberOfRounds < 1 || numberOfRounds > 10);

    return numberOfRounds;
}


enGameChoise ReadPlayerChoice() {

    short choice;
    do {
        cout << "\nEnter your choice [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    return enGameChoise(choice);
}


enGameChoise GetComputerChoice() {

    return enGameChoise(RandomNumber(1, 3));
}


enGameWinner WhoWonTheRound(stRoundInfo RoundInfo)
{

    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enGameWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoise::Paper:
        if (RoundInfo.ComputerChoice == enGameChoise::Scissors)
            return enGameWinner::Computer;
        break;

    case enGameChoise::Stone:
        if (RoundInfo.ComputerChoice == enGameChoise::Paper)
            return enGameWinner::Computer;
        break;

    case enGameChoise::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoise::Stone)
            return enGameWinner::Computer;
        break;

    }
    return enGameWinner::Player1;
}


string GetWinnerName(enGameWinner GameWinner) {

    string arrWinnerName[3] = { "Player1", "Computer", "Draw" };
    return arrWinnerName[GameWinner - 1];
}


string GetChoiceName(enGameChoise GameChoice) {

    string arrChoiceName[3] = { "Stone", "Paper", "Scissors" };
    return arrChoiceName[GameChoice - 1];
}


void SetWinnerScreenColor(enGameWinner GameWinner) {

    switch (GameWinner)
    {
    case enGameWinner::Player1:
        system("color 2F");
        break;
    case enGameWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}


void PrintRoundResults(stRoundInfo RoundInfo) {

    cout << "\n----------Round[" << RoundInfo.RoundNumber << "]----------\n\n";
    cout << "Player 1 choise :" << GetChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer choise :" << GetChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round winner    : [" << RoundInfo.WinnerName << "]" << endl;
    cout << "--------------------------------\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}


enGameWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enGameWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enGameWinner::Computer;
    else
        return enGameWinner::Draw;
}


stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {

    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.Winner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = GetWinnerName(GameResults.Winner);

    return GameResults;
}


stGameResults PlayGame(short numberOfRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= numberOfRounds; GameRound++)
    {
        cout << "\n______________Round [" << GameRound << "]_____________\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = GetWinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enGameWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enGameWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(numberOfRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}


string Tabs(short NumberOfTabs)
{
    string t = "";

    for (short i = 1; i <= NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}


void ResetScreen()
{
    system("cls");
    system("color 0F");
}


void ShowGameOverScreen()
{
    cout << Tabs(2) << "------------------------------------------\n\n";
    cout << Tabs(2) << " +  +  +  G  A  M  E  O  V  E  R  +  +  + \n";
    cout << Tabs(2) << "------------------------------------------\n\n";
}


void ShowFinalGameResults(stGameResults GameResults)
{

    cout << Tabs(2) << "--------------[Game Results]--------------\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player 1 won times : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "-------------------------------------------\n";

    SetWinnerScreenColor(GameResults.Winner);
}


void StartGame()
{
    char PlayAgain = 'Y'; 

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again ? Y/N ?";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
