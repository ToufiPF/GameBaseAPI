#ifndef GAMEBASEAPI_ENTITY_HPP
#define GAMEBASEAPI_ENTITY_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "SceneNode.hpp"

class Entity : public SceneNode {
public:
	explicit Entity() : SceneNode() { };

	void setVelocity(sf::Vector2f velocity) { setVelocity(velocity.x, velocity.y); };
	void setVelocity(float vx, float vy) { mVelocity.x = vx; mVelocity.y = vy; };
	sf::Vector2f getVelocity() const { return mVelocity; };

private:
	virtual void updateThis(const sf::Time& delta) {
		move(delta.asSeconds() * mVelocity);
	};
private:
	sf::Vector2f mVelocity;
};

#endif
