# template

> Yet another CMake template of mine.

## Why

I took a look at `cmake-init` and modified to my own use:

- Linking with sanitizers (ASan, UBSan, and such).

## How to use

Modify [this script](tools/sed.sh), and run it at the project root.

```bash
sh ./tools/sed.sh
```

## Todo

- [x] Package manager (conan).
- [x] At least it compiles.
- [ ] CI/CD (Windows causing trouble. Need more testing).
- [ ] Install (technically can install, not tested yet).
- [ ] CPack.
- [x] Licensing (it's a template. Probably just slap Unlicense on).

Modify the `project` section in the main CMake file to that of your project.

<!--
    The stuff above this comment should be deleted if you decide to use this
    template.
-->

## Building

See the BUILDING document.

## Contributing

See the CONTRIBUTING document.

## Licensing

Choose your own!
