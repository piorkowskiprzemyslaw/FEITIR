//
// Created by Przemek Piórkowski on 17.03.2016.
//

#ifndef FEITIR_UTIL_H
#define FEITIR_UTIL_H

#include <list>
#include <vector>
#include <numeric>
#include <boost/filesystem.hpp>
#include <boost/dynamic_bitset.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>

namespace feitir {

    class Util {
    private:
    protected:
    public:
        Util();

        template <class Predicate>
        static std::list<std::string> findInDirectory(const std::string &root, bool findRecursive, Predicate pred) {
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
        static RT median(std::vector<T>& v) {
            return Util::median(v, std::greater<T>());
        }

        template <class T, class Compare, class RT = T>
        static RT median(std::vector<T>& v, Compare compare) {
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
        static RT median(const std::vector<T>& v) {
            std::vector<T> localCopy{v};
            return Util::median<T, RT>(localCopy);
        }

        static auto hammingDistance(boost::dynamic_bitset<> a, boost::dynamic_bitset<> b) -> decltype(a.count()) {
            return (a ^ b).count();
        }


        static float euclideanDistance(cv::Mat a, cv::Mat b) {
            assert (a.cols == b.cols);
            assert (a.rows == b.rows);
            assert (a.rows == 1);
            std::vector<float> aVec, bVec, result;
            a.copyTo(aVec);
            b.copyTo(bVec);

            std::transform(aVec.begin(), aVec.end(), bVec.begin(), std::back_inserter(result),
                           [&](float aVal, float bVal) {
                return (aVal-bVal) * (aVal-bVal);
            });

            return static_cast<float>(sqrt(std::accumulate(result.begin(), result.end(), 0.0f)));
        }

        static std::vector<float> euclideanDistanceVector(cv::Mat a, cv::Mat b) {
            assert (a.cols == b.cols && a.rows == b.rows);
            cv::Mat pow, sub = a - b;
            cv::multiply(sub, sub, pow);
            assert (a.rows == pow.rows);
            std::vector<float> result;

            for (int i = 0; i < pow.rows; ++i) {
                float tmp = 0;
                for (int j = 0; j < pow.cols; ++j) {
                    tmp += pow.at<float>(i, j);
                }
                result.push_back(static_cast<float>(sqrt(tmp)));
            }

            return result;
        }
    };

}

#endif //FEITIR_FEITIRUTIL_H
