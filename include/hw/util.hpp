//
// Created by julian on 5/24/19.
//

#ifndef HWCPP_UTIL_HPP
#define HWCPP_UTIL_HPP

#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace hw::util {

namespace units {

class Degrees {
public:
    explicit constexpr Degrees(float amount) : amount(amount) {}

    constexpr Degrees() = delete;

    ~Degrees() = default;

    constexpr float to_rad() {
        return this->amount * M_PI / 180.0;
    }

private:
    float amount;
};

} // namespace hw::util::units

namespace color {

enum Color {
    RED,
    GREEN,
    BLUE
};

const static cv::Vec3b RGBRED = cv::Vec3b{255, 0, 0};
const static cv::Vec3b RGBGREEN = cv::Vec3b{0, 255, 0};
const static cv::Vec3b RGBBLUE = cv::Vec3b{0, 0, 255};

bool same_color(const cv::Mat &im, const cv::KeyPoint &point, Color color, float tolerance = 75.0) {
    // opencv idiots thought it was a good idea to return color in BGR
    auto true_color = im.at<cv::Vec3b>(point.pt);
    switch (color) {
        case RED:
            if (std::abs(RGBRED[0] - true_color.val[2]) < tolerance) return true;
        case GREEN:
            if (std::abs(RGBGREEN[1] - true_color.val[1]) < tolerance) return true;
        case BLUE:
            if (std::abs(RGBBLUE[2] - true_color.val[0]) < tolerance) return true;
    }

    return false;
}

} // namespace hw::util::color

namespace geo {

using UnitVector = cv::Point2f;

geo::UnitVector connecting_vector(const cv::Point2f &a, const cv::Point2f &b) {
    float x = std::abs(a.x - b.x);
    float y = std::abs(a.y - b.y);
    float length = std::sqrt(std::pow(x, 2.0) + std::pow(y, 2.0));
    return geo::UnitVector{x / length, y / length};
}

// see https://stackoverflow.com/questions/25642532/opencv-pointx-y-represent-column-row-or-row-column
void to_cartesian(cv::Point2f& point) {
    point.y *= -1;
}

} // namespace hw::util::geo

namespace calc {

void rotate(cv::Point2f &point, units::Degrees degrees) {
    float angle = degrees.to_rad();
    auto x = point.x; // original x is saved for later calculation
    point.x = point.x * std::cos(angle) - point.y * std::sin(angle);
    point.y = x * std::sin(angle) + point.y * std::cos(angle);
}

float norm(const cv::Point2f& point) {
    return std::sqrt(std::pow(point.x, 2.0) + std::pow(point.y, 2.0));
}

} // namespace hw::util::calc
} // namespace hw::util

#endif //HWCPP_UTIL_HPP
