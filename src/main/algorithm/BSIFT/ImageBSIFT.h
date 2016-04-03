//
// Created by Przemek Piórkowski on 26.03.2016.
//

#ifndef FEITIR_IMAGEBSIFT_H
#define FEITIR_IMAGEBSIFT_H

#include <iostream>
#include "src/main/database/image/Image.h"

namespace feitir {

    typedef std::vector<bool> BSIFT;

    class ImageBSIFT : public Image {
    private:
        const std::vector<BSIFT> bsift;

    protected:
    public:
        ImageBSIFT(const std::string &name, const std::string &fullPath, const std::string &path,
                   const Extension extension, const std::vector<cv::KeyPoint> &&keyPoints,
                   const cv::Mat &descriptors, const std::vector<BSIFT> &&bsift);

        ImageBSIFT(const ImagePtr image, const std::vector<BSIFT>&& bsift);

        const std::vector<BSIFT> & getBsift() const;
    };

    typedef std::shared_ptr<ImageBSIFT> ImageBSIFTPtr;

}

#endif //FEITIR_IMAGEBSIFT_H
