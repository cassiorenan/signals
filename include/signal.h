/** @file
 *  The main header.
 **/
#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <map>
#include <type_traits>
#include <typeindex>

/** A signal that may be emitted. It will remmember any slots listening
 *  to it and notify each of them when emit() is called.
 * 
 *  The template parameters are the types of the objects that will be
 *  passed when the signal is emitted. To emit a signal, all objects
 *  must be provided to the emit() member function.
 * 
 *  ## Example
 * 
 *  ~~~
 *      class signaling_int {
 *        int value;
 *      public:
 *        // Declare a signal. It must be public, so other classes may
 *        // listen to it using listen()
 *        signal<int> value_changed;
 *        void set_value(int new_value) {
 *          if (new_value != value) {
 *            value = new_value;
 *            // Emit the signal.
 *            value_changed.emit(value);
 *          }
 *        }
 *      };
 *  ~~~
 * 
 *  Signals may not be copied or moved. You should also avoid using
 *  pointers or references to signals. Consider them an intrinsic piece
 *  of their containing class, much like a member function.
 * 
 *  @see listen
 *  @see forget
 **/
template<typename... Ts>
class signal {
   typedef std::function<void(Ts...)> listener_t;
   typedef std::pair<std::type_index,void*> key_t;
   std::map<key_t,listener_t> callbacks;
   
   void add_listener(key_t id, const listener_t& listener) {
      callbacks[id] = listener;
   }
   void remove_listener(key_t callback) {
	  callbacks.erase(callback);
   }
   
   template<typename class_t, typename H, typename... Us>
   friend void listen(signal<Us...>& sig, class_t* obj, H);
                               
   template<typename class_t, typename H, typename... Us>
   friend void forget(signal<Us...>& sig, class_t* obj, H) noexcept;
   
   signal(const signal&) = delete;
   signal(signal&&) = delete;
   signal& operator=(const signal&) & = delete;
   signal& operator=(signal&&) & = delete;
   signal(signal&);
   
public:
   signal() = default;
   
   /** Emits the signal.
    *  Any listeners will be notified.
    * 
    *  @param args Any information the signal needs to pass to the listener.
    *              The arguments' types must match the template arguments
    *              for the signal
    **/
   void emit(Ts... args) const {
      for(auto& callback : callbacks) {
         callback.second(args...);
      }
   }
};

#endif
