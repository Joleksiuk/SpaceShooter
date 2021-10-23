#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Enemy
{
private:
	
	Sprite sprite;
	
	/*Enemy gamer logic atributes:
	*	- points:			- number of points the player gets by killing the enemy
	*	- speed:			- number of pixels enemy moves every frame
	*	- hpMax:			- initial number of hp of the enemy
	*	- hp:				- keeps track of the current hp
	*	- damage			- number of hp the enemy subtracts from player after it hits the bottom of the screen
	*	- move_pat			- numer of the pattern of movement
	*	- move_prog			- progress of movement in a pattern for knowing where the enemy is and how to proceed
	*	- shoot_cooldown	- cooldown time beetween each shot from given enemy based on type of enemy 
	*/
	int points;
	float speed;
	int hpMax;
	int hp;
	int damage;
	int move_pat;
	int move_prog;
	int shoot_cooldown;

	void initVariables();
	void initSprite(RenderTarget * target, Texture* texture, float pos_x, float pos_y,float &resolutionModifier,int type, int pattern);

public:
	//Constructor / Destructor
	Enemy(RenderTarget * target, Texture* texture, float pos_x, float pos_y, float& resolutionModifier, int type, int pattern);
	virtual ~Enemy();
	
	//Accessors to private atributes
	const int& getPoints()	const;
	const int& getDamage()	const;
	const int& getHp()		const;
	const FloatRect getBounds() const;
	const int& getPattern() const;
	const int& getMovementProgress() const;
	const int& getShootCooldown() const;
	const Vector2f& getPosition() const;

	//Game logic
	void changePosition(int direction, float change);
	void changeMovementProgress(int change);
	void changeHp(int change);
	void changeShootCooldown(int change);
	void moveAttackRecoil(const float& recoil);

	//Update / Render
	void update();
	void render(RenderTarget * target);
};

