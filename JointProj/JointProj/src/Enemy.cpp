#include "../include/Enemy.h"

SpeedStratergy Enemy::m_speedStrategy;
CrawlerStrategy Enemy::m_crawlerStrategy;
BalancedStrategy Enemy::m_balancedStrategy;

Enemy::Enemy()
{
	m_isActive = false;
	m_strategy = &m_balancedStrategy;

	if (!m_texture.loadFromFile("Resources\\ASSETS\\IMAGES\\enemy_spritesheet.png"))
	{
		std::cout << "problem loading enemy texture" << std::endl;
	}
	
	m_sprite.setTexture(m_texture,true);
	m_sprite.setTextureRect(sf::IntRect({ 0,0 }, { 48, 48 }));
	m_sprite.setOrigin({ 24.0f, 24.0f });

	// ---------------- FSM SETUP ----------------//
	m_currentState = EnemyStates::IDLE;
	m_previousState = EnemyStates::IDLE;

	//defining valid transitions for each state
	static int idleNext[] = { RUN, ATTACK, DIE };
	static int runNext[] = { IDLE, ATTACK, DIE };
	static int attackNext[] = { IDLE, RUN, DIE };
	static int dieNext[] = { IDLE }; //DIE state needs a possible transition or it has error

	//configure state behaviours - name, entry, update, exit, allowed transitions
	m_stateConfigs[IDLE] = { "Idle", Idle_Entry, Idle_Update, Idle_Exit, idleNext, 3 };
	m_stateConfigs[RUN] = { "Run", Run_Entry, Run_Update, Run_Exit, runNext, 3 };
	m_stateConfigs[ATTACK] = { "Attack", Attack_Entry, Attack_Update, Attack_Exit, attackNext, 2 };
	m_stateConfigs[DIE] = { "Die", Die_Entry, Die_Update, Die_Exit, dieNext, 0 };
}

void Enemy::init(const Level& t_level, sf::Vector2f t_pos)
{
	m_isActive = true;
	m_position = t_pos;
	m_velocity = { 0.0f, 0.0f };

	m_currentState = EnemyStates::IDLE;
	m_previousState = EnemyStates::IDLE;

	m_level = &t_level;
	m_levelWidth = m_level->getWidth();

	int rnadNum = rand() % 3;

	if (rnadNum == 0) setStrategy(&m_speedStrategy);
	if (rnadNum == 1) setStrategy(&m_crawlerStrategy);
	if (rnadNum == 2) setStrategy(&m_balancedStrategy);
}

void Enemy::setStrategy(EnemyStrategy* strategy)
{
	m_strategy = strategy;
}

bool Enemy::canEnterState(EnemyStates t_newState)
{
	StateConfig& config = m_stateConfigs[m_currentState];

	for (int i = 0; i < config.nextStatesCount; i++) //loop through allowed next states
	{
		if (config.nextStates[i] == t_newState) return true;
	}

	return false;
}

void Enemy::changeState(float t_dt, EnemyStates t_newState) //handle switching states
{
	if (!canEnterState(t_newState)) return;

	StateConfig& current = m_stateConfigs[m_currentState];
	StateConfig& next = m_stateConfigs[t_newState];

	if (current.Exit) current.Exit(this, t_dt);

	m_previousState = m_currentState;
	m_currentState = t_newState;
	m_stateTimer = 0.0f;

	if (next.Entry) next.Entry(this, t_dt);
}

void Enemy::updateState(float t_dt) //runs current states update function
{
	StateConfig& current = m_stateConfigs[m_currentState];
	if (current.Update) current.Update(this, t_dt);
}

//class functions
void Enemy::update(float t_dt, bool t_sameCell, std::vector<int> t_path)
{
	if (!t_path.empty() && (m_path.size() < 2 || m_path.back() != t_path.back())) //update path only if changed
	{
		m_path = t_path;
	}

	m_inSameCell = t_sameCell;

	updateAnimation(t_dt); //update animation frame
	updateState(t_dt); //update FSM
}

void Enemy::addObserver(Observer* t_observer)
{
	m_observers.push_back(t_observer);
}

void Enemy::notifyDamage()
{
	for (auto observer : m_observers)
	{
		observer->onNotify(EventType::DAMAGE_PLAYER, m_strategy->getDamage());
	}
}

