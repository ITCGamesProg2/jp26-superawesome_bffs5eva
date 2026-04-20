#pragma once

class BulletManager
{
public:
	void spawnBullets();			//adds new bullet
	void updateBullets();			//updates all active bullets
	void removeBullet();			//removes a bullet
									
private:
	const static int m_MAX_BULLETS{ 10 };

	const static int m_COOLDOWN_LENGTH{ 300 };
	float m_shootingCooldown{ m_COOLDOWN_LENGTH };
};