## Analysis
The data created by running all the methods will be available in `./data/` folder.
Utilities functions are available in `./utility/` folder.
1. Various functions have been defined in ./analysis/utility/ folder.
    - 1. `compareTwoData.py` takes two argument data1 (used as base data) and data2 (data to be compared) and print RMS errors.
    - 2. `method4.py` takes data from all the threads of method4 and combines into one.
    - 3. `method5.py` takes data from all the threads of method5 and combines into one.
    - 4. `graph.py` makes queueDensity and DynamicDensity graph as a function of frame number for any data (takes argument).
    - 5. `method1_graph.py`, `method2_graph.py`, `method4_graph.py` or `method5_graph.py`  makes the corresponding tradeoff (runtime vs error) graphs.
    - 6. `utility.py` makes the main (comparing all the methods) tradeoff graph (runtime vs error).
2. All the graphs made during the process are saved in this `./graphs/` folder.
3. All the data are saved in `./data/` folder.

### Data
1. Subfolders have created for each method to store its data.
2. For baseline `data.csv` will be created.
3. For method2 `dataM2.csv` will be created.

#### Naming Convention
1. method1 - `dataM1F<frameToSkip>`
2. method2 - `dataM2.csv`
3. method3 - `dataM3_<width>_<height>.csv`
4. method4 - `dataM4N<totalThreads>T<ThreadNum>.csv` and `dataM4N<NumOfThreads`>
5. method5 - `dataM5N<totalThreads>T<ThreadNum>.csv` and `dataM5N<NumOfThreads`>

### Graph Description (Types of Graphs)
1. Normal garph - Same as in subtask 2 but with any data.
    - Naming convention - `<data>.png`
2. Method wise utility vs run-time - Here we are plotting error vs run-time graphs of any method with its parameters.
    - Naming Convention - `method<methodnum>_tradeoff_<type>`
    - `<type>` is queue, dynamic or both(both queue and dynamic density error on same plot)
3. Main graph utility vs run-time - Here we are plotting error vs run-time for all the methods where each point represents average error and average run-time across all its parameter.
    - Naming convention - `tradeoff_<type>`.type param is same as above.

#### For more help regarding command line argument of utility function use `func.py --help`.