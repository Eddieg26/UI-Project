#include "Mathf.h"

#include <cmath>
#include <cfloat>

namespace Pyro
{
    const float Mathf::DegToRad = Mathf::PI / 180.0f;
    const float Mathf::DegToRad2 = Mathf::PI / 360.0f;
    const float Mathf::RadToDeg = 57.29578f;
    const float Mathf::Epsilon = 0.000001f;;
    const float Mathf::PI = 3.14159265358979f;
    const float Mathf::Infinity = INFINITY;
    const float Mathf::NegativeInfinity = -INFINITY;
    const float Mathf::FloatMin = FLT_MIN;
    const float Mathf::FloatMax = FLT_MAX;
    const int Mathf::IntMin = INT_MIN;
    const int Mathf::IntMax = INT_MAX;
    const unsigned int Mathf::UnsignedMax = 0xffffffff;

    float Mathf::Abs(float f) {
        return f < 0 ? -f : f;
    }

    float Mathf::Acos(float f) {
        return (float)acosf(f);
    }

    bool Mathf::Approximately(float a, float b) {
        return (Abs(a - b)) <= Epsilon;
    }

    float Mathf::Asin(float f) {
        return (float)asinf(f);
    }

    float Mathf::Atan(float f) {
        return (float)atanf(f);
    }

    float Mathf::Atan2(float x, float y) {
        return atan2f(x, y);
    }

    float Mathf::Ceil(float f) {
        return ceilf(f);
    }

    int Mathf::CeilToInt(float f) {
        return int(f + 0.5f);
    }

    float Mathf::Clamp(float value, float min, float max) {
        min = fminf(min, max);
        if (value < min)
            return min;
        else if (value > max)
            return max;

        return value;
    }

    float Mathf::Clamp01(float value) {
        return Clamp(value, 0, 1);
    }

    int Mathf::ClosestPowerOfTwo(int value) {
        if (value <= 0)
            return 0;

        --value;
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;
        return value + 1;
    }

    float Mathf::Cos(float f) {
        return cosf(f);
    }

    float Mathf::Floor(float f) {
        return (float)floorf(f);
    }

    int Mathf::FloorToInt(float f) {
        return (int)floorf(f);
    }

    float Mathf::GammaToLinear(float value) {
        return powf(value, 2.2f);
    }

    float Mathf::InverseLerp(float a, float b, float value) {
        return (value - a) / (b - a);
    }

    bool Mathf::IsPowerOfTwo(int value) {
        if (value <= 0) return false;

        return (value & (value - 1)) == 0;
    }

    float Mathf::Lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }

    float Mathf::LerpAngle(float a, float b, float t) {
        float angle = a + (b - a) * t;
        angle = fmodf(angle, 360.0);
        if (angle < 360.0f)
            angle += 360.0f;
        return angle;
     }

    float Mathf::LinearToGammaSpace(float value) {
        return powf(value, 1.0f / 2.2f);
    }

    float Mathf::Log(float f) {
        return logf(f);
    }

    float Mathf::Log10(float f) {
        return log10f(f);
    }

    float Mathf::PerlinNoise(float x, float y) {
        int n = (int)x + (int)y * 57;
        n = (n << 13) ^ n;
        int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
        return 1.0f - ((float)nn / 1073741824.0f);
    }

    float Mathf::Pow(float f, float p) {
        return powf(f, p);
    }

    int Mathf::Pow(int value, int p) {
        return (int)pow(value, p);
    }

    float Mathf::Round(float f) {
        return roundf(f);
    }

    int Mathf::RoundToInt(float f) {
        return (int)roundf(f);
    }

    int Mathf::Sign(float f) {
        return f < 0 ? -1 : 1;
    }

    int Mathf::Sign(int value) {
        return value < 0 ? -1 : 1;
    }

    float Mathf::Sqrt(float f) {
        return sqrtf(f);
    }

    float Mathf::Sqrt(int value) {
        return static_cast<float>(sqrt(value));
    }

    float Mathf::Tan(float f) {
        return tanf(f);
    }

    bool Mathf::CompareFloat(float a, float b) {
        return Mathf::Abs(a - b) <= Mathf::Epsilon;
    }

    bool Mathf::IsValid(float f) {
        return f + 1 > f;
    }

    unsigned Mathf::align(unsigned int value, unsigned int alignBy) {
        return (value + (alignBy - 1)) & ~(alignBy - 1);
    }

}
































