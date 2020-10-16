<h4 align="center">
  <img src="https://img.shields.io/github/languages/top/LinArcX/iproc.svg"/>  <img src="https://img.shields.io/github/repo-size/LinArcX/iproc.svg"/>  <img src="https://img.shields.io/github/tag/LinArcX/iproc.svg?colorB=green"/>
</h4>

# iproc
A utility that help you gather information(cpu_usage, memory_usage, ...)from a particular process.

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
        -p,--process-id  Specify the process-id to watch
        -i,--interval   Specify interval
        -h,--help       Show this help message
```

# Build
## Linux
First make sure you have these tools on your machine:
- `make`
- `clang` or `gcc`

Then:
`cd linux; make; ./release/iproc -p <PID>`

## Windows
TODO

## License
![License](https://img.shields.io/github/license/LinArcX/iproc.svg)
