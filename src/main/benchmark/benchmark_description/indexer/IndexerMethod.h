//
// Created by Przemek Piórkowski on 21.07.2016.
//

#ifndef FEITIR_INDEXERMETHODDESCRIPTION_H
#define FEITIR_INDEXERMETHODDESCRIPTION_H

#include <src/main/util/JSON/JSONObject.h>

namespace feitir {

    /**
     * Class which represents indexer method description.
     * Holds all parameters required for correct setup of any indexer object.
     *
     * Supported indexer methods:
     *  - inverted_file
     *  - cross_indexer
     *  - binary_inverted_file
     *  - supporting_words_inverted_file
     *
     */
    class IndexerMethod : public JSONObject  {
    public:

        /**
         * String holding indexer method name
         * @return methodName
         */
        const string &getMethodName() const;

        /**
         * String holding path to vocabulary created on training dataset
         * @return vocabularyPath
         */
        const string &getVocabularyPath() const;

        /**
         * String holding vocabulary type
         * @return vocabularyType
         */
        const string &getVocabularyType() const;

        /**
         * String holding path to training dataset
         * @return databasePath
         */
        const string &getDatabasePath() const;

        /**
         * Number holding threshold for acceptable distance
         * between two BSIFT descriptors to treat them as a match.
         * @return threshold
         */
        number getThreshold() const;

        /**
         * Number holding k parameter value used in Supporting Words Inverted File Indexer
         * @return K
         */
        number getK() const;

        /**
         * Number holding N parameter value used in Cross Indexer
         * @return N
         */
        number getN() const;

        /**
         * Number holding R parameter value used in Cross Indexer
         * @return R
         */
        number getR() const;

        /**
         * Number holding P parameter value used in Supporting Words Inverted File Indexer
         * @return P
         */
        number getP() const;

        /**
         * Number holding code word size used in Cross Indexer
         * @return codeWordSize
         */
        number getCodeWordSize() const;

    protected:
        virtual JSONObjectPtr constructNewObject() const override;

        virtual FieldNames basicFieldNames() const override;

        virtual void setBasicFields(const ValuesMap &valuesMap) override;

    private:
        static const std::vector<std::string> FIELD_NAMES;
        string methodName;
        string vocabularyPath;
        string vocabularyType;
        string databasePath;
        number threshold;
        number K;
        number N;
        number R;
        number P;
        number codeWordSize;

    };

    using IndexerMethodPtr = std::shared_ptr<IndexerMethod>;
}


#endif //FEITIR_INDEXERMETHODDESCRIPTION_H
