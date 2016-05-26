//
// Created by Przemek Piórkowski on 26.03.2016.
//

#ifndef FEITIR_IMAGEBSIFT_H
#define FEITIR_IMAGEBSIFT_H

#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include "src/main/database/image/Image.h"

namespace feitir {

    /**
     * Class representing Image with Binary SIFT descriptors value computed. Each Binary SIFT is N bits long.
     */
    class ImageBSIFT : public Image {
    public:
        /**
         * Single descriptor type
         */
        using BSIFT = boost::dynamic_bitset<>;

        ImageBSIFT(const std::string &name, const std::string &fullPath, const std::string &path,
                   const Extension extension, const cv::Mat &descriptors, const unsigned N, std::vector<BSIFT> bsift)
                : Image{name, fullPath, path, extension, descriptors}, N{N}, bsift{std::move(bsift)} { }

        ImageBSIFT(const ImagePtr image, const unsigned N, std::vector<BSIFT> bsift)
                : Image{image}, N{N}, bsift{std::move(bsift)} { }

        ImageBSIFT(const std::shared_ptr<ImageBSIFT> imageBSIFTPtr,
                   std::vector<cv::DMatch> matches) : Image{imageBSIFTPtr, std::move(matches)}, N{imageBSIFTPtr->getN()},
                                                      bsift{imageBSIFTPtr->getBsift()} { }

        ImageBSIFT(const std::shared_ptr<ImageBSIFT> imageBSIFTPtr) : Image{imageBSIFTPtr}, N{imageBSIFTPtr->getN()},
                                                                      bsift{imageBSIFTPtr->getBsift()} { }

        virtual ~ImageBSIFT() { }

        const unsigned int getN() const {
            return N;
        }

        const std::vector<BSIFT> &getBsift() const {
            return bsift;
        }

    private:
        const unsigned N;
        const std::vector<BSIFT> bsift;
    };

    using ImageBSIFTPtr = std::shared_ptr<ImageBSIFT>;

}

#endif //FEITIR_IMAGEBSIFT_H
