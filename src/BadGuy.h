/*
 * BadGuy.h
 *
 *  Created on: 12.02.2013
 *      Author: philip
 */

#ifndef BADGUY_H_
#define BADGUY_H_

#include <string>

#include "Entity.h"

using namespace std;

class BadGuy: public Entity {
public:
	BadGuy(string type, int x, int y);
	virtual ~BadGuy();

	void move();
	void logic();

	float getY() const;
};

#endif /* BADGUY_H_ */
