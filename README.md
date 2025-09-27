![test](https://github.com/ayumi-aiko/banners/blob/main/ayaka-banner.png?raw=true)
# Ayaka
Yet another Adblocker but written in C (work-in-progress)

### To build
> **NOTE:** As of now, the build system only has `ayaka-cli-android` because the main app is still in it's early stages.
- Change these following variables according to the toolchain path: CC_ROOT
- Don't forget to change it, else the program won't get compiled or will have any random issues.
```bash
make SDK=<sdk version here> ARCH=<arch here>
```
- ARCH can be `arm`, `arm64`, `x86` and `x86_64`.
- SDK can be anything above or equal to `28`.