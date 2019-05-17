# Shell

Shell includes 8 module:

        - Help
        - New Process
        - Set Current Directory
        - Set Environment Variable
        - Utinity
        - Additional Function
        - Ctrl-C
        - Wrong input
      
I. Help Module

        - Describe the structure of the Shell and all support command in Shell

        help
II. New Process Module

        - Create new process type .exe, .bat

        1. Create back ground process:
                back "main.exe"
                back "C:\Users\nghia.vt173284\Desktop\main.exe"
        2. Create fore ground process:
                fore "main.exe"
                fore "C:\Users\nghia.vt173284\Desktop\main.exe"

III. Set Current Directory

        - Change current path

        cd "./.."
        cd "main"
        cd "C:\Users\nghia.vt173284\Desktop\main"
IIII. Set environment Variable

        - Change environment variable

        env: "VariablName" "Value"
V. Unitity Module

        - Some command to support Shell

        date
        dir
        list
        exit
        exitall
        getenv
        getenv "VariableName"
        terminate ProcessID
        resume ProcessID
        suspend ProcessID
        
VI. Additional Function

        - Allow Shell to manage all the processes in the computer
        
        listall
        listthread ProcessID
        suspendadd ProcessID
        resumeadd ProcessID
        terminateadd Process ID

VII. Ctrl-C Module

        - Handle Ctrl-C signal
        - Terminate a foreground process
        
VIII. Wrong Input Module

        - Print message error

IX. Compile: 
        
        g++ main.cpp -o MyShell -std=c++11 -lpsapi
