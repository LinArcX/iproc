<h4 align="center">
  <img src="https://img.shields.io/github/languages/top/LinArcX/iproc.svg"/>  <img src="https://img.shields.io/github/repo-size/LinArcX/iproc.svg"/>  <img src="https://img.shields.io/github/tag/LinArcX/iproc.svg?colorB=green"/>
</h4>

# iproc
A utility that help you gather information (*cpu_usage*, *memory_usage*, ...) from a particular process.

# Usage
You'll see something like this:
```
↳ iproc -p 25933 -r 4
[2]
        Mem: 8524 Kb
        Cpu: 0.1%
[4]
        Mem: 1524 Kb
        Cpu: 1.4%
[6]
        Mem: 4523 Kb
        Cpu: 0.0%
[8]
        Mem: 4220 Kb
        Cpu: 2.3%

```


To see full range of options, use `-h`:
```
Options:
        -p,--process-id     The process-id to watch
        -i,--interval       The period of time to do unlimited calculations.(default = 2)
        -o,--one-shot       Just calculate once
        -r,--repetition     The number of repetitions
        -h,--help           Show this help message
```

# Build
## Linux
First make sure you have these tools on your machine:
- `make`
- `clang` or `gcc` or any other c-compiler that you prefre.

Then:
`cd linux; make; ./release/iproc -p <PID>`

## Windows
You have three options:
1. Open solution file that resides here: `.\windows\visual_studio\iproc.sln` and build the project through IDE.
2. Build from command-line via `cl.exe`.

    2.1. Open visual studio command prompt.

    2.3. Change to __.\iproc\windows__ direcotry.

    2.4. `cl.exe ..\core\iproc.c .\windows.c`

    Tip: If you don't have visual-studio command prompt or prefer to stay in your current pwsh, you can prepare `cl.exe` via this command:

    `Invoke-CmdScript "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"`

3. Or you can use __mingw__(that contains **gcc**), or __clang__ or any other c-compiler that you prefer.

# Todo
- [ ] Cpu usage in linux isn't correct.
- [ ] Memory usage in windows isn't correct.

## License
![License](https://img.shields.io/github/license/LinArcX/iproc.svg)
