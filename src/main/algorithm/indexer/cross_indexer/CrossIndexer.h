//
// Created by Przemek Piórkowski on 08.07.2016.
//

#ifndef FEITIR_CROSSINDEXER_H
#define FEITIR_CROSSINDEXER_H

#include "src/main/algorithm/indexer/Indexer.h"
#include <unordered_map>
#include <vector>
#include <opencv2/features2d.hpp>

#include "CrossConfig.h"

namespace feitir {

    /**
     * Implementation of Cross Indexer algorithm
     */
    class CrossIndexer : public Indexer<CrossResultPtr, CrossQueryPtr, CrossParametersPtr> {
    public:
        template <typename... Ts> CrossIndexer(Ts&&... args)
                : Indexer{std::make_shared<CrossParameters>(std::forward<Ts>(args)...)},
                  parameters{std::make_shared<CrossParameters>(std::forward<Ts>(args)...)} {
            setupIndexer();
        }

        explicit CrossIndexer(const CrossParametersPtr &parameters);

        virtual CrossResultPtr query(CrossQueryPtr query) override;

        /**
         * Extracts codeword from binary SIFT descriptor value. Length depends on indexer parameter - codeWordSize.
         * This method is public onfy for testing purposes.
         * @param bsift Binary SIFT descriptor
         * @return
         */
        ImageBSIFT::BSIFT generateCodeWord(const ImageBSIFT::BSIFT& bsift);

        /**
         * Performs R bit codeword expansion where n denotes parameter passed to indexer.
         * @param codeWord
         * @return
         */
        std::vector<ImageBSIFT::BSIFT> expandCodeWord(const ImageBSIFT::BSIFT &codeWord);

        /**
         * Performs expansionSize bit codeword expansion.
         * @param codeWord
         * @param expansionSize
         * @return
         */
        std::vector<ImageBSIFT::BSIFT> expandCodeWord(const ImageBSIFT::BSIFT &codeWord, const size_t expansionSize);

    protected:
        /**
         * setup indexer
         */
        void setupIndexer();

        /**
         * Performs code word cell check
         * @param queryBSIFT
         * @param codeWord
         * @param V
         * @param visitedV
         */
        void codeWordCellCheck(const ImageBSIFT::BSIFT &queryBSIFT, const ImageBSIFT::BSIFT &codeWord,
                               std::unordered_set<int> &V, std::unordered_set<int> &visitedV) const;

    private:
        const cv::BFMatcher matcher;
        const CrossParametersPtr parameters;
        std::unordered_map<boost::uuids::uuid, ImageBSIFTPtr> uuidToImg;
        std::unordered_multimap<int, std::tuple<ImageBSIFTPtr, ImageBSIFT::BSIFT>> visualWordIndex;
        std::unordered_multimap<ImageBSIFT::BSIFT, std::tuple<int, ImageBSIFT::BSIFT>> codeWordIndex;
        std::vector<std::vector<cv::DMatch>> nearestVW;

        std::set<size_t> allPositionsSet() const;
    };

}



#endif //FEITIR_CROSSINDEXER_H
