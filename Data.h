#pragma once
#include <memory>
#include <random>
#include <iostream>
#include <time.h>
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

	UINT GetRandUINT(const UINT max);

	class Point {
	private:
		UINT x;
		UINT y;

	public:
		explicit Point(
			UINT new_x = -1,
			UINT new_y = -1
		) :
			x{ new_x },
			y{ new_y }
		{}

		UINT X() const;
		UINT Y() const;

		bool IsNan(const UINT max = -1) const;

		Point Up() const;
		Point Down() const;
		Point Left() const;
		Point Right() const;

		enum class Direct {
			up,
			down,
			left,
			right,
			center
		};
		static Direct RotateDirect(const Direct direct);
		static Direct GetRandDirect();
		Point MoveDirect(const Direct direct) const;

		bool operator== (const Point point) const {
			if (this->IsNan() || point.IsNan())
				return false;
			return x == point.x && y == point.y;
		}
	};

	class Data {
	public:
		const HINSTANCE GetHInstance() const { return hInstance; };

		Size GetSize() const { return size; };
		Scale GetScale() const { return scale; };
		Level GetLevel() const { return level; };

		UINT GetSizeUINT() const {
			return static_cast<UINT>(size);
		}
		UINT GetScaleUINT() const {
			return static_cast<UINT>(scale);
		}
		UINT GetLevelUINT() const {
			return static_cast<UINT>(level);
		}
	protected:
		Data(const HINSTANCE hInstance_ = NULL) :
			hInstance{ hInstance_ },
			size{ Size::size_10 },
			scale{ Scale::scale_2 },
			level{ Level::level_4 }
		{
			std::srand(std::time(NULL));
		};
	private:
		HINSTANCE hInstance;

		Size size;
		Scale scale;
		Level level;
	};
}
