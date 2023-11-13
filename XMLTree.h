#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Tree.h"
#include "Reader.h"

class XML_Tree
{
public:
    static std::unique_ptr<XML_Tree> create(const std::string& path)
    {
        auto tokens = Reader::takeData(path);
        return std::unique_ptr<XML_Tree>(new XML_Tree{ tokens });
    }

    Tree::Iterator find(const std::string& name, const std::string& value) const noexcept
    {
        for (auto it = tree.begin(); it != tree.end(); ++it)
        {
            if (it->getName() == name && it->getValue() == value) { return it; }
        }

        return tree.end();
    }

    Tree::Iterator add(const std::string& name, const std::string& value, Tree::Iterator it)
    {
        return tree.add(name, value, it);
    }

    bool erase(Tree::Iterator eraseIt)
    {
        bool success = tree.erase(eraseIt);
        return success;
    }

    Tree::Iterator begin() const noexcept
    {
        return tree.begin();
    }

    Tree::Iterator end() const noexcept
    {
        return tree.end();
    }

private:
    Tree tree;

    XML_Tree(std::vector<std::pair<std::string, std::string>>& tokens)
    {
        auto tokenBegin = tokens.begin();
        auto tokenEnd = tokens.end();
        auto dataBegin = tree.begin();
        recursiveAdd(tokenBegin, tokenEnd, dataBegin);
    }

    using tokenIt = std::vector<std::pair<std::string, std::string>>::iterator;
    void recursiveAdd(tokenIt& it, tokenIt& tokenEnd, Tree::Iterator cur)
    {
        while (it != tokenEnd && !it->first.empty()) {
            auto childIt = tree.add(std::move(it->first), std::move(it->second), cur);
            recursiveAdd(++it, tokenEnd, childIt);
        }
        if (it != tokenEnd) ++it;
    }
};