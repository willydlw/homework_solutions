#include "GameTest.h"


int main()
{
	{
		const char* filename = "../config/configBullet.txt";
		GameTest gt;
		gt.testLoadBulletConfig(filename);
	}

	return 0;
}