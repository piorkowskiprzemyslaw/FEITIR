//
// Created by Przemek Piórkowski on 17.03.2016.
//

#ifndef FEITIR_UTIL_H
#define FEITIR_UTIL_H

#include <list>
#include <vector>
#include <boost/filesystem.hpp>
#include <bitset>

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

        template <class T, class RT = T>
        RT median(std::vector<T>& v) {
            return median(v, std::greater<T>());
        }

        template <class T, class Compare, class RT = T>
        RT median(std::vector<T>& v, Compare compare) {
            typename std::vector<T>::size_type s = v.size();
            if (s & 0x1) {
                std::nth_element(v.begin(), v.begin() + s/2, v.end(), compare);
                return static_cast<RT>(v[s/2]);
            } else {
                std::nth_element(v.begin(), v.begin() + s/2, v.end(), compare);
                std::nth_element(v.begin(), v.begin() + s/2 - 1, v.begin() + s/2, compare);
                return (static_cast<RT>(v[s/2]) + static_cast<RT>(v[s/2 - 1]))/2;
            }
        }

        template <class T, class RT = T>
        RT median(const std::vector<T>& v) {
            std::vector<T> localCopy{v};
            return median<T, RT>(localCopy);
        }

        template <std::size_t N>
        auto hammingDistance(std::bitset<N> a, std::bitset<N> b) const -> decltype(a.count()) {
            return (a ^ b).count();
        }
    };

}

#endif //FEITIR_FEITIRUTIL_H
