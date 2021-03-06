#pragma once

namespace imqs {
namespace compress {
namespace lz4 {

// This is a thin wrapper around LZ4_decompress_safe. See lz4 docs for details
IMQS_PAL_API Error DecompressSafe(const void* compressed, size_t compressedLen, void* raw, size_t& rawLen);

// This is a thin wrapper around LZ4_decompress_fast. See lz4 docs for details
IMQS_PAL_API Error DecompressFast(const void* compressed, void* raw, size_t rawLen);
}
}
}