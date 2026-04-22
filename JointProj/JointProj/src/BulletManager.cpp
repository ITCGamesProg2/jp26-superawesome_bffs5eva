#include "../include/BulletManager.h"

void BulletManager::spawnBullets(sf::Vector2f t_playerPos, float t_playerAngle)
{
	for (int index = 0; index < MAX_BULLETS; index++)
	{
		if (!bullets[index].checkActive())
		{
			bullets[index].init(t_playerPos, t_playerAngle);
		}
	}
}

void BulletManager::updateBullets()
{
	for (int index = 0; index < MAX_BULLETS; index++)
	{
		bullets[index].update();
	}
}

sf::RectangleShape BulletManager::draw(int t_index)
{
	if (bullets[t_index].checkActive())
	{
		return bullets[t_index].getBody();
	}
}
