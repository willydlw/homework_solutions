#include "GameTest.h"
#include "Game.h"

#include <fstream>
#include <cassert>

void GameTest::testLoadBulletConfig(const char* filename)
{
	Game g;
	
	g.loadConfigFromFile(filename);

	assert(g.m_bulletConfig.SR == 10 &&
		g.m_bulletConfig.CR == 10 &&
		g.m_bulletConfig.S == 20 &&
		g.m_bulletConfig.FR == 255 &&
		g.m_bulletConfig.FG == 255 &&
		g.m_bulletConfig.FB == 255 &&
		g.m_bulletConfig.OR == 255 &&
		g.m_bulletConfig.OG == 255 &&
		g.m_bulletConfig.OB == 255 &&
		g.m_bulletConfig.OT == 2 &&
		g.m_bulletConfig.V == 20 &&
		g.m_bulletConfig.L == 90);

}

void GameTest::testLoadFontConfig(const char* filename)
{
	Game g;
	g.loadConfigFromFile(filename);

	assert(g.m_fontConfig.F == "fonts/tech.ttf" &&
		g.m_fontConfig.S == 24 &&
		g.m_fontConfig.R == 255 &&
		g.m_fontConfig.G == 255 &&
		g.m_fontConfig.B == 255);
}


void GameTest::testLoadPlayerConfig(const char* filename)
{
	Game g;
	g.loadConfigFromFile(filename);

	assert(g.m_playerConfig.SR == 32 &&
		g.m_playerConfig.CR == 32 &&
		g.m_playerConfig.FR == 250 &&
		g.m_playerConfig.FG == 200 &&
		g.m_playerConfig.FB == 150 &&
		g.m_playerConfig.OR == 255 &&
		g.m_playerConfig.OG == 255 &&
		g.m_playerConfig.OB == 255 &&
		g.m_playerConfig.OT == 2 &&
		g.m_playerConfig.S == 4 &&
		g.m_playerConfig.V == 8);
}

void GameTest::testLoadEnemyConfig(const char* filename)
{
	Game g;
	g.loadConfigFromFile(filename);

	assert(g.m_enemyConfig.SR == 32 &&
		g.m_enemyConfig.CR == 32 &&
		g.m_enemyConfig.SMIN == 3 &&
		g.m_enemyConfig.SMAX == 8 &&
		g.m_enemyConfig.OR == 255 &&
		g.m_enemyConfig.OG == 255 &&
		g.m_enemyConfig.OB == 255 &&
		g.m_enemyConfig.OT == 2 &&
		g.m_enemyConfig.VMIN == 3 &&
		g.m_enemyConfig.VMAX == 8 &&
		g.m_enemyConfig.L == 90 &&
		g.m_enemyConfig.SI == 60);
}



void GameTest::testLoadWindowConfig(const char* filename)
{
	Game g;	
	g.loadConfigFromFile(filename);

	assert(g.m_windowConfig.W == 1280 &&
		g.m_windowConfig.H == 720 &&
		g.m_windowConfig.FL == 60 &&
		g.m_windowConfig.FS == 0);
}


void GameTest::testLoadConfig(const char* filename)
{
	Game g;	
	g.loadConfigFromFile(filename);

	assert(g.m_windowConfig.W == 1280 &&
		g.m_windowConfig.H == 720 &&
		g.m_windowConfig.FL == 60 &&
		g.m_windowConfig.FS == 0);

	assert(g.m_fontConfig.F == "fonts/tech.ttf" &&
		g.m_fontConfig.S == 24 &&
		g.m_fontConfig.R == 255 &&
		g.m_fontConfig.G == 255 &&
		g.m_fontConfig.B == 255);

	assert(g.m_bulletConfig.SR == 10 &&
		g.m_bulletConfig.CR == 10 &&
		g.m_bulletConfig.S == 20 &&
		g.m_bulletConfig.FR == 255 &&
		g.m_bulletConfig.FG == 255 &&
		g.m_bulletConfig.FB == 255 &&
		g.m_bulletConfig.OR == 255 &&
		g.m_bulletConfig.OG == 255 &&
		g.m_bulletConfig.OB == 255 &&
		g.m_bulletConfig.OT == 2 &&
		g.m_bulletConfig.V == 20 &&
		g.m_bulletConfig.L == 90);

	assert(g.m_enemyConfig.SR == 32 &&
		g.m_enemyConfig.CR == 32 &&
		g.m_enemyConfig.SMIN == 3 &&
		g.m_enemyConfig.SMAX == 8 &&
		g.m_enemyConfig.OR == 255 &&
		g.m_enemyConfig.OG == 255 &&
		g.m_enemyConfig.OB == 255 &&
		g.m_enemyConfig.OT == 2 &&
		g.m_enemyConfig.VMIN == 3 &&
		g.m_enemyConfig.VMAX == 8 &&
		g.m_enemyConfig.L == 90 &&
		g.m_enemyConfig.SI == 60);

	assert(g.m_playerConfig.SR == 32 &&
		g.m_playerConfig.CR == 32 &&
		g.m_playerConfig.FR == 250 &&
		g.m_playerConfig.FG == 200 &&
		g.m_playerConfig.FB == 150 &&
		g.m_playerConfig.OR == 255 &&
		g.m_playerConfig.OG == 255 &&
		g.m_playerConfig.OB == 255 &&
		g.m_playerConfig.OT == 2 &&
		g.m_playerConfig.S == 4 &&
		g.m_playerConfig.V == 8);

}
