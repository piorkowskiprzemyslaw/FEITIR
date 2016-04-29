//
// Created by Przemek Piórkowski on 07.04.2016.
//

#include "DatabaseTranslator.h"

namespace feitir {

    DatabaseTranslator::DatabaseTranslator() { }

    DatabaseTranslator::~DatabaseTranslator() { }

    DatabasePtr DatabaseTranslator::transformDatabase(const VocabularyTypePtr vocabulary,
                                                      const DatabasePtr database) const {
        std::vector<ImagePtr> rootImage;
        for (const auto& image : database->getImages()) {
            ImagePtr img = transformImage(vocabulary, image);
            if (img != nullptr) {
                rootImage.push_back(img);
            }
        }

        std::vector<CategoryPtr> categories;
        for (const auto& category : database->getCategories()) {
            CategoryPtr categoryPtr = transformCategory(vocabulary, category);
            if(categoryPtr != nullptr) {
                categories.push_back(categoryPtr);
            }
        }

        return databaseFactory.createDatabase(database,
                                              std::move(categories),
                                              std::move(rootImage));
    }

    CategoryPtr DatabaseTranslator::transformCategory(const VocabularyTypePtr vocabulary,
                                                      const CategoryPtr category) const {
        std::vector<ImagePtr> images;
        for (const auto& image : category->getImages()) {
            ImagePtr img = transformImage(vocabulary, image);
            if (img != nullptr) {
                images.push_back(img);
            }
        }
        return categoryFactory.createCategory(category, std::move(images));
    }

    ImagePtr DatabaseTranslator::transformImage(const VocabularyTypePtr vocabulary, const ImagePtr image) const {
        return imageFactory.createImage(image, std::move(vocabulary->getNearestVisualWords(image->getDescriptors())));
    }
}