#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
	Sprite bulletSprite;
	Vector2f direction;

	float movementSpeed;
	float recoil;

public:
	
	/*Constructor arguments:
		- texture		: texture of the bullet, 
		- pos_x			: x coordinate of the spawn <window 0>
		- pos_y			: y coordinate of the spawn <random between window width>
		- dir_x			: x direction of the movement - <-1, 0, 1>
		- dir_x			: y direction of the movement - <-1, 0, 1>
		- movementSpeed : number of pixels, the bullet moves every frame <N>	
	*/
	Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessors of private atributes
	const FloatRect getBounds() const;
	const float getRecoil()const;

	void update();
	void render(RenderTarget* target);
};

