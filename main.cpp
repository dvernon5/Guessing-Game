#include <iostream>
#include <cstdlib>
#include <ctime>

void guessingGame (int, int, int);

int main(void)
{
    std::srand((unsigned) std::time(0));
    int winningNumber = (std::rand() % 100) + 1;
    const int guessingAttemptsAmount = 5;
    int numberOfAttempts = 0;
    
    guessingGame(winningNumber, guessingAttemptsAmount, numberOfAttempts);
    
    return 0;
}

void guessingGame (int winningNumber, int guessingAttemptsAmount, int numberOfAttempts)
{
    int guessingNumber = 0;
    int replayGuessingGame = 0;
    
    while (1)
    {
        std::cout << "Enter a number between 1 and 100. If you guess the right number you win a prize: ";
        std::cin  >> guessingNumber;
        
        if (guessingNumber < 1 || guessingNumber > 100)
        {
            std::cout << "You enter an invalid number.\n";
            continue;
        } else if (guessingNumber == winningNumber) {
            std::cout << "Congratulations!! You won on " << (numberOfAttempts + 1) << " attempts!" << std::endl;
            std::cout << "Would you like to play again? if yes enter 1, no enter 0: ";
            std::cin  >> replayGuessingGame;
            
            while (replayGuessingGame < 0 || replayGuessingGame > 1)
            {
                std::cout << "Invalid number. Please enter 1 to replay or 0 to exit: ";
                std::cin  >> replayGuessingGame;
            }
            if (replayGuessingGame == 1)
            {
                numberOfAttempts = 0;
                std::srand((unsigned) std::time(0));
                winningNumber = (std::rand() % 100) + 1;
                continue;
            } else if (replayGuessingGame == 0) {
                std::cout << "You are leaving the game. We hope to see you again." << std::endl;
                break;
            }
        } else if (guessingNumber > winningNumber) {
            std::cout << guessingNumber << " is too high." << std::endl;
            std::cout << "You have " << (guessingAttemptsAmount - numberOfAttempts - 1) << " attempts left." << std::endl;
        } else if (guessingNumber < winningNumber) {
            std::cout << guessingNumber << " is too low." << std::endl;
            std::cout << "You have " << (guessingAttemptsAmount - numberOfAttempts - 1) << " sttempts left." << std::endl;
        }
        
        ++numberOfAttempts;
        
        if (numberOfAttempts == guessingAttemptsAmount)
        {
            std::cout << "Gameover! Winning number is " << winningNumber << std::endl;
            std::cout << "Would you like to play again? If yes enter 1, no enter 0: ";
            std::cin  >> replayGuessingGame;
            
            while (replayGuessingGame < 0 || replayGuessingGame > 1)
            {
                std::cout << "Invalid number. Please enter 1 to replay or 0 to exit: ";
                std::cin  >> replayGuessingGame;
            }
            
            if (replayGuessingGame == 1)
            {
                numberOfAttempts = 0;
                std::srand((unsigned) std::time(0));
                winningNumber = (std::rand() % 100) + 1;
                continue;
            } else if (replayGuessingGame == 0)
            {
                std::cout << "You are now leaving the game. We hope to see you again!" << std::endl;
                break;
            }
        }
    }
}
