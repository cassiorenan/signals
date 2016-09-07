/** @file
 * Defines the `forget()` function*/
#ifndef FORGET_H
#define FORGET_H

#include <type_traits>
#include <typeindex>
#include <utility>

#include "signal.h"

/**
 *  Removes a listener from a signal. The arguments must be the exact
 *  same that were passed to `listen()`.
 *
 *  @param sig  The signal to remove the listener from
 *  @param obj  The address of the object listener
 *  @param slot The member function used as callback
 *
 *  ## Example
 *
 *  \code{.cpp}
 *      class emitter {
 *      public:
 *        signal<const std::string&> sig;
 *        void emit(const std::string& s) {
 *          sig.emit(s);
 *        }
 *      };
 *
 *      class listener {
 *        emitter& e
 *      public:
 *        void on_signal_emitted(const std::string& s) {
 *          std::cout << s;
 *        }
 *        listener(emitter& e) : e(e) {
 *          listen(e.sig,this,SLOT(on_signal_emitted));
 *        }
 *        ~listener() {
 *          forget(e.sig,this,SLOT(on_signal_emitted));
 *        }
 *      };
 *  \endcode
 *
 *  @see listen
 *
 **/
template <typename Class_t, typename handler_t, typename... Ts>
void forget(signal<Ts...> &sig, Class_t *obj, handler_t h) noexcept {
  sig.remove_listener(std::pair<std::type_index, void *>{
      std::type_index{typeid(h)}, (void *)obj});
}

#endif
