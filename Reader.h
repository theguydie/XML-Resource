#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

struct Reader
{
public:
    static std::vector<std::pair<std::string, std::string>> takeData(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("File open error");
        }

        std::vector<std::pair<std::string, std::string>> tokenz1;
        std::string token;
        std::getline(file, token, '<');
        while (std::getline(file, token, '<'))
        {
            auto sep = token.find('>');

            if (sep == std::string::npos)
            {
                throw std::runtime_error("XML_Tree structure error");
            }

            std::string name = token.substr(0, sep);

            if (name[0] == '/') { tokenz1.push_back(std::pair<std::string, std::string>{"", ""}); continue; } // add empty space to the end

            std::string data = token.substr(sep + 1);

            if (name.empty() || data.empty())
            {
                throw std::runtime_error("XML_Tree structure error");
            }

            //for better visualization, without spaces, tabs and endlines
            deleteAllSpaces(name);
            deleteAllSpaces(data);

            std::pair<std::string, std::string> XMLdata{ std::move(name), std::move(data) };

            tokenz1.push_back(std::move(XMLdata));
        }

        return tokenz1;
    }

    static void deleteAllSpaces(std::string& str) noexcept
    {
        while (!str.empty() && (str.back() == ' ' || str.back() == '\n' || str.back() == '\t'))
        {
            str.pop_back();
        }
        int i = 0;
        while (!str.empty() && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
        {
            i++;
        }
        if (i)
        {
            str = str.substr(i);
        }
    }
};