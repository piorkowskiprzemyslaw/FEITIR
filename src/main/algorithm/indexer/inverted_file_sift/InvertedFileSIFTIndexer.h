//
// Created by Przemek Piórkowski on 05.09.2016.
//

#ifndef FEITIR_INVERTEDFILESIFTINDEXER_H
#define FEITIR_INVERTEDFILESIFTINDEXER_H

#include <src/main/algorithm/indexer/Indexer.h>
#include "IFSConfig.h"

namespace feitir {

    class InvertedFileSIFTIndexer : public Indexer {
    public:
        InvertedFileSIFTIndexer(const IFSParametersPtr &parameters);

        virtual IndexerResultPtr query(IndexerQueryPtr queryPtr) override;

        virtual IndexerResultPtr query(IFSQueryPtr query);

    protected:
        void processImage(ImagePtr img);

    private:
        const int treshold;
        DatabasePtr database;
        std::unordered_multimap<int, std::tuple<ImagePtr, cv::Mat>> invertedFile;
        std::unordered_map<boost::uuids::uuid, ImagePtr> uuidToImageMap;

    };

}



#endif //FEITIR_INVERTEDFILESIFTINDEXER_H
