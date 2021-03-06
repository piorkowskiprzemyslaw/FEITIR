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

    /**
     * Standard implementation of inverted file indexer.
     */
    class InvertedFileIndexer : public Indexer {
    private:
        std::unordered_multimap<int, ImagePtr> invertedFile;
        std::unordered_map<boost::uuids::uuid, ImagePtr> uuidToImageMap;

    protected:
        void processImage(const ImagePtr img);

    public:
        explicit InvertedFileIndexer(const IFParametersPtr parameters);
        virtual ~InvertedFileIndexer();
        virtual IndexerResultPtr query(IndexerQueryPtr queryPtr) override;
        virtual IndexerResultPtr query(IFQueryPtr query);

    };

    using InvertedFileIndexerPtr = std::shared_ptr<InvertedFileIndexer>;

}


#endif //FEITIR_INVERTEDFILEINDEXER_H
