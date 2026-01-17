#include <iostream>
#include <cstdlib>
#include <ctime> 

using namespace std;


// This project made by Eng.Hazem Hamada
// Math-Game-version-3.0 Final Version


enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOPType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };


string GetQuestionsLevelText(enQuestionsLevel QuestionsLevel)
{
    string arrQuestionsLevel[4] = { "Easy" , "Med", "Hard", "MixLevel" };

    return arrQuestionsLevel[int(QuestionsLevel - 1)];
};


string GetenOPTypeSymbol(enOPType OPType) 
{
    switch (OPType)
    {
    case enOPType::Add:
        return "+";
    case enOPType::Sub:
        return "-";
    case enOPType::Mult:
        return "x";
    case enOPType::Div:
        return "/";
    default:
        return "Mix";
    }
}


int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}


struct stQuestionInfo
{
    int Number1 = 0;
    int Number2 = 0;
    enOPType OPType;
    enQuestionsLevel QuestionsLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};


struct stQuizz
{
    stQuestionInfo QuestionList[100];
    int NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel;
    enOPType OPType;
    int NumberOfWrongAnswer = 0;
    int NumberOfRightAnswer = 0;
    bool IsPass = false;
};


void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}


int ReadHowManyQuestions() 
{
    int Number = 0;
    do
    {
        cout << "\nHow many questions do you want to answer [1] to [100] ? : ";
        cin >> Number;
    } while (Number < 1 || Number > 100);

    return Number;
}


enQuestionsLevel ReadQuestionsLevel() 
{
    int level;

    do
    {
        cout << "\nEnter Question level [1]:Easy, [2]:Medium, [3]:Hard, [4]:MixLevel ? ";
        cin >> level;

    } while (level < 1 || level > 4);

    return enQuestionsLevel(level);
}


enOPType ReadOPType() 
{
    int OPTypeNum;

    do
    {
        cout << "Enter Operation type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ";
        cin >> OPTypeNum;

    } while (OPTypeNum < 1 || OPTypeNum > 5);

    return enOPType(OPTypeNum);
}


int SimpleCalculator(int Number1, int Number2, enOPType OpType)
{
    switch (OpType)
    {
    case enOPType::Add:
        return Number1 + Number2;
    case enOPType::Sub:
        return Number1 - Number2;
    case enOPType::Mult:
        return Number1 * Number2;
    case enOPType::Div:
        return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
    default:
        return Number1 + Number2;
    }
}


enOPType GetRandomOpType() {

    return enOPType(RandomNumber(1, 4));
}


stQuestionInfo GenerateQuestionInfo(enQuestionsLevel QuestionsLevel, enOPType OPType) 
{
    stQuestionInfo QuestionInfo;

    if (QuestionsLevel == enQuestionsLevel::MixLevel) {

        QuestionsLevel = enQuestionsLevel(RandomNumber(1, 3));
    }
    if (OPType == enOPType::MixOp) {

        OPType = GetRandomOpType();
    }
    QuestionInfo.OPType = OPType;

    switch (QuestionsLevel)
    {
    case enQuestionsLevel::Easy:
        QuestionInfo.Number1 = RandomNumber(1, 10);
        QuestionInfo.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionsLevel::Med:
        QuestionInfo.Number1 = RandomNumber(10, 50);
        QuestionInfo.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionsLevel::Hard:
        QuestionInfo.Number1 = RandomNumber(50, 100);
        QuestionInfo.Number2 = RandomNumber(50, 100);
        break;
    }

    QuestionInfo.CorrectAnswer = SimpleCalculator(QuestionInfo.Number1, QuestionInfo.Number2, QuestionInfo.OPType);
    QuestionInfo.QuestionsLevel = QuestionsLevel;

    return QuestionInfo;
}


void GenerateQuizzQuestion(stQuizz &Quizz)
{
    for (int quetion = 0; quetion < Quizz.NumberOfQuestions; quetion++) {

        Quizz.QuestionList[quetion] = GenerateQuestionInfo(Quizz.QuestionsLevel, Quizz.OPType);
    }
};


void PrintTheQuestion(stQuizz& Quizz, int QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl << Quizz.QuestionList[QuestionNumber].Number2
         << " " << GetenOPTypeSymbol(Quizz.QuestionList[QuestionNumber].OPType) << "\n___________\n";

}


int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}


void CorrectTheQuestionAnswer(stQuizz &Quizz, int QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {

        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        cout << "\nWrong answer :( \n";
        cout << "\nRight answer is : ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else 
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;

        cout << "\nRight answer :) \n\n";
    }
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
};


void AskAndCorrectQuestionAnswerList(stQuizz& Quizz)
{
    for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {

        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.IsPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}


string GetFinalResultText(bool IsPass)
{
    if (IsPass) {
        return "Pass";
    }
    return "Fail";
}


void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "-------------------------------\n\n";
    cout << "Final Result is " << GetFinalResultText(Quizz.IsPass);
    cout << "\n------------------------------\n\n";
    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Question Level     : " << GetQuestionsLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType             : " << GetenOPTypeSymbol(Quizz.OPType) << endl;
    cout << "Number of right answer: " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number of wrong ansewr: " << Quizz.NumberOfWrongAnswer << endl;
    cout << "-------------------------------\n\n";
}


void ResetScreen()
{
    system("cls");
    system("color 0F");
}


void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OPType = ReadOPType();

    GenerateQuizzQuestion(Quizz);
    AskAndCorrectQuestionAnswerList(Quizz);

    PrintQuizzResults(Quizz);
}


void PrintAboutUs()
{
    system("cls");
    system("color 0B");

    cout << "========================================\n";
    cout << "               ABOUT ME                 \n";
    cout << "========================================\n\n";

    cout << "Name      : Hazem Hamada Emara\n";
    cout << "Age       : 19 Years Old\n";
    cout << "Role      : Future Software Engineer & Cybersecurity Engineer\n\n";

    cout << "Interests :\n";
    cout << "- Computer Science (Core Concepts)\n";
    cout << "- Software Engineering\n";
    cout << "- Cybersecurity\n\n";

    cout << "Description:\n";
    cout << "I am passionate about learning Computer Science and gaining\n";
    cout << "both theoretical and practical knowledge.\n\n";

    cout << "I build practical projects to apply what I learn and turn\n";
    cout << "concepts into real-world experience.\n\n";

    cout << "========================================\n";
}


void StartGame() 
{
    char PlayAgain = 'Y';
    char AboutUS = 'N';

    do
    {
        ResetScreen();
        PlayMathGame();

        cout << endl << "Do you want play again Y/N ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

    cout << "\nEnter [Y] to Read About US Or [N] ? ";
    cin >> AboutUS;

    if (AboutUS == 'Y' || AboutUS == 'y') {
        PrintAboutUs();
    }
}


int main() {
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}