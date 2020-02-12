# README for Project 1, Parts 1 and 2
By: Devin Hopkins

# For Part 1
In a terminal, navigate to the directory containing part 1.
In that directory, type:
make
to make the necessary files and then
./rsa435
to run the program.

# For Part 2
In a terminal, navigate to the directory containing part 2.
In that directory, type:
make
to make the necessary files. Then, to "sign" a document, type:
./messageDigest435 s file.txt
to create a signature using the contents of "file.txt". Note: I have provided a file called "file.txt".
To then check to make sure if it's authentic, type:
./messageDigest435 v file.txt signature_file
This will say if it's authentic or not. Again, "file.txt" is the file that has the contents from earlier. The "signature_file" is automatically generated and save by the program, so that should stay the same everytime.