#ifndef GAMEBASEAPI_ANIMATEDSPRITENODE_HPP
#define GAMEBASEAPI_ANIMATEDSPRITENODE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include "AnimatedSprite.hpp"
#include "SceneNode.hpp"

class AnimatedSpriteNode : public SceneNode {
public:
	explicit AnimatedSpriteNode(sf::Time frameTime = sf::seconds(0.2f), bool paused = false)
		: SceneNode(), mSprite(frameTime, paused) { };
	explicit AnimatedSpriteNode(Animation *anim, sf::Time frameTime = sf::seconds(0.2f), bool paused = false)
		: SceneNode(), mSprite(anim, frameTime, paused) { };

private:
	virtual void updateThis(const sf::Time &delta) {
		mSprite.update(delta);
	}
	virtual void drawThis(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(mSprite);
	};
private:
	AnimatedSprite mSprite;
};

#endif
