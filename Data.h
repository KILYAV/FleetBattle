#pragma once
#include <memory>
#include <random>
#include <iostream>
#include <windows.h>

namespace domain {
	enum class Size {
		size_10 = 10
	};
	enum class Scale {
		scale_1 = 10,
		scale_2 = 20
	};
	enum class Level {
		level_1 = 1,
		level_2,
		level_3,
		level_4
	};
	enum class Cell {
		sea,
		sky,
		ship
	};
	enum class Diff {
		up = +1,
		down = -1
	};
	class Point {
	private:
		UINT x;
		UINT y;

	public:
		explicit Point(
			UINT x_ = 0,
			UINT y_ = 0
		) :
			x{ x_ },
			y{ y_ }
		{}

		const UINT X() const {
			return x;
		};
		const UINT Y() const {
			return y;
		};
		const Point Up() const {
			return Point{ x - 1, y };
		}
		const Point Down() const {
			return Point{ x + 1, y };
		}
		const Point Left() const {
			return Point{ x, y - 1 };
		}
		const Point Right() const {
			return Point{ x, y + 1 };
		}
	};

	class Data {
	public:
		const HINSTANCE GetHInstance() const { return hInstance; };

		const Size GetSize() const { return size; };
		const Scale GetScale() const { return scale; };
		const Level GetLevel() const { return level; };

		const UINT GetSizeUINT() const {
			return static_cast<UINT>(size);
		}
		const UINT GetScaleUINT() const {
			return static_cast<UINT>(scale);
		}
		const UINT GetLevelUINT() const {
			return static_cast<UINT>(level);
		}
		const UINT RandUINT(UINT max) {
			return std::rand() / (RAND_MAX / max);
		}
	protected:
		Data(const HINSTANCE hInstance_ = NULL) :
			hInstance{ hInstance_ },
			size{ Size::size_10 },
			scale{ Scale::scale_2 },
			level{ Level::level_4 }
		{};
	private:
		HINSTANCE hInstance;

		Size size;
		Scale scale;
		Level level;
	};
}
