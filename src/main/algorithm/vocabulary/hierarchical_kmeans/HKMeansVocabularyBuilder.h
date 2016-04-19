//
// Created by Przemek Piórkowski on 18.04.2016.
//

#ifndef FEITIR_HKMEANSVOCABULARYBUILDER_H
#define FEITIR_HKMEANSVOCABULARYBUILDER_H

#include "HKMeansConfig.h"
#include "src/main/algorithm/vocabulary/VocabularyBuilder.h"

namespace feitir {

    class HKMeansVocabularyBuilder : public VocabularyBuilder<HKMeansParameterPtr, HKMeansVocabularyTypePtr> {
    public:
        static const std::string VOCABULARY_FILE_K;
        static const std::string VOCABULARY_FILE_L;
        static const std::string VOCABULARY_FILE_NODE_NAME;

        explicit HKMeansVocabularyBuilder() = default;
        virtual ~HKMeansVocabularyBuilder() = default;
        virtual HKMeansVocabularyTypePtr build(HKMeansParameterPtr parameter);
        virtual void saveToFile(HKMeansVocabularyTypePtr vocabulary, const std::string &file) const;
        virtual HKMeansVocabularyTypePtr readFromFile(const std::string &file) const;

    protected:
        HKMeansNodePtr buildVocabularyNode(cv::Mat data, HKMeansNodeWeakPtr parent, unsigned K, unsigned L);
        int saveVocabularyNodeToFile(HKMeansNodePtr root, cv::FileStorage &fs, int nodeNumber) const;
    };

}


#endif //FEITIR_HKMEANSVOCABULARYBUILDER_H
