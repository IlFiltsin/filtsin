# Mind 

Mind is **math library with support long arithmetic**

---

## Current functionality 
+ **Long arithmetic**.
	+ Support number of **any** size.
	+ Fast **`+` `-` `/` `*`** operators.
	+ Easy using on **C++11**.
	+ Overloading all necessary operator for nice and fast using.
+ **Math functions**: Realizations of some functions for **long arithmetic** and usual arithmetic types.
+ **Exceptions**: Can work without exceptions or with it. Use flag **MIND_STRICT**.
+ **Operating systems**: support of Linux.

## Installation
### Clone the repository
The first step is to clone the repository or download last release. Write in terminal:
```bash
git clone https://github.com/ilfiltsin/mind.git
```
### Installation
Write in terminal in building directory:
```bash
cmake <path to mind>
sudo make install
```
**Check the [install](INSTALL) for additional information.**
## Using
### Add library
**Static**
```cmake
find_library(MIND libmind.a)
target_link_libraries(${PROJECT_NAME} ${MIND})
```
**Shared**
```cmake
find_library(MIND mind)
target_link_libraries(${PROJECT_NAME} ${MIND})
```
### Add all necessary headers
```c++
#include <mind/math/number.hpp>
```
### Continue using
```c++
mind::math::Number a = 2017;
a++;
```
**Check the [examples](./examples/) for examples of using.**
### License
Mind is freely available for absolutely any use. Please, check the [license](LICENSE).