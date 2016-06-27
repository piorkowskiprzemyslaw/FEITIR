//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include "IFConfig.h"

namespace feitir {

    IFParameters::IFParameters(const DatabasePtr &database, const MatchingFunc &matchingFunction)
            : database{database}, matchingFunction{matchingFunction} { }

    const DatabasePtr &IFParameters::getDatabase() const {
        return database;
    }

    MatchingFunc IFParameters::getMatchingFunction() const {
        return this->matchingFunction;
    }

    IFQuery::IFQuery(const ImagePtr &img) : img(img) { }

    const ImagePtr IFQuery::getImg() const {
        return img;
    }

    IFResult::IFResult() { }

    const std::vector<IFResultEntry> &IFResult::getImages() const {
        return images;
    }

    void IFResult::addResultEntry(std::pair<ImagePtr, float> element) {
        this->images.push_back(std::move(element));
    }
}