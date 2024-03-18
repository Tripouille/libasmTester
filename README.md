# libasmTester (2019+)

Tester for the libasm project of 42school (macOS and Linux only); features include checking malloc sizes and errno values. 

## Setup

Clone this tester in your libasm repository:
```bash
git clone git@github.com:Tripouille/libasmTester.git && echo "libasmTester" >> .gitignore
```

## Commands

`make` = alias to `make a`

`make m` = launch mandatory tests  
`make b` = launch bonus tests  
`make a` = launch mandatory tests + bonus tests  

`make vm` = launch mandatory tests with valgrind  
`make vb` = launch bonus tests with valgrind  
`make va` = launch mandatory tests + bonus tests with valgrind  

`make [function name]` = launch associated test (ex: `make strlen`)  
`make v[function name]` = launch associated test with valgrind (ex: `make vstrlen`)  
`make vs[function name]` = open the corresponding tests in vscode (ex: `make vsstrlen`)  
`make vi[function name]` = open the corresponding tests in vi (ex: `make vistrlen`)  

> [!WARNING]
> For rigorous testing, you should run **all** your tests with *Valgrind*.

## Outputs

![output of the tester, with everything green saying OK](https://i.imgur.com/bOLM4c7.png)

`MOK` / `MKO` = test about your malloc size  
`ERRNOOK` / `ERRNOKO` = test about errno value  

# Report bugs / Improvement

Contact me on slack or discord : jgambard
