#include <SFML/Graphics.hpp>
#include <cassert>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;
RenderWindow window(VideoMode(450, 750), "Game"); //�e���]�w 

int num = 4, dir = 0; //���פΤ�V 

int score = 0, walknum = 0; //����

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
	walknum = 1;
	if(s[0].x == p.x&&s[0].y == p.y)
	{
		num++; score++;
		s[num-1].x = s[num-2].x;
		s[num-1].y = s[num-2].y;
		p.x = rand()%15;
		p.y = rand()%22+3;
	}
}

void lobby()
{
	bool screen = false;
	Font font; //�r�� 
	font.loadFromFile("font/font.ttf");
	
	Text text; //��r�]�w 
	text.setFont(font);
	text.setCharacterSize(50);
	
	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseMoved) //�P�_�ƹ��y�� 
			{
				if(event.mouseMove.y >= 300&&event.mouseMove.y <= 370&&event.mouseMove.x >= 170&&event.mouseMove.x <= 290){
					if(!screen)screen = true;
				}
				else if(screen)screen = false;
			}
			if(event.type == Event::MouseButtonPressed) //�P�_�ƹ��I�����y�� 
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if(event.mouseButton.y >= 300&&event.mouseButton.y <= 370&&event.mouseButton.x >= 170&&event.mouseButton.x <= 290)
					return;
				}
			}
		}
		window.clear(Color::White);
		if(!screen){
			Texture button;
			button.loadFromFile("image/button.png");
			Sprite bt(button);
			bt.setPosition(162, 300);
			window.draw(bt);
	
			text.setColor(Color::Black);
			text.setPosition(170, 300);
			text.setString("Play!");
			window.draw(text);
		}
		else{
			Texture button;
			button.loadFromFile("image/button2.png");
			Sprite bt(button);
			bt.setPosition(162, 300);
			window.draw(bt);
	
			text.setColor(Color::Red);
			text.setPosition(175, 305);
			text.setString("Play!");
			window.draw(text);
		}
		window.display();
	}
}

void end()
{
	while(window.isOpen()) 
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				window.close();
			}
		}
		
		window.clear(Color::White);
		
		Font font; //�r�� 
		font.loadFromFile("font/font.ttf");
	
		Text text; //��r�]�w 
		text.setFont(font);
		text.setCharacterSize(50);
		text.setColor(Color::Black);
		text.setPosition(80, 350);
		text.setString("Game Over!");
		window.draw(text);
		
		ostringstream showscore;
		showscore.str("");
		showscore << "Your Score : " << score;
		text.setPosition(60, 250);
		text.setColor(Color::Red);
		text.setString(showscore.str());
		window.draw(text);
		window.display();
	}
}

int main()
{
	lobby();
	s[0].y = 3;
	
	p.x = rand()%15; //�Ĥ@�Ӥ����H���ͦ� 
	p.y = rand()%22+3;
	
	for(int i = 1; num >= i; i++) //�N�}�l�ɪ��D�w�q��m 
	{
		s[i].y = s[i-1].y;
	}
	
	Font font; //�r�� 
	font.loadFromFile("font/font.ttf");
	
	Clock clock; //�ɶ�
	clock.restart();
	float timer = 0, delay = 0.5; //����D�����ʳt�� 
	double times = 0; //�����`�ɶ�
	
	Texture player; //�w�q���� 
	player.loadFromFile("image/snake.png"); //����Ϥ�
	Sprite body(player);
	Texture bg;
	bg.loadFromFile("image/background.png");
	Sprite background(bg);
		
	ostringstream totalscore;
	totalscore << "Score: " << score;
	
	ostringstream totaltime;
	totaltime << "Time: " << times << "s";
	
	Text text; //��r�]�w ���� 
	text.setFont(font);
	text.setCharacterSize(30);
	text.setColor(Color::Red);

	while(window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				window.close();
			}
			if(event.type == Event::KeyPressed)
			{
				if(event.key.code == Keyboard::Down){if(dir != 2&&walknum == 1)dir = 0; walknum = 0;}
				else if(event.key.code == Keyboard::Up){if(dir != 0&&walknum == 1)dir = 2; walknum = 0;}
				else if(event.key.code == Keyboard::Right){if(dir != 3&&walknum == 1)dir = 1; walknum = 0;}
				else if(event.key.code == Keyboard::Left){if(dir != 1&&walknum == 1)dir = 3; walknum = 0;}
			}
			if(Keyboard::isKeyPressed(Keyboard::Space)) //���ť���ɥ[�t 
			{
				delay = 0.1;
			}
			else //��}�ɴ�t
			{ 
				delay = 0.4;
			}
		}
		
		if(timer > delay){timer = 0; walk(); times += delay;}
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
		text.setPosition(30, 20);
		window.draw(text);
		
		totaltime.str("");
		totaltime << "Time: " << times << "s";
		text.setString(totaltime.str());
		text.setPosition(280, 20);
		window.draw(text);
		
		body.setPosition(p.x*30, p.y*30);
		window.draw(body);
		window.display();
	}
    return 0;
}
