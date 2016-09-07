/** @file
 *  Defines half the signal key type, a type_index for a slot's function.
 *  The other half is the actual object that is listening.
 **/
#ifndef SIGNAL_HANDLE_H
#define SIGNAL_HANDLE_H

#include <type_traits>

/** @private */
template <typename T, T> struct signal_handle;

/** @private */
template <typename Class_t, typename... Args, void (Class_t::*target)(Args...)>
struct signal_handle<void (Class_t::*)(Args...), target> {
  constexpr static void (Class_t::*slot)(Args...) = target;
};

/** @private */
#define EXTRACT_SLOT_FROM_MEMBER_FUNCTION(a)                                   \
  signal_handle<std::remove_reference<decltype(                                \
                    &std::remove_reference<decltype(*this)>::type::a)>::type,  \
                &std::remove_reference<decltype(*this)>::type::a> {}

/** A macro used to bind a slot to a signal.
 *  Use only inside a member function from the class in which the slot
 *  belongs.
 *
 *  @param f The member function used as a slot
 */
#define SLOT(f) EXTRACT_SLOT_FROM_MEMBER_FUNCTION(f)

#endif
