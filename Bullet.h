#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
	Sprite shape;
	Vector2f direction;

	float movementSpeed;
	float recoil;

public:
	Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessor
	const FloatRect getBounds() const;
	const float getRecoil()const;

	void update();
	void render(RenderTarget* target);
};

