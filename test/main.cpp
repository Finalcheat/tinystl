#include "type_traits_unittest.cpp"
#include "algobase_unittest.cpp"
#include "vector_unittest.cpp"
#include "array_unittest.cpp"
#include "stack_unittest.cpp"
#include "forward_list_unittest.cpp"
#include "list_unittest.cpp"
#include "queue_unittest.cpp"
#include "gtest/gtest.h"


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
