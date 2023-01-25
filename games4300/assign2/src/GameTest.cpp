#include "GameTest.h"
#include "Game.h"

#include <fstream>
#include <cassert>

void GameTest::testLoadBulletConfig(const char* filename, BulletConfig b)
{
	Game g;
	g.loadConfigFromFile(filename);
	assert(bool(equalto(g.m_bulletConfig, b)) == true);
}

void GameTest::testLoadFontConfig(const char* filename, FontConfig f)
{
	Game g;
	g.loadConfigFromFile(filename);
	assert(bool(equalto(g.m_fontConfig, f)) == true);
}

void GameTest::testLoadPlayerConfig(const char* filename, PlayerConfig p)
{
	Game g;
	g.loadConfigFromFile(filename);
	assert(bool(equalto(g.m_playerConfig, p)) == true);
}

void GameTest::testLoadEnemyConfig(const char* filename, EnemyConfig e)
{
	Game g;
	g.loadConfigFromFile(filename);

	assert(bool(equalto(g.m_enemyConfig, e)) == true);
}

void GameTest::testLoadWindowConfig(const char* filename, WindowConfig w)
{
	Game g;	
	g.loadConfigFromFile(filename);
	assert(bool(equalto(g.m_windowConfig, w)) == true);
}

void GameTest::testLoadConfig(const char* filename, BulletConfig b, EnemyConfig e,
							FontConfig f, PlayerConfig p, WindowConfig w)
{
	Game g;	
	g.loadConfigFromFile(filename);

	assert(bool(equalto(g.m_bulletConfig, b)) == true);
	assert(bool(equalto(g.m_enemyConfig, e)) == true);
	assert(bool(equalto(g.m_fontConfig, f)) == true);
	assert(bool(equalto(g.m_playerConfig, p)) == true);
	assert(bool(equalto(g.m_windowConfig, w)) == true);
}

bool GameTest::equalto (WindowConfig a, WindowConfig e)
{
	return a.W == e.W &&
		a.H ==  e.H &&
		a.FL == e.FL &&
		a.FS == e.FS;
}

bool GameTest::equalto(FontConfig a, FontConfig e)
{
	return a.F == e.F &&
		a.S == e.S &&
		a.R == e.R &&
		a.G == e.G &&
		a.B == e.B;
}

bool GameTest::equalto(BulletConfig a, BulletConfig e)
{
	assert( a.SR == e.SR);
	assert(a.CR == e.CR);
	assert(a.S == e.S);
	assert(a.FR == e.FR);
	assert(a.FG == e.FG);
	assert(a.FB == e.FB);
	assert(a.OR == e.OR);
	assert(a.OG == e.OG);
	assert(a.OB == e.OB);
	assert(a.OT == e.OT);
	assert(a.V == e.V);
	assert(a.L == e.L);

	return a.SR == e.SR &&
		a.CR == e.CR &&
		a.S == e.S &&
		a.FR == e.FR &&
		a.FG == e.FG &&
		a.FB == e.FB &&
		a.OR == e.OR &&
		a.OG == e.OG &&
		a.OB == e.OB &&
		a.OT == e.OT &&
		a.V == e.V &&
		a.L == e.L;

}


bool GameTest::equalto(PlayerConfig a, PlayerConfig e)
{
	assert(a.CR == e.CR);
	assert(a.SR == e.SR);
	assert(a.FR == e.FR);
	assert(a.FG == e.FG);
	assert(a.FB == e.FB);
	assert(a.OR == e.OR);
	assert(a.OG == e.OG);
	assert(a.OB == e.OB);
	assert(a.OT == e.OT);
	assert(a.S == e.S);
	assert(a.V == e.V);

	return
		a.SR == e.SR &&
		a.CR == e.CR &&
		a.FR == e.FR &&
		a.FG == e.FG &&
		a.FB == e.FB &&
		a.OR == e.OR &&
		a.OG == e.OG &&
		a.OB == e.OB &&
		a.OT == e.OT &&
		a.S == e.S &&
		a.V == e.V;

}

bool GameTest::equalto(EnemyConfig a, EnemyConfig e)
{
	assert(a.CR == e.CR);
	assert(a.SR == e.SR);
	
	assert(a.OR == e.OR);
	assert(a.OG == e.OG);
	assert(a.OB == e.OB);
	assert(a.OT == e.OT);
	assert(a.SMIN == e.SMIN);
	assert(a.SMAX == e.SMAX);
	assert(a.VMIN == e.VMIN);
	assert(a.VMAX == e.VMAX);
	assert(a.L == e.L);
	assert(a.SI == e.SI);

	return a.SR == e.SR &&
		a.CR == e.CR &&
		a.SMIN == e.SMIN &&
		a.SMAX == e.SMAX &&
		a.OR == e.OR &&
		a.OG == e.OG &&
		a.OB == e.OB &&
		a.OT == e.OT &&
		a.VMIN == e.VMIN &&
		a.VMAX == e.VMAX &&
		a.L == e.L &&
		a.SI == e.SI;

}

void GameTest::testDefaultConfig(const char* filename)
{
	WindowConfig w = Game::WINDOW_CONFIG_DEFAULT;
	FontConfig f = Game::FONT_CONFIG_DEFAULT;
	BulletConfig b = Game::BULLET_CONFIG_DEFAULT;
	EnemyConfig e = Game::ENEMY_CONFIG_DEFAULT;	
	PlayerConfig p = Game::PLAYER_CONFIG_DEFAULT;

	Game g;	
	g.loadConfigFromFile(filename);

	assert(bool(equalto(g.m_windowConfig, w)) == true);
	assert(bool(equalto(g.m_fontConfig, f)) == true);
	assert(bool(equalto(g.m_bulletConfig, b)) == true);
	assert(bool(equalto(g.m_playerConfig, p)) == true);
	assert(bool(equalto(g.m_enemyConfig, e)) == true);
	
}
