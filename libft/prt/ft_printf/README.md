# ft_printf
**easier than ft_putchar..**
<br>
<br>
An easy re-implementations of the well known printf C stdio function
<br>
We find thinks like :
- base conversion 
- string manipulation
- parsing `printf("show this value : %s", value)`

There is two main approach : 
1. Printing each time we find a new `%` and the variable it points to
2. Do all the parsing, convert every variable and print once everything is converted in one string

I went with the second approach wich allow me later to re-implement `sprintf` (return the formatted string instead of printing it)
