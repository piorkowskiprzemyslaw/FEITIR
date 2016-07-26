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
        size_t R;
        size_t codeWordSize;
        size_t binaryTreshold;
        MatchingFunc matchingFunc;

    public:
        CrossParameters(const DatabasePtr &database, const VocabularyTypePtr vocabulary,
                        const MatchingFunc &matchingFunction, const int N, const size_t binaryTreshold,
                        const size_t R = 1, const size_t codeWordSize = 32);
        const DatabasePtr & getDatabase() const;
        int getN() const;
        size_t getR() const;
        VocabularyTypePtr getVocabulary() const;
        size_t getCodeWordSize() const;
        size_t getBinaryTreshold() const;
        const MatchingFunc & getMatchingFunc() const;
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

    class CrossResult : public IndexerResult {
    private:
        std::vector<std::pair<ImagePtr, float>> images;
    public:
        CrossResult() = default;
        void addResultEntry(std::pair<ImagePtr, float> element);
        const std::vector<std::pair<ImagePtr, float>> & getImages() const;
        virtual ~CrossResult() = default;
    };

    typedef std::pair<ImagePtr, float> CrossResultEntry;

    typedef std::shared_ptr<CrossResult> CrossResultPtr;

    typedef std::shared_ptr<CrossQuery> CrossQueryPtr;

    typedef std::shared_ptr<CrossParameters> CrossParametersPtr;
}


#endif //FEITIR_CROSSCONFIG_H
