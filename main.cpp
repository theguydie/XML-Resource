#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <memory>

/*XML resource
����� �� ����� ��������� �-�����
���� ����������� ��������� � ��������� ������ �� xml
����� ����� find (name/value), ���������� iterator
����� ����� add (name + value, iterator) � ���������� �������� �� ����������� �������
Erase � ���������� bool, ��������� iterator
����� ��������� strong exception guarantee*/

#include "XMLTree.h"

int main()
{

    auto XML_resource = XML_Tree::create("resource.xml");

    //test throwing exception
    try {
        auto XML_resource = XML_Tree::create("incorrect.xml");
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Output using my iterator" << std::endl;
    for (auto it = XML_resource->begin(); it != XML_resource->end(); ++it)
    {
        std::cout << "name: [" << it->getName() << "] value: [" << it->getValue() << "]" << std::endl;
    }

    //add/erase/find
    XML_resource->add("CHILD3", "value=6", XML_resource->begin());

    XML_resource->erase(XML_resource->find("HEAD", "value=1"));

    std::cout << "One more using iterator to output what we have after our manipulations" << std::endl;
    for (auto it = XML_resource->begin(); it != XML_resource->end(); ++it)
    {
        std::cout << "name: [" << it->getName() << "] value: [" << it->getValue() << "]" << std::endl;
    }

    return 0;
}