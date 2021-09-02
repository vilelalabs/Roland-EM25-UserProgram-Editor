 # ![](icone.ico) Roland-EM25-UserProgram-Editor
An old project I made to fill up the User Programs of Roland EM-25 Keyboard with a Windows App instead doind this directly in Keyboard.

This project was a personal need, to be able to edit and mostly important **copy** user programs used by Roland EM-25 keyboard.

- As a fast explanation, Roland EM25 is a keyboard where you may have 8 instrument sets to change at one button press.

- Additionally with this editor you can get configurations that isn't possible with the normal keyboard editing (like choose another instrument instead a bass for left hand  in some configurations, so you can configure up to 3 instruments at same time (instead only 2 by the normal split configuration).

- As explaned at program run (Help menu), this program doesn't cover the Styles configuration (just because wasn't needed for my pourposes. But, with this code you can manipulate even each instrument of the styles (both, original and uploaded, by floppy disk).

:warning: To use the executable you may need some files (Windows will ask you for) - (it's an old project and executable)
  one important file you'll need is **Vcl40.bpl** , another can be borlndmm.dll (for project editing) and others.

ℹ This project was written in Borland C++ Builder 4. If it's possible, use it (or C++ Builder 6 - tested too) for safe project editing.


PS: And yes, this project was a kind of "reverse engineering" of files created by the keyboard - at the time, didn't exist a downloadable editor on Roland website, so I needed to do this (for my personal use only - and I recommend this kind of use it too).


[Official keyboard site](https://www.roland.com/us/products/em-25/)

![image](https://static.roland.com/assets/images/products/main/em_25_main.jpg)

-Unit1.cpp will have most of the logic in this program.



