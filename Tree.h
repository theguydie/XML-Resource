#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <queue>

class Node {
private:
	std::string name, value;
	std::vector<std::unique_ptr<Node>> children;
	void addChild(std::unique_ptr<Node> child) { children.push_back(std::move(child)); }
    friend class Tree;
public:
	Node(const std::string& _name, const std::string& _value) : name(_name), value(_value) {}

	std::string getName() const noexcept { return name; }
	std::string getValue() const noexcept { return value; }

	bool IfNoChild() { return children.empty(); }
	std::size_t childAmount() const noexcept { return children.size(); }
};

class Tree {
private:
	std::unique_ptr<Node> head;

public:
    Tree(const std::string& _name, const std::string& _data) { head = std::make_unique<Node>(_name, _data); }
    Tree() = default;

	//iterator as class
    class Iterator
    {
    public:

        Iterator(Node* _nodePtr) : nodePtr(_nodePtr) {}

        Iterator& operator++()
        {
            addNextIters();
            if (nextNodes.empty())
            {
                nodePtr = nullptr;
            }
            else
            {
                nodePtr = nextNodes.front();
                nextNodes.pop();
            }
            return *this;
        }

        Node& operator*() noexcept
        {
            return *nodePtr;
        }

        Node* operator->() noexcept
        {
            return nodePtr;
        }

        const Node* operator->() const noexcept
        {
            return nodePtr;
        }

        bool operator==(const Iterator& other) const noexcept
        {
            return nodePtr == other.nodePtr;
        }

        bool operator!=(const Iterator& other) const noexcept
        {
            return nodePtr != other.nodePtr;
        }

    private:
        Node* nodePtr;

        //WFS
        std::queue<Node*> nextNodes;
        void addNextIters()
        {
            if (nodePtr == nullptr)
                return;

            for (auto it = nodePtr->children.begin(); it != nodePtr->children.end(); ++it)
            {
                nextNodes.push(it->get());
            }
        }
    };

    //iterators in class Tree

    Iterator begin() const noexcept { return Iterator{ head.get() };}

    Iterator end() const noexcept { return Iterator{ nullptr }; }

    Iterator add(const std::string& _name, const std::string& _data, Iterator member = Iterator{ nullptr })
    {
        if (head == nullptr)
        {
            head = std::make_unique<Node>(std::move(_name), std::move(_data));
            return Iterator{ head.get() };
        }

        auto child = std::make_unique<Node>(std::move(_name), std::move(_data));
        Iterator it{ child.get() };

        if (member == end())
        {
            head->addChild(std::move(child));
        }
        else
        {
            member->addChild(std::move(child));
        }

        return it;
    }

    bool erase(Iterator member)
    {
        if (!head)
            return false;

        if (member == begin()) // delete root case
        {
            if (head->IfNoChild())
            {
                head.reset();
            }
            else
            {
                auto& tmpChildren = head->children;
                auto tmp = std::move(tmpChildren.back());
                for (std::size_t idx = 0; idx < tmpChildren.size() - 1; ++idx)
                {
                    tmp->children.push_back(std::move(tmpChildren[idx]));
                }
                head.reset();
                head = std::move(tmp);
            }
            return true;
        }

        for (auto it = begin(); it != end(); ++it)
        {
            auto childIt = it;
            for (std::size_t c = 0; c < it->childAmount(); ++c)
            {
                if (++childIt == member)
                {
                    for (auto& elem : member->children)
                    {
                        it->children.push_back(std::move(elem));
                    }
                    it->children.erase(it->children.begin() + c);
                    return true;
                }
            }
        }
        return false;
    }
};