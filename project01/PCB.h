/**
 * @file PCB.h
 * @brief Declaration of the PCB struct and state values
 * @author Cavan Crawford, Brandon Kasa
 * @version 1.0
 * @date 2012-02-12
 */

#ifndef PCB_H
#define PCB_H

/**
 * @brief The states that the process can take on
 */
enum { NEW, READY, RUNNING, WAITING, TERMINATED };

/**
 * @brief The Process Control Block structure.
 *        This is a struct rather than a class to maximize performance
 *        (no constructor/function call overhead).  Later, if this becomes
 *        complex enough that it warrants the usage of classes to be more
 *        easily readable, it can be changed.
 */
struct PCB
{
    int id;
    int state;
    int priority;
};

#endif /* end of include guard: PCB_H */
