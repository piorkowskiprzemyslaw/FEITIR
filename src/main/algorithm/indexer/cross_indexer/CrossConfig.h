//
// Created by Przemek Piórkowski on 07.07.2016.
//

#ifndef FEITIR_CROSSCONFIG_H
#define FEITIR_CROSSCONFIG_H

#include "src/main/algorithm/indexer/Indexer.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/database/Database.h"

namespace feitir {

    class CrossParameters : public IndexerParameters {
    private:
        DatabasePtr database;
        VocabularyTypePtr vocabulary;
        int N;
        int R;
        int codeWordSize;
        int binaryTreshold;

    public:
        CrossParameters(const DatabasePtr &database, const VocabularyTypePtr vocabulary, const int N,
                        const int binaryTreshold, const int R = 1, const int codeWordSize = 32);
        const DatabasePtr & getDatabase() const;
        int getN() const;
        int getR() const;
        VocabularyTypePtr getVocabulary() const;
        int getCodeWordSize() const;
        int getBinaryTreshold() const;
        virtual ~CrossParameters() = default;
    };

    class CrossQuery : public IndexerQuery {
    private:
        ImageBSIFTPtr img;

    public:
        CrossQuery(const ImageBSIFTPtr &img);
        const ImageBSIFTPtr getImg() const;
        virtual ~CrossQuery() = default;
    };

    typedef std::pair<ImagePtr, ResultCountT> CrossResultEntry;

    class CrossResult : public IndexerResult {
    private:
        std::vector<CrossResultEntry> images;
    public:
        CrossResult() = default;
        void addResultEntry(CrossResultEntry element);
        const std::vector<CrossResultEntry> & getImages() const;
        virtual ~CrossResult() = default;
    };


    typedef std::shared_ptr<CrossResult> CrossResultPtr;

    typedef std::shared_ptr<CrossQuery> CrossQueryPtr;

    typedef std::shared_ptr<CrossParameters> CrossParametersPtr;
}


#endif //FEITIR_CROSSCONFIG_H
