# Project 1 SimCity

## Names of Group Members in Group 4
- Elisa Arbaiza
- Kiyana Baghbadrani
- Nikki Black
- Shinji Kato

## Instructions on How To Compile Program
First, ensure that all files are downloaded and in the same folder.
Then, change terminal into the directory of the folder. 
The code should be able to compile using the command g++ -std=c++11 -o simulation main.cpp Analysis.cpp Residential.cpp Industrial.cpp commercial.cpp Region.cpp Pollution.cpp

This command will create a simulation file that can then be used to run the code. 


## Instructions on How to Run Program
Ensure that all code files are compiled and that you are in the right directory. 
Use the command ./simulation.exe
The user will then be asked to enter the configuration file name.
After configuration file name is given, the program will execute.

## Description
This README file gives instructions on how to compile and run the SimCity Program. Our project requires compiling all of the files in the submission zip.

The user will enter the name of the configuration file in the userinput. 
The .txt file is asked to open, we check if it is open. If it is, the contents of the file is added to the vector fileContents. This allows us to seperate the information and for now access the csv file from line 1.
If the .txt file is not opened then an error is output to the user.
The region file is accessed through calling the first element of the vector fileContents. We ask to open the file contents and check if it is open. if it opens, the region is read in from the CSV file into a vector of vectors called RegionLayout. We parse through the lines of the csv file then we break the line down cell by cell and add it into the vector of strings called row. Then the vector row is added to the vector of vectors regionLayout.
The region is then displayed by iterating through the regionLayout vector and output for the user to see. 
If the csv file doesn't open, an error message is output to the user. 
