#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

struct Pair
{
    std::string key;
    std::string value;
};

static const char ESCAPE_CH = '\\';
static const char DELIMITER_STRING_CH = '/';
static const char DELIMITER_PAIR_CH = '=';

std::list<std::string> parserOfString(const std::string &srcString);
std::vector<Pair> parserOfPair(const std::list<std::string> &listOfPair);

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "Not correct argument for program";
        return -1;
    }

    auto listOfStringsPairs = parserOfString(std::string(argv[1]) + '/');
    auto vectorOfPairs = parserOfPair(listOfStringsPairs);

    for(auto it : vectorOfPairs)
    {
        std::cout << it.key << "  " << it.value << std::endl;
    }
    return 0;
}

std::list<std::string> parserOfString(const std::string &srcString)
{
    std::list<std::string> result;
    std::string currentString = "";
    bool isEscapeCh = false;

    for(auto currentChar : srcString)
    {
        if(!isEscapeCh)
        {
            if(currentChar == ESCAPE_CH)
            {
                isEscapeCh = true;
                continue;
            }
            else if(currentChar == DELIMITER_STRING_CH)
            {
                if(!currentString.empty())
                {
                    result.push_back(currentString);
                    currentString = "";
                }
                continue;
            }
        }

        if(!(currentChar == ESCAPE_CH || currentChar == DELIMITER_STRING_CH) && isEscapeCh) //ошибка экранирования
            throw std::invalid_argument("Not correct escape character");

        currentString += currentChar;
        isEscapeCh = false;
    }

    return result;
}

std::vector<Pair> parserOfPair(const std::list<std::string> &listOfPair)
{
    std::vector<Pair> result(listOfPair.size());

    for(auto pair : listOfPair)
    {
        if(std::count(pair.begin(), pair.end(), '=') > 1)
            throw std::invalid_argument("Not correct pair in source string");

        Pair tmpPair = { pair.substr(0, pair.find(DELIMITER_PAIR_CH)),
                    pair.substr(pair.find(DELIMITER_PAIR_CH) + 1, pair.size() - 1)};

        result.push_back(tmpPair);
    }

    return result;
}