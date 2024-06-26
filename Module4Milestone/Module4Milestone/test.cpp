// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
//TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
//{
//    // is the collection created
//    ASSERT_TRUE(collection);
//
//    // if empty, the size must be 0
//    ASSERT_NE(collection.get(), nullptr);
//}

// Test that a collection is empty when created.
//TEST_F(CollectionTest, IsEmptyOnCreate)
//{
//    // is the collection empty?
//    ASSERT_TRUE(collection->empty());
//
//    // if empty, the size must be 0
//    ASSERT_EQ(collection->size(), 0);
//}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());

    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    add_entries(5);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());

    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanOrEqualToSize)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // is max_size greater than or equal to 0?
    ASSERT_GE(collection->max_size(), 0);
    
    // add 1 entry. Total of 1
    add_entries(1);
    // is max_size greater than or equal to 0?
    ASSERT_GE(collection->max_size(), 1);

    // add 4 entries. Total of 5
    add_entries(4);
    // is max_size greater than or equal to 5?
    ASSERT_GE(collection->max_size(), 5);

    // add 5 entries. Total of 10
    add_entries(5);
    // is max_size greater than or equal to 10?
    ASSERT_GE(collection->max_size(), 10);
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanOrEqualToSize)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // is capacity greater than or equal to 0?
    ASSERT_GE(collection->capacity(), 0);

    // add 1 entry. Total of 1
    add_entries(1);
    // is capacity greater than or equal to 1?
    ASSERT_GE(collection->capacity(), 1);

    // add 4 entries. Total of 5
    add_entries(4);
    // is capacity greater than or equal to 5?
    ASSERT_GE(collection->capacity(), 5);

    // add 5 entries. Total of 10
    add_entries(5);
    // is capacity greater than or equal to 5?
    ASSERT_GE(collection->capacity(), 10);
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollection)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Add some initial values to the collection
    add_entries(5);
    int initialSize = collection->size();
    EXPECT_EQ(initialSize, 5);

    // Resize the collection to a larger size
    collection->resize(10);

    // Verify that the collection size has increased
    ASSERT_GT(collection->size(), initialSize);
    ASSERT_EQ(collection->size(), 10);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollection)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Add some initial values to the collection
    add_entries(10);
    int initialSize = collection->size();
    EXPECT_EQ(initialSize, 10);

    // Resize the collection to a smaller size
    collection->resize(5);

    // Verify that the collection size has decreased
    ASSERT_LT(collection->size(), initialSize);
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingToZero)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Add some initial values to the collection
    add_entries(10);
    int initialSize = collection->size();
    EXPECT_EQ(initialSize, 10);

    // Resize the collection to zero
    collection->resize(0);

    // Verify that the collection is empty after resizing to zero
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Add some initial values to the collection
    add_entries(10);
    EXPECT_EQ(collection->size(), 10);

    // Clear the collection
    collection->clear();

    // Verify that the collection is empty after clearing
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Add some initial values to the collection
    add_entries(10);
    EXPECT_EQ(collection->size(), 10);

    // Erase the entire collection
    collection->erase(collection->begin(), collection->end());

    // Verify that the collection is empty after erasing
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacity)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Reserve space for 10 elements
    collection->reserve(10);

    // Verify that the capacity has increased
    ASSERT_GE(collection->capacity(), 10);
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExceptionThrown)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Add some initial values to the collection
    add_entries(10);
    EXPECT_EQ(collection->size(), 10);

    // Try accessing an element out of range
    ASSERT_THROW(collection->at(20), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// Test to verify the collection can be sorted
TEST_F(CollectionTest, CanSortElements)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Add some initial values to the collection
    add_entries(10);
    EXPECT_EQ(collection->size(), 10);

    // sort the collection
    std::sort(collection->begin(), collection->end());

    // Verify the collection is sorted
    for (size_t i = 0; i < collection->size() - 1; ++i) {
        ASSERT_LE(collection->at(i), collection->at(i+1));
    }
}

// Test of throw std::length_error exception for resizing to negative
// negative test
TEST_F(CollectionTest, ResizeToNegativeSize)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // Try to resize the collection to a negative size
    ASSERT_THROW(collection->resize(-1), std::length_error);
}