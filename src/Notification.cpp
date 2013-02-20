/*
 * Notification.cpp
 *
 *  Created on: 19.02.2013
 *      Author: philip
 */

#include "Notification.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "define.h"
#include "Game.h"

using namespace std;

vector<Notification*> Notification::notificationList;

Notification::Notification(string message, int displaySecs, int type, string iconName) {
	SDL_Surface *temp;
	if ((temp = IMG_Load(IMG"notification.png")) == NULL) {
		//TODO Throw exception
		std::cout << "unable to load notification.png" << std::endl;
	}
	notificationSurface = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);

	counter = displaySecs * FPS;

	SDL_Color color;
	if (type == NOTIFICATION_INFO) {
		color.r = 255;
		color.g = 255;
		color.b = 255;
	} else if (type == NOTIFICATION_WARNING) {
		color.r = 255;
		color.g = 0;
		color.b = 0;
	}
	if (iconName == "") {
		if (type == NOTIFICATION_INFO) {
			iconName = IMG"info.bmp";
		} else if (type == NOTIFICATION_WARNING) {
			iconName = IMG"warning.bmp";
		}
	}
	SDL_Surface *icon;

	if ((temp = SDL_LoadBMP(iconName.c_str())) == NULL) {
		//TODO Throw exception
		std::cout << "unable to load :" << iconName << std::endl;
	} else {
		icon = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		if (temp != 0) {
			SDL_SetColorKey(icon, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(icon->format, 255, 0, 255));

		}
	}

	SDL_Rect dRect;
	dRect.x = 10;
	dRect.y = 6;
	dRect.w = icon->w;
	dRect.h = icon->h;

	SDL_BlitSurface(icon, NULL, notificationSurface, &dRect);

	SDL_Surface *text = TTF_RenderUTF8_Solid(Game::curGame->getFont(FONT_NOTIFICATION), message.c_str(), color);

	dRect.x = 60;
	dRect.y = 6;
	dRect.w = text->w;
	dRect.h = text->h;
	SDL_BlitSurface(text, NULL, notificationSurface, &dRect);

	notificationList.push_back(this);

}

Notification::~Notification() {
	SDL_FreeSurface(notificationSurface);
	std::vector<Notification*>::iterator pos;
	if ((pos = std::find(notificationList.begin(), notificationList.end(), this)) != notificationList.end()) {
		notificationList.erase(pos);
	}
}

void Notification::timeout() {
	if (--counter <= 0) {
		delete this;
	}
}

SDL_Surface* Notification::getNotificationSurface() {
	return notificationSurface;
}
