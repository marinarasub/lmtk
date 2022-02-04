# Contributing Guidelines

## Issues
For now, open an issue on [github](https://github.com/marinarasub/lmtk).
In the future this will be more organized.

## Commits & Pull Requests
First, work on your own branch (i.e. mygitusername-dev). You may fix issues, add
new features, tests, or help in any other way! Any and all help is appreciated.
Submit a pull request once you think you are ready.
As the project is in early development, we don't have too many rules! But try
to use common sense.

Currently there are status checks for building on windows and linux.

## Code Style
The code style attempts to be consistent and readable, and is subject to change,
but here are the styling I use so far:

For the most part, I follow a similar format to 
<a href="https://google.github.io/styleguide/cppguide.html">
Google C++ Style Guide</a>

This will get updated as the project matures.

### General
- Try to adhere to ISO C++ 11, so the project can build on both linux and 
windows. 
- Use whitespace where appropriate for readability
- two newlines at after include, header guards, macros before content
    - header guards follow google C++ conventions
    - include c++ library, then external library headers before user defined
```
#ifndef _SILLYPROJECT_HEADER_H_
#define _SILLYPROJECT_HEADER_H_

#include <stdlib.h>
#include <externallib.h>
#include userfile.h"


class Content 
{
    ...
}

#endif // _SILLYPROJECT_HEADER_H_
```
 <br/>

### Comments
- Follow Doxygen Javadoc styling for formal API specification
```
/**
* Brief description.
*
# @tags like this
*/
code...
```
- Use // for temporary comments, TODO comments, and code comments
```
// TODO fix this "later"
messy code...
```
- All files belonging to the same subproject should have the same banner.
    - Currently only header files have one, this is not a struct requirement and
    can always be mass updated later.
```
/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * <subproject specific text ...>
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/
```
 <br/>

### Naming
- UPPERCASE for constants, macros etc.
```
#define MACRO

const char* CONSTANT
```
- PascalCase for classes
```
class HelloWorld
```
- camelCase for functions
```
void myFunc()
```
- snake_case for fields/members and structs (more hidden/low level stuff)
```    
double me_is_snake_case
struct my_struct
```
- snake_case for namespaces
```
namespace not_std
```
 <br/>

### Brackets/Code Blocks
- curly on next line for functions, classes and branch logic
```
class Class
{
    void func()
    {
        ...
    }
}
```
- curly on same line for namespaces and try/catch blocks
```
namespace hello {

    try {

    }
    catch (...) {

    }
}
```
- branch logic (not as strict) followed by space for condition and curly next line
```
if (condition)
{
    ...
}
else
{
    ...
}
```
 <br/>