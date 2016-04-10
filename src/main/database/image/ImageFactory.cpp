//
// Created by Przemek Piórkowski on 28.02.2016.
//

#include "ImageFactory.h"

namespace feitir {

    const std::string ImageFactory::IMAGE_DATA_FILE_POSTFIX = ".imgdata";
    const std::string ImageFactory::IMAGE_DATA_FILE_PREFIX = ".";

    ImageFactory::ImageFactory() : fileNameRegex{"(([^\\/\\.]+).([^\\/\\.]+))$"},
                                   DESCRIPTORS_FILE_NODE_NAME{"descriptors"} {
        sift = cv::xfeatures2d::SIFT::create();
    }

    const ImagePtr ImageFactory::createImage(const std::string &fullPath) const {
        if (!boost::filesystem::exists(fullPath) || !boost::filesystem::is_regular_file(fullPath))
            return nullptr;

        std::string fileName = extractFileName(fullPath);
        std::string path = extractPath(fullPath);
        return createImage(fullPath, path, fileName);
    }

    const ImagePtr ImageFactory::createImage(const std::string &fullPath,
                                             const std::string &path,
                                             const std::string &fileName) const {
        Extension extension = extractFileExtension(fullPath);
        if (extension == Extension::UNKNOWN)
            return nullptr;

        cv::Mat descriptors;
        loadImageData(path, fileName, descriptors);
        auto imgPtr = std::make_shared<Image>(fileName, fullPath, path, extension, descriptors);
        saveImageData(imgPtr);
        return imgPtr;
    }

    const ImagePtr ImageFactory::createImage(const ImagePtr img) const {
        return std::make_shared<Image>(img);
    }

    void ImageFactory::loadImageData(const std::string& path, const std::string& fileName, cv::Mat& descriptors) const {
        std::vector<cv::KeyPoint> keyPoints;
        std::string imageDataFileName = this->imageDataFile(path, fileName);
        if (!boost::filesystem::exists(imageDataFileName)) {
            cv::Mat image = cv::imread(path + fileName);
            sift->detectAndCompute(image, cv::noArray(), keyPoints, descriptors);
        } else {
            cv::FileStorage fs(imageDataFileName.c_str(), cv::FileStorage::READ);
            cv::read(fs[DESCRIPTORS_FILE_NODE_NAME], descriptors);
            fs.release();
        }
    }

    std::string ImageFactory::extractFileName(const std::string &path) const noexcept {
        std::smatch smatch;
        std::regex_search(path, smatch, fileNameRegex);
        if (smatch.empty()) {
            return "";
        } else {
            return smatch[1].str().c_str();
        }
    }

    Extension ImageFactory::extractFileExtension(const std::string &path) const noexcept {
        std::string extension = boost::filesystem::extension(path);
        if (extension.empty()) {
            return Extension::UNKNOWN;
        } else {
            std::transform(std::begin(extension), std::end(extension), std::begin(extension), ::tolower);
            if (!extension.compare(".png")) {
                return Extension::PNG;
            } else if (!extension.compare(".tiff")) {
                return Extension::TIFF;
            } else if (!extension.compare(".jpeg") || !extension.compare(".jp2")) {
                return Extension::JPEG;
            } else if (!extension.compare(".bmp") || !extension.compare(".dib")) {
                return Extension::BITMAP;
            } else if (!extension.compare(".webp")) {
                return Extension::WEBP;
            } else {
                return Extension::UNKNOWN;
            }
        }
    }

    std::string ImageFactory::extractPath(const std::string &fullPath) const noexcept {
        u_long lastIndex = fullPath.find_last_of("/");
        std::string path = fullPath.substr(0, lastIndex + 1);
        return path;
    }

    void ImageFactory::saveImageData(const std::shared_ptr<Image> img) const {
        std::string imageDataFile = this->imageDataFile(img->getPath(), img->getFileName());
        if (!boost::filesystem::exists(imageDataFile)) {
            cv::FileStorage fs(imageDataFile.c_str(), cv::FileStorage::WRITE);
            cv::write(fs, DESCRIPTORS_FILE_NODE_NAME, img->getDescriptors());
            fs.release();
        }
    }

    inline const std::string ImageFactory::imageDataFile(const std::string &path, const std::string &fileName) const noexcept {
        return path + IMAGE_DATA_FILE_PREFIX + fileName + IMAGE_DATA_FILE_POSTFIX;
    }

    bool ImageFactory::deleteImageData(const std::shared_ptr<Image> img) const {
        return boost::filesystem::remove(imageDataFile(img->getPath(), img->getFileName()));
    }

    const ImagePtr ImageFactory::createImage(const ImagePtr img, std::vector<cv::DMatch> matches) const {
        return std::make_shared<Image>(img, std::move(matches));
    }

}


