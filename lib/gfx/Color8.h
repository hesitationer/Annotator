#pragma once

#include "ColorHSV.h"
#include <cmath>
#include "Vec4.h"

namespace imqs {
namespace gfx {

class ColorHSVA;

// Jim Blinn's perfect unsigned byte multiply
inline unsigned ByteMul(unsigned a, unsigned b) {
	unsigned i = a * b + 128;
	return (i + (i >> 8)) >> 8;
}

// A cheaper unsigned byte multiplier, which only guarantees that 1 * x = x, and 0 * x = 0
inline unsigned ByteMulCheap(unsigned a, unsigned b) {
	return ((a + 1) * b) >> 8;
}

/* 8-bit RGBA color

If not specified, then:
 * RGB values are sRGB
 * Alpha values are linear
 * Not premultiplied

*/
class Color8 {
public:
	union {
		struct
		{
			uint8_t r, g, b, a;
		};
		uint32_t u;
	};

	Color8() {}
	Color8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
	bool   operator==(const Color8& b) const { return u == b.u; }
	bool   operator!=(const Color8& b) const { return u != b.u; }
	void   Premultiply();
	Color8 Premultipied() const;

	ColorHSVA   ToHSVA() const;
	static void ToHSVA(const Vec4f& rgba, Vec4f& hsva);
	std::string ToCSS() const;

	float Rf() const { return (float) r / 255.0f; } // Returns Red 0..1
	float Gf() const { return (float) g / 255.0f; } // Returns Green 0..1
	float Bf() const { return (float) b / 255.0f; } // Returns Bue 0..1
	float Af() const { return (float) a / 255.0f; } // Returns Alpha 0..1

	// Input values are clamped between 0..1
	static Color8 FromFloat(float h, float s, float v, float a);

	static Color8 White() { return Color8(255, 255, 255, 255); }
	static Color8 Black() { return Color8(0, 0, 0, 255); }
	static Color8 Transparent() { return Color8(0, 0, 0, 0); }

	static float SRGBtoLinear(float v) {
		const float a = 0.055f;
		return v <= 0.04045f ? v / 12.92f : pow((v + a) / (1 + a), 2.4f);
	}

	static void SRGBtoLinear(Vec4f& v) {
		v.x = SRGBtoLinear(v.x);
		v.y = SRGBtoLinear(v.y);
		v.z = SRGBtoLinear(v.z);
	}

	static float LinearToSRGB(float v) {
		const float a = 0.055f;
		return v <= 0.0031308f ? 12.92f * v : (1 + a) * pow(v, (1 / 2.4f));
	}

	static void LinearToSRGB(Vec4f& v) {
		v.x = math::Clamp(v.x, 0.0f, 1.0f);
		v.y = math::Clamp(v.y, 0.0f, 1.0f);
		v.z = math::Clamp(v.z, 0.0f, 1.0f);
		v.x = LinearToSRGB(v.x);
		v.y = LinearToSRGB(v.y);
		v.z = LinearToSRGB(v.z);
	}
};

inline void Color8::Premultiply() {
	r = ByteMul(r, a);
	g = ByteMul(g, a);
	b = ByteMul(b, a);
}

inline Color8 Color8::Premultipied() const {
	Color8 copy = *this;
	copy.Premultiply();
	return copy;
}

} // namespace gfx
} // namespace imqs
