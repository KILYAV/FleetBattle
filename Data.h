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
		ship,
		blast,
		missle
	};
	enum Direct {
		up,
		down,
		left,
		right
	};

	static UINT GetRandUINT(const UINT max) {
		if (max)
			return std::rand() / (RAND_MAX / max);
		else
			return 0;
	}
	static UINT GetRandBool() {
		return GetRandUINT(2);
	}

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

		bool IsNan() const;
		bool IsNan(const UINT max) const;

		bool IsNotNan() const;
		bool IsNotNan(const UINT max) const;

		Point& North();
		Point& South();
		Point& West();
		Point& East();

		Point North() const;
		Point South() const;
		Point West() const;
		Point East() const;
	};

	class Data {
	public:
		HINSTANCE GetHInstance() const;

		Size GetSize() const;
		Scale GetScale() const;
		Level GetLevel() const;

		UINT GetMaxUINT() const;
		UINT GetSizeUINT() const;
		UINT GetScaleUINT() const;
		UINT GetLevelUINT() const;
	protected:
		explicit Data(const HINSTANCE hInstance_ = NULL);
	private:
		HINSTANCE hInstance;

		Size size;
		Scale scale;
		Level level;
	};
}
