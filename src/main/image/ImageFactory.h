//
// Created by Przemek Piórkowski on 28.02.2016.
//

#ifndef FEITIR_IMAGEFACTORY_H
#define FEITIR_IMAGEFACTORY_H

#include <iostream>
#include <utility>
#include <memory>
#include <regex>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <boost/filesystem.hpp>

#include "Image.h"

namespace feitir {

    class ImageFactory {
    private:
        const std::regex fileNameRegex;
        const std::string KEYPOINTS_FILE_NODE_NAME;
        const std::string DESCRIPTORS_FILE_NODE_NAME;
        cv::Ptr<cv::xfeatures2d::SIFT> sift;


    protected:
        std::string extractFileName(const std::string& path) const;
        Extension extractFileExtension(const std::string& path) const;
        std::string extractPath(const std::string &fullPath) const;
        const std::string imageDataFile(const std::string &path, const std::string &fileName) const;
        void loadImageData(const std::string &path, const std::string &fileName,
                           std::vector<cv::KeyPoint> &keyPoints, cv::Mat& descriptors) const;
    public:
        static const std::string IMAGE_DATA_FILE_INFIX;

        explicit ImageFactory();
        const std::shared_ptr<Image> createImage(const std::string &fullPath) const;
        const std::shared_ptr<Image> createImage(const std::string &fullPath,
                                                 const std::string &path,
                                                 const std::string &fileName) const;
        void saveImageData(const std::shared_ptr<Image> img) const;
        bool deleteImageData(const std::shared_ptr<Image> img) const;
    };

}

#endif //FEITIR_IMAGEFACTORY_H
