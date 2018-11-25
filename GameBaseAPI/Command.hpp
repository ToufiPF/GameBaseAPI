#ifndef GAMEBASEAPI_COMMAND_HPP
#define GAMEBASEAPI_COMMAND_HPP

#include <SFML/System/Time.hpp>

#include <functional>

class SceneNode;

struct Command {
	std::function< void(SceneNode&, sf::Time) > action;
	unsigned int category = 0;
};

#endif
