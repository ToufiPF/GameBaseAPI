#ifndef GAMEBASEAPI_ANIMATEDSPRITE_HPP
#define GAMEBASEAPI_ANIMATEDSPRITE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Animation.hpp"

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
public:
	explicit AnimatedSprite(sf::Time frameTime = sf::seconds(0.2f), bool paused = false)
		: AnimatedSprite(nullptr, frameTime, paused) {
	};
	explicit AnimatedSprite(Animation* animation, sf::Time frameTime = sf::seconds(0.2f), bool paused = false)
		: sf::Drawable(), sf::Transformable(), mAnimation(animation), mFrameTime(frameTime), mVertices(sf::PrimitiveType::Quads, 4) {
		if (mAnimation != nullptr)
			mSpriteSheet = mAnimation->getSpriteSheet();
		else
			mSpriteSheet = nullptr;

		mActualFrame = 0;
		mIsPaused = paused;
	};

	void play() { mIsPaused = false; };
	void play(Animation* anim) {
		if (mAnimation != anim)
			setAnimation(anim);
		play();
	};
	void pause() { mIsPaused = true; };
	void stop() {
		mIsPaused = true;
		setFrame(0, true);
	};
	bool isPaused() { return mIsPaused; }

	void setAnimation(Animation* anim) {
		mAnimation = anim;

		if (mAnimation != nullptr)
			mSpriteSheet = mAnimation->getSpriteSheet();
		else
			mSpriteSheet = nullptr;

		setFrame(0, true);
	};

	void setFrame(size_t frame, bool resetTime = false) {
		if (mAnimation == nullptr)
			return;

		// On essaye de recuperer le rectangle de la frame
		sf::IntRect rect;
		try {
			rect = mAnimation->getFrame(frame);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return;
		}

		// Coordonnees relatives a this (sf::Transformable)
		mVertices[0].position = sf::Vector2f(0.f, 0.f);
		mVertices[1].position = sf::Vector2f((float)rect.width, 0.f);
		mVertices[2].position = sf::Vector2f((float)rect.width, (float)rect.height);
		mVertices[3].position = sf::Vector2f(0.f, (float)rect.height);

		// Coordonnes de la frame dans la sprite sheet
		mVertices[0].texCoords = sf::Vector2f((float)rect.left, (float)rect.top);
		mVertices[1].texCoords = sf::Vector2f((float)(rect.left + rect.width), (float)rect.top);
		mVertices[2].texCoords = sf::Vector2f((float)(rect.left + rect.width), (float)(rect.top + rect.height));
		mVertices[3].texCoords = sf::Vector2f((float)rect.left, (float)(rect.top + rect.height));

		if (resetTime)
			mCurrentTime = sf::Time::Zero;
	};

	void setFrameTime(sf::Time frameTime) { mFrameTime = frameTime; };

	void update(sf::Time delta) {
		if (mAnimation == nullptr || mIsPaused)
			return;
		mCurrentTime += delta;
		if (mCurrentTime >= mFrameTime) {
			mCurrentTime %= mFrameTime;

			if (mActualFrame + 1 < mAnimation->getFrameCount())
				++mActualFrame;
			else
				mActualFrame = 0;

			setFrame(mActualFrame);
		}
	};

	sf::FloatRect getLocalBounds() const {
		if (mAnimation == nullptr)
			return sf::FloatRect();

		sf::IntRect rect = mAnimation->getFrame(mActualFrame);
		return sf::FloatRect(0.f, 0.f, (float)rect.width, (float)rect.height);
	};
	sf::FloatRect getGlobalBounds() const {
		return getTransform().transformRect(getLocalBounds());
	};

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (mAnimation == nullptr || mSpriteSheet == nullptr) {
			std::cerr << "pas de texture !" << std::endl;
			return;
		}

		states.transform *= getTransform();
		states.texture = mSpriteSheet;
		target.draw(mVertices, states);
	};

private:
	Animation* mAnimation;
	sf::VertexArray mVertices;
	sf::Texture* mSpriteSheet;

	sf::Time mFrameTime;
	sf::Time mCurrentTime;
	size_t mActualFrame;

	bool mIsPaused;
};

#endif
