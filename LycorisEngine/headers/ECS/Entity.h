#pragma once

#include <vector>
#include <memory>
#include <typeinfo>
#include <functional>
#include <array>
#include <concepts>

#include "Component.h"

class Entity
{
public:
	Entity(std::function<void(Entity*)> needUpdateCallback);
	Entity(Entity& other) = delete;
	Entity(Entity&& other);
	~Entity();

private:
	std::vector<Component*> _components;

	std::function<void(Entity*)> _needUpdateCallback; // Call the callback to notify the scene this entity has changed (new component for exemple)

public:
	bool _needUpdate;

public:

	template<typename T> bool TryFind(T*& out) {
		for (Component* comp : _components) {
			if (auto* result = (T*)(comp)) {
				out = result;
				return true;
			}
		}
		return false;
	};

	template<typename T> bool Contains() {
		for (Component* comp : _components) {
			if (auto* result = (T*)(comp)) {
				return true;
			}
		}
		return false;
	};

	template<typename TDescriptor> bool AddComponent(const TDescriptor desc) {
		using TComponent = typename TDescriptor::ComponentType;
		if (Contains<TComponent>())
			return false;

		//auto uPtr = std::make_unique<TComponent>(desc);
		_components.push_back((Component*)(new TComponent(desc)));

		if (false == _needUpdate) {
			_needUpdate = true;
			_needUpdateCallback(this);
		}
		return true;
	}
};

