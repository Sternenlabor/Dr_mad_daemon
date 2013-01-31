/*
 * Entity.h
 *
 *  Created on: 27.09.2012
 *      Author: medi
 */
#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <Box2D/Box2D.h>

#include "define.h"
//TODO REMOVE!!!!!!!!!
#include "Tools.h"
#include "Game.h"

#define UP 0x01
#define RIGHT 0x02
#define DOWN 0x04
#define LEFT 0x08

#define ACTION_STAY 0
#define ACTION_WALK_LEFT 1
#define ACTION_WALK_RIGHT 2
#define ACTION_JUMP_LEFT  3
#define ACTION_JUMP_RIGHT 4
#define ACTION_DUCK_LEFT 5
#define ACTION_DUCK_RIGHT 6


using namespace std;

/**
 * Entity Class all things you can interact with.
 */
class Entity {
private:
	SDL_Surface * image; /**< Image of the entity with all animationframes */
	bool alive; /**< contain true if the entity is still alive and false if not */
	int currentframe; /**< Current Frame number this is used to calculate the correct part of the image */
	int action; /**< the action e.g. move left, move right, jump, needed for rendering  */
	//TODO: actionframes get from File ?!?


	int flags;
	float width;
	float height;

	bool ground; //TODO test only

	b2Body *body;
	b2FixtureDef *fixtureDef;

	Uint8 direction;

	void nextframe();



public:
	static vector<Entity*> entityList;

	Entity();
	Entity(string imagename,float w, float h,int x, int y);
	virtual ~Entity();

	void move();



	//----------------------------------- Getter and Setter ------------------------------

	SDL_Rect getCurFrameRect();

	bool isAlive() const;

	void setAlive(bool alive);

	Uint8 getDirection() const;

	void setDirection(Uint8 direction);

	void  delDirection(Uint8 direction);

	int getFlags() const;

	void setFlags(int flags);

	float getX() const;

	float getY() const;

	SDL_Surface* getImage();

	int getCurrentframe() const;

	void setCurrentframe(int currentframe);

	float getHeight() const;

	void setHeight(float height);

	float getWidth() const;

	void setWidth(float width);

	b2Body* getBody();
};

#endif /* ENTITY_H_ */