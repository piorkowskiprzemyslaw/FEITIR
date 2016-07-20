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
                : Image{name, fullPath, path, extension, descriptors}, N{N}, bsift{std::move(bsift)} {
            assert (this->getDescriptors().rows > 0);
            assert (this->getDescriptors().rows == this->getBsift().size());
        }

        ImageBSIFT(const ImagePtr image, const unsigned N, std::vector<BSIFT> bsift)
                : Image{image}, N{N}, bsift{std::move(bsift)} {
            assert (image->getDescriptors().rows > 0);
            assert (image->getDescriptors().rows == this->getBsift().size());
        }

        ImageBSIFT(const std::shared_ptr<ImageBSIFT> imageBSIFTPtr,
                   std::vector<cv::DMatch> matches) : Image{imageBSIFTPtr, std::move(matches)}, N{imageBSIFTPtr->getN()},
                                                      bsift{imageBSIFTPtr->getBsift()} {
            assert (this->getMatches().size() > 0);
            assert (this->getMatches().size() == this->getBsift().size());
        }

        ImageBSIFT(const std::shared_ptr<ImageBSIFT> imageBSIFTPtr) : Image{imageBSIFTPtr}, N{imageBSIFTPtr->getN()},
                                                                      bsift{imageBSIFTPtr->getBsift()} {
            assert (imageBSIFTPtr->getMatches().size() > 0);
            assert (imageBSIFTPtr->getMatches().size() == imageBSIFTPtr->getBsift().size());
        }

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

namespace boost {
    template <typename B, typename A>
    std::size_t hash_value(const boost::dynamic_bitset<B, A>& bs) {
        std::vector<B, A> v;
        boost::to_block_range(bs, std::back_inserter(v));
        return boost::hash_value(v);
    }
}

namespace std
{
    template<>
    struct hash<boost::dynamic_bitset<>>
    {
        typedef boost::dynamic_bitset<> argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& bitset) const {
            return dynamic_bitset_hasher(bitset);
        }
    private:
        boost::hash<boost::dynamic_bitset<>> dynamic_bitset_hasher;
    };
}

#endif //FEITIR_IMAGEBSIFT_H
