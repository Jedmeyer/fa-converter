Welcome to Elaina and Jason's project on a back C++ solution for a FA Translator.

There are two portions of this project: the backend (CPPCMS) and the termianl.

The terminal binaries have been added for convenience, but you can change the code to 
customize what gets passed (`FAclassEpsilon.cpp`).

The backend is currently non-functional due to some thread safety issues - 
but it can be built using the following steps.

 Get source of CPPCMS:
 
```
git clone https://github.com/artyom-beilis/cppcms.git cppcms
```

Get into the build directory:
```
cd cppcms && mkdir build && cd build
```

Run CMAKE and Make
```
cmake ..
make
make install
```

Add path for cppcms - else will fail on compilation:
```
export LD_LIBRARY_PATH=/usr/local/lib
```

Then, you can just:
```
make
```


# How to:

You'll need to run the cppcms_run command with your host IP in order to run the program.

```
cppcms_run -h 157.230.188.32 -p 80 hello -c config.js
```




