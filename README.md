# img2b64

Created to convert images as png to base64 encoded files.

pre build versions : 

[![Downloads](res/Windows.png)](https://raw.githubusercontent.com/ox223252/img2b64/master/bin/img2b64.exe)
[![Downloads](res/Tux.png)](https://raw.githubusercontent.com/ox223252/img2b64/master/bin/img2b64)

## Installation
download the binary file and execute it

Under Linux to prepare project
```Shell
> git clone --recursive http://github.com/ox223252/img2b64
> cd img2b64
img2b64 > ./Configure/configure
```

Compilation for a Linux tool
```Shell
img2b64 > make
```

Compilation for a Windows 64 tool
```Shell
img2b64 > make HARD_ARCH=w64 EXEC=img2b64.exe
```

## Usage

```Shell
> ./bin/img2b64 -i res/Tux.png -o tux.b64
```


```Shell
> ./bin/img2b64
```

## Note
if you set an image as input and a HTML as output it will create a tag with your img as src

```Shell
> ./bin/img2b64 -i res/Tux.png -o tux.html
```