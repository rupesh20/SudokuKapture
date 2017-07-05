# SudokuKapture
Opencv project on solving sudoku images by processing the image with opencv techniues and solving the captured sudoku by Backtracking.

To run opencv file in your pc, download the "setup.sh" bash file and run it in your ubuntu distribution, and you are good to go.

After setup.sh installation is done, do the below mentioned commands.

`sudo nano /etc/ld.so.conf.d/opencv.conf`

#Write the below line in the comf file that has been opened.
`/usr/local/lib`

`sudo ldconfig`
`sudo nano /etc/bash.bashrc`

#Write the below line in the bashrc file opened above.
`PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
export PKG_CONFIG_PATH`

Tesseract installtion part


Now, you have done the installation of libraries and dependencies, now you have to run the "main.cpp" file, by typing the below defined command.

`g++ main.cpp -o main `pkg-config opencv --cflags --libs` -llept -ltesseract std=c+11`
