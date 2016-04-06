//
// Created by Przemek Piórkowski on 26.03.2016.
//

#include "ImageBSIFT.h"

namespace feitir {

    ImageBSIFT::ImageBSIFT(const std::string &name, const std::string &fullPath, const std::string &path,
                           const feitir::Extension extension, const cv::Mat &descriptors,
                           const std::vector<BSIFT> &&bsift)
            : Image{name, fullPath, path, extension, descriptors}, bsift{std::move(bsift)} {

    }

    ImageBSIFT::ImageBSIFT(const ImagePtr image, const std::vector<BSIFT>&& bsift) : Image{image}, bsift{std::move(bsift)} {

    }



    const std::vector<BSIFT> &ImageBSIFT::getBsift() const {
        return bsift;
    }

    ImageBSIFT::~ImageBSIFT() {

    }

    ImageBSIFT::ImageBSIFT(const std::shared_ptr<ImageBSIFT> imageBSIFTPtr,
                           const std::vector<cv::DMatch>&& matches) : Image(imageBSIFTPtr, std::move(matches)),
                                                                      bsift{imageBSIFTPtr->getBsift()} {

    }


}