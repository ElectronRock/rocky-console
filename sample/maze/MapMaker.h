#pragma once
#include <vector>;

class MapMaker final {
public:
	enum class EntityType 
	{
		Field,
		Wall,
	};
	using tmap = std::vector<std::vector<EntityType>>;
	MapMaker(const int w, const int h) : width(w), height(h) {}
	tmap Make();
private:
	const int width;
	const int height;
};