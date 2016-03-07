//
// Created by Przemek Piórkowski on 28.02.2016.
//

#include "ImageFactory.h"

namespace feitir {

    const std::string ImageFactory::IMAGE_DATA_FILE_INFIX = ".IMAGE_DATA_";

    ImageFactory::ImageFactory() : fileNameRegex{"(([^\\/\\.]+).([^\\/\\.]+))$"},
                                   KEYPOINTS_FILE_NODE_NAME{"keypoints"},
                                   DESCRIPTORS_FILE_NODE_NAME{"descriptors"} {
        sift = cv::xfeatures2d::SIFT::create();
    }

    const std::shared_ptr<Image> ImageFactory::createImage(const std::string &fullPath) const {
        std::string fileName = extractFileName(fullPath);
        std::string path = extractPath(fullPath);
        return createImage(fullPath, path, fileName);
    }

    const std::shared_ptr<Image> ImageFactory::createImage(const std::string &fullPath,
                                                           const std::string &path,
                                                           const std::string &fileName) const {
        Extension extension = extractFileExtension(fullPath);
        std::vector<cv::KeyPoint> keyPoints;
        cv::Mat descriptors;
        loadImageData(path, fileName, keyPoints, descriptors);
        return std::make_shared<Image>(fileName, fullPath, path, extension,
                                       std::forward<std::vector<cv::KeyPoint>>(keyPoints), descriptors);
    }

    void ImageFactory::loadImageData(const std::string& path, const std::string& fileName,
                                     std::vector<cv::KeyPoint> &keyPoints, cv::Mat& descriptors) const {
        std::string imageDataFileName = this->imageDataFile(path, fileName);
        if (!boost::filesystem::exists(imageDataFileName)) {
            cv::Mat image = cv::imread(path + fileName);
            sift->detectAndCompute(image, cv::noArray(), keyPoints, descriptors);
        } else {
            cv::FileStorage fs(imageDataFileName.c_str(), cv::FileStorage::READ);
            cv::read(fs[KEYPOINTS_FILE_NODE_NAME], keyPoints);
            cv::read(fs[DESCRIPTORS_FILE_NODE_NAME], descriptors);
            fs.release();
        }
    }

    std::string ImageFactory::extractFileName(const std::string &path) const {
        std::smatch smatch;
        std::regex_search(path, smatch, fileNameRegex);
        if (smatch.empty()) {
            return "";
        } else {
            return smatch[1].str().c_str();
        }
    }

    Extension ImageFactory::extractFileExtension(const std::string &path) const {
        std::string extension = boost::filesystem::extension(path);
        if (extension.empty()) {
            return Extension::UNKNOWN;
        } else {
            if (extension.compare(".png") || extension.compare(".PNG")) {
                return Extension::PNG;
            } else if (extension.compare(".tiff") || extension.compare(".TIFF")) {
                return Extension::TIFF;
            } else if (extension.compare(".jpeg") || extension.compare(".JPEG")) {
                return Extension::JPEG;
            } else {
                return Extension::UNKNOWN;
            }
        }
    }

    std::string ImageFactory::extractPath(const std::string &fullPath) const {
        u_long lastIndex = fullPath.find_last_of("/");
        std::string path = fullPath.substr(0, lastIndex + 1);
        return path;
    }

    void ImageFactory::saveImageData(const std::shared_ptr<Image> img) const {
        std::string imageDataFile = this->imageDataFile(img->getPath(), img->getFileName());
        if (!boost::filesystem::exists(imageDataFile)) {
            cv::FileStorage fs(imageDataFile.c_str(), cv::FileStorage::WRITE);
            cv::write(fs, KEYPOINTS_FILE_NODE_NAME, img->getKeyPoints());
            cv::write(fs, DESCRIPTORS_FILE_NODE_NAME, img->getDescriptors());
            fs.release();
        }
    }

    inline const std::string ImageFactory::imageDataFile(const std::string &path, const std::string &fileName) const {
        return path + IMAGE_DATA_FILE_INFIX + fileName;
    }

    bool ImageFactory::deleteImageData(const std::shared_ptr<Image> img) const {
        return boost::filesystem::remove(imageDataFile(img->getPath(), img->getFileName()));
    }
}


