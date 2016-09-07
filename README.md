Signals
---------
*A signals and slots library for C++*

*Signals* is a library that implements Qt's [signals and slots](http://doc.qt.io/qt-4.8/signalsandslots.html) using only standard C++. It is **not** compatible with Qt. If you're using Qt, just stick with the built-in signals and slots functionality, which is great. The minimum required version of C++ to use it is C++11.

**Signals** has a few advantages:

**It is non-intrusive**. You don't need to inherit from a super class. There are no intrusive macros. An emitter doesn't need any special declarations: It just needs to own a signal. Slots are just plain member functions: A listener just needs to call `listen()` in a signal somewhere.

**It is easy to use.** *Signals* is header-only. There's no installation, just add it to the include path and `#include "signals.h"`. Every operation is a one-liner: Adding a signal to a class, emitting them, listening to a signal, forgetting ("un-listening") it. The syntax is easy to read.

**It is fully documented**. To have a look at the documentation, just run *doxygen* using the included Doxyfile and open the generated `index.html` inside `SIGNALS_ROOT_DIRECTORY/doc/html`.

**It is free**. *Signals* is licensed under the [LGPL, version 3.0](https://opensource.org/licenses/LGPL-3.0).

If you're interested in more libraries like this one, please donate.

[<img src='https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif'>](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=SSTHTDASSJBNU)

