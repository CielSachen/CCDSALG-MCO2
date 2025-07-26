#include "social_network/queue.h"

#include <gtest/gtest.h>

#include <cstring>

TEST(InitializeQueue, SetsAllIntegerFieldsToZero) {
    Queue queue;

    initialize_queue(&queue);

    EXPECT_EQ(queue.front, 0);
    EXPECT_EQ(queue.rear, 0);
}

TEST(InitializeQueue, SetsDataToEmptyStrings) {
    Queue queue;

    initialize_queue(&queue);

    for (std::size_t i = 0; i < MAX_GRAPH_VERTEX_COUNT; i++) {
        EXPECT_TRUE(std::strlen(queue.data[i]) == 0);
    }
}

TEST(Enqueue, AddsElementToData) {
    Queue queue;

    initialize_queue(&queue);

    Vertex elm = "Test";

    enqueue(&queue, elm);

    EXPECT_TRUE(std::strncmp(elm, queue.data[0], MAX_VERTEX_LABEL_LENGTH) == 0);
}

TEST(Enqueue, IncreasesRear) {
    Queue queue;

    initialize_queue(&queue);

    enqueue(&queue, "Test");

    EXPECT_EQ(queue.rear, 1);
}

TEST(Dequeue, IncreasesFront) {
    Queue queue;

    initialize_queue(&queue);

    enqueue(&queue, "Test");

    dequeue(&queue);

    EXPECT_EQ(queue.front, 1);
}

TEST(Peak, CopiesFrontElementToOutputParameter) {
    Queue queue;

    initialize_queue(&queue);

    enqueue(&queue, "Test");

    Vertex first_elm = {0};

    peak(&queue, first_elm);

    EXPECT_TRUE(std::strncmp(first_elm, queue.data[0], MAX_VERTEX_LABEL_LENGTH) == 0);
}

TEST(Peak, DoesNotMutate) {
    Queue queue;

    initialize_queue(&queue);

    enqueue(&queue, "Test");

    Vertex first_elm = {0};

    peak(&queue, first_elm);

    EXPECT_EQ(queue.rear, 1);
    EXPECT_EQ(queue.front, 0);
}

TEST(IsFull, ReturnsTrueIfRearIsMax) {
    Queue queue;

    initialize_queue(&queue);

    for (std::size_t i = 0; i < MAX_GRAPH_VERTEX_COUNT; i++) {
        enqueue(&queue, "Test");
    }

    EXPECT_TRUE(is_full(&queue));
}

TEST(IsFull, ReturnsFalseIfRearIsNotMax) {
    Queue queue;

    initialize_queue(&queue);

    enqueue(&queue, "Test");

    EXPECT_FALSE(is_full(&queue));
}

TEST(IsEmpty, ReturnsTrueIfFrontIsEqualToQueue) {
    Queue queue;

    initialize_queue(&queue);

    EXPECT_TRUE(is_empty(&queue));

    enqueue(&queue, "Test");
    dequeue(&queue);

    EXPECT_TRUE(is_empty(&queue));
}

TEST(IsEmpty, ReturnsFalseIfFrontIsNotEqualToQueue) {
    Queue queue;

    initialize_queue(&queue);

    enqueue(&queue, "Test");

    EXPECT_FALSE(is_empty(&queue));
}
