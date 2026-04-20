#include "../include/BulletManager.h"

void BulletManager::spawnBullets()
{
	for (int index = 0; index < MAX_BULLETS; index++)
	{
		if (!bullets[index].checkActive())
		{
			bullets[index].init();
		}
	}
}
