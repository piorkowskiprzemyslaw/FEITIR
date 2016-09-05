//
// Created by Przemek Piórkowski on 05.09.2016.
//

#include <src/main/util/Util.h>
#include "InvertedFileSIFTIndexer.h"

namespace feitir {

    InvertedFileSIFTIndexer::InvertedFileSIFTIndexer(const IFSParametersPtr &parameters)
            : Indexer(parameters), treshold{parameters->getThreshold()},
              database{parameters->getDatabase()} {
        for (const auto& img : *database) {
            processImage(img);
        }
    }

    void InvertedFileSIFTIndexer::processImage(ImagePtr img) {
        uuidToImageMap.emplace(img->getUuid(), img);
        for (auto& match : img->getMatches()) {
            invertedFile.emplace(match.trainIdx,
                                 std::make_tuple(img, img->getDescriptors().row(match.queryIdx)));
        }
    }

    IndexerResultPtr InvertedFileSIFTIndexer::query(IndexerQueryPtr queryPtr) {
        return query(std::static_pointer_cast<IFSQuery>(queryPtr));
    }

    IndexerResultPtr InvertedFileSIFTIndexer::query(IFSQueryPtr query) {
        std::unordered_map<boost::uuids::uuid, IndexerResultMap> uuidToResult;
        IndexerResultPtr resultPtr = std::make_shared<IndexerResult>();
        cv::Mat sift;
        ImagePtr imgPtr;

        auto img = query->getImg();
        for (auto& match : img->getMatches()) {
            auto range = invertedFile.equal_range(match.trainIdx);
            for (auto dbImage = range.first; dbImage != range.second; ++dbImage) {
                std::tie(imgPtr, sift) = dbImage->second;
                if (Util::euclideanDistance(img->getDescriptors().row(match.queryIdx), sift) <= treshold) {

                    if (uuidToResult.find(imgPtr->getUuid()) == uuidToResult.end()) {
                        uuidToResult[imgPtr->getUuid()] = {{match.trainIdx, 1}};
                    } else {
                        uuidToResult[imgPtr->getUuid()][match.trainIdx]++;
                    }
                }
            }
        }

        for (auto& val : uuidToResult) {
            resultPtr->addResultEntry({uuidToImageMap[val.first], val.second});
        }

        return resultPtr;
    }
}