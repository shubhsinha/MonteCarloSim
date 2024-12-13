#include "include/ColorUtils.h"
#include <algorithm> // For clamping values

Color getGradientColor(double temperature, double T_min, double T_max) {
    // Normalize the temperature between 0 and 1
    double normalized = (temperature - T_min) / (T_max - T_min);
    normalized = std::clamp(normalized, 0.0, 1.0); // Clamp between 0 and 1

    // Interpolate color between blue (low) and red (high)
    float r = static_cast<float>(normalized);
    float g = static_cast<float>(1.0 - std::abs(0.5 - normalized) * 2.0); // Green fades in the middle
    float b = static_cast<float>(1.0 - normalized);

    return Color(r, g, b);
}
