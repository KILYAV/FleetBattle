#pragma once
#include "Random.h"

#include <string>
#include <optional>

namespace fleet {
	using namespace domain;

	class Fleet :
		virtual Data,
		protected random::Random
	{
	protected:
		Fleet();

		std::optional<std::pair<UINT, bool>> Status() const;
		std::optional<std::wstring> Cancel() const;
	private:
		std::vector<UINT>& Ranks() override;

		std::vector<UINT> ranks;
	};
}
