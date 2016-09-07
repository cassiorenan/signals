/** @file 
 * Defines the `listen()` function. */
#ifndef LISTEN_H
#define LISTEN_H

#include <functional>
#include <type_traits>
#include <typeindex>
#include <utility>

#include "signal.h"

/** 
 *  Adds a listener to a signal. The slot is any member function which
 *  fulfils these prerequisites:
 * 
 *   - It must return nothing, i.e.: `void`;
 *   - Its signature must match the signal's parameters;
 * 
 *  The macro SLOT() must be used to select the member function that
 *  will be used as a callback. It adds some boilerplate code you most
 *  certainly don't want to do by hand.
 * 
 *  @param sig  The signal to listen to
 *  @param obj  The address of the object listener. Normally, you should 
 *              pass <span style='color:blue;'>this</span>.
 *  @param slot The member function to use as callback.
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
 *      public:
 *        void on_signal_emitted(const std::string& s) {
 *          std::cout << s;
 *        }
 *        listener(emitter& e) {
 *          listen(e.sig,this,SLOT(on_signal_emitted));
 *        }
 *      };
 *  \endcode
 * 
 *  @see signal::emit
 *  @see forget
 *  @see SLOT
 * 
 **/
template<typename Class_t, typename handler_t, typename... Ts>
void listen(signal<Ts...>& sig, Class_t* obj, handler_t slot)  {
	std::function<void(Ts...)> wrapper = [=](Ts... args){
	   (obj->*(slot.slot))(args...);
	};
	
	sig.add_listener(
	    std::pair<std::type_index, void*>{
		    std::type_index{typeid(slot)},
		    (void*)obj
		},
		wrapper
    );
}

#endif
