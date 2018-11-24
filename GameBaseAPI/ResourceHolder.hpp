#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

template <class Resource, class Identifier>
class ResourceHolder
{
public:
	void load(Identifier const& id, const std::string& filename) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

		insertResource(id, std::move(resource));
	};
	template <typename Parameter>
	void load(Identifier const& id, const std::string& filename, const Parameter& secondParam) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename, secondParam))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

		insertResource(id, std::move(resource));
	};

	Resource& get(Identifier const& id) {
		auto found = mResourceMap.find(id);

		if (found == mResourceMap.end())
			throw std::invalid_argument("ResourceHolder::get - " + toString(id) + " not found.");

		return *found->second;
	};
	const Resource&	get(Identifier const& id) const {
		auto found = mResourceMap.find(id);

		if (found == mResourceMap.end())
			throw std::invalid_argument("ResourceHolder::get - " + toString(id) + " not found.");

		return *found->second;
	};

private:
	void insertResource(Identifier const& id, std::unique_ptr<Resource> resource) {
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));

		if (!inserted.second)
			throw std::logic_error("ResourceHolder::insertResource - Could not insert resource.");
	}

private:
	std::map< Identifier, std::unique_ptr<Resource> > mResourceMap;
};
#endif
