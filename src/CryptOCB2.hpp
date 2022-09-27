// Copyright 2022 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_SRC_CRYPTOCB2_HPP
#define MUMBLE_SRC_CRYPTOCB2_HPP

#include "mumble/CryptOCB2.hpp"

#include "mumble/Types.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

#include <gsl/span>

#include <openssl/ossl_typ.h>

namespace mumble {
class CryptOCB2::P {
	friend CryptOCB2;

public:
#if defined(__LP64__)
	using SubBlock = uint64_t;

	static constexpr uint8_t subBlocks = 2;
	static constexpr uint8_t shiftBits = 63;
#else
	using SubBlock = uint32_t;

	static constexpr uint8_t subBlocks = 4;
	static constexpr uint8_t shiftBits = 31;
#endif
	using KeyBlock         = std::array< SubBlock, subBlocks >;
	using KeyBlockRef      = gsl::span< SubBlock, subBlocks >;
	using KeyBlockRefConst = gsl::span< const SubBlock, subBlocks >;

	static constexpr uint8_t blockSize = 128 / 8;
	static constexpr uint8_t keySize   = 128 / 8;
	static constexpr uint8_t nonceSize = 128 / 8;

	P();
	~P();

private:
	size_t process(const bool encrypt, const BufRef out, const BufRefConst in);

	static void xorBlock(const KeyBlockRef dst, const KeyBlockRefConst a, const KeyBlockRefConst b);

	static void s2(const KeyBlockRef block);
	static void s3(const KeyBlockRef block);

	static KeyBlockRef toBlockRef(const BufRef buf);
	static KeyBlockRefConst toBlockRef(const BufRefConst buf);

	bool m_ok;
	FixedBuf< keySize > m_key;
	FixedBuf< nonceSize > m_nonce;
	EVP_CIPHER_CTX *m_ctx;
};
} // namespace mumble

#endif
