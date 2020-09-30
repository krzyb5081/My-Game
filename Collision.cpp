#include "Collision.h"


bool Collision::checkPlayerCollision(Player player, Obiekt obiekt) {
	sf::FloatRect playerRect = player.sprite->getGlobalBounds();
	sf::FloatRect obiektRect = obiekt.sprite->getGlobalBounds();

	if (playerRect.intersects(obiektRect)) {
		return true;
	}
	else {
		return false;
	}
}