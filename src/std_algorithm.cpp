#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"

#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

bool is_even(int i)
{
    return i % 2 == 0;
}

TEST_CASE("std::all_of") {
    // true case
    std::vector<int> all_even = {2, 4, 6};
    REQUIRE(true == std::all_of(all_even.begin(), all_even.end(), is_even));

    // false case
    std::vector<int> mixed = {1, 2, 4};
    REQUIRE(false == std::all_of(mixed.begin(), mixed.end(), is_even));

    // empty case
    std::vector<int> empty = {};
    REQUIRE(true == std::all_of(empty.begin(), empty.end(), is_even));

    int array_all_even[] = {2, 4, 6};
    REQUIRE(true == std::all_of(std::begin(array_all_even),
                                std::end(array_all_even),
                                is_even));
}

TEST_CASE("std::begin/end") {
    // multi
    int array_all_even[] = {2, 4, 6};
    REQUIRE(true == std::all_of(std::begin(array_all_even),
                                std::end(array_all_even),
                                is_even));

    // single
    int array_one_even[] = {2};
    REQUIRE(true == std::all_of(std::begin(array_one_even),
                                std::end(array_one_even),
                                is_even));

    // empty
    // NOTE(frank): No, did not compile
    // int array_empty[] = {};
    // REQUIRE(false == std::all_of(std::begin(array_empty),
    //                              std::end(array_empty),
    //                              is_even));
}

TEST_CASE("std::for_each") {
    int sum = 0;
    std::vector<int> nums = {1, 2, 3};
    std::for_each(nums.begin(), nums.end(), [&](int n) {sum += n; });
    REQUIRE(sum == 6);
}

TEST_CASE("std::count") {
    std::vector<int> nums = {1, 0, 1, 2, 0, 1};
    REQUIRE(3 == std::count(nums.begin(), nums.end(), 1));
}

TEST_CASE("std::count_if") {
    std::vector<int> nums = {1, 2, 4, 1, 3, 8};
    REQUIRE(3 == std::count_if(nums.begin(), nums.end(), is_even));
}

TEST_CASE("std::mismatch") {
    // same length
    std::vector<int> sl1 = {1, 2, 3, 4, 5};
    std::vector<int> sl2 = {1, 2, 4, 3, 5};
    auto sl = std::mismatch(sl1.begin(), sl1.end(), sl2.begin());
    REQUIRE(*sl.first == 3);
    REQUIRE(*sl.second == 4);
    
    // same vector
    std::vector<int> sv1 = {1, 2, 3, 4, 5};
    std::vector<int> sv2 = sv1;
    auto sv = std::mismatch(sv1.begin(), sv1.end(), sv2.begin());
    REQUIRE(sv.first == sv1.end());
    REQUIRE(sv.second == sv2.end());

    // diff length
    std::vector<int> dl1 = {1, 2, 3};
    std::vector<int> dl2 = {1, 2, 3, 4};
    auto dl = std::mismatch(dl1.begin(), dl1.end(),
                            dl2.begin());
    REQUIRE(dl.first == dl1.end());
    REQUIRE(*dl.second == 4);
}

TEST_CASE("std::find") {
    std::vector<int> nums = {1, 2, 3};

    REQUIRE(nums.begin() == std::find(nums.begin(), nums.end(), 1));
    REQUIRE(nums.end() == std::find(nums.begin(), nums.end(), 0));
}

TEST_CASE("std::find_if") {
    std::vector<int> nums = {1, 2, 3};

    REQUIRE(2 == *std::find_if(nums.begin(), nums.end(), is_even));
    REQUIRE(1 == *std::find_if_not(nums.begin(), nums.end(), is_even));
}

TEST_CASE("std::find_end") {
    std::string s1 = "/var/last/last/";
    std::string s = "/last";
    std::string f = "/first";
    std::string empty = "";
    
    // multiple match
    auto r = std::find_end(s1.begin(), s1.end(), s.begin(), s.end());
    REQUIRE(std::string(r, s1.end()) == "/last/");
    
    // no match
    r = std::find_end(s1.begin(), s1.end(), f.begin(), f.end());
    REQUIRE(r == s1.end());
    
    // zero length
    r = std::find_end(s1.begin(), s1.end(), empty.begin(), empty.end());
    REQUIRE(r == s1.end());
}

TEST_CASE("std::find_first_of") {
    std::vector<int> nums = {1, 2, 4, 5, 6, 7};
    std::vector<int> t1 = {4, 7};
    std::vector<int> t2 = {8};

    REQUIRE(*std::find_first_of(nums.begin(), nums.end(),
                                t1.begin(), t1.end()) == 4);
    REQUIRE(nums.end() == std::find_first_of(nums.begin(), nums.end(),
                                             t2.begin(), t2.end()));
}

TEST_CASE("adjacent_find") {
    std::vector<int> nums = {1, 2, 3, 3, 4, 5};
    REQUIRE(*std::adjacent_find(nums.begin(), nums.end()) == 3);
    std::vector<int> nn = {1, 2, 3};
    REQUIRE(nn.end() == std::adjacent_find(nn.begin(), nn.end()));
}

TEST_CASE("std::search") {
    std::string s1 = "/var/last/last/";
    std::string s = "/last";
    std::string f = "/first";
    std::string empty = "";
    
    // multiple match
    auto r = std::search(s1.begin(), s1.end(), s.begin(), s.end());
    REQUIRE(std::string(r, s1.end()) == "/last/last/");
    
    // no match
    r = std::search(s1.begin(), s1.end(), f.begin(), f.end());
    REQUIRE(r == s1.end());
    
    // zero length
    r = std::search(s1.begin(), s1.end(), empty.begin(), empty.end());
    REQUIRE(r == s1.begin());
}

