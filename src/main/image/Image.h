//
// Created by Przemek Piórkowski on 27.02.2016.
//

#ifndef FEITIR_IMAGE_H
#define FEITIR_IMAGE_H

#include <iostream>
#include <vector>

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

namespace feitir {

    enum class Extension {PNG, JPEG, TIFF, UNKNOWN};

    class Image {

    private:
        // Full filename (including file extension)
        const std::string name;
        // Full path to file
        const std::string fullPath;
        // Path where file is located
        const std::string path;
        // Enum representing file extension
        const Extension extension;
        // vector of keypoints locations
        const std::vector<cv::KeyPoint> keyPoints;
        // each row of descriptors matrix represents SIFT descriptor value in respectively choosen keyPoint
        const cv::Mat descriptors;

    protected:

    public:
        Image(const std::string & name,
              const std::string & fullPath,
              const std::string & path,
              const Extension extension,
              const std::vector<cv::KeyPoint> && keyPoints,
              const cv::Mat descriptors);

        const std::vector<cv::KeyPoint>& getKeyPoints() const;
        const std::string &getFullPath() const;
        const std::string &getFileName() const;
        const Extension &getExtension() const;
        const cv::Mat &getDescriptors() const;
        const std::string &getPath() const;
    };

}

#endif //FEITIR_IMAGE_H
