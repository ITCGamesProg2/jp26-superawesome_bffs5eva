#pragma once

class BulletManager
{
public:
	void spawnBullets();			//adds new bullet
	void updateBullets();			//updates all active bullets
	void removeBullet();			//removes a bullet
									
private:
	const static int MAX_BULLETS{ 10 };

	const static int COOLDOWN_LENGTH{ 300 };
	float shootingCooldown{ COOLDOWN_LENGTH };
};