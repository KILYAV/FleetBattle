#pragma once
#include <windows.h>

namespace domain {
	//using UINT = unsigned;

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
	enum class Color {
		Blace = 0x000000,
		Red = 0x0000FF,
		Blue = 0xFF0000,
		White = 0xFFFFFF
	};
	enum class Diff {
		up = +1,
		down = -1
	};
	struct Point {
		UINT x;
		UINT y;

		explicit Point(UINT x_, UINT y_) :
			x{ x_ },
			y{ y_ }
		{}
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
