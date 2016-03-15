//
// Created by Przemek Piórkowski on 07.03.2016.
//

#ifndef FEITIR_DATABASE_H
#define FEITIR_DATABASE_H

#include <iostream>
#include <vector>
#include <memory>
#include <src/main/database/category/Category.h>

namespace feitir {

    class Database {
    private:
        const std::string rootPath;
        const std::vector<CategoryPtr> categories;
        const std::vector<ImagePtr> images;

    protected:

    public:
        Database(const std::string &rootPath,
                 const std::vector<CategoryPtr> &&categories,
                 const std::vector<ImagePtr> &&images);
        const std::string & getRootPath() const;
        const std::vector<CategoryPtr> & getCategories() const;
        const std::vector<ImagePtr> & getImages() const;
    };

    typedef std::shared_ptr<Database> DatabasePtr;
}


#endif //FEITIR_DATABASE_H
