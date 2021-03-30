## Preprocessing
Download the `requirement.txt` from the repo.
Install all the requiremnets.

## How to Run
1. create a folder named `video` in main folder and put the video file there.
2. Navigate to code folder using `cd code` commands.
3. use `make all` or simply `make` to compile the codes.
4. First run `./ip` to initailise points on the video. Click the desired four points and press Enter.
5. use `./main <videoName> <MethodNum> <arg1> <arg2>` to run the code.
    - `<videoName>` should be given with extension.
    - `<arg1>` and `<arg2>` depends on the parameters used in that method.
    - `<MethodNum>` ranges from 0 to 5.<br/> **0** stands for *subtask 2* while **1-5** stands for corresponding methods.
    ### OR
    use **`./run.sh`** for complete procedure.
6. use `make deleteData` to delete all the data and graph images.
7. use `make clean` to delete executables.

## Analysis
The data created by running all the methods will be available in `analysis/data/` folder.
Utilities functions are available in `./analysis/utility/` folder.
1. Various functions have been defined in ./analysis/utility/ folder.
    - 1. `compareTwoData.py` takes two argument data1 (used as base data) and data2 (data to be compared) and print RMS errors.
    - 2. `graph.py` makes queueDensity and DynamicDensity graph as a function of frame number for any data (takes argument).
    - 3. `method1_graph.py`, `method2_graph.py`, `method4_graph.py` or `method5_graph.py`  makes the corresponding tradeoff (runtime vs error) graphs.
    - 4. `utility.py` makes the main (comparing all the methods) tradeoff graph (runtime vs error).
2. All the graphs made during the process are saved in this `./analysis/graphs/` folder.
3. All the data are saved in `./analysis/data/` folder.

#### For more help regarding command line argument of utility function use `func.py --help`.


