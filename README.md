

<h1 align="center">JavaExitHook</h1>
<div align="center">
<img src="https://img.shields.io/badge/build-passing-brightgreen.svg?style=flat" alt="Build: passing">
<img src="https://img.shields.io/badge/license-MPL%202.0-green.svg?style=flat" alt="License: MPL">
<a href="https://discord.gg/b2AUPaj"><img src="https://img.shields.io/badge/chat%20on-discord-7289da.svg?style=flat" alt="discord"></a>

</div>
<hr>
<p>Simple hook that prevent to halt Java Virtual Machine (mostly used in hacking java programs)</p>

## What is used for?

Idea to create that simple hook was born when i saw a lot of system licenses in minecraft plugins on MC-Market working in that way, when valid pass it through, but when invalid call JVM Exit.
This way completely bypass that checks and causes the virtual machine to move on next instructions.
Hook and the way is very simple :)

## Building

### Visual Studio
Simplest way to build project. Just import or clone repo and click "Build". Simple as that.

### Command line
Just run `msbuild /m /p:Configuration=Release .`

## Screenshots

Example java code:

![alt text](https://i.imgur.com/YNcbrYj.png)

Injected DLL cause that our code will throw <b>Your license is not active disabling"</b> but after that <b>Your license is active!</b> and whole code after that, completely ignoring fact that Virtual Machine should be halted.


## License

[MPL-2.0](https://github.com/TheEasyPeasy/JavaExitHook/blob/master/LICENSE)

Copyright (c) 2021-present, TheEasyPeasy
