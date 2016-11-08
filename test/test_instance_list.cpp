#include <catch.hpp>
#include <motion_control/instance_linked_list.h>

using namespace MotionControl;

TEST_CASE("InstanceLinkedList", "[linkedlist]")
{
    int a = 0;
    int b = 1;
    int c = 2;

    SECTION("add")
    {
        InstanceLinkedList<int> list;
        InstanceListNode<int> node1(a);
        InstanceListNode<int> node2(b);
        InstanceListNode<int> node3(c);

        list.add(&node1);
        list.add(&node2);
        list.add(&node3);

        REQUIRE(node1.next == &node2);
        REQUIRE(node2.next == &node3);
        REQUIRE(node3.next == NULL);

        REQUIRE(node3.prev == &node2);
        REQUIRE(node2.prev == &node1);
        REQUIRE(node1.prev == NULL);
    }

    SECTION("remove in middle")
    {
        InstanceLinkedList<int> list;
        InstanceListNode<int> node1(a);
        InstanceListNode<int> node2(b);
        InstanceListNode<int> node3(c);

        list.add(&node1);
        list.add(&node2);
        list.add(&node3);

        list.remove(&node2);

        REQUIRE(node1.next == &node3);
        REQUIRE(node3.next == NULL);

        REQUIRE(node3.prev == &node1);
        REQUIRE(node1.prev == NULL);
    }

    SECTION("remove root")
    {
        InstanceLinkedList<int> list;
        InstanceListNode<int> node1(a);
        InstanceListNode<int> node2(b);
        InstanceListNode<int> node3(c);

        list.add(&node1);
        list.add(&node2);
        list.add(&node3);

        list.remove(&node1);

        REQUIRE(node2.next == &node3);
        REQUIRE(node2.next == &node3);

        REQUIRE(node3.prev == &node2);
        REQUIRE(node2.prev == NULL);
    }

    SECTION("remove end")
    {
        InstanceLinkedList<int> list;
        InstanceListNode<int> node1(a);
        InstanceListNode<int> node2(b);
        InstanceListNode<int> node3(c);

        list.add(&node1);
        list.add(&node2);
        list.add(&node3);

        list.remove(&node3);

        REQUIRE(node1.next == &node2);
        REQUIRE(node2.next == NULL);

        REQUIRE(node2.prev == &node1);
        REQUIRE(node1.prev == NULL);
    }


    SECTION("removed when node is destroyed")
    {
        InstanceLinkedList<int> list;
        InstanceListNode<int> node1(a);
        InstanceListNode<int> node3(c);

        {
            InstanceListNode<int> node2(b);
            list.add(&node1);
            list.add(&node2);
            list.add(&node3);


            // Make sure everything got added
            REQUIRE(node1.next == &node2);
            REQUIRE(node2.next == &node3);
            REQUIRE(node3.next == NULL);

            REQUIRE(node3.prev == &node2);
            REQUIRE(node2.prev == &node1);
            REQUIRE(node1.prev == NULL);
        }

        // node2 is out of scope and should have been removed
        REQUIRE(node1.next == &node3);
        REQUIRE(node3.next == NULL);

        REQUIRE(node3.prev == &node1);
        REQUIRE(node1.prev == NULL);

    }

    SECTION("iterate")
    {
        InstanceLinkedList<int> list;
        InstanceListNode<int> node1(a);
        InstanceListNode<int> node2(b);
        InstanceListNode<int> node3(c);

        list.add(&node1);
        list.add(&node2);
        list.add(&node3);

        InstanceListNode<int> *node = list.get_root();

        REQUIRE(node->prev == NULL);
        REQUIRE(node->get() == a);
        node = node->next;
        REQUIRE(node->get() == b);
        node = node->next;
        REQUIRE(node->get() == c);
        REQUIRE(node->next == NULL);
    }
}

