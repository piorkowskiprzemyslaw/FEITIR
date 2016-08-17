//
// Created by Przemek Piórkowski on 07.03.2016.
//

#ifndef FEITIR_DATABASE_H
#define FEITIR_DATABASE_H

#include <iostream>
#include <vector>
#include <memory>
#include <src/main/database/category/Category.h>
#include <unordered_map>

namespace feitir {

    class Database {
    public:
        Database(const std::string &rootPath,
                 std::vector<CategoryPtr> categories,
                 std::vector<ImagePtr> images);
        const std::string & getRootPath() const;
        const std::vector<CategoryPtr> & getCategories() const;
        const std::vector<ImagePtr> & getImages() const;
        CategoryPtr getImageCategory(const ImagePtr img) const;
        CategoryPtr getCategoryByName(const std::string & name) const;

        /**
         * Const iterator implementation
         */
        class const_iterator : public std::iterator<std::forward_iterator_tag, ImagePtr> {
        public:
            const_iterator() = default;

            explicit inline const_iterator(const Database *database)
                    : currentVector{&(database->getImages())},
                      categories{&(database->getCategories())},
                      currentIterator{database->getImages().begin()},
                      nextCategory{database->getCategories().begin()} {
                if (database->getImages().empty()) {
                    for (auto it = database->getCategories().begin(); it != database->getCategories().end(); ++it) {
                        currentIterator = (*it)->getImages().begin();
                        currentVector = &((*it)->getImages());
                        nextCategory = it + 1;

                        if (!(*it)->getImages().empty()) break;
                    }
                }
            }

            inline const_iterator(const const_iterator& it)
                    : currentVector{it.currentVector},
                      categories{it.categories},
                      currentIterator{it.currentIterator},
                      nextCategory{it.nextCategory} { }

            inline const_iterator(const std::vector<ImagePtr> *currentVector,
                                  const std::vector<CategoryPtr> *categories,
                                  std::vector<ImagePtr>::const_iterator currentIterator,
                                  std::vector<CategoryPtr>::const_iterator nextCategory)
                    : currentVector{currentVector}, categories{categories},
                      currentIterator{currentIterator}, nextCategory{nextCategory} { }

            inline const_iterator& operator=(const const_iterator& it) {
                currentVector=it.currentVector;
                categories=it.categories;
                currentIterator=it.currentIterator;
                nextCategory=it.nextCategory;
                return *this;
            }

            inline ImagePtr operator*() {
                return *currentIterator;
            }

            inline const_iterator& operator++() {
                currentIterator++;

                if (currentVector == nullptr) {
                    return *this;
                }

                if (currentIterator != currentVector->end()) {
                    return *this;
                }

                if (nextCategory == categories->end()) {
                    return *this;
                }

                currentVector = &((*nextCategory)->getImages());
                ++nextCategory;
                currentIterator = currentVector->begin();

                return *this;
            }

            inline const_iterator& operator++(int) {
                return this->operator++();
            }

            inline const_iterator& operator+(unsigned offset) {
                while (offset--) {
                    this->operator++();
                }
                return *this;
            }

            inline bool operator==(const const_iterator& other) {
                return (currentIterator == other.currentIterator) && (other.nextCategory == nextCategory);
            }

            inline bool operator!=(const const_iterator& other) {
                return !(*this == other);
            }

        private:
            const std::vector<ImagePtr> *currentVector;
            const std::vector<CategoryPtr> *categories;
            std::vector<ImagePtr>::const_iterator currentIterator;
            std::vector<CategoryPtr>::const_iterator nextCategory;

        };

        const_iterator begin() const;
        const_iterator end() const;

    private:
        const std::string rootPath;
        const std::vector<CategoryPtr> categories;
        const std::vector<ImagePtr> images;
        // map which allows fast lookup for image category
        std::unordered_map<boost::uuids::uuid, CategoryPtr> imageUUIDToCategory;
        // map which allows fast category lookup by its name
        std::unordered_map<std::string, CategoryPtr> categoryNameToCategory;
    };

    typedef std::shared_ptr<Database> DatabasePtr;
}


#endif //FEITIR_DATABASE_H
