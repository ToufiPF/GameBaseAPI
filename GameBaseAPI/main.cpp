#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>

#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "AnimatedSpriteNode.hpp"
#include "Animation.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

namespace ResID {
	enum class Texture {
		CHARACTER, TILESET
	};
	string toString(Texture id) {
		switch (id)
		{
		case ResID::Texture::CHARACTER:
			return "ID::Texture::Character";
		case ResID::Texture::TILESET:
			return "ID::Texture::Tileset";
		default:
			return "ID::Texture::Unknown";
		}
	}

	enum class Font {
		ARIAL, TIMES_NEW_ROMAN
	};
	string toString(Font id) {
		switch (id)
		{
		case ResID::Font::ARIAL:
			return "ID::Font::Arial";
		case ResID::Font::TIMES_NEW_ROMAN:
			return "ID::Font::Times_new_roman";
		default:
			return "ID::Font::Unknown";
		}
	}
};

void testResourceHolder() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "Test ResourceHolder");

	gb::ResourceHolder< sf::Texture, ResID::Texture > textureHolder;

	gb::ResourceHolder< sf::Font, ResID::Font > fontHolder;

	gb::ResourceHolder < sf::SoundBuffer, ResID::Font > soundBuffer;

	sf::Sprite sprite;

	try {
		textureHolder.loadFromFile(ResID::Texture::TILESET, "test.png");
		sprite.setTexture(textureHolder.get(ResID::Texture::TILESET));

		//fontHolder.loadFromFile(ResID::Font::ARIAL, "arial.ttf");

		soundBuffer.loadFromFile(ResID::Font::ARIAL, "test.ogg");
	}
	catch (std::exception const& e) {
		cout << e.what() << endl;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}

void testSceneNodes() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "Test SceneNode");
	sf::Clock clock;

	gb::ResourceHolder< sf::Texture, ResID::Texture > textureHolder;
	Animation tileAnim;
	try {
		textureHolder.loadFromFile(ResID::Texture::TILESET, "test.png");
		tileAnim.setSpriteSheet(&textureHolder.get(ResID::Texture::TILESET));

		tileAnim.addFrame(sf::IntRect(0, 0, 32, 32));
		tileAnim.addFrame(sf::IntRect(32, 0, 32, 32));
		tileAnim.addFrame(sf::IntRect(64, 0, 32, 32));
		tileAnim.addFrame(sf::IntRect(96, 0, 32, 32));
	}
	catch (std::exception const& e) {
		cout << e.what() << endl;
	}

	SceneNode sceneGraph;
	AnimatedSpriteNode::Ptr animNodePtr(new AnimatedSpriteNode(&tileAnim, sf::seconds(0.5f)));
	try {
		sceneGraph.attachChild(std::move(animNodePtr));
	}
	catch (std::exception const& e) {
		cout << e.what() << endl;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		sceneGraph.update(clock.restart());
		window.draw(sceneGraph);
		window.display();
	}
};

int main()
{
	//testResourceHolder();
	testSceneNodes();

	return 0;
}
