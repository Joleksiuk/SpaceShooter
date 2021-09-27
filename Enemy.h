#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Enemy
{
private:
	
	Sprite sprite;
	CircleShape shape;
	
	unsigned pointCount;
	int type;
	float speed;
	int hpMax;
	int damage;
	int points;
	int hp;

	void initShape();
	void initVariables();
	void initSprite(RenderTarget * target, Texture* texture, float pos_x, float pos_y);

public:
	Enemy(RenderTarget * target, Texture* texture, float pos_x, float pos_y);
	virtual ~Enemy();
	

	const int& getPoints()	const;
	const int& getDamage()	const;
	const int& getHp()		const;

	void changeHp(int change);
	void moveAttackRecoil(const float& recoil);

	const FloatRect getBounds() const;
	void update();
	void render(RenderTarget * target);
};

