# C++ and Python Interoperability Demo
This project demonstrates how to use SWIG and CMake to facilitate the passing of pointers between C++ and Python. It showcases the creation of Python bindings for a C++ Shape class, leveraging SWIG to manage the interface between the two languages.

## Prerequisites
* C++ compiler (e.g., GCC, MSVC)
* CMake (version 3.18 or later)
* Python (version 3.9 or later)
* SWIG (version 4.x or later)

## Building the Project

``` bash
mkdir build && cd build
cmake ..
make
```
This will compile the C++ code and generate Python bindings, enabling Python scripts to interact with C++ classes.

## Using the Python Bindings
Once the project is built, you can use the generated Python module to interact with the C++ Shape class from Python. Here is an example Python script that demonstrates this:
```python
from shape import Circle

# Create an instance of the Circle class
circle = Circle(10)

# Call a method on the Shape instance
print(circle.area())
```
## Demonstrating Interoperability
The `main.cpp` file demonstrates how to create a Python runtime context in C++ using the `python.h` header. It imports the Python bindings into the C++ Python runtime and transfers the C++ object for `Circle` class to Python using SWIG runtime commands.

### Key Concepts Demonstrated
* **Setting Python Home and Initializing Python Runtime:** The application sets the Python home directory and initializes the Python interpreter.

* **Creating and Manipulating C++ Objects:** A Circle object is created in C++ and its attributes are manipulated.

* **Executing Embedded Python Script:** The C++ application executes Python code that interacts with the transferred C++ object.


## Contributing 
Feel free to contribute to this project by submitting pull requests or opening issues.
