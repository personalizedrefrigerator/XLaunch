# What is it?
A lightweight replacement for `dmenu`, intended for use with the [`sway` Wayland compositor](https://github.com/swaywm/sway).

# Why?
On my machine, `dmenu` and other launchers can take several seconds to start. `XLaunch` takes roughly 0.5 seconds. `XLaunch` is used like `dmenu`: it allows a user to enter text and displays suggestions.

Each suggestion should be given on its own line of standard input. For example,
```
$ dmenu_path | XLaunch
```
prints the text entered by the user.

# About
`XLaunch` is based on the toolkit from [this project](https://github.com/personalizedrefrigerator/testProjectML). It uses a custom pixel-font and, as a result, lacks support for most languages.

