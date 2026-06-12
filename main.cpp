#include <raylib.h>
#include <iostream>
using namespace std;

enum GameState
{
    MAIN_MENU,
    DIFFICULTY_MENU,
    PLAYER_MENU,
    GAMEPLAY
};

enum Difficulty
{
    EASY,
    MEDIUM,
    HARD
};
enum Player
{
    SINGLE_PLAYER,
    TWO_PLAYER
};
class GameMenu
{
private:
    GameState currentState;
    Difficulty selectedDifficulty;
    Player selectPlayer;
    Rectangle startButton;
    Rectangle easyButton;
    Rectangle mediumButton;
    Rectangle hardButton;
    Rectangle singlePlayer;
    Rectangle multiPlayer;
    Music menuMusic;
    int selectedOption;

public:
    GameMenu()
    {
        currentState = MAIN_MENU;
        selectedDifficulty = EASY;

        startButton = {300, 250, 200, 60};
        easyButton = {300, 180, 200, 60};
        mediumButton = {300, 280, 200, 60};
        hardButton = {300, 380, 200, 60};
        singlePlayer = {300, 200, 200, 60};
        multiPlayer = {300, 300, 200, 60};
        selectedOption = 0;
        menuMusic = LoadMusicStream("Assets/menu.mp3");
        PlayMusicStream(menuMusic);
    }

