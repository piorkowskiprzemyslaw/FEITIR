//
// Created by Przemek Piórkowski on 11.03.2016.
//

#include "DatabaseFactory.h"

namespace feitir {

    DatabaseFactory::DatabaseFactory() { }

    const DatabasePtr DatabaseFactory::createDatabase(const std::string& rootDir) const {
        return createDatabase(rootDir, false);
    }

    const DatabasePtr DatabaseFactory::createDatabase(const std::string &rootDir, bool nestedCategories) const {
        std::list<std::string> categoriesRoots = findCategoriesRoots(rootDir, nestedCategories);
        std::vector<CategoryPtr> categories;
        std::transform(categoriesRoots.begin(), categoriesRoots.end(), back_inserter(categories),
                       [&](const std::string &path) {
                           return categoryFactory.createCategory(rootDir, path, !nestedCategories);
                       });

        std::list<std::string> rootImages = findRootImages(rootDir);
        std::vector<ImagePtr> images;
        std::transform(rootImages.begin(), rootImages.end(), back_inserter(images),
                        [&](const std::string &path) {
                           return imageFactory.createImage(path);
                        });
        images.erase(std::remove(images.begin(), images.end(), nullptr), images.end());

        return std::make_shared<Database>(rootDir, std::move(categories), std::move(images));
    }

    const DatabasePtr DatabaseFactory::createDatabase(const DatabasePtr database,
                                                      std::vector<CategoryPtr> categories,
                                                      std::vector<ImagePtr> images) const {
        return std::make_shared<Database>(database->getRootPath(), std::move(categories), std::move(images));
    }

    std::list<std::string> DatabaseFactory::findCategoriesRoots(const std::string &root, bool nestedCategories) const {
        return Util::findInDirectory(root, nestedCategories, [] (const boost::filesystem::path &path) {
            return boost::filesystem::is_directory(path);
        });
    }

    std::list<std::string> DatabaseFactory::findRootImages(const std::string &root) const {
        return Util::findInDirectory(root, false, [] (const boost::filesystem::path &path) {
            return boost::filesystem::is_regular_file(path);
        });
    }
}