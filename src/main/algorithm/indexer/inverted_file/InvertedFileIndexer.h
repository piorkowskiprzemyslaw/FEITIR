//
// Created by Przemek Piórkowski on 04.04.2016.
//

#ifndef FEITIR_INVERTEDFILEINDEXER_H
#define FEITIR_INVERTEDFILEINDEXER_H

#include <iostream>
#include <unordered_map>
#include <opencv2/features2d.hpp>
#include "src/main/database/image/Image.h"
#include "src/main/algorithm/indexer/Indexer.h"
#include "IFConfig.h"

namespace feitir {

    class InvertedFileIndexer : public Indexer<IFResultPtr, IFQueryPtr, IFParametersPtr> {
    private:
        const VocabularyTypePtr vocabulary;
        cv::BFMatcher matcher;
        std::unordered_multimap<int, ImagePtr> invertedFile;

    protected:
        void processImage(const ImagePtr img);

    public:
        InvertedFileIndexer(const IFParametersPtr &parameters);
        virtual ~InvertedFileIndexer();
        virtual IFResultPtr query(IFQueryPtr query);

    };

}


#endif //FEITIR_INVERTEDFILEINDEXER_H
