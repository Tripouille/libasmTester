# libasmTester (2019+)

Tester for the libasm project of 42 school.   
Clone this tester in your libasm repository. (works on linux and mac)  
It checks your malloc size and the value of errno after read and write.

# Commands
make m = launch mandatory tests  
make b = launch bonus tests  
make a = launch mandatory tests + bonus tests 

make vm = launch mandatory tests with valgrind  
make vb = launch bonus tests with valgrind   
make va = launch mandatory tests + bonus tests with valgrind  

make [funtion name] = launch associated test ex: make strlen  
make v[funtion name] = launch associated test with valgrind ex: make vstrlen  
make vs[funtion name] = open the corresponding tests in vscode ex: make vsstrlen  

*FOR RIGOROUS TEST YOU SHOULD RUN ALL TESTS WITH VALGRIND*  

# Outputs

![alt text](https://i.imgur.com/bOLM4c7.png)

MOK / MKO = test about your malloc size  
ERRNOOK / ERRNOKO = test about errno value  

# Report bugs / Improvement
Contact me on slack or discord : jgambard 
