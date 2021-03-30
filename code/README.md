## How to Run
1. use `make all` or simply `make` to compile the codes.
2. First run `./ip` to initailise points on the video. Click the desired four points and press Enter.
3. use `./main <videoName> <MethodNum> <arg1> <arg2>` to run the code.
    - `<videoName>` should be given with extension.
    - `<arg1>` and `<arg2>` depends on the parameters used in that method.
    - `<MethodNum>` ranges from 0 to 5.<br/> **0** stands for *subtask 2* while **1-5** stands for corresponding methods.
    ### OR
    use **`./run.sh`** for complete procedure.
4. use `make deleteData` to delete all the data and graph images.
5. use `make clean` to delete executables.