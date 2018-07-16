# vtoi

Vtoi is a C library for converting verilog-esque integers into unsigned long
integers. This is useful in cases where the user may wish to input numbers in
one of several radices. The specific use case for which this library was
created as to parse integers in a command shell running on an embedded
processor.

Currently, the library supports the following input formats:

* Binary: `b11100 == 28`
* Octal: `o32 == 28`
* Decimal: `d28 == 28` (also `28 == 28`)
* Hex: `h1c == 28`
