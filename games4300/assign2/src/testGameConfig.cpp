#include "GameTest.h"



int main()
{
	/*
	{
		const char* filenameB = "../config/configBullet.txt";	
		GameTest gt;
		BulletConfig b = {10, 10, 255, 155, 75, 50, 90, 150, 2, 10, 90, 20};
		gt.testLoadBulletConfig(filenameB, b);
	}

	
	{
		const char* filename = "../config/configWindow.txt";
		WindowConfig w = { 1280, 720, 60, 0};
		GameTest gt;
		gt.testLoadWindowConfig(filename, w);
		
	}
	
	
	{
		const char* filename = "../config/configFont.txt";
		FontConfig f = { "fonts/tech.ttf", 24, 255, 242, 100};
		GameTest gt;
		gt.testLoadFontConfig(filename, f);
	}
	

	{
		const char* filename = "../config/configPlayer.txt";
		PlayerConfig p = {32, 32, 250, 200, 150, 255, 255, 255, 2, 8, 4};
		GameTest gt;
		gt.testLoadPlayerConfig(filename, p);
	}

	{
		const char* filename = "../config/configEnemy.txt"; 
		EnemyConfig e = {32, 32, 255, 255, 255, 2, 3, 8, 90, 60, 3, 8};
		GameTest gt;
		gt.testLoadEnemyConfig(filename, e);
	}


	{
		const char* filename = "../config/config.txt";

		// Bullet 10 10 20 255 255 255 255 255 255 2 20 90
		BulletConfig b = {10, 10, 255, 255, 255, 255, 255, 255, 2, 20, 90, 20};

		// Enemy 32 32 3 8 255 255 255 2 3 8 90 60
		EnemyConfig e = {32, 32, 255, 255, 255, 2, 3, 8, 90, 60, 3, 8};

		// Font fonts/tech.ttf 24 255 255 255
		FontConfig f = { "fonts/tech.ttf", 24, 255, 255, 255};

		// Player 32 32 4 250 200 150 255 255 255 2 8
		PlayerConfig p = {32, 32, 250, 200, 150, 255, 255, 255, 2, 8, 4};

		// Window 1280 720 60 0
		WindowConfig w = { 1280, 720, 60, 0};

		GameTest gt;
		gt.testLoadConfig(filename, b, e, f, p, w);
	}
	
*/
	{
		const char* filename = "../config/bogus.txt";
		GameTest gt;
		gt.testDefaultConfig(filename);
	}

	return 0;
}