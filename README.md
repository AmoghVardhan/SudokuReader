
# SudokuReader
Detects the outer boundaries of a sudoku in a given image without using in-built library functions

## Steps:-
<b>
<ul>
  <li>Gaussian Blur</li>
  <li>Adaptive Threshold</li>
  <li>Bitwise Not</li>
  <li>Dilation</li>
  <br>
  <img src="pics/Capture1.PNG">
  <br>
  <li>Flood-Fill</li>
  <li>Point which is the cuase for the largest area</li>
  <li>Focus on the boundaries of the blob</li>
  <br>
  <img src="pics/Capture2.PNG">
  <br>
  <li>Find lines geometric lines on the image using Hough Transform</li>
  <br>
  <img src="pics/Capture3.PNG" height="300" width="400">
  <img src="pics/Capture4.PNG" height="300" width="400">
  <br>
  <li>Merge Lines which have nearest slopes</li>
  <li>Find outermost intersections</li>
  <br>
  <img src="pics/Capture5.PNG" height="300" width="400">
  <br>
  <li>Crop the image</li>
  <br>
  <img src="pics/Capture6.PNG" height="300" width="400">
