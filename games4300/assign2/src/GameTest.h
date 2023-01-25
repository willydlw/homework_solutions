#pragma once
#include "Game.h"

class GameTest
{
public:
	GameTest() = default;
	void testLoadBulletConfig(const char* filename, BulletConfig b);
	void testLoadEnemyConfig(const char* filename, EnemyConfig e);
	void testLoadFontConfig(const char* filename, FontConfig f);
	void testLoadPlayerConfig(const char* filename, PlayerConfig p);
	void testLoadWindowConfig(const char* filename, WindowConfig w);
	void testLoadConfig(const char* filename, BulletConfig b, EnemyConfig e,
							FontConfig f, PlayerConfig p, WindowConfig w);

	// filename should be a non-existent configuration file
	void testDefaultConfig(const char* filename);

private:

	bool equalto(WindowConfig a, WindowConfig e);
	bool equalto(FontConfig a, FontConfig e);
	bool equalto(BulletConfig a, BulletConfig e);
	bool equalto(PlayerConfig a, PlayerConfig e);
	bool equalto(EnemyConfig a, EnemyConfig e);
};
