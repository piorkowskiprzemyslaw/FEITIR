//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include "InvertedFileIndexer.h"

namespace feitir {
    InvertedFileIndexer::InvertedFileIndexer(const IFParametersPtr &parameters) : Indexer(parameters) { }

    IFResultPtr InvertedFileIndexer::query(IFQueryPtr query) {
        return nullptr;
    }

    InvertedFileIndexer::~InvertedFileIndexer() {

    }
}