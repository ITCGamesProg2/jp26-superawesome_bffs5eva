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

sf::Vector2f BulletManager::getPos(int t_index) const
{
	return bullets[t_index].getPosition();
}

bool BulletManager::isActive(int t_index) const
{
	return bullets[t_index].checkActive();
}
