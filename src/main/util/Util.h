//
// Created by Przemek Piórkowski on 17.03.2016.
//

#ifndef FEITIR_UTIL_H
#define FEITIR_UTIL_H

#include <iostream>
#include <list>
#include <boost/filesystem.hpp>

namespace feitir {

    class Util {
    private:
    protected:
    public:
        Util();

        template <class Predicate>
        std::list<std::string> findInDirectory(const std::string &root, bool findRecursive, Predicate pred) const {
            std::list<std::string> result;
            if (boost::filesystem::is_directory(root)) {
                std::vector<boost::filesystem::path> paths;
                std::copy(boost::filesystem::directory_iterator(root),
                          boost::filesystem::directory_iterator(),
                          back_inserter(paths));

                for (auto& path: paths) {
                    if (pred(path)) {
                        result.push_back(path.native());
                    }

                    if (findRecursive && boost::filesystem::is_directory(path)) {
                        std::list<std::string> nestedCategoriesNames = findInDirectory(path.native(),
                                                                                       findRecursive, pred);
                        std::copy(nestedCategoriesNames.begin(), nestedCategoriesNames.end(),
                                  back_inserter(result));
                    }
                }
            }
            return result;
        }
    };

}

#endif //FEITIR_FEITIRUTIL_H
