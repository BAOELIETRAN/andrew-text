# Contributing

<!-- 
    Style, guidelines, PRs,...
-->

## Code of conduct

Read [CODE\_OF\_CONDUCT.md](CODE_OF_CONDUCT.md).

## Coding style

### Before you move on

- clang-tidy should catch a bunch of this already.
- So, follow what clang-tidy shouts to your face.
- Similarly for codespell and all those good stuff.

### Notes

- If this project ever uses modules, brace yourself for LSP hallucinations.
- Hopefully the situation gets better with newer versions of each LSP. For
now, `clangd` is the most consistent one.

### Looks and feels

- Indent with 2 spaces. No tab.
- Use snake case for function names, camel case for struct/class/enum names.
- Use trailing return type for functions.
- Use `assert` as a way to specify runtime contracts/invariants.
- Use `static_assert` for compile-time checking.
- If you think the function needs documentation, use Doxygen-style documentation.
- Some examples:

```cpp
namespace random_stuff {
/**
* @brief This is a function.
* @param a A number.
* @param b Another number. Must be different than a.
* @return The sum of a and b.
* This is just an example function.
*/
auto this_is_a_func(int a, int b) -> int {
  assert(a != b);
  return a + b;
}

/**
* @class SomeStruct
* @brief Just a struct.
*/
struct SomeStruct {
  explicit SomeStruct();
  SomeStruct(const SomeStruct&);
  SomeStruct(SomeStruct&&);
  auto operator=(const SomeStruct&) -> SomeStruct&;
  auto operator=(SomeStruct&&) -> SomeStruct&;
  virtual ~SomeStruct();
};

/**
* @class SomeChildStruct
* @brief Just a child struct.
*/
struct SomeChildStruct : SomeStruct {
  ~SomeChildStruct() override;
};
} // namespace random_stuff
```

### File names

- `cpp` for C++ source and module files.
- `hpp` for C++ header files.
- File names should be in snake cases, unless you can't (for example, `CMakeLists.txt`).
- Use `in` as the extra extension if you plan to run a file through `configure_file`.
  - For example, `my_header.hpp.in`

### Features

- Prefer ranges over raw loops, save for `iota`.
  - Sometimes it looks uglier though, like the example below:

```cpp
#include <ranges>

// ...

// index-based loop
for(std::size_t idx = 0; idx < arr.len(); ++arr) {
  if(idx % 2 != 0) {
    continue;
  }
  if(arr[idx] == 0) {
    continue;
  }
  const auto data = arr[idx];
  // some more code
}

// you can use iterators, but,
// this index thingy is at the outside scope.
std::size_t idx = 0;
for(const auto& data : arr) {
  if(idx % 2 != 0) {
    continue;
  }
  if(data == 0) {
    continue;
  }
  // some more code
  ++idx;
}

// not very well-formatted but just for showcase.
for(const auto data : arr | std::views::enumerate |
                                std::views::filter(
                                    [](const auto& [idx, data]) {
                                      return idx % 2 != 0 && data != 0;
                                    }) |
                                std::views::transform(
                                    [](const auto& [idx, data]){
                                      return data;
                                    })) {
  // some more code
}
```

- For logging purposes, prefer `spdlog` over the built-in `print` stuff.
  - Mainly because `spdlog` is a little less work to do :).
  - For read/write to files, prefer streams.

### Random gibberish

- Avoid the evil function.
  - There are a ton of them. Looking very innocent.
  - `clang-tidy` gonna help you. AddressSanitizer too.
  - Or, maybe shoulda used Rust :(.

```cpp
#include <print>

auto evil_function() -> const std::string& {
  return "Causing you a segfault";
}

auto main() -> int {
  std::println("{}", evil_function());
}
```
