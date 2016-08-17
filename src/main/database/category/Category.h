//
// Created by Przemek Piórkowski on 07.03.2016.
//

#ifndef FEITIR_CATEGORY_H
#define FEITIR_CATEGORY_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "src/main/database/image/Image.h"

namespace feitir {

    class Category {
    public:
        Category(const std::string &name, const std::string &path, std::vector<ImagePtr> images);
        const boost::uuids::uuid &getUuid() const;
        const std::string & getName() const;
        const std::string & getPath() const;
        const std::vector<ImagePtr> & getImages() const;

        /**
         * Const iterator implementation
         */
        class const_iterator : public std::iterator<std::forward_iterator_tag, ImagePtr> {
        public:
            const_iterator() = default;

            explicit inline const_iterator(std::vector<ImagePtr>::const_iterator it) : innerIterator{it} { }

            inline const_iterator(const const_iterator& it) : innerIterator{it.innerIterator} { }

            inline const_iterator& operator=(const const_iterator& it) {
                innerIterator=it.innerIterator;
                return *this;
            }

            inline ImagePtr operator*() {
                return *innerIterator;
            }

            inline const_iterator& operator++() {
                innerIterator++;
                return *this;
            }

            inline const_iterator& operator++(int) {
                innerIterator++;
                return *this;
            }

            inline bool operator==(const const_iterator& other) {
                return innerIterator == other.innerIterator;
            }

            inline bool operator!=(const const_iterator& other) {
                return innerIterator != other.innerIterator;
            }

        private:
            std::vector<ImagePtr>::const_iterator innerIterator;
        };

        const_iterator begin() const;
        const_iterator end() const;

    private:
        const boost::uuids::uuid uuid;
        const std::string name;
        const std::string path;
        const std::vector<ImagePtr> images;
    };

    typedef std::shared_ptr<Category> CategoryPtr;

}


#endif //FEITIR_CATEGORY_H
