#include <SFML/Graphics.hpp>
#include <cassert>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(450, 750), "Game"); //畫面設定 

int num = 4, dir = 0; //長度及方向 

int score = 0; //分數

struct snake{
	int x, y;
}s[500];

struct point{
	int x, y;
}p;

void walk()
{
	for(int i = num-1; i > 0; i--)
	{
		s[i].x = s[i-1].x;
		s[i].y = s[i-1].y;
	}
	switch(dir){
		case 0:
			s[0].y += 1;
			break; 
		case 1:
			s[0].x += 1;
			break;
		case 2:
			s[0].y -= 1;
			break;
		case 3:
			s[0].x -= 1;
			break;
	}
	
	if(s[0].x == p.x&&s[0].y == p.y)
	{
		num++; score++;
		s[num-1].x = s[num-2].x;
		s[num-1].y = s[num-2].y;
		p.x = rand()%15;
		p.y = rand()%22+3;
	}
}

void end()
{
	Font font; //字體 
	font.loadFromFile("font/font.ttf");
	
	Text text; //文字設定 
	text.setFont(font);
	text.setCharacterSize(50);
	text.setString("Game Over!");
	
	window.clear(Color::White);
	window.draw(text);
	window.display();
	
	window.close();
}

int main()
{
	s[0].y = 3;
	
	p.x = rand()%15; //第一個分數隨機生成 
	p.y = rand()%22+3;
	
	for(int i = 1; num >= i; i++) //將開始時的蛇定義位置 
	{
		s[i].y = s[i-1].y;
	}
	
	Font font; //字體 
	font.loadFromFile("font/font.ttf");
	
	Clock clock; //時間
	clock.restart();
	float timer = 0, delay = 0.2;
	
	Texture player; //定義物件 
	player.loadFromFile("image/snake.png"); //物件圖片
	Sprite body(player);
	Texture bg;
	bg.loadFromFile("image/background.png");
	Sprite background(bg);
		
	ostringstream totalscore;
	totalscore << "Score: " << score;
	
	Text text; //文字設定 
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(20, 20);
	text.setColor(Color::Red);

	while(window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		
		Event e;
		while(window.pollEvent(e))
		{
			if(e.type == Event::Closed)
			{
				window.close();
			}
			
			if(e.type == Event::KeyPressed)
			{
				if(e.key.code == Keyboard::Down){if(dir != 2)dir = 0;}
				else if(e.key.code == Keyboard::Up){if(dir != 0)dir = 2;}
				else if(e.key.code == Keyboard::Right){if(dir != 3)dir = 1;}
				else if(e.key.code == Keyboard::Left){if(dir != 1)dir = 3;}
			}
		}
		
		if(timer > delay){timer = 0; walk();}
		if(s[0].y == 25){end(); break;}
		else if(s[0].y == 2){end(); break;}
		else if(s[0].x == -1){end(); break;}
		else if(s[0].x == 15){end(); break;}
		else if(num >= 5){
			for(int i = 1; num >= i; i++)
			{
				if(s[0].x == s[i].x&&s[0].y == s[i].y){
					end();
				}
			}
		}
		
		window.clear(Color::White);
		
		for(int i = 0; 15 > i; i++)
		{
			for(int j = 3; 25 > j; j++)
			{
				background.setPosition(i*30, j*30);
				window.draw(background);
			}
		}
		
		for(int i = 0; num > i; i++)
		{
			body.setPosition(s[i].x*30, s[i].y*30);
			window.draw(body);
		}
		
		totalscore.str("");
		totalscore << "Score: " << score;
		text.setString(totalscore.str());
		window.draw(text);
		body.setPosition(p.x*30, p.y*30);
		window.draw(body);
		window.display();
	}
    return 0;
}
