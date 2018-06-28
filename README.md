# SudokuReader
Detects the outer boundaries of a sudoku in a given image without using in-built library functions

## Steps:-
<b>
<ul>
  <li>Gaussian Blur</li>
  <li>Adaptive Threshold</li>
  <li>Bitwise Not</li>
  <li>Dilation</li>
  <img src="pics/Capture1.PNG">
  <li>Flood-Fill</li>
  <li>Point which is the cuase for the largest area</li>
  <li>Focus on the boundaries of the blob</li>
  <img src="pics/Capture2.PNG">
  <li>Find lines geometric lines on the image using Hough Transform</li>
  <img src="pics/Capture3.PNG" height="300" width="400">
  <img src="pics/Capture4.PNG" height="300" width="400">
  <li>Merge Lines which have nearest slopes</li>
  <li>Find outermost intersections</li>
  <img src="pics/Capture5.PNG" height="300" width="400">
  <li>Crop the image</li>
  <img src="pics/Capture6.PNG" height="300" width="400">
