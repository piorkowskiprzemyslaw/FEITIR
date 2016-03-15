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
                           return categoryFactory.createCategory(path, !nestedCategories);
                        });

        std::list<std::string> rootImages = findRootImages(rootDir);
        std::vector<ImagePtr> images;
        std::transform(rootImages.begin(), rootImages.end(), back_inserter(images),
                        [&](const std::string &path) {
                           return imageFactory.createImage(path);
                        });

        return std::make_shared<Database>(rootDir, std::move(categories), std::move(images));
    }

    std::list<std::string> DatabaseFactory::findCategoriesRoots(const std::string &root, bool nestedCategories) const {
        return findInDirectory(root, nestedCategories, [] (const boost::filesystem::path &path) {
            return boost::filesystem::is_directory(path);
        });
    }

    std::list<std::string> DatabaseFactory::findRootImages(const std::string &root) const {
        return findInDirectory(root, false, [] (const boost::filesystem::path &path) {
            return boost::filesystem::is_regular_file(path);
        });
    }

    template<class Predicate>
    std::list<std::string> DatabaseFactory::findInDirectory(const std::string &root, bool findRecursive,
                                                            Predicate pred) const {
        std::list<std::string> result;
        if (boost::filesystem::is_directory(root)) {
            std::vector<boost::filesystem::path> paths;
            std::copy(boost::filesystem::directory_iterator(root),
                      boost::filesystem::directory_iterator(),
                      back_inserter(paths));

            for (auto& path: paths) {
                if (pred(path)) {
                    result.push_back(path.native());
                    if (findRecursive) {
                        std::list<std::string> nestedCategoriesNames = findInDirectory(path.native(),
                                                                                       findRecursive, pred);
                        std::copy(nestedCategoriesNames.begin(), nestedCategoriesNames.end(),
                                  back_inserter(result));
                    }
                }
            }
        }
        return result;
    }
}