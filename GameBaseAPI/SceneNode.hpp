#ifndef GAMEBASEAPI_SCENENODE_HPP
#define GAMEBASEAPI_SCENENODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
	typedef typename std::unique_ptr<SceneNode> Ptr;
public:
	SceneNode() : sf::Drawable(), sf::Transformable(), sf::NonCopyable(), mChildrenList(), mParent(nullptr) { };

	void attachChild(Ptr child) {
		child->mParent = this;
		mChildrenList.push_back(std::move(child));
	};
	Ptr detachChild(const SceneNode& child) {
		auto found = std::find_if(mChildrenList.begin(), mChildrenList.end(), [&](Ptr const& p) -> bool { return p.get() == &child; });

		if (found == mChildrenList.end())
			throw std::invalid_argument("SceneNode::detachChild - Child not found");

		Ptr result = std::move(*found);
		result->mParent = nullptr;
		mChildrenList.erase(found);
		return result;
	};

	void update(const sf::Time &delta) {
		updateThis(delta);
		updateChildren(delta);
	};

private:
	virtual void updateThis(const sf::Time &delta) {
	};
	void updateChildren(const sf::Time & delta) {
		for (const Ptr& child : mChildrenList)
			child->update(delta);
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();

		drawThis(target, states);
		drawChildren(target, states);
	};
	virtual void drawThis(sf::RenderTarget& target, sf::RenderStates states) const {
	};
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
		for (const Ptr& child : mChildrenList)
			child->draw(target, states);
	};

private:
	std::vector<Ptr> mChildrenList;
	SceneNode* mParent;
};

#endif
