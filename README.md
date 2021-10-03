# JavaExitHook

Simple hook that prevent to halt Java Virtual Machine (mostly used in hacking java programs)

## What is used for?

Idea to create that simple hook was born when i saw a lot of system licenses in minecraft plugins on MC-Market working in that way, when valid pass it through, but when invalid call JVM Exit.
This way completely bypass that checks and causes the virtual machine to move on next instructions.
Hook and the way is very simple :)

### Screenshots

Example java code:

![alt text](https://i.imgur.com/YNcbrYj.png)

Injected DLL cause that our code will throw <b>Your license is not active disabling"</b> but after that <b>Your license is active!</b> and whole code after that, completely ignoring fact that Virtual Machine should be halted.
