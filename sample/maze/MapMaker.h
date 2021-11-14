/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include <vector>

class MapMaker final {
public:
	enum class EntityType 
	{
		Field,
		Wall,
	};

	using TMap = std::vector<std::vector<EntityType>>;

	static TMap Make(unsigned w, unsigned h);
};