#include "common.h"
using namespace std;

bool debug = false;

struct PalindromInfo
{
    size_t indexOfCenter;
    size_t length;
};

bool inBounds(size_t index1, size_t index2, size_t size)
{
    if (index1 > 0 && index1 < size && index2 > 0 && index2 < size)
        return true;
    return false;
}
struct InitPalindromInfo
{
    bool isPotential = false;
    size_t prev;
    size_t next;
    size_t index;
    size_t length;
};

InitPalindromInfo isPotentialPalindrom(const string & palindroms, size_t i)
{
    auto prev = i;
    auto next = i + 1;
    if (inBounds(prev, next, palindroms.size()) && palindroms[prev] == palindroms[next])
        return {true, prev, next, i + 1, 0};
    --prev;
    if (inBounds(prev, next, palindroms.size()) && palindroms[prev] == palindroms[next])
        return {true, prev, next, i, 1};
    return {false, 0, 0, 0, 0};
}

PalindromInfo findCenterOfLongestPalindrom(const string & palindroms)
{
    size_t indexCenterMaxPalindrom = 0;
    size_t lengthMaxPalindrom = 0;
    for (size_t i = 1; i < palindroms.size() - 1; ++i)
    {
        auto initInfo = isPotentialPalindrom(palindroms, i);
        if (initInfo.isPotential)
        {
            while(inBounds(initInfo.prev, initInfo.next, palindroms.size()) && palindroms[initInfo.prev] == palindroms[initInfo.next])
            {
                initInfo.length += 2;
                --initInfo.prev;
                ++initInfo.next;
            }

            if (initInfo.length > lengthMaxPalindrom)
            {
                lengthMaxPalindrom = initInfo.length;
                indexCenterMaxPalindrom = initInfo.index;
            }
        }
    }

    return { indexCenterMaxPalindrom, lengthMaxPalindrom };
}

string longestPalindrom(const string & palindroms)
{
    auto result = findCenterOfLongestPalindrom(palindroms.c_str());
    return palindroms.substr(result.indexOfCenter - result.length/2, result.length );
}

int main()
{    
    auto stringWithPalindroms = "acaestotseperonotdasdijokgasdmmkmkmkxxxxxxxxxxxxxxxxxxxxxxxxxzzzzzwwww";
    //auto stringWithPalindroms = "1235üpacchhccd87953i";
    cout<<"Longest palindrom in "<<stringWithPalindroms<<endl;
    auto result = longestPalindrom(stringWithPalindroms);
    cout<<result<< " with length "<< result.size()<<endl;
}
