#include "Analyzer.h"

#include <algorithm>
#include <iostream>

void showFps(const std::vector<int>& fps)
{
    for (std::size_t i = 0; i < fps.size(); ++i)
    {
        std::cout << fps[i];

        if (i + 1 < fps.size())
        {
            std::cout << ", ";
        }
        else
        {
            std::cout << "\n";
        }
    }

    std::cout
        << "Medidas processadas: "
        << fps.size()
        << "\n";
}

void sortFps(std::vector<int>& fps)
{
    std::sort(
        fps.begin(),
        fps.end()
    );
}