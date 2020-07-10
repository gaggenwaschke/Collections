/**
 * @file LifetimeListNode.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief implementation of nodes for the LifetimeList class
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

//--------------------------------- INCLUDES ----------------------------------

#include "LifetimeList.h"

//--------------------------- STRUCTS AND ENUMS -------------------------------

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

/**
 * @brief Private constructor only to be called by factory method.
 * 
 * @tparam T 
 * @param value 
 * @param list 
 * @param insertAfter node to insert this node after. nullptr for first position.
 */
template <class T>
Collections::LifetimeList<T>::Node::Node(T value, LifetimeList<T>& list, Node* insertAfter) :
    value(value), list(list), previous(nullptr), next(nullptr)
{
    if ((insertAfter != nullptr) && (&insertAfter->list != &list)) {
        throw new std::invalid_argument("insertAfter does not belong to the same list");
    }

    if (list.root == nullptr) {
        // empty list
        if (insertAfter != nullptr) {
            throw new std::invalid_argument("insert after must be nullptr for empty list");
        }

        list.root = this;
        list.tail = this;
        return;
    }

    if (insertAfter == nullptr) {
        // insert as first element
        next = list.root;
        list.root->previous = this;
        list.root = this;
    } else {
        // insert after node
        if (insertAfter == list.tail) {
            list.tail = this;
        }
        next = insertAfter->next;
        if (next != nullptr) {
            next->previous = this;
        }
        previous = insertAfter;
        insertAfter->next = this;
    }
}

/**
 * @brief Remove node from LifetimeList
 * 
 */
template <class T>
Collections::LifetimeList<T>::Node::~Node()
{
    if (previous != nullptr) {
        previous->next = next;
    } else {
        // first element
        list.root = next;
    }

    if (next != nullptr) {
        next->previous = previous;
    } else {
        // last element
        list.tail = previous;
    }
}

//--------------------------- EXPOSED FUNCTIONS -------------------------------

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------