#include "GameTest.h"



int main()
{
	/*
	{
		const char* filenameB = "../config/configBullet.txt";	
		GameTest gt;
		gt.testLoadBulletConfig(filenameB);
	}
	
	{
		const char* filename = "../config/configWindow.txt";
		GameTest gt;
		gt.testLoadWindowConfig(filename);
	}
	

	{
		const char* filename = "../config/configFont.txt";
		GameTest gt;
		gt.testLoadFontConfig(filename);
	}
	

	{
		const char* filename = "../config/configPlayer.txt";
		GameTest gt;
		gt.testLoadPlayerConfig(filename);
	}

	{
		const char* filename = "../config/configEnemy.txt";
		GameTest gt;
		gt.testLoadEnemyConfig(filename);
	}
	*/

	{
		const char* filename = "../config/config.txt";
		GameTest gt;
		gt.testLoadConfig(filename);
	}

	return 0;
}