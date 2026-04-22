#pragma once
#include "Bullet.h"

class BulletManager
{
public:
	void spawnBullets(sf::Vector2f t_playerPos, float t_playerAngle);			//adds new bullet
	void updateBullets();			//updates all active bullets
	void removeBullet();			//removes a bullet

	sf::RectangleShape draw(int t_index);
									
private:
	const static int MAX_BULLETS{ 10 };
	Bullet bullets[MAX_BULLETS];

	const static int COOLDOWN_LENGTH{ 300 };
	float shootingCooldown{ COOLDOWN_LENGTH };
};