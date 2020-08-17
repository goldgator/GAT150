#pragma once
#include <functional>
#include <map>

namespace nc {
	template<typename TBase, typename TKey>

	class Factory {
	public:
		using function_t = std::function<>;
	public:
		TBase* Create(TKey key);
		void Register(TKey key, function_t function)
	protected:
		std::map<TKey, function_t> m_registry;
	};

	template<typename TBase, typename TKey>
	inline TBase* Factory<TBase, TKey>::Create(TKey key) {
		TBase* object{ nullptr };

		auto iter = m_registry.find(key);
		if (iter != m_registry.end()) {
			object = iter->second();
		}

		return object;
	}

	template<typename TBase, typename TKey>
	inline void Factory<TBase, TKey>::Register(TKey key, function_t function) {
		m_registry[key] = function;
	}
	
}