#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
	Sprite bulletSprite;
	Vector2f direction;

	/*Game logic atributes
	*	- movementSpeed		- number of frames the bullet moves every frame
	*	- recoil			- number of frames the target that was hit by bullet moves in the opposite direction
	*	- isFriendly		- bool deciding if bullet is from player or not
	*/
	float movementSpeed;
	float recoil;
	bool isFriendly;

public:
	
	/*Constructor arguments:
		- texture		: texture of the bullet, 
		- pos_x			: x coordinate of the spawn <window 0>
		- pos_y			: y coordinate of the spawn <random between window width>
		- dir_x			: x direction of the movement - <-1, 0, 1>
		- dir_x			: y direction of the movement - <-1, 0, 1>
		- movementSpeed : number of pixels, the bullet moves every frame <N>	
	*/
	Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, bool isFriendly);
	virtual ~Bullet();

	//Accessors of private atributes
	const FloatRect getBounds() const;
	const float getRecoil()const;
	const bool getIsFriendly()const;

	//Update / Render
	void update();
	void render(RenderTarget* target);
};

