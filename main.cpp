#include <raylib.h>
#include <iostream>
using namespace std;

enum GameState
{
    MAIN_MENU,
    DIFFICULTY_MENU,
    GAMEPLAY
};

enum Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

class GameMenu
{
private:
    GameState currentState;
    Difficulty selectedDifficulty;

    Rectangle startButton;

    Rectangle easyButton;
    Rectangle mediumButton;
    Rectangle hardButton;

public:
    GameMenu()
    {
        currentState = MAIN_MENU;
        selectedDifficulty = EASY;

        startButton = {300, 250, 200, 60};

        easyButton = {300, 180, 200, 60};
        mediumButton = {300, 280, 200, 60};
        hardButton = {300, 380, 200, 60};
    }

    void Update()
    {
        Vector2 mousePos = GetMousePosition();

        
        if (currentState == MAIN_MENU)
        {
            if (CheckCollisionPointRec(mousePos, startButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentState = DIFFICULTY_MENU;
            }
        }

        
        else if (currentState == DIFFICULTY_MENU)
        {
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
    }

    void Draw()
{
    if (currentState == MAIN_MENU)
    {
        DrawText("PONG GAME", 250, 120, 50, WHITE);

        DrawRectangleRec(startButton, DARKBLUE);
        DrawText("START", 350, 268, 25, WHITE);
    }

    else if (currentState == DIFFICULTY_MENU)
    {
        DrawText("SELECT DIFFICULTY", 180, 80, 40, WHITE);

        DrawRectangleRec(easyButton, GREEN);
        DrawText("EASY", 360, 198, 25, BLACK);

        DrawRectangleRec(mediumButton, ORANGE);
        DrawText("MEDIUM", 340, 298, 25, BLACK);

        DrawRectangleRec(hardButton, RED);
        DrawText("HARD", 360, 398, 25, BLACK);
    }
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

};

class Ball{
private:
int ballCentreX;
int ballCentreY;
int ballRadius;
int ballSpeedX;
int ballSpeedY;
int playerScore;
int computerScore;
Color ballColor;
public:
Ball()
{
    ballCentreX=400;
    ballCentreY=300;
    ballRadius=20;
    ballSpeedX=5;
    ballSpeedY=5;
    playerScore=0;
    computerScore=0;    
    ballColor=WHITE;
}
    void setBallSpeed(float ballSpeedX,float ballSpeedY)
    {
        this->ballSpeedX=ballSpeedX;
        this->ballSpeedY=ballSpeedY;
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
        ballCentreX+=ballSpeedX;
        ballCentreY+=ballSpeedY;
        
    }
    void resetBall()
    {
        ballCentreX=GetScreenWidth() /2;
        ballCentreY=GetScreenHeight() /2;
        ballSpeedX*=-1;
    }
    void checkGameScore()
    {
        if(ballCentreX-ballRadius <=0)
        {
            computerScore++;
            resetBall();

        }
        if(ballCentreX + ballRadius >=GetScreenWidth())
        {
            playerScore++;
            resetBall();
        }
    }
    void resetScore()
    {
        if(playerScore==10 or computerScore==10)
        {
            playerScore=0;
            computerScore=0;
        }
    }
    void playerWin()
    {
        if(playerScore==10)
        {
            DrawText("You Won",GetScreenWidth()/2 ,GetScreenHeight()/2,50,GOLD);
            
        }
    }
    void computerWin()
    {
        if(computerScore==10)
        {
            DrawText("You Lost",GetScreenWidth()/2,GetScreenHeight()/2,50,GOLD);
            
        }
    }
    void checkCollision()
    {
        if(ballCentreY+ballRadius>=GetScreenHeight() || ballCentreY-ballRadius<=0)
        {
            ballSpeedY*=-1;
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
        DrawCircle(ballCentreX,ballCentreY,ballRadius,ballColor);
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
    ballSpeedX*=-1;
    
}
void increaseBallSpeed()
{
    if(abs(ballSpeedX) < 10)
    {
        if(ballSpeedX > 0)
        {
            ballSpeedX++;
        }
        else
        {
            ballSpeedX--;
        }
    }

    if(abs(ballSpeedY) < 10)
    {
        if(ballSpeedY > 0)
        {
            ballSpeedY++;
        }
        else
        {
            ballSpeedY--;
        }
    }
}
};
class Paddle{
    protected:
    int paddleCentreX;
    int paddleCentreY;
    int paddleWidth;
    int paddleHieght;
    int paddleSpeedY;
    int paddleSpeedX;
    Color paddleColor;
    public:
    Paddle(int paddleCentreX,int paddleHieght,int paddleWidth,int paddleCentreY)
    {
        this->paddleCentreX=paddleCentreX;
        this->paddleHieght=paddleHieght;
        this->paddleWidth=paddleWidth;
        this->paddleCentreY=paddleCentreY;
        paddleSpeedY=10;
        paddleSpeedX=10;
        paddleColor=WHITE;
    }
    virtual void drawPaddle()=0;
    virtual void movePaddle()=0;
    virtual void checkCollisionWithPaddle()=0;
    
};
class HumanPaddle:public Paddle
{
    private:
    Ball *ball;
    public:
    HumanPaddle(Ball *b):Paddle(25,125,20,(GetScreenHeight()-125)/2)
    {
        ball=b;
    }
    void drawPaddle()
    {
        DrawRectangle(paddleCentreX,paddleCentreY,paddleWidth,paddleHieght,paddleColor);
    }
    
    void movePaddle()
    {
        if(IsKeyDown(KEY_UP))
        {
            paddleCentreY-=paddleSpeedY;
            
        }
        if(paddleCentreY<=0 )
        {
            paddleCentreY=0;
        }
        if(paddleCentreY+paddleHieght>GetScreenHeight())
        {
            paddleCentreY=GetScreenHeight()-paddleHieght;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            paddleCentreY+=paddleSpeedY;
        }
        
    }
    void checkCollisionWithPaddle()
    {
        if(ball->getBallCentreX() - ball->getBallRadius() <= paddleCentreX+paddleWidth
        &&
    ball->getBallCentreY() >= paddleCentreY
   &&
   ball->getBallCentreY() <= paddleCentreY + paddleHieght)
        {
            ball->reverseBallSpeedX();
            ball->increaseBallSpeed();
        }
    }
};

class ComputerPaddle:public Paddle
{
    private:
    Ball *ball;
    bool isLeftPaddle;
    public:
 ComputerPaddle(Ball *b,int xPosition,bool isLeft) :Paddle(xPosition,125,20,(GetScreenHeight()-125)/2)
{
    ball=b;
    isLeftPaddle=isLeft;
}
    void drawPaddle()
    {
        DrawRectangle(paddleCentreX,paddleCentreY,paddleWidth,paddleHieght,paddleColor);
    }
    void movePaddle()
    {
       int paddleMiddle=paddleCentreY+paddleHieght/2;
       if(ball->getBallCentreY() >= paddleMiddle+5)
       {
        paddleCentreY+=paddleSpeedY;
       } 
       else if(ball->getBallCentreY() <= paddleMiddle-5)
       {
        paddleCentreY-=paddleSpeedY;
       }
       if(paddleCentreY<=0)
       {
        paddleCentreY=0;
       }
       if(paddleCentreY+paddleHieght >=GetScreenHeight())
       {
        paddleCentreY=GetScreenHeight()-paddleHieght;
       }
    }
   void checkCollisionWithPaddle()
{
    
    if(isLeftPaddle)
    {
        if(ball->getBallSpeedX() < 0 &&
           ball->getBallCentreX() - ball->getBallRadius() <= paddleCentreX + paddleWidth
           &&
           ball->getBallCentreY() >= paddleCentreY
           &&
           ball->getBallCentreY() <= paddleCentreY + paddleHieght)
        {
            ball->reverseBallSpeedX();
            ball->increaseBallSpeed();
        }
    }

    else
    {
        if(ball->getBallSpeedX() > 0 &&
           ball->getBallCentreX() + ball->getBallRadius() >= paddleCentreX
           &&
           ball->getBallCentreY() >= paddleCentreY
           &&
           ball->getBallCentreY() <= paddleCentreY + paddleHieght)
        {
            ball->reverseBallSpeedX();
            ball->increaseBallSpeed();
        }
    }
}
    void setAISpeed(int paddleSpeedY)
    {
        this->paddleSpeedY=paddleSpeedY;
    }
   int getAISpeed()
   {
        return paddleSpeedY;    
   } 
};
   
        
    



int main () {

 
const int screenWidth = 800;
const int screenHieght = 600;
    InitWindow(screenWidth, screenHieght, "Classic Pong:1980s");
    SetTargetFPS(60);
Ball b1;
HumanPaddle *player;
player = new HumanPaddle(&b1);

ComputerPaddle *aiLeft;
aiLeft = new ComputerPaddle(&b1,25,true);

ComputerPaddle *aiRight;
aiRight = new ComputerPaddle(&b1,GetScreenWidth()-40,false);
GameMenu menu;

    while (WindowShouldClose() == false)
{
    BeginDrawing();
    ClearBackground(BLACK);

    
    menu.Update();
    if(menu.GetDifficulty()==EASY)
    {
        aiRight->setAISpeed(5);
    }
    else if(menu.GetDifficulty()==MEDIUM)
    {
        aiRight->setAISpeed(7);
    }
    else
    {
        aiRight->setAISpeed(9);
    }
    menu.Draw();

    if(menu.GetState() == MAIN_MENU)
{
    b1.update();

    aiLeft->movePaddle();
    aiRight->movePaddle();

    aiLeft->drawPaddle();
    aiRight->drawPaddle();

    aiLeft->checkCollisionWithPaddle();
    aiRight->checkCollisionWithPaddle();

    b1.drawBall();

    menu.Draw();
}

    else if(menu.IsGameStarted())
{
    
    b1.update();
    player->movePaddle();
    aiRight->movePaddle();

    player->drawPaddle();
    aiRight->drawPaddle();
DrawText(TextFormat("%i", b1.getPlayerScore()), 300, 20, 40, GOLD);
DrawText(TextFormat("%i", b1.getComputerScore()), 500, 20, 40, GOLD);
   
player->checkCollisionWithPaddle();
aiRight->checkCollisionWithPaddle();


    
    b1.playerWin();
    b1.computerWin();
    b1.resetScore();
    b1.drawBall();
}

    EndDrawing();
}    
}
