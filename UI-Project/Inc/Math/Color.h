#pragma once

namespace Pyro
{
    class String;

    struct Color {

    public:
        union {
            struct {
                /// Red value
                float r;
                /// Green value
                float g;
                /// Blue value
                float b;
                /// Alpha value
                float a;
            };
            float data[4];
        };

    public:
        /// Construct
        Color();
        /// Construct with parameters
        Color(float r, float g, float b, float a = 1.0f);
        /// Copy-construct
        Color(const Color& color);
        /// Assignment operator
        Color& operator=(const Color& color);

        /// Return color value at index
        float operator[](unsigned index) { return index < 4 ? data[index] : 0.0f; }
        /// Return color value at index
        const float operator[](unsigned index) const { return index < 4 ? data[index] : 0.0f; }

        /// Lerp between this color and target color
        Color Lerp(const Color& targetColor, float ratio) const;
        /// Return average
        float Average() const;

        /// Return color as float array
        float* Data() { return &r; }
        /// Return color as float array
        const float* Data() const { return &r; }

        static Color Red();
        static Color Green();
        static Color Blue();
        static Color Yellow();
        static Color Cyan();
        static Color Transparent();
        static Color Black();
        static Color White();
        static Color Clear();
    };
}
