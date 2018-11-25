#ifndef GAMEBASEAPI_SPRITENODE_HPP
#define GAMEBASEAPI_SPRITENODE_HPP

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "SceneNode.hpp"

class SpriteNode : public SceneNode {
public:
	explicit SpriteNode(const sf::Texture& texture)
		: SceneNode(), mSprite(texture) { };
	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
		: SceneNode(), mSprite(texture, textureRect) { };

private:
	virtual void drawThis(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(mSprite, states);
	};

private:
	sf::Sprite mSprite;
};

#endif
