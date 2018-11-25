#ifndef GAMEBASEAPI_RESOURCEHOLDER_HPP
#define GAMEBASEAPI_RESOURCEHOLDER_HPP

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace gb {
	template <class Resource, typename Identifier>
	class ResourceHolder
	{
	public:
		typedef typename std::unique_ptr<Resource> Ptr;
	public:
		void loadFromFile(const Identifier& id, const std::string& filepath) {
			std::unique_ptr<Resource> resource(new Resource());
			if (!resource->loadFromFile(filepath))
				throw std::runtime_error("ResourceHolder::loadFromFile - Failed to load " + filepath);

			insertResource(id, std::move(resource));
		};
		template <typename Parameter>
		void loadFromFile(Identifier const& id, const std::string& filepath, const Parameter& secondParam) {
			std::unique_ptr<Resource> resource(new Resource());
			if (!resource->loadFromFile(filepath, secondParam))
				throw std::runtime_error("ResourceHolder::loadFromFile - Failed to load " + filepath);

			insertResource(id, std::move(resource));
		};

		void loadFromStream(Identifier const& id, sf::InputStream &stream) {
			std::unique_ptr<Resource> resource(new Resource());
			if (!resource->loadFromStream(stream))
				throw std::runtime_error("ResourceHolder::loadFromStream - Failed to load, pos = " + stream.tell());

			insertResource(id, std::move(resource));
		};
		template <typename Parameter>
		void loadFromStream(Identifier const& id, sf::InputStream &stream, const Parameter& secondParam) {
			std::unique_ptr<Resource> resource(new Resource());
			if (!resource->loadFromStream(stream, secondParam))
				throw std::runtime_error("ResourceHolder::loadFromStream - Failed to load, pos = " + stream.tell());

			insertResource(id, std::move(resource));
		};

		Resource& get(Identifier const& id) {
			auto found = mResourceMap.find(id);

			if (found == mResourceMap.end())
				throw std::invalid_argument("ResourceHolder::get - " + toString(id) + " not found.");

			return *(found->second);
		};
		const Resource&	get(Identifier const& id) const {
			auto found = mResourceMap.find(id);

			if (found == mResourceMap.end())
				throw std::invalid_argument("ResourceHolder::get - " + toString(id) + " not found.");

			return *(found->second);
		};

	private:
		void insertResource(Identifier const& id, Ptr resource) {
			auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));

			if (!inserted.second)
				throw std::logic_error("ResourceHolder::insertResource - Could not insert resource " + toString(id));
		}

	private:
		std::map< Identifier, Ptr > mResourceMap;
	};
};
#endif
