# A Simple REST Service using C++

Use cmake and make to build the project on a linux machine.

execute:

calculator



Description of parameters:
	cnumber: Denotes the number currently entered by the user.


	pnumber: Denotes the number previously entered by the user.


	operation: Denotes the requested operation.


	cmemory: Denotes the memory value used my mem+, mem-, memrcl


Addition
=======================================================================================

Input:

http://localhost:8888/calculator/calculator?cnumber=10&pnumber=5&operation=add&cmemory=0

Output:

{"CurrentNumber":15,"PreviousNumber":10,"Operation":"add","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=100000000000000000000000000000000&pnumber=100&operation=add&cmemory=0

Output:

{"CurrentNumber":100000000000000000000000000000100,"PreviousNumber":100000000000000000000000000000000,"Operation":"add","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=-100&pnumber=100&operation=add&cmemory=0

Output:

{"CurrentNumber":0,"PreviousNumber":-100,"Operation":"add","MemoryValue":0}


Subtraction
=======================================================================================


Input:

http://localhost:8888/calculator/calculator?cnumber=10&pnumber=5&operation=sub&cmemory=0

Output:

{"CurrentNumber":-5,"PreviousNumber":10,"Operation":"sub","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=100000000000000000000000000000000&pnumber=100&operation=sub&cmemory=0

Output:

{"CurrentNumber":-99999999999999999999999999999900,"PreviousNumber":100000000000000000000000000000000,"Operation":"sub","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=-100&pnumber=100&operation=sub&cmemory=0

Output:

{"CurrentNumber":200,"PreviousNumber":-100,"Operation":"sub","MemoryValue":0}


Multiplication
=======================================================================================


Input:

http://localhost:8888/calculator/calculator?cnumber=10&pnumber=5&operation=mul&cmemory=0

Output:

{"CurrentNumber":50,"PreviousNumber":10,"Operation":"mul","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=100000000000000000000000000000000&pnumber=100&operation=mul&cmemory=0

Output:

{"CurrentNumber":10000000000000000000000000000000000,"PreviousNumber":100000000000000000000000000000000,"Operation":"mul","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=-100&pnumber=100&operation=mul&cmemory=0

Output:

{"CurrentNumber":-10000,"PreviousNumber":-100,"Operation":"mul","MemoryValue":0}


Division
=======================================================================================

Input:

http://localhost:8888/calculator/calculator?cnumber=10&pnumber=5&operation=div&cmemory=0

Output:

{"CurrentNumber":0.5,"PreviousNumber":10,"Operation":"div","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=100000000000000000000000000000000&pnumber=100&operation=div&cmemory=0

Output:

{"CurrentNumber":1e-30,"PreviousNumber":100000000000000000000000000000000,"Operation":"div","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=-100&pnumber=100&operation=div&cmemory=0

Output:

{"CurrentNumber":-1,"PreviousNumber":-100,"Operation":"div","MemoryValue":0}

Mod
=======================================================================================

Input:

http://localhost:8888/calculator/calculator?cnumber=10&pnumber=5&operation=mod&cmemory=0

Output:

{"CurrentNumber":5,"PreviousNumber":10,"Operation":"mod","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=100000000000000000000000000000000&pnumber=100&operation=mod&cmemory=0

Output:

{"CurrentNumber":100,"PreviousNumber":100000000000000000000000000000000,"Operation":"mod","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=-100&pnumber=100&operation=mod&cmemory=0

Output:

{"CurrentNumber":0,"PreviousNumber":-100,"Operation":"mod","MemoryValue":0}


sqrt
=======================================================================================

Input:

http://localhost:8888/calculator/calculator?cnumber=10&pnumber=5&operation=sqrt&cmemory=0

Output:

{"CurrentNumber":3.16228,"PreviousNumber":10,"Operation":"sqrt","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=100000000000000000000000000000000&pnumber=100&operation=sqrt&cmemory=0

Output:

{"CurrentNumber":1e+16,"PreviousNumber":100000000000000000000000000000000,"Operation":"sqrt","MemoryValue":0}

Input:

http://localhost:8888/calculator/calculator?cnumber=-100&pnumber=100&operation=sqrt&cmemory=0

Output:

Operation failed!


mem+
=======================================================================================

Input:

http://localhost:8888/calculator/calculator?cnumber=99999999999999999999&pnumber=5&operation=mempls&cmemory=1

Output:

{"CurrentNumber":99999999999999999999,"PreviousNumber":5,"Operation":"mempls","MemoryValue":100000000000000000000}



mem-
=======================================================================================

Input:

http://localhost:8888/calculator/calculator?cnumber=100000000000000000000&pnumber=5&operation=memin&cmemory=1

Output:

{"CurrentNumber":100000000000000000000,"PreviousNumber":5,"Operation":"memmin","MemoryValue":-99999999999999999999}


mem-recall
=======================================================================================

Input:

http://localhost:8888/calculator/calculator?cnumber=99&pnumber=5&operation=memrcl&cmemory=1000000000

Output:

{"CurrentNumber":1000000000,"PreviousNumber":99,"Operation":"memrcl","MemoryValue":1000000000}