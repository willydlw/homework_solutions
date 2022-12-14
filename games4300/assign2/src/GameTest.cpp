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
