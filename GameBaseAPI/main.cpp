#include <SFML/Graphics.hpp>
#include <iostream>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

#include "ResourceHolder.hpp"

void testResourceHolder();

int main()
{
	testResourceHolder();

	return 0;
}

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
};

void testResourceHolder() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

	ResourceHolder< sf::Texture, ResID::Texture > textureHolder;
	textureHolder.load(ResID::Texture::TILESET, "test.png");

	sf::Sprite sprite(textureHolder.get(ResID::Texture::TILESET));

	try {
		textureHolder.get(ResID::Texture::CHARACTER);
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
