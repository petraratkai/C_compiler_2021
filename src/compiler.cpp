#include<iostream>
#include <fstream>
#include <vector>
#include "../include/ast.hpp"
#include "../include/ast/Context.hpp"
//#include "../include/ast/ast_primitives.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	//parse the AST
//Context ctxt(0);
	Program *prog = parseAST(argv[2]); //arguments?? which file?

//	Number const1(1);
	//std::cout<<const
	/*Number* const2 = new Number(2);
	Number* const4 = new Number(4);
	Declaration* Decl = new Declaration(IntType, "a", nullptr);
	Operator* add2_4 = new Operator(const2, const4, "+");
	ReturnStmt* ret2 = new ReturnStmt(add2_4);

	//std::cout<<(ret2->getRetVal())->getValue();
	std::vector<Statement*>* stmts = new std::vector<Statement*>;
	stmts->push_back(Decl);
	stmts->push_back(ret2);

	CompoundStmt* mainbody = new CompoundStmt(stmts);
	std::vector<Statement*> param;
	Function *mainfunct = new Function("main", mainbody, &param, IntType);
	//std::vector<Function*> functions;
	//functions.push_back(mainfunct);
	//Program *prog = new Program(functions);*/
	std::ofstream Out(argv[4]);

	//create hash table for variables
	//std::vector<Variable_hash> variables; //will need to push back an element every time a variable is declared
	/*Out<<"j main"<<std::endl;
	std::vector<Function*> funct; //=  prog->getFunctions();
	funct.push_back(mainfunct);
	//CompoundStmt* body =
	//vector<Statement*>* stmts = body->getStmts();*/
	std::vector<Function*> fns = prog->getFunctions();
	//(fns[0])->getName();
	//std::cerr<<"here";
	try {
	Out<<".data" << std::endl;

	std::vector<Statement*> decl = prog->getDeclarations();
	std::vector<Variable_hash> global_variables;
	//std::cerr<<decl.size(); //decl[0]->getArraySize()->getValue();
	for(int i = 0; i<decl.size(); i++)
	{	//std::cerr<<"here";

		if(decl[i]->getArraySize())
		{
			Out << decl[i]->getVariable() + ":" << std::endl;
			for(int j = 0; j<decl[i]->getArraySize(); j++)
			{ //std::cerr<<"here";
			Out <<"		.word		";
			if(decl[i]->getExpr())
			{
				Out<<decl[i]->getExpr(j)->getValue() << std::endl;
				Out << std::endl;
			}
			else
			{
				Out <<"0" << std::endl;
			}
			Variable_hash newGlobal(decl[i]->getVariable(), ((Declaration*)decl[i])->getType(global_variables), true);
			global_variables.push_back(newGlobal);
		}
		}


	}
//std::cerr<<"here";
	Out << "$Ltext0:" << std::endl;
	//std::vector<Variable_hash> global_vars;
		//std::cerr<<"here";
	for(int i = 0; i<fns.size(); i++)
	{
		Out << ".global " + fns[i]->getName()  << std::endl;
	}
		//std::cerr<<"here";
	for(int i = 0; i<fns.size(); i++)
	{
	CompileFunct(fns[i], Out, global_variables);
	}

//delete ret2;
//delete mainfunct;
delete prog;
//registers
//ideas: vector of bools -> taken or notes
//
	Out.close();
}
catch (std::string msg)
{
	std::cerr << msg;
}



}
