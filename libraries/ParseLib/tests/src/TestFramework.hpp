#pragma once

#include <gtest/gtest.h>

class LucTestFramework : public ::testing::Test
{
public:
    static void SetPath(std::string new_path)
    {
        root = new_path;
    }

    static std::string path(std::string relative_path)
    {
        std::string path_buffer = root;
        path_buffer.append(relative_path);
        std::cout << "Path used: " << path_buffer << std::endl;
        return path_buffer;
    }
protected:
    static std::string root;

};

std::string LucTestFramework::root = "";