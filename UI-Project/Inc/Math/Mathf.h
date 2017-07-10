#pragma once
namespace Pyro
{

    class Mathf {

    public:
        /// Degrees-to-radians conversion constant
        static const float DegToRad;
        /// Degrees-to-radians times 2 conversion constant
        static const float DegToRad2;
        /// Radians-to-degree conversion constant
        static const float RadToDeg;
        /// The smallest value that a float can have different from zero
        static const float Epsilon;
        /// The infamous 3.14159265358979... value 
        static const float PI;
        /// A representation of positive infinity
        static const float Infinity;
        /// A representation of negative infinity
        static const float NegativeInfinity;
        /// Smallest float value
        static const float FloatMin;
        /// Largest float value
        static const float FloatMax;
        /// Smallest integer value
        static const int IntMin;
        /// Largest integer value
        static const int IntMax;
        /// Largest unsigned int value
        static const unsigned int UnsignedMax;

    public:
        /// Returns absolute value of f
        static float Abs(float f);
        /// Returns the arc-cosine of f - the angle in radians whose cosine is f
        static float Acos(float f);
        /// Compares two floating point values and returns true if they are similar.
        static bool Approximately(float a, float b);
        /// Returns the arc-sine of f - the angle in radians whose sine is f
        static float Asin(float f);
        /// Returns the arc-tangent of f - the angle in radians whose tangent is f
        static float Atan(float f);
        /// Returns the angle in radians whose Tan is y/x
        static float Atan2(float x, float y);
        /// Returns the smallest float greater to or equal to f
        static float Ceil(float f);
        /// Returns the smallest float greater to or equal to f
        static int CeilToInt(float f);
        /// Clamps a value between a minimum float and maximum float value
        static float Clamp(float value, float min, float max);
        /// Clamps a value between 0 and 1
        static float Clamp01(float value);
        /// Find the closst point of  2
        static int ClosestPowerOfTwo(int value);
        /// Returns the cosine of angle f in radians
        static float Cos(float f);
        /// Returns the largest float smaller to or equal to f
        static float Floor(float f);
        /// Returns the largest integar smaller to or equal to f
        static int FloorToInt(float f);
        /// Converts the given value from gamma (sRGB) to linear color space
        static float GammaToLinear(float value);
        /// Calculates the linear parameter t that produces the interpolant value within the range
        static float InverseLerp(float a, float b, float value);
        /// Returns true if the value is power of two
        static bool IsPowerOfTwo(int value);
        /// Linearly interpolates between a and b by t
        static float Lerp(float a, float b, float t);
        /// Same as Lerp but makes sure the values interpolate correctly when they wrap around 360 degrees
        static float LerpAngle(float a, float b, float t);
        /// Convert from linera to gamma space
        static float LinearToGammaSpace(float value);
        /// Returns the logarithm of a specified number in a specified base
        static float Log(float f);
        /// Returns the base 10 logarithm of a specified number
        static float Log10(float f);

        /// Return the smallest value
        template<typename Type>
        static Type Min(Type a, Type b) {
            return a < b ? a : b;
        }
        /// Return the smallest value
        template<typename Type>
        static Type Min(Type* values, unsigned int count) {
            Type smallest = values[0];
            for (unsigned int i = 1; i < count; ++i) {
                if (values[i] < smallest)
                    smallest = values[i];
            }

            return smallest;
        }
        /// Return largest value
        template<typename Type>
        static Type Max(Type a, Type b) {
            return a > b ? a : b;
        }
        /// Return largest value
        template<typename Type>
        static Type Max(Type* values, unsigned int count) {
            Type largest = values[0];
            for (unsigned int i = 1; i < count; ++i) {
                if (values[i] > largest)
                    largest = values[i];
            }
            return largest;
        }

        /// Generate 2D Perlin noise
        static float PerlinNoise(float x, float y);
        /// Returns f raised to power p.
        static float Pow(float f, float p);
        /// Returns value raised to power p.
        static int Pow(int value, int p);
        /// Returns f rounded to the nearest integer
        static float Round(float f);
        /// Returns f rounded to the nearest integer
        static int RoundToInt(float f);
        /// Return value is 1 when f is positive or zero, -1 when f is negative
        static int Sign(float f);
        /// Return value is 1 when f is positive or zero, -1 when f is negative
        static int Sign(int value);
        /// Returns square root of f
        static float Sqrt(float f);
        /// Returns square root of value
        static float Sqrt(int value);
        /// Returns the tangent of angle f in radians
        static float Tan(float f);
        /// Checks if two floats are equal
        static bool CompareFloat(float a, float b);
        /// Checks if a float is valid
        static bool IsValid(float f);
        /// Aligns the passed in value to a multiple of the align by value, only works with powers of 2
        static unsigned align(unsigned int value, unsigned int alignBy);

    private:
        /// Delete ctor, copy ctor, and assignment operator to prevent creation
        Mathf() = delete;
        Mathf(const Mathf& rhs) = delete;
        Mathf& operator=(const Mathf& rhs) = delete;
    };
}