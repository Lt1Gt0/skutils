# Flag Parser

Although this is not necessarily a gnu util remake of anything that I am aware of, it is more of something I can use as a utility in my other c++ projects by having an interface to parse command line flags passed to a program

## Usage

Import the `skutilflagparser.hpp` header file into the program

### Flag definitions

A flag is just a struct with the following members

```cpp
Short Identifier;
Long Identifier;
Description;
Expected Value Count;
Function Pointer;
```

An example defition of a valid flag list that can be used as the argument provided to the parser can be made like this

```cpp
SKUTIL::SK_VEC<SKUTIL::Flag> flags {
    {
        't',
        "test",
        "Test function",
        2,
        testFunc,
    },
};
```

### Method definition

Create a method with the following defined format

`void method_name(OPT int inputCount, OPT char** inputVals)`

The argument names and method names can be called whatever is most convienent but should be defined in the format shown above

The `inputCount` argument is the amount of inputs that the flag is expecting to see from the user and should be the same as the one defined in the flag definition

`inputVals` is the actual values that the user passes in when the flag is called. All of the inputVals are returned as char* since they are given to the program as string values from the cli

### Parser initialization and usage

To create a parser make an instance of SKUTIL::Flagparser with the address of the flags list as an argument

```cpp
SKUTIL::FlagParser parser = SKUTIL::FlagParser(&flags);
```

The parser's `ParseFlags` method takes in the argument count and argument list provided by the main method (or any other similar inputs depending on the usecase) and handles the rest

### Example

```cpp
#include "skutilflagparser.hpp"

// Method definition should follow the same format
void test(OPT int inputCount, OPT char** inputVals)
{
    // Method Logic
}

int main(int argc, char** argv) 
{
	// Initialize flags
	SKUTIL::SK_VEC<SKUTIL::Flag> flags {
		{
			't', // Short Identifier
			"test", // Long Identifier
			"Test function", // Description
			2, // Argument Count
			test, // Function pointer
		},
	};

	SKUTIL::FlagParser parser = SKUTIL::FlagParser(&flags);

	if (argc < 2)
		std::cout << "No Flags Passed\n";
	else
		parser.ParseFlags(argc, argv);

	return 0;
}
```
