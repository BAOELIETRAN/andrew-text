# Building

- Requires CMake version >= 3.28.0.
  - Probably only 3.24 is required, but anyways.

## Release build

- If you're an user, and don't intend to contribute (yet).

```shell
# if you don't have the deps installed (check conanfile.py for which dep is needed)
# if you do, just skip this step.
conan install . -s build_type=Release --build=missing
# or release if you don't use conan
cmake --preset release-conan
cmake --build build/rel
# installing (I hope I have this enabled by default)
# you can change install directory like you do with any other CMake project
cmake --build build/rel --target install
```

## Debug build

- If you're a developer.

```shell
# if you don't have the deps installed (check conanfile.py for which dep is needed)
# if you do, just skip this step.
conan install . -s build_type=Debug --build=missing
# or dev if you don't use conan
cmake --preset dev-conan
cmake --build build/dev
# run tests
ctest --test-dir build/dev/src
# generate documents
```