    void audioManager()
    {
        if (currentState == MAIN_MENU ||
            currentState == DIFFICULTY_MENU || currentState == PLAYER_MENU)
        {
            if (!IsMusicStreamPlaying(menuMusic))
            {
                PlayMusicStream(menuMusic);
            }

            UpdateMusicStream(menuMusic);
        }
        else
        {
            StopMusicStream(menuMusic);
        }
    }
    /*void resetMenu()
{
    selectedOption = 0;
    currentState = MAIN_MENU;
}*/
    void resetDifficultyMenu()
    {
        selectedOption = 0;
        currentState = MAIN_MENU;
    }
    void Update()
    {
        Vector2 mousePos = GetMousePosition();

        if (currentState == MAIN_MENU)
        {
            if (CheckCollisionPointRec(mousePos, startButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentState = PLAYER_MENU;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = PLAYER_MENU;
            }
        }

        else if (currentState == DIFFICULTY_MENU)
        {
            if (IsKeyPressed(KEY_UP))
            {
                selectedOption--;
                if (selectedOption < 0)
                {
                    selectedOption = 2;
                }
            }
            if (IsKeyPressed(KEY_DOWN))
            {
                selectedOption++;
                if (selectedOption > 2)
                {
                    selectedOption = 0;
                }
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                if (selectedOption == 0)
                {
                    selectedDifficulty = EASY;
                    currentState = GAMEPLAY;
                }
                else if (selectedOption == 1)
                {
                    selectedDifficulty = MEDIUM;
                    currentState = GAMEPLAY;
                }
                else if (selectedOption == 2)
                {
                    selectedDifficulty = HARD;
                    currentState = GAMEPLAY;
                }
            }
            if (CheckCollisionPointRec(mousePos, easyButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedDifficulty = EASY;
                currentState = GAMEPLAY;
            }

            if (CheckCollisionPointRec(mousePos, mediumButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedDifficulty = MEDIUM;
                currentState = GAMEPLAY;
            }

            if (CheckCollisionPointRec(mousePos, hardButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedDifficulty = HARD;
                currentState = GAMEPLAY;
            }
        }
        else if (currentState == PLAYER_MENU)
        {

            if (IsKeyPressed(KEY_UP))
            {

                selectedOption--;
                if (selectedOption < 0)
                {
                    selectedOption = 1;
                }
            }
            if (IsKeyPressed(KEY_DOWN))
            {
                selectedOption++;
                if (selectedOption > 1)
                {
                    selectedOption = 0;
                }
            }
            if (CheckCollisionPointRec(mousePos, singlePlayer) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectPlayer = SINGLE_PLAYER;
                currentState = DIFFICULTY_MENU;
                resetPlayerMenu();
            }
            if (CheckCollisionPointRec(mousePos, multiPlayer) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectPlayer = TWO_PLAYER;
                currentState = GAMEPLAY;
                resetPlayerMenu();
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                if (selectedOption == 0)
                {
                    selectPlayer = SINGLE_PLAYER;
                    currentState = DIFFICULTY_MENU;
                    resetPlayerMenu();
                }
                else if (selectedOption == 1)
                {
                    selectPlayer = TWO_PLAYER;
                    currentState = GAMEPLAY;
                    resetPlayerMenu();
                }
            }
        }
    }

    void Draw()
    {
        if (currentState == MAIN_MENU)
        {
            DrawText("THE ULTIMATE PONG", 130, 120, 50, WHITE);

            DrawRectangleRec(startButton, DARKBLUE);
            DrawText("START", 350, 268, 25, WHITE);
        }

        else if (currentState == DIFFICULTY_MENU)
        {
            DrawText("SELECT DIFFICULTY", 180, 80, 40, WHITE);
            DrawText("Use Down and Up Keys to Navaigate OR Mouse Click", 150, 140, 20, GOLD);
            DrawRectangleRec(easyButton, LIGHTGRAY);
            DrawRectangleRec(mediumButton, LIGHTGRAY);
            DrawRectangleRec(hardButton, LIGHTGRAY);
            if (selectedOption == 0)
            {
                DrawRectangleLinesEx(easyButton, 8, YELLOW);
                DrawText("Select This Mode If You are new to Gaming", 200, 250, 20, GOLD);
            }
            if (selectedOption == 1)
            {
                DrawRectangleLinesEx(mediumButton, 8, YELLOW);
                DrawText("Select This Mode If You Want A Balanced Gameplay", 150, 350, 20, GOLD);
            }
            if (selectedOption == 2)
            {
                DrawRectangleLinesEx(hardButton, 8, YELLOW);
                DrawText("Select This Mode If You've Got Guts! (AI shows No Mercy)", 110, 450, 20, GOLD);
            }

            DrawText("NOOB", 360, 198, 25, BLACK);

            DrawText("REGULAR", 340, 298, 25, BLACK);
            DrawText("PRO", 360, 398, 25, BLACK);
        }
        if (currentState == PLAYER_MENU)
        {

            DrawText("SELECT YOUR OPONENT!", 240, 50, 30, GOLD);
            DrawRectangleRec(singlePlayer, GRAY);
            DrawRectangleRec(multiPlayer, GRAY);
            DrawText("SINGLE PLAYER", 320, 220, 20, BLACK);
            DrawText("TWO PLAYER", 320, 320, 20, BLACK);
            if (selectedOption == 0)
            {
                DrawRectangleLinesEx(singlePlayer, 8, YELLOW);
            }
            else if (selectedOption == 1)
            {
                DrawRectangleLinesEx(multiPlayer, 8, YELLOW);
            }
        }
        if (currentState == GAMEPLAY)
        {
            DrawText("PRESS R TO RESTART GAME", 250, 80, 20, GOLD);
            DrawText("PRESS D TO SWITCH DIFFICULITY", 240, 110, 20, BLUE);
            DrawText("PRESS P To CHANGE PLAYER MODE",230,550,20,RED);
        }
    }
    void resetPlayerMenu()
    {
        selectedOption = 0;
    }
    Difficulty GetDifficulty()
    {
        return selectedDifficulty;
    }

    bool IsGameStarted()
    {
        return currentState == GAMEPLAY;
    }
    GameState GetState()
    {
        return currentState;
    }
    void getGameState(GameState state)
    {
        currentState = state;
    }
    Player GetPlayerMode()
    {
        return selectPlayer;
    }
    ~GameMenu()
    {
        UnloadMusicStream(menuMusic);
    }
};

class Ball
{
private:
    int ballCentreX;
    int ballCentreY;
    int ballRadius;
    int ballSpeedX;
    int ballSpeedY;
    int playerScore;
    int computerScore;
    Sound ballHit;
    Color ballColor;

public:
    Ball()
    {
        ballCentreX = 400;
        ballCentreY = 300;
        ballRadius = 20;
        ballSpeedX = 5;
        ballSpeedY = 5;
        playerScore = 0;
        computerScore = 0;
        ballColor = WHITE;
        ballHit = LoadSound("Assets/paddle.wav");
    }

    void setBallSpeed(float ballSpeedX, float ballSpeedY)
    {
        this->ballSpeedX = ballSpeedX;
        this->ballSpeedY = ballSpeedY;
    }

    int getPlayerScore()
    {
        return playerScore;
    }
    int getComputerScore()
    {
        return computerScore;
    }
    void moveBall()
    {
        ballCentreX += ballSpeedX;
        ballCentreY += ballSpeedY;
    }
    void resetBall()
    {
        ballCentreX = GetScreenWidth() / 2;
        ballCentreY = GetScreenHeight() / 2;
        ballSpeedX *= -1;
    }
    void checkGameScore()
    {
        if (ballCentreX - ballRadius <= 0)
        {
            computerScore++;
            resetBall();
        }
        if (ballCentreX + ballRadius >= GetScreenWidth())
        {
            playerScore++;
            resetBall();
        }
    }
    void resetScore()
    {
        if (playerScore == 10 or computerScore == 10)
        {
            playerScore = 0;
            computerScore = 0;
        }
    }

    void checkCollision()
    {
        if (ballCentreY + ballRadius >= GetScreenHeight() || ballCentreY - ballRadius <= 0)
        {
            ballSpeedY *= -1;
        }
    }
    void update()
    {
        moveBall();
        checkCollision();
        checkGameScore();
    }
    void drawBall()
    {
        DrawCircle(ballCentreX, ballCentreY, ballRadius, ballColor);
    }
    int getBallCentreX()
    {
        return ballCentreX;
    }
    int getBallCentreY()
    {
        return ballCentreY;
    }
    int getBallSpeedX()
    {
        return ballSpeedX;
    }
    int getBallSpeedY()
    {
        return ballSpeedY;
    }
    int getBallRadius()
    {
        return ballRadius;
    }
    void reverseBallSpeedX()
    {
        ballSpeedX *= -1;
    }
    void increaseBallSpeed()
    {
        if (abs(ballSpeedX) < 10)
        {
            if (ballSpeedX > 0)
            {
                ballSpeedX++;
            }
            else
            {
                ballSpeedX--;
            }
        }

        if (abs(ballSpeedY) < 10)
        {
            if (ballSpeedY > 0)
            {
                ballSpeedY++;
            }
            else
            {
                ballSpeedY--;
            }
        }
    }
    void playBallSound()
    {
        if (getBallCentreY() + getBallRadius() >= GetScreenHeight() ||
            getBallCentreY() - getBallRadius() <= 0)
        {
            playCollisionSound();
        }
    }

    void restartGame()
    {
        playerScore = 0;
        computerScore = 0;

        ballCentreX = GetScreenWidth() / 2;
        ballCentreY = GetScreenHeight() / 2;

        ballSpeedX = 5;
        ballSpeedY = 5;
    }
    void updateMenu()
    {
        moveBall();
        checkCollision();
        if (ballCentreX - ballRadius <= 0)
        {
            resetBall();
        }
        if (ballCentreX + ballRadius >= GetScreenWidth())
        {
            resetBall();
        }
    }
    void playCollisionSound()
    {
        PlaySound(ballHit);
    }
    ~Ball()
    {
        UnloadSound(ballHit);
    }
};
class GameManager
{
private:
    float messageTimer;
    bool showMessage;

    enum Winner
    {
        NONE,
        PLAYER,
        COMPUTER
    };

    Winner winner;

public:
    GameManager()
    {
        messageTimer = 0.0f;
        showMessage = false;
        winner = NONE;
    }

    void checkWinner(int playerScore, int computerScore)
    {

        if (!showMessage)
        {
            if (playerScore >= 10)
            {
                winner = PLAYER;
                showMessage = true;
                messageTimer = 5.0f;
            }
            else if (computerScore >= 10)
            {
                winner = COMPUTER;
                showMessage = true;
                messageTimer = 5.0f;
            }
        }

        if (showMessage)
        {
            messageTimer -= GetFrameTime();

            if (winner == PLAYER)
            {
                DrawText("YOU WON!",
                         GetScreenWidth() / 2 - 120,
                         GetScreenHeight() / 2,
                         50,
                         GOLD);
            }
            else if (winner == COMPUTER)
            {
                DrawText("YOU LOST!",
                         GetScreenWidth() / 2 - 120,
                         GetScreenHeight() / 2,
                         50,
                         RED);
            }
        }
    }

    bool isGameOver()
    {
        return showMessage;
    }

    void reset()
    {
        messageTimer = 0.0f;
        showMessage = false;
        winner = NONE;
    }
};
class Paddle
{
protected:
    int paddleCentreX;
    int paddleCentreY;
    int paddleWidth;
    int paddleHieght;
    int paddleSpeedY;
    int paddleSpeedX;
    Color paddleColor;

public:
    Paddle(int paddleCentreX, int paddleHieght, int paddleWidth, int paddleCentreY)
    {
        this->paddleCentreX = paddleCentreX;
        this->paddleHieght = paddleHieght;
        this->paddleWidth = paddleWidth;
        this->paddleCentreY = paddleCentreY;
        paddleSpeedY = 10;
        paddleSpeedX = 10;
        paddleColor = WHITE;
    }
    virtual void drawPaddle() = 0;
    virtual void movePaddle() = 0;
    virtual void checkCollisionWithPaddle() = 0;
};
class HumanPaddle : public Paddle
{
private:
    Ball *ball;

public:
    HumanPaddle(Ball *b) : Paddle(25, 125, 20, (GetScreenHeight() - 125) / 2)
    {
        ball = b;
    }
    void drawPaddle()
    {
        DrawRectangle(paddleCentreX, paddleCentreY, paddleWidth, paddleHieght, paddleColor);
    }

    void movePaddle()
    {
        if (IsKeyDown(KEY_UP))
        {
            paddleCentreY -= paddleSpeedY;
        }
        if (paddleCentreY <= 0)
        {
            paddleCentreY = 0;
        }
        if (paddleCentreY + paddleHieght > GetScreenHeight())
        {
            paddleCentreY = GetScreenHeight() - paddleHieght;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            paddleCentreY += paddleSpeedY;
        }
    }
    void checkCollisionWithPaddle()
    {
        if (ball->getBallCentreX() - ball->getBallRadius() <= paddleCentreX + paddleWidth &&
            ball->getBallCentreY() >= paddleCentreY &&
            ball->getBallCentreY() <= paddleCentreY + paddleHieght)
        {
            ball->reverseBallSpeedX();
            ball->increaseBallSpeed();
        }
    }
};
class HumanPaddle2 : public Paddle
{
private:
    Ball *ball;

public:
    HumanPaddle2(Ball *b)
        : Paddle(GetScreenWidth() - 40, 125, 20,
                 (GetScreenHeight() - 125) / 2)
    {
        ball = b;
    }

    void drawPaddle()
    {
        DrawRectangle(paddleCentreX, paddleCentreY,
                      paddleWidth, paddleHieght, paddleColor);
    }

    void movePaddle()
    {
        if (IsKeyDown(KEY_W))
        {
            paddleCentreY -= paddleSpeedY;
        }

        if (IsKeyDown(KEY_S))
        {
            paddleCentreY += paddleSpeedY;
        }

        if (paddleCentreY < 0)
        {
            paddleCentreY = 0;
        }

        if (paddleCentreY + paddleHieght > GetScreenHeight())
        {
            paddleCentreY = GetScreenHeight() - paddleHieght;
        }
    }

    void checkCollisionWithPaddle()
    {
        if (ball->getBallSpeedX() > 0 &&
            ball->getBallCentreX() + ball->getBallRadius() >= paddleCentreX &&
            ball->getBallCentreY() >= paddleCentreY &&
            ball->getBallCentreY() <= paddleCentreY + paddleHieght)
        {
            ball->reverseBallSpeedX();
            ball->increaseBallSpeed();
        }
    }
};
class ComputerPaddle : public Paddle
{
private:
    Ball *ball;
    bool isLeftPaddle;

public:
    ComputerPaddle(Ball *b, int xPosition, bool isLeft) : Paddle(xPosition, 125, 20, (GetScreenHeight() - 125) / 2)
    {
        ball = b;
        isLeftPaddle = isLeft;
    }
    void drawPaddle()
    {
        DrawRectangle(paddleCentreX, paddleCentreY, paddleWidth, paddleHieght, paddleColor);
    }
    void movePaddle()
    {
        int paddleMiddle = paddleCentreY + paddleHieght / 2;
        if (ball->getBallCentreY() >= paddleMiddle + 5)
        {
            paddleCentreY += paddleSpeedY;
        }
        else if (ball->getBallCentreY() <= paddleMiddle - 5)
        {
            paddleCentreY -= paddleSpeedY;
        }
        if (paddleCentreY <= 0)
        {
            paddleCentreY = 0;
        }
        if (paddleCentreY + paddleHieght >= GetScreenHeight())
        {
            paddleCentreY = GetScreenHeight() - paddleHieght;
        }
    }
    void checkCollisionWithPaddle()
    {

        if (isLeftPaddle)
        {
            if (ball->getBallSpeedX() < 0 &&
                ball->getBallCentreX() - ball->getBallRadius() <= paddleCentreX + paddleWidth &&
                ball->getBallCentreY() >= paddleCentreY &&
                ball->getBallCentreY() <= paddleCentreY + paddleHieght)
            {
                ball->reverseBallSpeedX();
                ball->increaseBallSpeed();
            }
        }

        else
        {
            if (ball->getBallSpeedX() > 0 &&
                ball->getBallCentreX() + ball->getBallRadius() >= paddleCentreX &&
                ball->getBallCentreY() >= paddleCentreY &&
                ball->getBallCentreY() <= paddleCentreY + paddleHieght)
            {
                ball->reverseBallSpeedX();
                ball->increaseBallSpeed();
            }
        }
    }
    void setAISpeed(int paddleSpeedY)
    {
        this->paddleSpeedY = paddleSpeedY;
    }
    int getAISpeed()
    {
        return paddleSpeedY;
    }
};

int main()
{

    const int screenWidth = 800;
    const int screenHieght = 600;
    InitWindow(screenWidth, screenHieght, "Classic Pong:1980s");
    InitAudioDevice();
    SetTargetFPS(60);
    Ball b1;
    GameManager gameManager;
    HumanPaddle *player;
    player = new HumanPaddle(&b1);
    HumanPaddle2 *player2;
    player2 = new HumanPaddle2(&b1);
    ComputerPaddle *aiLeft;
    aiLeft = new ComputerPaddle(&b1, 25, true);

    ComputerPaddle *aiRight;
    aiRight = new ComputerPaddle(&b1, GetScreenWidth() - 40, false);
    GameMenu menu;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        menu.audioManager();
        menu.Update();
        if (menu.GetDifficulty() == EASY)
        {
            aiRight->setAISpeed(5);
        }
        else if (menu.GetDifficulty() == MEDIUM)
        {
            aiRight->setAISpeed(8);
        }
        else
        {
            aiRight->setAISpeed(9);
        }
        menu.Draw();

        if (menu.GetState() == MAIN_MENU)
        {
            b1.updateMenu();

            aiLeft->movePaddle();
            aiRight->movePaddle();

            aiLeft->drawPaddle();
            aiRight->drawPaddle();

            aiLeft->checkCollisionWithPaddle();
            aiRight->checkCollisionWithPaddle();

            b1.drawBall();

            menu.Draw();
        }

        else if (menu.IsGameStarted())
        {
            if (!gameManager.isGameOver())
            {
                b1.update();
                b1.playBallSound();

                player->movePaddle();

                if (menu.GetPlayerMode() == SINGLE_PLAYER)
                {
                    aiRight->movePaddle();

                    player->checkCollisionWithPaddle();
                    aiRight->checkCollisionWithPaddle();
                }
                else
                {
                    player2->movePaddle();

                    player->checkCollisionWithPaddle();
                    player2->checkCollisionWithPaddle();
                }
            }

            player->drawPaddle();

            if (menu.GetPlayerMode() == SINGLE_PLAYER)
            {
                aiRight->drawPaddle();
            }
            else
            {
                player2->drawPaddle();
            }

            DrawText(TextFormat("%i", b1.getPlayerScore()), 300, 20, 40, GOLD);
            DrawText(TextFormat("%i", b1.getComputerScore()), 500, 20, 40, GOLD);

            gameManager.checkWinner(
                b1.getPlayerScore(),
                b1.getComputerScore());

            b1.drawBall();
        }
        if (menu.GetState() == GAMEPLAY && IsKeyPressed(KEY_R))
        {
            b1.restartGame();
            gameManager.reset();
            menu.resetDifficultyMenu();
            menu.getGameState(MAIN_MENU);
        }
        if (menu.GetState() == GAMEPLAY && IsKeyPressed(KEY_D))
        {
            b1.restartGame();
            gameManager.reset();
            menu.resetPlayerMenu();

            menu.getGameState(DIFFICULTY_MENU);
        }
        if(menu.GetState()==GAMEPLAY && IsKeyPressed(KEY_P))
        {
            b1.restartGame();
            gameManager.reset();
            menu.resetPlayerMenu();
            
            menu.getGameState(PLAYER_MENU);
        }
        EndDrawing();
    }

    CloseAudioDevice();
}
