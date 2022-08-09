# Lane_Detection_Algorithm
### Authors: Francisco Abreu Gonçalves and Tarcísio Prates

This program was the final project of my Algorithm and Data Structures I subject, during my sophomore year. The following Algorithm was inspired by Ziviani's Data Structure Book.

#### About the Algorithm:

  Giving a file which contains information of a lane, the programs returns piece of information about it, such as: If it is a valid Lane pattern, Lane's midpoint and Lane's Direction.

#### Lane pattern:
  
  At first, the program will save the Lane's information in a array and by the function below, return if the lane has a valid pattern:



  Every lane must have the following pattern inside the array:

  ```
  1 3 2 3 1
  ```
  Each number represents a certain color:

  | Color    | True Value  | Mapping value |
  |----------|:-----------:|--------------:|
  | Black    | 0           | 1             | 
  | Red      | 128         | 2             |
  | White    | 255         | 3             |

  