# Forward Declaration

Though [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Forward_Declarations) mentions we should avoid forward declaration if possible, I still think it's quite useful. See [What is forward declaration](https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c) for more details.

- For cyclic references, we **have to** to it and we can't avoid it.
- For including headers, to use forward declaration to declare types instead of including the header files can save compiling time especially when the project is large.
  - try to update [book.hh](./forward-declaration-exp/src/helpers/book_helper.hh) to use `#include "objects/book.hh"` and build it again using `time make`, you should be albe to see the difference.
  - note: you might not see much difference if your CPU is really powerful.

Similar to our experimental code, we have `<iosfwd>` header as a forward declaration for `<iostream>` because this quite large and we really want to avoid including it if possible. ref: [link](https://stackoverflow.com/questions/4300696/what-is-the-iosfwd-header).
