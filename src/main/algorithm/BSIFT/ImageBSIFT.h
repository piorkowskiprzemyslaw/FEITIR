//
// Created by Przemek Piórkowski on 26.03.2016.
//

#ifndef FEITIR_IMAGEBSIFT_H
#define FEITIR_IMAGEBSIFT_H

#include <iostream>
#include <bitset>
#include "src/main/database/image/Image.h"

namespace feitir {

    /**
     * Template representing Image with Binary SIFT descriptors value computed. Each Binary SIFT is N bits long.
     */
    template <std::size_t N>
    class ImageBSIFT : public Image {
    public:
        /**
         * Single descriptor type
         */
        using BSIFT = std::bitset<N>;

        ImageBSIFT(const std::string &name, const std::string &fullPath, const std::string &path,
                   const Extension extension, const cv::Mat &descriptors, std::vector<BSIFT> bsift)
                : Image{name, fullPath, path, extension, descriptors}, bsift{std::move(bsift)} { }

        ImageBSIFT(const ImagePtr image, std::vector<BSIFT> bsift) : Image{image}, bsift{std::move(bsift)} { }

        ImageBSIFT(const std::shared_ptr<ImageBSIFT<N>> imageBSIFTPtr,
                   std::vector<cv::DMatch> matches) : Image{imageBSIFTPtr, std::move(matches)},
                                                              bsift{imageBSIFTPtr->getBsift()} { }

        ImageBSIFT(const std::shared_ptr<ImageBSIFT<N>> imageBSIFTPtr) : Image{imageBSIFTPtr},
                                                                         bsift{imageBSIFTPtr->getBsift()} { }

        virtual ~ImageBSIFT() { }

        const std::vector<BSIFT> &getBsift() const {
            return bsift;
        }

    private:
        const std::vector<BSIFT> bsift;
    };

    template <std::size_t N>
    using ImageBSIFTPtr = std::shared_ptr<ImageBSIFT<N>>;

}

#endif //FEITIR_IMAGEBSIFT_H
