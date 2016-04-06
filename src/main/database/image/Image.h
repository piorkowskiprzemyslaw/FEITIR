//
// Created by Przemek Piórkowski on 27.02.2016.
//

#ifndef FEITIR_IMAGE_H
#define FEITIR_IMAGE_H

#include <iostream>
#include <vector>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

namespace feitir {

    enum class Extension {PNG, JPEG, TIFF, BITMAP, WEBP, UNKNOWN};

    class Image {

    private:
        // unified resource identifier
        const boost::uuids::uuid uuid;
        // Full filename (including file extension)
        const std::string name;
        // Full path to file
        const std::string fullPath;
        // Path where file is located
        const std::string path;
        // Enum representing file extension
        const Extension extension;
        // each row of descriptors matrix represents SIFT descriptor value in respectively chosen keyPoint
        const cv::Mat descriptors;
        // mapping from original descriptor value to mapped
        const std::vector<cv::DMatch> matches;

    protected:

    public:
        Image(const std::string &name,
              const std::string &fullPath,
              const std::string &path,
              const Extension extension,
              const cv::Mat descriptors);

        Image(const std::string &name,
              const std::string &fullPath,
              const std::string &path,
              const Extension extension,
              const std::vector<cv::DMatch>&& matches);

        Image(const std::shared_ptr<Image> img);

        Image(const std::shared_ptr<Image> img,
              const std::vector<cv::DMatch>&& matches);

        virtual ~Image();

        const std::string &getFullPath() const;
        const std::string &getFileName() const;
        const Extension &getExtension() const;
        const cv::Mat getDescriptors() const;
        const std::string &getPath() const;
        const std::vector<cv::DMatch> & getMatches() const;
    };

    typedef std::shared_ptr<Image> ImagePtr;

}

#endif //FEITIR_IMAGE_H
