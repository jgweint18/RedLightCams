# RedLightCams
A Project completed in the spring of 2025 for School
The code uses the data given for the project from red light cameras around Chicago and displays it.
A CameraRecord class is made with variables intersection, address, Camera Number, Date, Number of Violations, and the Neighborhood.
All the public functions are get functions and a constructor.
A print function was also created for testing purposes.
Program Guide:
  The first operation the program does is to ask the user for file input. Provided are 4 different files that can be used for input. It then reads the file and creates a new CameraRecord object for each line in the file. These are then all pushed back into a records vector
  1. Data Overview:
       This runs the Data Overview function, which first outputs a statement showing the number of records. It counts the total number of cameras and violations. The function then finds the day with the most violations and displays it.
  2. Results by neighborhood.
       Outputs each neighborhood, followed by the number of violations it has
  3. Chart By Month
       Outputs each month, then a star for the number of violations in thousands. (This is done with integer division, so it always rounds down)
  4. Search for cameras
       The most complex function. Takes in either a neighborhood or intersection from user input and displays all information about each camera there.
  
