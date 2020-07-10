/**
 * @file LifetimeList.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief generic list of nodes that get added and removed by their lifetime.
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
 * @brief Construct a new, empty Lifetime List
 * 
 */
template <class T>
Collections::LifetimeList<T>::LifetimeList() :
    root(nullptr)
{
}

//--------------------------- EXPOSED FUNCTIONS -------------------------------

/**
 * @brief factory function to add a node at the start of the list
 * 
 * @warning the added Node only persists until it runs out of scope.
 * In that case it removes itself from the list.
 * 
 * @param value 
 * @return Node<T> 
 */
template <class T>
typename Collections::LifetimeList<T>::Node Collections::LifetimeList<T>::pushStatic(T value)
{
    return Node(value, *this, nullptr);
}

/**
 * @brief factory function to add a node at the end of the list
 * 
 * @warning the added Node only persists until it runs out of scope.
 * In that case it removes itself from the list.
 * 
 * @param value 
 * @return Node<T> 
 */
template <class T>
typename Collections::LifetimeList<T>::Node Collections::LifetimeList<T>::appendStatic(T value)
{
    return Node(value, *this, tail);
}

/**
 * @brief factory function to add a node at the start of the list
 * 
 * @warning the added Node is heap allocated. Only use when pushStatic is not appropriate.
 * 
 * @param value 
 * @return Node<T> 
 */
template <class T>
std::unique_ptr<typename Collections::LifetimeList<T>::Node> Collections::LifetimeList<T>::pushDynamic(T value)
{
    return std::unique_ptr<Node>(new Node(value, *this, static_cast<Node*>(nullptr)));
}

/**
 * @brief factory function to add a node at the end of the list
 * 
 * @warning the added Node is heap allocated. Only use when appendStatic is not appropriate.
 * 
 * @param value 
 * @return Node<T> 
 */
template <class T>
std::unique_ptr<typename Collections::LifetimeList<T>::Node> Collections::LifetimeList<T>::appendDynamic(T value)
{
    return std::unique_ptr<Node>(new Node(value, *this, static_cast<Node*>(tail)));
}

/**
 * @brief get begin iterator 
 * 
 * @return Iterator 
 */
template <class T>
typename Collections::LifetimeList<T>::Iterator Collections::LifetimeList<T>::begin()
{
    return Iterator(static_cast<LifetimeList&>(*this));
}

/**
 * @brief get end iterator
 * 
 * @return Iterator 
 */
template <class T>
typename Collections::LifetimeList<T>::Iterator Collections::LifetimeList<T>::end()
{
    return Iterator();
}

/**
 * @brief returns the number of elements in this LifetimeList
 * 
 * @tparam T 
 * @return size_t 
 */
template <class T>
size_t Collections::LifetimeList<T>::size()
{
    size_t n = 0;
    auto node = begin();
    for (; node != end(); ++node) {
        ++n;
    }
    return n;
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------