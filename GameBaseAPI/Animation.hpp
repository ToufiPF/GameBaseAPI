#ifndef GAMEBASEAPI_ANIMATION_HPP
#define GAMEBASEAPI_ANIMATION_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <stdexcept>
#include <string>
#include <vector>

class Animation {
public:
	explicit Animation() : mSpriteSheet(nullptr) { };
	explicit Animation(sf::Texture *spriteSheet) : mSpriteSheet(spriteSheet) { };

	sf::Texture* getSpriteSheet() const { return mSpriteSheet; };
	void setSpriteSheet(sf::Texture* sheet) { mSpriteSheet = sheet; };

	void addFrame(const sf::IntRect &frame) {
		mFrames.push_back(frame);
	};
	size_t getFrameCount() const { return mFrames.size(); };
	sf::IntRect getFrame(size_t id) {
		if (id >= getFrameCount())
			throw std::out_of_range("Animation::getFrame - Frame id : " + std::to_string(id) + " is not repertoried.");
		return mFrames.at(id);
	};
	sf::IntRect deleteFrame(size_t id) {
		if (id >= getFrameCount())
			throw std::out_of_range("Animation::deleteFrame - Frame id : " + std::to_string(id) + " is not repertoried.");
		return *mFrames.erase(mFrames.begin() + id);
	};

private:
	sf::Texture *mSpriteSheet;
	std::vector< sf::IntRect > mFrames;
};

#endif
