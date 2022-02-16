
## Building the profiler

In the tracy source:
```
cd profiler/build/unix
make -j12

# install manually:
cp Tracy-release ~/install/bin/tracy
export PATH=~/install/bin:"$PATH"
```

## Running

1. Build application with `tracy/Tracy.cpp`.
2. Instrument code
3. Launch profiler
4. Run application

Full stack traces and context switch information require that the application be run with escalated privelates, i.e. `sudo`.
