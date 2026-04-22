#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"

enum EnemyStates {IDLE, RUN, ATTACK, DIE, STATE_COUNT};

class Enemy;

typedef void (*StateFunc)(Enemy*, float);


struct StateConfig
{
	const char* name;

	StateFunc Entry;				//called when entering state
	StateFunc Update;				//called every frame in state
	StateFunc Exit;					//called when leaving state

	int* nextStates;				//allowed transitions
	int nextStatesCount;
};

class Enemy
{
public:
	Enemy();
	void init(const Level& t_level, sf::Vector2f t_pos);					//called to spawns enenmy

	void update(float t_dt, bool t_sameCell, std::vector<int> t_path);		//updates the enemy

	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
									
private:
	// ---------------- FSM ----------------//
	bool canEnterState(EnemyStates t_newState);
	void changeState(float dt, EnemyStates newState);
	void updateState(float dt);

	EnemyStates m_currentState;
	EnemyStates m_previousState;
	StateConfig m_stateConfigs[STATE_COUNT];

	float m_stateTimer{ 0.0f };

	//state functions
	static void Idle_Entry(Enemy*, float);
	static void Idle_Update(Enemy*, float);
	static void Idle_Exit(Enemy*, float);

	static void Run_Entry(Enemy*, float);
	static void Run_Update(Enemy*, float);
	static void Run_Exit(Enemy*, float);

	static void Attack_Entry(Enemy*, float);
	static void Attack_Update(Enemy*, float);
	static void Attack_Exit(Enemy*, float);

	static void Die_Entry(Enemy*, float);
	static void Die_Update(Enemy*, float);
	static void Die_Exit(Enemy*, float);

	// ---------------- FUNCTIONDS ----------------//
	void railMoveTowards();													//moves towards player position
	void die();																//despawns/dissactivates enemy

	// ---------------- VARIABLES ----------------//
	const Level* m_level{ nullptr };
	int m_levelWidth;

	bool m_inSameCell{ false };
	std::vector<int> m_path;
	sf::Vector2f m_targetPos;
	sf::Vector2f m_direction;

	sf::Vector2f m_position{ 0.0f, 0.0f };
	sf::Vector2f m_velocity;
	const static int m_MAX_SPEED{ 50 };

	const static int m_damadgeAmount{ 10 };

	sf::Texture m_texture;
	sf::Sprite m_sprite{ m_texture };

	bool m_isActive;

	// ---------------- ANIMANTION ----------------//
	void setAnimation(int row, int frameCount, float frameTime);
	void updateAnimation(float dt);

	int m_animRow{ 0 };
	int m_frameCount{ 1 };
	int m_currentFrame{ 0 };

	float m_animTimer{ 0.0f };
	float m_frameTime{ 0.12f };

	const int m_frameWidth{ 48 };
	const int m_frameHeight{ 48 };
};