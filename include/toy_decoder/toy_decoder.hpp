//
// Created by julian on 5/25/19.
//

#ifndef HWCPP_TOY_DECODER_HPP
#define HWCPP_TOY_DECODER_HPP

#include <opencv2/opencv.hpp>
#include <toy_decoder/util.hpp>
#include <vector>
#include <tuple>

namespace toy_decoder {


/**
 * Draw keypoints/orientation in image with Draw::YES
 */
enum Draw {
    YES,
    NO,
};

/**
 * Handles all operations necessary to decode Code (sample seen in README.md)
 */
class ToyDecoder {
public:
    /*
     * Init with OpenCV image
     */
    ToyDecoder(cv::Mat &img);

    /*
     * Init with OpenCV Image and custom Simpleblobdetector params
     */
    ToyDecoder(cv::Mat &img, cv::SimpleBlobDetector::Params params);

    /// default constructor deleted
    ToyDecoder() = delete;

    /// default destructor
    ~ToyDecoder() = default;

    /**
     * Calculates keypoints
     * @param mark: marks keypoint when chosen (optional)
     */
    void calculate_keypoints(Draw mark = NO);

    /**
     * Calculates orientation from keypoint
     * @return orientation, success (true if successful)
     */
    std::tuple<float, bool> calculate_orientation(Draw mark = NO);

    /**
     * Rotate keypoints by specified amout
     * @param degrees amount to rotate
     */
    void rotate_keypoints(toy_decoder::util::units::Degrees degrees);

    /**
     * Rotate opencv image
     * @param degrees amount to rotate
     */
    void rotate_img(toy_decoder::util::units::Degrees degrees);

    /**
     * Decodes code
     * @return cv::Point2i with coordinates and success or not
     */
    std::tuple<cv::Point2i, bool> decode();

    /**
     * Saves image
     * @param name to save with (optional)
     */
    void save_img(std::string name = "output.jpg");

    /**
     * Opens opencv window with image in current state
     * @param name of the window (optional)
     */
    void open_img(std::string name = "img");
private:
    /// opencv image
    cv::Mat &_img;
    /// simple blobdetector
    cv::SimpleBlobDetector::Params _params;
    /// vector to save keypoints
    std::vector<cv::KeyPoint> _keypoints;
    /// cv::Keypoint to save orientation point
    cv::KeyPoint _orientation_point;
    /// avg_size used to calculate avg size of all detected rectangles
    float _avg_size;
};

}

#endif //HWCPP_TOY_DECODER_HPP
