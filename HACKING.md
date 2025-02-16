# Hacking

- This is a brief intro to the project structure, in case you want to read the
code and/or contribute.

## The obvious stuff

- Written in C++23 and built with CMake.
  - May tone down to C++20 due to compiler support.
- The required CMake version is, for now, 3.28.0, in case of modules.
  - Unlikely to use modules due to, again, compiler support.

## Package management

- Conan. [Read the tutorial here](https://docs.conan.io/2/tutorial.html).
  - Search for packages in [conan center](https://conan.io/center).

## Coding style

- Mostly covered by `clang-tidy`.
- Refer to [CONTRIBUTING](CONTRIBUTING.md) document.

## Internal working of the project

- There isn't even a line of code yet :(.

## Testing

### Unit testing

- Currently considering Catch2 or Google Test.
[Catch2 tutorial](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top)
and [GTest tutorial](https://google.github.io/googletest/).

### Benchmarking

- If using Catch2, it has a built-in benchmarking solution.
[Here is the documentation](https://github.com/catchorg/Catch2/blob/devel/docs/benchmarks.md).

- If using GTest, [Google bench](https://github.com/google/benchmark) needed.

### Fuzz testing

- libFuzzer is the simple answer, but it seems like there isn't GCC support. So,
to compile fuzz testing, you may need clang or msvc.

### Regression testing

- GitHub Actions.
