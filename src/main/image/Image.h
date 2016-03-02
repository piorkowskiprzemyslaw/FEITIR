//
// Created by Przemek Piórkowski on 27.02.2016.
//

#ifndef FEITIR_IMAGE_H
#define FEITIR_IMAGE_H

#include <iostream>
#include <vector>

#include <opencv2/core/types.hpp>

namespace feitir {

    enum class Extension {PNG, JPEG, TIFF, UNKNOWN};

    class Image {

    private:
        std::string path;
        std::string name;
        std::vector<cv::KeyPoint> keyPoints;
        Extension extension;

    protected:

    public:
        Image(const std::string & path,
              const std::string & name,
              const std::vector<cv::KeyPoint> && keyPoints,
              const Extension extension);

        const std::vector<cv::KeyPoint>& getKeyPoints() const;
        const std::string & getPath() const;
        const std::string & getName() const;
        const Extension & getExtension() const;
    };

}

#endif //FEITIR_IMAGE_H
