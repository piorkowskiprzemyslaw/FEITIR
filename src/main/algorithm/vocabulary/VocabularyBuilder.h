//
// Created by Przemek Piórkowski on 04.04.2016.
//

#ifndef FEITIR_VOCABULARY_H
#define FEITIR_VOCABULARY_H

#include <iostream>
#include <vector>
#include "src/main/database/Database.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/database/category/Category.h"
#include "src/main/database/category/CategoryFactory.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"

namespace feitir {

    template <class Parameter, class Vocabulary>
    class VocabularyBuilder {
    protected:
        const CategoryFactory categoryFactory;
        const DatabaseFactory databaseFactory;
        const ImageFactory imageFactory;
        cv::BFMatcher matcher;

        virtual ImagePtr processImage(const Vocabulary vocabulary, const ImagePtr image) const {
            std::vector<cv::DMatch> matches;
            matcher.match(image->getDescriptors(), vocabulary->getVocabularyMatrix(), matches);
            ImageBSIFTPtr bsiftPtr = std::dynamic_pointer_cast<ImageBSIFT>(image);

            if (bsiftPtr != nullptr) {
                return std::make_shared<ImageBSIFT>(bsiftPtr, std::forward<std::vector<cv::DMatch>>(matches));
            }

            return imageFactory.createImage(image, std::forward<std::vector<cv::DMatch>>(matches));
        }

    public:
        virtual ~VocabularyBuilder() {

        }

        virtual Vocabulary build(Parameter parameter) = 0;

        virtual void saveToFile(Vocabulary vocabulary, const std::string& file) const = 0;

        virtual Vocabulary readFromFile(const std::string& file) const = 0;

        virtual DatabasePtr transformDatabase(const Vocabulary vocabulary, const DatabasePtr database) const {
            std::vector<ImagePtr> rootImage;
            for (const auto& image : database->getImages()) {
                ImagePtr img = processImage(vocabulary, image);
                if (img != nullptr) {
                    rootImage.push_back(img);
                }
            }

            std::vector<CategoryPtr> categories;
            for (const auto& category : database->getCategories()) {
                std::vector<ImagePtr> images;
                for (const auto& image : category->getImages()) {
                    ImagePtr img = processImage(vocabulary, image);
                    if (img != nullptr) {
                        images.push_back(img);
                    }
                }
                categories.push_back(categoryFactory.createCategory(category,
                                                                    std::forward<std::vector<ImagePtr>>(images)));
            }

            return databaseFactory.createDatabase(database,
                                                  std::forward<std::vector<CategoryPtr>>(categories),
                                                  std::forward<std::vector<ImagePtr>>(rootImage));
        }
    };
}


#endif //FEITIR_VOCABULARY_H
