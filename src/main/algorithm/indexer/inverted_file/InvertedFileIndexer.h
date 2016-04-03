//
// Created by Przemek Piórkowski on 04.04.2016.
//

#ifndef FEITIR_INVERTEDFILEINDEXER_H
#define FEITIR_INVERTEDFILEINDEXER_H

#include "src/main/algorithm/indexer/Indexer.h"
#include "IFConfig.h"

namespace feitir {

    class InvertedFileIndexer : public Indexer<IFResultPtr, IFQueryPtr, IFParametersPtr> {

    public:
        InvertedFileIndexer(const IFParametersPtr &parameters);
        virtual ~InvertedFileIndexer();
        virtual IFResultPtr query(IFQueryPtr query);

    };

}


#endif //FEITIR_INVERTEDFILEINDEXER_H
