// Copyright 2022 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_ENDIAN_HPP
#define MUMBLE_ENDIAN_HPP

#include "Macros.hpp"

#include <cstdint>

namespace mumble {
class MUMBLE_EXPORT Endian {
public:
	Endian();
	virtual ~Endian() = delete;

	static constexpr bool isBig() { return SingleSplit64(0x0102030405060708).split[0] == 1; }
	static constexpr bool isLittle() { return SingleSplit64(0x0102030405060708).split[0] == 8; }

	static uint16_t swap(const uint16_t value);
	static uint32_t swap(const uint32_t value);
	static uint64_t swap(const uint64_t value);

	static uint16_t toNetwork(const uint16_t value) { return isBig() ? value : swap(value); }
	static uint32_t toNetwork(const uint32_t value) { return isBig() ? value : swap(value); }
	static uint64_t toNetwork(const uint64_t value) { return isBig() ? value : swap(value); }

	static uint16_t toHost(const uint16_t value) { return isBig() ? value : swap(value); }
	static uint32_t toHost(const uint32_t value) { return isBig() ? value : swap(value); }
	static uint64_t toHost(const uint64_t value) { return isBig() ? value : swap(value); }

private:
	union SingleSplit64 {
		uint64_t single;
		uint8_t split[sizeof(single)];

		constexpr SingleSplit64(const uint64_t value) : single(value) {}
	};

	Endian(const Endian &)                    = delete;
	virtual Endian &operator=(const Endian &) = delete;
};
} // namespace mumble

#endif
