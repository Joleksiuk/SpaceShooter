#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Enemy
{
private:
	
	Sprite sprite;
	
	/*Enemy gamer logic atributes:
	* 	- type:		- type of enemy - the bigger the number the more powerful the enemy is <1, 4>
	*	- points:	- number of points the player gets by killing the enemy
	*	- speed:	- number of pixels enemy moves every frame
	*	- hpMax:	- initial number of hp of the enemy
	*	- hp:		- keeps track of the current hp
	*	- damage	- number of hp the enemy subtracts from player after it hits the bottom of the screen
	*/
	int type;
	int points;
	float speed;
	int hpMax;
	int hp;
	int damage;
	
	void initVariables();
	void initSprite(RenderTarget * target, Texture* texture, float pos_x, float pos_y,float &resolutionModifier);

public:
	//Constructor / Destructor
	Enemy(RenderTarget * target, Texture* texture, float pos_x, float pos_y, float& resolutionModifier);
	virtual ~Enemy();
	
	//Accessors to private atributes
	const int& getPoints()	const;
	const int& getDamage()	const;
	const int& getHp()		const;
	const FloatRect getBounds() const;

	//Game logic
	void changeHp(int change);
	void moveAttackRecoil(const float& recoil);

	//Update / Render
	void update();
	void render(RenderTarget * target);
};

