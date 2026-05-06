#include <iostream>
#include <raylib.h>
using namespace std;

int screenWidth=800;
int screenHieght=600;
class paddle;	
class ball
{
	private:
		int ballCenterX;
		int ballCenterY;
		int ballRadius;
		int ballSpeedX;
		int ballSpeedY;
		Color ballColor;
		public:
			ball(int x,int y,int r,int ballSpeedX,int ballSpeedY,Color color)
			{
				ballCenterX=x;
				ballCenterY=y;
				ballRadius=r;
				ballColor=color;
				this->ballSpeedX=ballSpeedX;
				this->ballSpeedY=ballSpeedY;
			}
			void drawBall()
			{
			DrawCircle(ballCenterX,ballCenterY,ballRadius,WHITE);	
			}
			void updateBallpos()
			{
				ballCenterX=ballCenterX+ballSpeedX;
				ballCenterY=ballCenterY+ballSpeedY;
				
				if(ballCenterX+ballRadius>=screenWidth or ballCenterX-ballRadius<=0)
				{
					ballSpeedX*=-1;
				}
				if(ballCenterY+ballRadius>=screenHieght or ballCenterY-ballRadius<=0)
				{
					ballSpeedY*=-1;
				}
				
			}
			friend void checkCollision(ball &b,paddle &p);
};

class paddle
{
	private:
		int paddleX;
		int paddleY;
		int paddleHieght;
		int paddleWidth;
		int paddleSpeedY;
		Color paddleColor;
		
		public:
			paddle(int px,int py,int paddleHieght,int paddleWidth,Color color)
			{
				paddleX=px;
				paddleY=py;
				this->paddleHieght=paddleHieght;
				this->paddleWidth=paddleWidth;
				paddleColor=color;
				
			}
			
			void drawPaddle()
			{
				DrawRectangle(paddleX,paddleY,paddleWidth,paddleHieght,WHITE);
			}
			void movePaddle()
			{
				paddleSpeedY=5;
				if(IsKeyDown(KEY_UP))
				{	
				paddleY-=paddleSpeedY;
						
				}
				 if(IsKeyDown(KEY_DOWN))
				{
												
		          paddleY+=paddleSpeedY;
				  							
				}
				else{
					paddleSpeedY=0;
				}
				
			}
			void stopPaddle()
			{
				if(paddleY<=0)
				{
					paddleY=0;
				}
				if(paddleY>=screenHieght-paddleHieght)
				{
					paddleY=screenHieght-paddleHieght;
				}
				
			}
friend void checkCollision(ball &b , paddle &p);			
};

int hits=0;
void checkCollision(ball &b ,paddle &p)
{
	 
	if((b.ballCenterX)-(b.ballRadius)<=p.paddleX+p.paddleWidth && b.ballCenterY>=p.paddleY && b.ballCenterY<p.paddleY+p.paddleHieght)
	{
		b.ballSpeedX*=-1;
		hits++;
	}
	
}

int main()
{
SetTargetFPS(60); 
ball b1(400,300,30,5,5,WHITE);


paddle p1(30, (screenHieght - 125)/2, 125, 25, WHITE); 
paddle p2(screenWidth - 30 - 25, (screenHieght - 125) / 2, 125, 25,WHITE);


	InitWindow(screenWidth,screenHieght,"My first Game");
	
	
	while(!WindowShouldClose())
	{			
		BeginDrawing();
		ClearBackground(BLACK);
		b1.drawBall();
		b1.updateBallpos();
		checkCollision(b1, p1);
		p1.drawPaddle();
		p1.movePaddle();
		p1.stopPaddle();
		p2.drawPaddle();
		DrawText(("Hits: " + std::to_string(hits)).c_str() , 20 , 20,20 , WHITE);
		EndDrawing();
	}
	CloseWindow();
}