void Enemy::railMoveTowards()
{
	if (m_path.size() < 2) return;

	int nextCell = m_path[1];

	int row = nextCell / m_levelWidth;
	int col = nextCell % m_levelWidth;

	m_targetPos = { (float)col + 0.5f, (float)row + 0.5f }; //convert tile position to world position
	m_direction = m_targetPos - m_position;

	float length = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);

	if (length < 0.1f)
	{
		m_position = m_targetPos;
		m_path.erase(m_path.begin());

		return;
	}

	if (length > 0.0f) //normalize direction
	{
		m_direction /= length;
	}

	m_velocity = m_direction * m_strategy->getSpeed();
	m_position += m_velocity;
}

void Enemy::setAnimation(int row, int frameCount, float frameTime)
{
	m_animRow = row;
	m_frameCount = frameCount;
	m_frameTime = frameTime;

	m_currentFrame = 0;
	m_animTimer = 0.0f;
}

void Enemy::updateAnimation(float dt)
{
	m_animTimer += (dt / 1000);

	if (m_animTimer >= m_frameTime)
	{
		m_animTimer = 0.0f;
		m_previousFrame = m_currentFrame;
		m_currentFrame++;

		//special case: death locks at end
		if (m_currentState == DIE)
		{
			if (m_currentFrame >= m_frameCount)
			{
				m_currentFrame = m_frameCount - 1;
				m_isActive = false; //DIE ends enemy life
			}
		}
		else
		{
			if (m_currentFrame >= m_frameCount) m_currentFrame = 0;
		}
	}

	//apply to sprite
	m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, m_animRow * m_frameHeight }, { m_frameWidth, m_frameHeight }));
}

void Enemy::die()
{
	m_isActive = false;
}

sf::Vector2f Enemy::getPosition() const
{
	return m_position;
}

sf::Sprite Enemy::getSprite() const
{
	return m_sprite;
}

//update FSM
//IDLE
void Enemy::Idle_Entry(Enemy* t_enemy, float t_dt)
{
	t_enemy->m_velocity = { 0,0 };
	t_enemy->setAnimation(0, 1, 0.2f); //row 0, 1 frame
}

void Enemy::Idle_Update(Enemy* t_enemy, float t_dt)
{
	t_enemy->m_stateTimer += t_dt;

	if (!t_enemy->m_path.empty()) //start moving if path becomes available
	{
		t_enemy->changeState(t_dt, RUN);

		return;
	}

	if (t_enemy->m_inSameCell) //attack if player is in same tile
	{
		t_enemy->changeState(t_dt, ATTACK);

		return;
	}
}

void Enemy::Idle_Exit(Enemy* t_enemy, float t_dt) 
{
}

//RUN
void Enemy::Run_Entry(Enemy* t_enemy, float t_dt) 
{
	t_enemy->setAnimation(1, 4, 0.1); //row 1, 4 frames
}

void Enemy::Run_Update(Enemy* t_enemy, float t_dt)
{
	t_enemy->railMoveTowards();

	if (t_enemy->m_inSameCell) //attack if player is in same tile
	{
		t_enemy->changeState(t_dt, ATTACK);

		return;
	}

	if (t_enemy->m_path.empty()) //idle if loose path
	{
		t_enemy->changeState(t_dt, IDLE);

		return;
	}
}

void Enemy::Run_Exit(Enemy* t_enemy, float t_dt) 
{
}

//ATTACK
void Enemy::Attack_Entry(Enemy* t_enemy, float t_dt) 
{
	t_enemy->m_velocity = { 0,0 };
	t_enemy->setAnimation(2, 3, 0.12f); //row 2, 3 frames
	t_enemy->m_hasDealtDamage = false;
}

void Enemy::Attack_Update(Enemy* t_enemy, float t_dt)
{
	if (!t_enemy->m_inSameCell) //return to chasing if player leaves tile
	{
		t_enemy->changeState(t_dt, RUN);

		return;
	}

	if (t_enemy->m_currentFrame == 2 && !t_enemy->m_hasDealtDamage)
	{
		t_enemy->notifyDamage();

		t_enemy->m_hasDealtDamage = true;

		t_enemy->changeState(t_dt, IDLE);

		return;
	}
}

void Enemy::Attack_Exit(Enemy* t_enemy, float t_dt) 
{
}

//DIE
void Enemy::Die_Entry(Enemy* t_enemy, float t_dt)
{
	t_enemy->m_isActive = false;
	t_enemy->setAnimation(3, 5, 0.15f); //row 3, 5 frames
}

void Enemy::Die_Update(Enemy* t_enemy , float t_dt) 
{
	if (100 == 200)//placeholder (no transitions allowed)
	{
		t_enemy->changeState(t_dt, IDLE);

		return;
	}
}

void Enemy::Die_Exit(Enemy* t_enemy, float t_dt) 
{
}