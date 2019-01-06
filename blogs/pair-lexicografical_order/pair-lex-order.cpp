#include <iostream>
#include <map>
#include <tuple>
#include <assert.h>

/**
 *  The code below is a copy of https://blogs.msdn.microsoft.com/oldnewthing/20181226-00/?p=100565
 */


/*
 * Data structure that holds inforamtion about supported version for
 * different software components.
 */
using ComponentId = unsigned;
std::map<ComponentId, std::pair<int/*MajorVersion*/, int/*MinorVersion*/>> requiredVersions;

/*
 * Not very good implementation because in does lexigr. checking by hand and
 * it is bug prone.
 */
bool IsSupported_1(ComponentId id, std::pair<int, int> actualVersion)
{
    auto item = requiredVersions.find(id);
        if (item == requiredVersions.end()) {
        return true;
    }

    auto& requiredVersion = item->second;

    if (actualVersion.first > requiredVersion.first ||
            (actualVersion.first == requiredVersion.first &&
            actualVersion.second >= requiredVersion.second)) {
        return true;
    }

    return false;
}

/*
 * Much better implementation because it uses the fact that pair has default impl.
 * for operator <.
 */
bool IsSupported_2(ComponentId id, std::pair<int, int> actualVersion)
{
    auto item = requiredVersions.find(id);
        if (item == requiredVersions.end()) {
        return true;
    }

    auto& requiredVersion = item->second;

    if (actualVersion >= requiredVersion) {
        return true;
    }

    return false;
}

int main()
{
    requiredVersions.insert({1, {4,2}});
    requiredVersions.insert({11, {5,3}});
    requiredVersions.insert({22, {6,1}});
    
    assert(IsSupported_1(12, {5, 6}) == true);
    assert(IsSupported_1(11, {5, 6}) == true);
    assert(IsSupported_1(11, {6, 0}) == true);
    assert(IsSupported_1(11, {4, 99}) == false);

    assert(IsSupported_2(12, {5, 6}) == true);
    assert(IsSupported_2(11, {5, 6}) == true);
    assert(IsSupported_2(11, {6, 0}) == true);
    assert(IsSupported_2(11, {4, 99}) == false);

    std::cout << "Program successfully finished\n";
    return 0;
}