//
// Created by Przemek Piórkowski on 14.03.2016.
//

#include "CategoryFactory.h"

namespace feitir {

    CategoryFactory::CategoryFactory() { }


    const CategoryPtr CategoryFactory::createCategory(const std::string &root, const std::string &path) const {
        return createCategory(root, path, true);
    }

    const CategoryPtr CategoryFactory::createCategory(const std::string &root, const std::string &path, bool findRecursive) const {
        std::string name = categoryName(root, path);
        std::list<std::string> paths = util.findInDirectory(path, findRecursive, [](const boost::filesystem::path &p) {
            return boost::filesystem::is_regular_file(p);
        });

        std::vector<ImagePtr> images;
        std::transform(paths.begin(), paths.end(), back_inserter(images),
            [&](const std::string &p) {
                return imageFactory.createImage(p);
            });
        images.erase(std::remove(images.begin(), images.end(), nullptr), images.end());

        if (images.size() == 0) {
            return nullptr;
        }

        return std::make_shared<Category>(name, path, std::move(images));
    }

    const CategoryPtr CategoryFactory::createCategory(const CategoryPtr category,
                                                      std::vector<ImagePtr> images) const {
        return std::make_shared<Category>(category->getName(), category->getPath(), std::move(images));
    }

    const std::string CategoryFactory::categoryName(const std::string &rootPath,
                                                    const std::string &categoryPath) const {
        std::string name = categoryPath;
        std::string::size_type n = categoryPath.find(rootPath);
        if (n != std::string::npos) {
            name.erase(n, n + rootPath.length());
        }
        return name;
    }
}