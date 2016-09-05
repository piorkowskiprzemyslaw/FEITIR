//
// Created by Przemek Piórkowski on 05.09.2016.
//

#ifndef FEITIR_IFSCONFIG_H
#define FEITIR_IFSCONFIG_H

#include <src/main/algorithm/indexer/IndexerConfig.h>

namespace feitir {

    class IFSParameters : public IndexerParameters {
    private:
        const DatabasePtr databaseWithOriginalValues;
        const int threshold;

    public:
        IFSParameters(const DatabasePtr database, const int threshold);
        virtual DatabasePtr getDatabase() override;
        const int getThreshold() const;
        virtual ~IFSParameters() = default;
    };

    class IFSQuery : public IndexerQuery {
    private:
        ImagePtr imageWithOriginalValues;
    public:
        IFSQuery(const ImagePtr img) :imageWithOriginalValues{img} {
            assert (img->getDescriptors().rows > 0);
            assert (img->getMatches().size() > 0);
        }

        virtual ImagePtr getImg() override {
            return imageWithOriginalValues;
        }

        virtual ~IFSQuery() = default;
    };

    using IFSQueryPtr = std::shared_ptr<IFSQuery>;

    using IFSParametersPtr = std::shared_ptr<IFSParameters>;
}


#endif //FEITIR_IFSCONFIG_H
