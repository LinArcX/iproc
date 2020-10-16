<h4 align="center">
  <img src="https://img.shields.io/github/languages/top/LinArcX/iproc.svg"/>  <img src="https://img.shields.io/github/repo-size/LinArcX/iproc.svg"/>  <img src="https://img.shields.io/github/tag/LinArcX/iproc.svg?colorB=green"/>
</h4>

# iproc
A utility that help you gather information(cpu_usage, memory_usage, ...)from a particular process.

# Build
## Linux
First make sure you have these tools on your machine:
- `make`
- `clang` or `gcc`

Then:
`cd linux; make; ./release/iproc -p <PID>`

You'll see something like this:
```
./iproc.exe -p 780 -i 5
[5] Mem: 9600 Kb
[10] Mem: 9600 Kb
[15] Mem: 9600 Kb
[20] Mem: 9600 Kb
.
.
.
```

To see full range of options, use `-h`:
```
Options:
        -p,--processID  Specify the processID to watch
        -i,--interval   Specify interval
        -h,--help       Show this help message
```


## Windows
TODO

## License
![License](https://img.shields.io/github/license/LinArcX/iproc.svg)
