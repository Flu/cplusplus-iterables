# cplusplus-iterables

My own line-up of iterables for using in C++. They may be buggy, have more overhead, and have less features than those already implemented, but they are mine. Besides, what would have I learned if I didn't make this? Probably some nice design patterns and a bit more knowledge about how C++ containers are actually built internally. So overall, I think this is a good project.

## What you will find in the box:
- [ ] Generator class - returns a nice smart pointer for you to access the other iterables
- [x] A String class that will disappoint
- [x] Vector - in case std::vector is too well made and you want something more 'experimental'
- [ ] Dictionary - class for key-value store (be careful, those are immutable and moody)
- [ ] Multi-dict - in case you thought a dictionary is not enough (use it to store more values for a key)

## Installation

For now just take the files, add them to your project and include the main file like so (the others are included recursively):
```c++
#include "cppit.hpp"
```
    
And use the containers at your own *risk*!

## Work in progress
This is still a work in progress so there's still bugs to kill and as this is one of my first big projects, the code is rather messy and unorganized (boy, are you gonna have some fun going in there). As always, if you find that something is not supposed to happen, [raise an issue](https://github.com/Flu/cplusplus/issues)/[submit a pull request](https://github.com/Flu/cplusplus/pulls). I am gonna take it from there (if I find the time).
