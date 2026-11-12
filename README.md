# Branch-Predictor-Simulator
Construction of a branch predictor simulator. Used to evaluate different configurations of branch predictors for coursework.
(No AI Used In Development)

## Instructions
1. Type "make" to build. (Type "make clean" first if you already compiled and want to recompile from scratch.)
     
3. Run trace reader:  
     
   To run without throttling output:  
   _./sim bimodal 6 gcc_trace.txt_  
   _./sim gshare 9 3 gcc_tracce.txt_  
     
   To run with throttling (via "less"):  
   _./sim bimodal 6 gcc_trace.txt | less_  
   _./sim gshare 9 3 gcc_trace.txt | less_

## Inputs 
**Format**: \<hex branch PC> t|n
- \<hex branch PC> is the address of the branch instruction in memory. this field is used to index into predictors.
- "t" indicates the branch is actually taken (Note: Not that it is predicted taken)
- "n" indicated the branch is not-taken

**Example**: 00a3b5fc t

   
     
