# xx-crypto-cli

Windows/Linux Crypto CLI Toolbox. 跨平台密码工具箱。

:warning: WIP: ONLY a few commands work. 开发中！仅部分功能可用。

## Build

Run `git submodule update --init` to fetch the submodules.

Linux:

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
make install
```

Windows:
```sh
mkdir build-win
cd build-win
cmake ..
cmake --build . --config release
```

## Links

[cmdparser](https://github.com/XUJINKAI/cmdparser)

[GmSSL](https://github.com/guanzhi/GmSSL)

[nist_sts](https://github.com/ZZMarquis/nist_sts)

## License

MIT © XUJINKAI
