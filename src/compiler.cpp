#include<iostream>
#include <fstream>
#include "../include/ast.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	//parse the AST
	Program *prog;
	//Program *prog = parseAST(); //arguments?? which file?
	std::ofstream Out(argv[3]);

	//create hash table for variables
	std::vector<Variable_hash> variables; //will need to push back an element every time a variable is declared

//registers
//ideas: vector of bools -> taken or notes
//
	Out.close();


	/*std::cout << "f:" << std::endl;
	std::cout << "PUSH0:" << std::endl;
	std::cout << "addiu $sp, $sp, -44" << std::endl;
	std::cout << "sw $ra, 40($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $fp, 36($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s0, 4($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s1, 8($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s2, 12($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s3, 16($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s4, 20($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s5, 24($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s6, 28($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s7, 32($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "move $fp, $sp" << std::endl;
	std::cout << "body2:" << std::endl;
	std::cout << "li $v0, 42" << std::endl;
	std::cout << "addiu $sp, $sp, 0" << std::endl;
	std::cout << "move $fp, $sp" << std::endl;
	std::cout << "b POP1" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "addiu $sp, $sp, 0" << std::endl;
	std::cout << "move $fp, $sp" << std::endl;
	std::cout << "POP1:" << std::endl;
	std::cout << "mtc1 $v0, $f0" << std::endl;
	std::cout << "lw $s0, 4($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s1, 8($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s2, 12($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s3, 16($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s4, 20($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s5, 24($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s6, 28($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s7, 32($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $ra, 40($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $fp, 36($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "move $sp, $fp" << std::endl;
	std::cout << "jr $ra" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << ".global f" << std::endl;*/
}
