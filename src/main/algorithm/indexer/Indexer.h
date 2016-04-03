//
// Created by Przemek Piórkowski on 03.04.2016.
//

#ifndef FEITIR_INDEXER_H
#define FEITIR_INDEXER_H

#include <list>

namespace feitir {

    template <class Result, class Query, class Parameters>
    class Indexer {

    public:
        explicit Indexer(Parameters parameters) {

        }
        virtual Result query(Query query) = 0;
        virtual ~Indexer();
    };
}

#endif //FEITIR_INDEXER_H
