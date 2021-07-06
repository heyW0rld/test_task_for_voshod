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

std::vector<Pair> parserOfPairs(const std::string &srcString);

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "Not correct argument for program";
        return -1;
    }

    auto listOfStringsPairs = parserOfPairs(std::string(argv[1]) + '/');

    for(auto it : listOfStringsPairs)
    {
        std::cout  << it.key << "  " << it.value << std::endl;
    }
    return 0;
}

std::vector<Pair> parserOfPairs(const std::string &srcString)
{
    std::list<Pair> listOfPairs;
    std::string currentString = "";
    bool isEscapeCh = false;

    std::string key, value;

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
                if(!currentString.empty() && !key.empty())
                {
                    value = currentString;
                    Pair tmpPair = {key, value};

                    listOfPairs.push_back(tmpPair);
                    currentString = "";
                    continue;
                }
                else
                {
                   throw std::invalid_argument("Not correct pair in source string1");
                }
            }
            else if(currentChar == DELIMITER_PAIR_CH)
            {
                if(!currentString.empty())
                {
                    key = currentString;
                    currentString = "";
                    continue;
                }
                else
                {
                    throw std::invalid_argument("Not correct pair in source string2");
                }
            }
        }

        if(!(currentChar == ESCAPE_CH || currentChar == DELIMITER_STRING_CH || currentChar == DELIMITER_PAIR_CH) && isEscapeCh) //ошибка экранирования
            throw std::invalid_argument("Not correct escape character");

        currentString += currentChar;
        isEscapeCh = false;
    }

    return std::vector<Pair> (listOfPairs.begin(), listOfPairs.end());
}
