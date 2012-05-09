/**
 * @file Page.cpp
 * @brief The implementation of the page object
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#include "Page.h"

/**
 * @brief Constructor.  Sets initial values
 */
Page::Page() :
    _valid(false),
    _dirty(false),
    _memLocation(0)
{

}

/**
 * @brief Destructor
 */
Page::~Page()
{

}

/**
 * @brief Checks whether this page is in use
 * @return The validity of the page
 */
bool Page::isValid()
{
    return _valid;
}

/**
 * @brief Sets whether this page needs to be written to memory
 * @param setValue Whether the page is dirty or not
 */
void Page::setDirtyBit(bool setValue)
{
    _dirty = setValue;
}

/**
 * @brief Determines whether this page needs to be written
 * @return Whether the page needs to be written
 */
bool Page::getDirtyBit()
{
    return _dirty;
}

/**
 * @brief Sets whether the page is in use or not
 * @param setValue The new validity of the page
 */
void Page::setValidBit(bool setValue)
{
    _valid = setValue;
}
