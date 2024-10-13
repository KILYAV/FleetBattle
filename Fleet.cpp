#include "Fleet.h"

using namespace fleet;

struct OR {
	static bool Operator(bool lft, bool rht) {
		return lft || rht;
	}
};
struct AND {
	static bool Operator(bool lft, bool rht) {
		return lft && rht;
	}
};

std::vector<UINT>& Fleet::Ranks() {
	return ranks;
}

Fleet::Fleet()
{
	ranks.resize(GetLevelUINT());
}
std::optional<std::pair<UINT, bool>> Fleet::Status() const {
	auto max{ GetLevelUINT() };
	for (UINT index = 0, size = ranks.size(); index < size; ++index) {
		if (ranks[index] == max) {
			--max;
		}
		else {
			return { { max, ranks[index] > max } };
		}
	}
	return {};
}
std::optional<std::wstring> Fleet::Cancel() const {
	if (auto check = Status(); check.has_value()) {
		auto [level, diff] {check.value()};
		std::wstring messing{ L"Too " };
		if (diff)
			messing += L"many ";
		else
			messing += L"few ";
		return
			messing + std::to_wstring(level) + L"-level ships";
	}
	else
		return {};
}
