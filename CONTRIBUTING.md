# Contributing

<!-- 
    Style, guidelines, PRs,...
-->

## Code of conduct

Read [CODE\_OF\_CONDUCT.md](CODE_OF_CONDUCT.md).

## How to contribute

- Fork the repository.
- Work on one bugfix/feature/... at a time.
- If any help needed, make a pull request to ask for help.
- If feature is done, make a pull request also.

## Coding style

### Before you move on

- We use C++23. Make sure your compiler supports it.
- clang-tidy should catch a bunch of this already.
- So, follow what clang-tidy shouts to your face.
- Similarly for codespell and all those good stuff.

### Notes

- If this project ever uses modules, brace yourself for LSP hallucinations.
- Hopefully the situation gets better with newer versions of each LSP. For
now, `clangd` is the most consistent one.

### Looks and feels

- Indent with 2 spaces. No tab.
  - If you have `clang-format`, it's gonna help you.
- Use snake case for function names, camel case for struct/class/enum names.
- Use trailing return type for functions.
- Use `assert` as a way to specify runtime contracts/invariants.
- Use `static_assert` for compile-time checking.
- If you think the function needs documentation, use
[Doxygen-style documentation](https://www.doxygen.nl/manual/docblocks.html).
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
* @brief Just a child struct of @ref SomeStruct.
*/
struct SomeChildStruct : SomeStruct {
  ~SomeChildStruct() override;
};
} // namespace random_stuff
```

- Name class/struct members with a preceding `m_`, function parameters with a
preceding `t_`. `public` declarations before `private` ones, most of the time:

```cpp
class SomeClass {
public:
  explicit SomeClass(std::unique_ptr<std::iostream> t_stream)
    : m_stream(std::move(t_stream)) {}
private:
  std::unique_ptr<std::iostream> m_stream;
};
```

### File names

- `cpp` for C++ source and module files.
- `hpp` for C++ header files.
- File names should be in snake cases, unless you can't, for example, `CMakeLists.txt`.
- Use `in` as the extra extension if you plan to run a file through `configure_file`.
  - For example, `my_header.hpp.in`.
- Unit tests of a particular file should be `filename.test.cpp`.
  - For example, unit test of `tree.cpp` should be `tree.test.cpp`.
- Group closely related source files into a directory. This is subjective, so
follow your judgement for this.
- Any non-unit-test should be in the `tests` directory at the project root.

### Features

- Try not to use any platform-specific API.
  - For example, `#include <windows.h>`, `#include <pthread.h>` or `#include <unistd.h>`.
  - There's a reason this project is in C++ instead; a lot of this has its
  cross-platform counterpart.
  - If you must, try find and use an external library.
- Manage packages with `conanfile.py`.
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

- Prefer sum types over exceptions to return optional or error values.
  - If the project's C++ version goes down to C++20, `std::expected` isn't
  available. In that case, use `std::variant` in its place.

```cpp

// no
auto exceptional() {
  throw 69;
}

// yes
enum struct ErrorCodes : uint8_t {
  YoMama = 69,
};

auto less_exceptional() -> std::expected<void, ErrorCodes> {
  return std::unexpected{ErrorCodes::YoMama};
}

auto find_stuff() -> std::optional<int> {
  // ...
  if(not_found) {
    return std::nullopt;
  }
  // ...
  return 420;
}


// in case std::expected isn't available, we can use something like:

template <typename E> struct Err {
  E value;
};

template <typename T, typename E>
using Result = std::conditional_t<std::is_same_v<T, void>,
                                  std::variant<std::monostate, Err<E>>,
                                  std::variant<T, Err<E>>>;

// Then you can chain a bunch of std::visit.
```

- Limit the use of templated class or function.

```cpp
// here are some cases where you should

auto take_a_string(const char* str);

auto take_a_string(const std::string& str);

auto take_a_string(std::string&& str);

auto take_a_string(std::string_view str);

// template use can reduce this to one function:

template <typename S>
  requires std::convertible_to<S, std::string>
auto take_a_string(S str) {
  // but now, you cannot forward-declare anymore.
}
```

- For logging purposes, prefer `spdlog` over the built-in `print` stuff.
  - Mainly because `spdlog` is a little less work to do :).
  - For read/write to files not for logging purpose, prefer streams.
- If multi-threading needed for some data structure, prefer a thread-safe version
over locking.
  - Good reference material is "Purely functional data structures."

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
