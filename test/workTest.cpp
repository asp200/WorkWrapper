// Export includes.
#include <work/Work.hpp>
#include <gtest/gtest.h>

// Standard includes.
#include <functional>
#include <type_traits>

namespace
{
    int aWorkID()
    {
        return 12;
    }

    work::WorkPriority aWorkPriority()
    {
        return 42;
    }

    void NOP()
    {
        // No Operation.
    }
}

TEST(WorkTest, workIDCanBeSet)
{
    auto work = work::makeWork(aWorkID(), aWorkPriority(), NOP);
    ASSERT_EQ(aWorkID(), work.getID());
}

TEST(WorkTest, workPriorityCanBeSet)
{
    auto work = work::makeWork(aWorkID(), aWorkPriority(), NOP);
    ASSERT_EQ(aWorkPriority(), work.getWorkPriority());
}

TEST(WorkTest, workCanBeRunWithValueArguments)
{
    int result, argA = 2, argB = 3;
    auto add = work::makeWork(aWorkID(), aWorkPriority(), [&result](int a, int b) { result = a+b; }, argA, argB);
    add.run();
    ASSERT_EQ(argA+argB,result);
}

TEST(WorkTest, workCanBeRunWithRefArguments)
{
    int result, argA = 2, argB = 3;
    auto add = work::makeWork(aWorkID(), aWorkPriority(), [&result](int & a, int & b) { result = a+b; }, std::ref(argA), std::ref(argB));
    ++argA;
    ++argB;
    add.run();
    ASSERT_EQ(argA+argB,result);
}