#include <iostream>
#include <raylib.h>
using namespace std;

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

int getBallCentreY()
{
    return ballCentreY;
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
        paddleSpeedY=5;
        paddleSpeedX=10;
        paddleColor=WHITE;
    }
    virtual void drawPaddle()=0;
    virtual void movePaddle()=0;

};
class HumanPaddle:public Paddle
{
    public:
    HumanPaddle():Paddle(25,125,20,(GetScreenHeight()-125)/2)
    {
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
};
class ComputerPaddle:public Paddle
{
    private:
    Ball *ball;
    public:
    ComputerPaddle(Ball *b):Paddle(GetScreenWidth()-40,125,20,(GetScreenHeight()-125)/2)
    {
        ball=b;
    }
    void drawPaddle()
    {
        DrawRectangle(paddleCentreX,paddleCentreY,paddleWidth,paddleHieght,paddleColor);
    }
    void movePaddle()
    {
       int paddleMiddle=paddleCentreY+paddleHieght/2;
       if(ball->getBallCentreY() >= paddleMiddle)
       {
        paddleCentreY+=paddleSpeedY;
       } 
       else if(ball->getBallCentreY() <= paddleMiddle)
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
        
    };



int main () {

 
const int screenWidth = 800;
const int screenHieght = 600;
    InitWindow(screenWidth, screenHieght, "Classic Pong:1980s");
    SetTargetFPS(60);
Ball b1;
Paddle *p1;
p1=new HumanPaddle();
Paddle *p2;
p2=new ComputerPaddle(&b1);

    while (WindowShouldClose() == false){
    
        
        BeginDrawing();
        ClearBackground(BLACK);
        b1.update();
        b1.drawBall();
        DrawText(TextFormat("%i",b1.getPlayerScore()),300,20,40,GOLD);
        DrawText(TextFormat("%i",b1.getComputerScore()),500,20,40,GOLD);
        b1.playerWin();
        b1.computerWin();
        b1.resetScore();
        p1->drawPaddle();
        p1->movePaddle();
        p2->drawPaddle();
        p2->movePaddle();        
        EndDrawing();
    }

    CloseWindow();
}
