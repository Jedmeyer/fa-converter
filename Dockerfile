#Trying TE Image
FROM steeze/cppcms
# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /usr/src/hello
# Specify the working directory
WORKDIR /usr/src/hello

#Setup Requirements

#Seems to be a JEssie error here. See online dockerfile stuff
RUN ls
#clone source
CMD ["git clone https://github.com/artyom-beilis/cppcms.git cppcms"]

CMD ["export" ,"LD_LIBRARY_PATH=/usr/local/lib"]

# Use GCC to compile the Test.cpp source file
RUN make
# Run the program output from the previous step
CMD ["./hello", "-c", "config.js"]
