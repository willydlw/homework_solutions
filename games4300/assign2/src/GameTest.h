#pragma once
class GameTest
{
public:
	GameTest() = default;
	void testLoadBulletConfig(const char* filename);
	void testLoadEnemyConfig(const char* filename);
	void testLoadFontConfig(const char* filename);
	void testLoadPlayerConfig(const char* filename);
	void testLoadWindowConfig(const char* filename);

	void testLoadConfig(const char* filename);
};
