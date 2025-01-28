#include <iostream>
#include <cstdlib>
#include <ctime>

struct Status {
    std::string status_code;
};

struct Rules {
    int winningNumber = 0;
    int guessTotal = 0;
    int numAttempts = 0;
};

struct UserInput {
    int guessingNumber = 0;
    char replayGuessingGame = NULL;
};

void guessingGameTest(UserInput& user, Rules& features);
void requestToPlayAgain(UserInput& user, Rules& features);
void updateUserOnGameStatus(UserInput& user, Rules& features);
void incrementGuessAttempts(Rules& features);
void clearKeyboard();
UserInput userGuessSelection(UserInput& user);
UserInput userReplaySelection(UserInput& user);
Status userGuessStatus(UserInput& user, Rules& features);
bool isGameWinner(UserInput& user, Rules& features);
bool isGuessingNumberTooHigh(UserInput& user, Rules& winningNumber);
bool areGuessesAvailable(Rules& features);
bool userWantsReplay(UserInput& user);

int main(void)
{
    std::srand((unsigned) std::time(0));
    Rules features;
    features.winningNumber = (std::rand() % 100) + 1;
    features.guessTotal = 5;
    features.numAttempts = 1;
    UserInput user;
    guessingGameTest(user, features);
    
    return EXIT_SUCCESS;
}

void guessingGameTest(UserInput& user, Rules& features) {
    while (true) {
        user = userGuessSelection(user);
        Status status = userGuessStatus(user, features);
        if (status.status_code == "Winner") {
            std::cout << "Congratulations!! You won on " << (features.numAttempts) << " attempts!" << std::endl;
            requestToPlayAgain(user, features);
        } else if (status.status_code == "Incorrect") {
            updateUserOnGameStatus(user, features);
            incrementGuessAttempts(features);
        } else {
            std::cout << "Gameover! Winning number is " << features.winningNumber << std::endl;
            requestToPlayAgain(user, features);
        }
    }
}

UserInput userGuessSelection(UserInput& user) {
    std::cout << "Enter a number between 1 and 100. If you guess the right number you win a prize: ";
    while (!(std::cin >> user.guessingNumber) || user.guessingNumber < 0 || user.guessingNumber > 100) {
        std::cerr << "Error! Please enter a number from 1 to 100: ";
        clearKeyboard();
    }
    clearKeyboard();
    
    return user;
}

void updateUserOnGameStatus(UserInput& user, Rules& features) {
    if (isGuessingNumberTooHigh(user, features)) {
        std::cout << user.guessingNumber << " is too high." << std::endl;
    } else {
        std::cout << user.guessingNumber << " is too low." << std::endl;
    }
    
    std::cout << "You have " << (features.guessTotal - features.numAttempts) << " attempts left." << std::endl;
}

void incrementGuessAttempts(Rules& features) {
    ++features.numAttempts;
}

void requestToPlayAgain(UserInput& user, Rules& features) {
    user = userReplaySelection(user);
    if (userWantsReplay(user)) {
        features.numAttempts = 1;
        std::srand((unsigned) std::time(0));
        features.winningNumber = (std::rand() % 100) + 1; // 100;
    } else {
        std::cout << "Thank you for playing! Please come again." << std::endl;
        exit(EXIT_SUCCESS);
    }
}

UserInput userReplaySelection(UserInput& user) {
    std::cout << "Would you like to play again? if yes enter (y or Y). To exit enter (n or N): ";
    while (!(std::cin >> user.replayGuessingGame) ||
           (user.replayGuessingGame != 'y' && user.replayGuessingGame != 'Y' &&
            user.replayGuessingGame != 'n' && user.replayGuessingGame != 'N')) {
        std::cerr << "Invalid selection. To replay please enter (y or Y) or (n or N) to exit: ";
        clearKeyboard();
    }
    clearKeyboard();
    
    return user;
}

void clearKeyboard() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}

Status userGuessStatus(UserInput& user, Rules& features) {
    Status status;
    if (isGameWinner(user, features)) {
        status.status_code = "Winner";
    } else if (areGuessesAvailable(features)) {
        status.status_code = "Incorrect";
    } else {
        status.status_code = "Gameover";
    }
    
    return status;
}
 
bool isGameWinner(UserInput& user, Rules& features) {
    return user.guessingNumber == features.winningNumber;
}

bool areGuessesAvailable(Rules& features) {
    return features.numAttempts != features.guessTotal;
}

bool userWantsReplay(UserInput& user) {
    return (user.replayGuessingGame == 'y' || user.replayGuessingGame == 'Y');
}

bool isGuessingNumberTooHigh(UserInput& user, Rules& features) {
    return user.guessingNumber > features.winningNumber;
}
