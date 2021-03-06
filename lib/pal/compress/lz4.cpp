#include "pch.h"
#include "compress/lz4.h"

namespace imqs {
namespace compress {
namespace lz4 {

IMQS_PAL_API Error DecompressSafe(const void* compressed, size_t compressedLen, void* raw, size_t& rawLen) {
	IMQS_ASSERT(compressedLen <= LZ4_MAX_INPUT_SIZE);
	int r = LZ4_decompress_safe((const char*) compressed, (char*) raw, (int) compressedLen, (int) rawLen);
	if (r < 0)
		return Error::Fmt("LZ4 decode error %v", r);
	rawLen = r;
	return Error();
}

IMQS_PAL_API Error DecompressFast(const void* compressed, void* raw, size_t rawLen) {
	IMQS_ASSERT(rawLen <= LZ4_MAX_INPUT_SIZE);
	int r = LZ4_decompress_fast((const char*) compressed, (char*) raw, (int) rawLen);
	if (r < 0)
		return Error::Fmt("LZ4 decode error %v", r);
	return Error();
}

}
}
}