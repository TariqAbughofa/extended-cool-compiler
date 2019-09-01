
#include "Actions.h"
#include <fstream>

char * file_name = "c:\\code.vm";
int if_count = 0;
int while_count = 0;
int switch_count = 0;
int let_count = 0;
SymbolTable* symbol_table = new SymbolTable();

//----------------------------------------- generate code ------------------------------------------
class GenerateCode
{
public:
	
	ofstream file;

	GenerateCode(char * file_name)
	{
		this->file.open(file_name);
	}

	void OrGenerateCode()
	{
		file << "or :" << endl;
		file << "PUSHL -2" << endl;
		file << "JZ or_1" << endl;
		file << "PUSHI 1" << endl;
		file << "STOREL -2" << endl;
		file << "RETURN" << endl;
		file << "or_1 :" << endl;
		file << "PUSHL -1" << endl;
		file << "JZ or_2" << endl;
		file << "PUSHI 1" << endl;
		file << "STOREL -2" << endl;
		file << "RETURN" << endl;
		file << "or_2 :" << endl;
		file << "PUSHI 0" << endl;
		file << "STOREL -2" << endl;
		file << "RETURN" << endl;
	}
};

GenerateCode* vm = new GenerateCode(file_name);

//----------------------------------------- symbol table ------------------------------------------
bool Check::checkEntryPoint()
{
	if ((symbol_table->hasMain)&&(symbol_table->entry_points == 1))
		return true;
	else
		return false;
}

void Actions::collectStatic(Variable *& var)
{
	if (my_modifiers::found(var->modi,Static))
	{
		var->id = symbol_table->staticVars.size() + 1;
		symbol_table->staticVars.push_back(var);
	}
}

void Actions::isEntryMethod()
{
	list <char*> t; t.push_back("SELF_TYPE");
	if ((strcmp(currClass->name,"Main")==0)&&(strcmp(currMethod->name,"main")==0)&&(currMethod->parameters.empty())&&(commonUse::equal_char(currMethod->returnType->implement,t)))
	{
		symbol_table->main = new Method(); symbol_table->main = currMethod;
		symbol_table->Main = new Class(); symbol_table->Main = currClass;
		symbol_table->entry_points++;
		symbol_table->hasMain = true;
	}
}

void Actions::generateCode()
{
	vm->file << "START" << endl;
	//Null value
	vm->file << "ALLOC 0" << endl;
	symbol_table->GenerateCodeStatic();
	vm->file << "PUSHN 1" << endl;
	//self for Main class
	vm->file << "ALLOC " << (symbol_table->Main->fieldCount+1) << endl;
	vm->file << "DUP 1" << endl;
	vm->file << "PUSHS " << '"' << symbol_table->Main->label.c_str() << '"' << endl;
	vm->file << "STORE 0" << endl;
	list <Variable *>::iterator i = symbol_table->Main->fields.begin();
	while (i != symbol_table->Main->fields.end())
	{
		if (!my_modifiers::found((*i)->modi,Static))
		{
			vm->file << "DUP 1" << endl;
			if (((*i)->val == NULL)||((*i)->val->grp != ARRAY_SIZE))
				(*i)->val->generateCode();
			else
				(*i)->generateCode();
			vm->file << "STORE " << ((Variable *)*i)->id << endl;
		}
		i++;
	}
	vm->file << "PUSHA " << symbol_table->main->label.c_str() << endl;
	vm->file << "CALL" << endl;
	vm->file << "POP 2" << endl;
	if (!symbol_table->staticVars.empty())
		vm->file << "POP " << symbol_table->staticVars.size() << endl;
	vm->file << "STOP" << endl;
	vm->OrGenerateCode();
	this->root->generateCode();
}

void SymbolTable::GenerateCodeStatic()
{
	list <Variable *>::iterator i = this->staticVars.begin();
	while (i != this->staticVars.end())
	{
		((Variable *)*i)->generateCode();
		((Variable *)*i)->val->generateCode();
		vm->file << "STOREG " << ((Variable *)*i)->id << endl;
		i++;
	}
}

void SymbolTable::GenerateCodeClassString()
{
	vm->file << "String_concat :" << endl;
	vm->file << "PUSHL -1" << endl;
	vm->file << "PUSHL -2" << endl;
	vm->file << "LOAD 0" << endl;
	vm->file << "CONCAT" << endl;
	vm->file << "STOREL -3" << endl;
	vm->file << "RETURN" << endl;
}

void SymbolTable::GenerateCodeClassIO()
{
	vm->file << "IO_in_string :" << endl;
	vm->file << "READ" << endl;
	vm->file << "STOREL -3" << endl;
	vm->file << "RETURN" << endl;
	vm->file << "IO_in_int :" << endl;
	vm->file << "READ" << endl;
	vm->file << "ATOI" << endl;
	vm->file << "STOREL -3" << endl;
	vm->file << "RETURN" << endl;
	vm->file << "IO_in_float :" << endl;
	vm->file << "READ" << endl;
	vm->file << "ATOF" << endl;
	vm->file << "STOREL -3" << endl;
	vm->file << "RETURN" << endl;
	vm->file << "IO_out_string :" << endl;
	vm->file << "PUSHL -2" << endl;
	vm->file << "LOAD 0" << endl;
	vm->file << "WRITES" << endl;
	vm->file << "RETURN" << endl;
	vm->file << "IO_out_int :" << endl;
	vm->file << "PUSHL -2" << endl;
	vm->file << "LOAD 0" << endl;
	vm->file << "WRITEI" << endl;
	vm->file << "RETURN" << endl;
	vm->file << "IO_out_float :" << endl;
	vm->file << "PUSHL -2" << endl;
	vm->file << "LOAD 0" << endl;
	vm->file << "WRITEF" << endl;
	vm->file << "RETURN" << endl;
}

void SymbolTable::GenerateCodeClassObject()
{
	vm->file << "Object_type_name :" << endl;
	vm->file << "PUSHL -1" << endl;
	vm->file << "LOAD 0" << endl;
	vm->file << "STOREL -3"  << endl;
	vm->file << "RETURN" << endl;
	vm->file << "Object_abort :" << endl;
	vm->file << "ERR " << '"' << "Program terminated" << '"' << endl;
	vm->file << "RETURN" << endl;
}

void Symbol::generateCode(){} //for interface

void NameSpace::generateCode()
{
	vm->file << "//namespace " << this->label.c_str() << endl;
	NameSpace * tmpNamespace = this;
	list <Symbol *>::iterator i = tmpNamespace->Local.begin();
	while (i != tmpNamespace->Local.end())
	{
		(*i)->generateCode();
		i++;
	}
	if (tmpNamespace->next != NULL)
		tmpNamespace->next->generateCode();
}

void Class::generateCode()
{
	if (strcmp(this->name,"String")==0)
		symbol_table->GenerateCodeClassString();
	else if (strcmp(this->name,"IO")==0)
		symbol_table->GenerateCodeClassIO();
	else if (strcmp(this->name,"Object")==0)
		symbol_table->GenerateCodeClassObject();
	else if ((strcmp(this->name,"Int")==0)||(strcmp(this->name,"Float")==0)||(strcmp(this->name,"Bool")==0)){}
	else
	{
		vm->file << "//class " << this->label.c_str() << endl;
		list <Method *>::iterator f = this->localFuncs.begin();
		while (f !=this->localFuncs.end())
		{
			if (!my_modifiers::found(this->modi,Abstract))
				(*f)->generateCode();
			f++;
		}
	}
}

void Method::generateCode()
{
	vm->file << this->label.c_str() << " :" << endl;
	list <Variable *>::iterator i = this->Local.begin();
	int mem = 0;
	while (i != this->Local.end())
	{
		((Variable *)*i)->generateCode();
		mem++;
		i++;
	}
	list <Scope *>::iterator s = this->LocalScopes.begin();
	while (s != this->LocalScopes.end())
	{
		list <Variable *>::iterator v = ((Scope *)*s)->Local.begin();
		while (v != ((Scope *)*s)->Local.end())
		{
			((Variable *)*v)->id += mem;
			((Variable *)*v)->generateCode();
			v++;
		}
		s++;
	}
	AST * tmpAST = this->absTree;
	while (tmpAST != NULL)
	{
		tmpAST->exprTree->generateCode();
		if ((tmpAST->exprTree->grp == FUNCTION_CALL)||(tmpAST->exprTree->grp == OBJ_FUNC_CALL))
			vm->file << "POP 1" << endl;
		tmpAST = tmpAST->nextExpr;
	}
	if (this->constructor)
	{
		vm->file << "PUSHL -1" << endl;
		vm->file << "STOREL -3" << endl;
		vm->file << "RETURN" << endl;
	}
	else if (strcmp(*this->returnType->implement.begin(),"Void")==0)
		vm->file << "RETURN" << endl;
	//add extra return for emergency!!
	else
	{
		if (strcmp(*this->returnType->implement.begin(),"Int")==0)
			vm->file << "PUSHI 0" << endl;
		else if (strcmp(*this->returnType->implement.begin(),"Float")==0)
			vm->file << "PUSHF 0.0" << endl;
		else if (strcmp(*this->returnType->implement.begin(),"String")==0)
			vm->file << "PUSHS " << '"' << '"' << endl;
		else if (strcmp(*this->returnType->implement.begin(),"Bool")==0)
			vm->file << "PUSHI 0" << endl;
		else //if object
			vm->file << "PUSHG 0" << endl;
		vm->file << "STOREL -3" << endl;
		vm->file << "RETURN" << endl;
	}
}

void Variable::generateCode()
{
	if ((this->val == NULL)||(this->val->grp != ARRAY_SIZE))
	{
		if (this->type == variable)
		{
			if (strcmp(*this->varType->implement.begin(),"Int")==0)
				vm->file << "PUSHI 0" << endl;
			else if (strcmp(*this->varType->implement.begin(),"Float")==0)
				vm->file << "PUSHF 0.0" << endl;
			else if (strcmp(*this->varType->implement.begin(),"String")==0)
				vm->file << "PUSHS " << '"' << '"' << endl;
			else if (strcmp(*this->varType->implement.begin(),"Bool")==0)
				vm->file << "PUSHI 0" << endl;
			else //if object
				vm->file << "PUSHG 0" << endl;
		}
		else if (this->type == field)
			this->val->generateCode();
	}
	else if (((ArraySize *)this->val)->x != 0) //if static array
	{
		vm->file << "ALLOC " << ((ArraySize *)this->val)->x << endl;
		if (strcmp(*this->varType->implement.begin(),"Int")==0)
			for (int i=0; i<((ArraySize *)this->val)->x; i++)
			{
				vm->file << "DUP 1" << endl;
				vm->file << "PUSHI 0" << endl;
				vm->file << "STORE 0" << endl;
			}
		else if (strcmp(*this->varType->implement.begin(),"Float")==0)
			for (int i=0; i<((ArraySize *)this->val)->x; i++)
			{
				vm->file << "DUP 1" << endl;
				vm->file << "PUSHF 0.0" << endl;
				vm->file << "STORE 0" << endl;
			}
		else if (strcmp(*this->varType->implement.begin(),"String")==0)
			for (int i=0; i<((ArraySize *)this->val)->x; i++)
			{
				vm->file << "DUP 1" << endl;
				vm->file << "PUSHS " << '"' << '"' << endl;
				vm->file << "STORE 0" << endl;
			}
		else if (strcmp(*this->varType->implement.begin(),"Bool")==0)
			for (int i=0; i<((ArraySize *)this->val)->x; i++)
			{
				vm->file << "DUP 1" << endl;
				vm->file << "PUSHI 0" << endl;
				vm->file << "STORE 0" << endl;
			}
		else //if object
			for (int i=0; i<((ArraySize *)this->val)->x; i++)
			{
				vm->file << "DUP 1" << endl;
				vm->file << "PUSHG 0" << endl;
				vm->file << "STORE 0" << endl;
			}
	}
	else  //if DYNAMIC array
		vm->file << "PUSHG 0" << endl;
}

//----------------------------------------- abstract tree ------------------------------------------

void Node::generateCode() {vm->file << "//empty node !!!" << endl;}  //shoudn't be called !!!

void Const_Node::generateCode()
{
	switch (this->type.type)
	{
	case 0: vm->file << "PUSHG 0" << endl; break;
	case 1: vm->file << "PUSHI " << this->type.iv << endl; break;
	case 2: vm->file << "PUSHF " << this->type.fv << endl; break;
	case 3: vm->file << "PUSHS " << '"' << this->type.chv.c_str() << '"' << endl; break;
	case 4: vm->file << "PUSHI " << (int)this->type.bv << endl; break;
	}
}

void ID_Node::generateCode()
{
	if (this->var->type == variable)						//local variable
		vm->file << "PUSHL " << this->var->id << endl;
	else if (this->var->type == parameter)					//parameter
	{
		if (strcmp(this->var->name,"self")==0)
			vm->file << "PUSHL -1" << endl;
		else
		{
			vm->file << "PUSHL -2" << endl;
			vm->file << "LOAD " << this->var->id << endl;
		}
	}
	else if (this->var->type == field)						//field
	{
		if (my_modifiers::found(this->var->modi,Static))
			vm->file << "PUSHG " << this->var->id << endl;
		else
		{
			vm->file << "PUSHL -1" << endl;
			vm->file << "LOAD " << this->var->id << endl;
		}
	}
	if ((this->var->val != NULL)&&(this->var->val->grp == ARRAY_SIZE))
	{
		vm->file << "PUSHI 0" << endl;
		vm->file << "LOADN" << endl;
	}
}

void ObjectID_Node::generateCode()
{
	this->object->generateCode();
	vm->file << "LOAD " << this->var->id << endl;
	if ((this->var->val != NULL)&&(this->var->val->grp == ARRAY_SIZE))
	{
		vm->file << "PUSHI 0" << endl;
		vm->file << "LOADN" << endl;
	}
}

void Array_Node::generateCode()
{
	if (this->var->type == variable)						//local variable
		vm->file << "PUSHL " << this->var->id << endl;
	else if (this->var->type == parameter)					//parameter
	{
		if (strcmp(this->var->name,"self")==0)
			vm->file << "PUSHL -1" << endl;
		else
		{
			vm->file << "PUSHL -2" << endl;
			vm->file << "LOAD " << this->var->id << endl;
		}
	}
	else if (this->var->type == field)						//field
	{
		if (my_modifiers::found(this->var->modi,Static))
			vm->file << "PUSHG " << this->var->id << endl;
		else
		{
			vm->file << "PUSHL -1" << endl;
			vm->file << "LOAD " << this->var->id << endl;
		}
	}
	this->x->generateCode();
	vm->file << "LOADN" << endl;
}

void ObjectArray_Node::generateCode()
{
	this->object->generateCode();
	vm->file << "LOAD " << this->var->id << endl;
	this->x->generateCode();
	vm->file << "LOADN" << endl;
}

void FunctionCall_Node::generateCode()
{
	//return value
	//if (this->locate->haveReturn)
		vm->file << "PUSHN 1" << endl;
	//parameter
	AST* para = this->callSegn;
	int len=0;
	//if (para->size()>0)
		vm->file << "ALLOC " << para->size() << endl;
	if (para->size()>0)
		while(para!=NULL)
		{
			vm->file << "DUP 1" << endl;
			para->exprTree->generateCode();
			vm->file << "STORE " << len << endl;
			para=para->nextExpr;
			len++;
		}
	//add paramter self
	//if (!my_modifiers::found(this->locate->modi,Static))
		vm->file << "PUSHL -1" << endl;
	vm->file << "PUSHA " << this->locate->label.c_str() << endl;
	vm->file << "CALL" << endl;
	//get rid of local
	//vm->file << "POP " << this->locate->Local.size() << endl;
	//if (!my_modifiers::found(this->locate->modi,Static))
		vm->file << "POP 1" << endl;
	//if (para->size()>0)
		vm->file << "FREE" << endl;
}

void ObjectFuncCall_Node::generateCode()
{
	if (this->grp == FUNCTION_CALL)
		(new FunctionCall_Node(this->locate,this->callSegn))->generateCode();
	else
	{
		//return value
		//if (this->locate->haveReturn)
			vm->file << "PUSHN 1" << endl;
		//parameter
		AST* para = this->callSegn; int len=0;
		//if (para->size()>0)
			vm->file << "ALLOC " << para->size() << endl;
		if (para->size()>0)
		{
			while(para!=NULL)
			{
				vm->file << "DUP 1" << endl;
				para->exprTree->generateCode();
				vm->file << "STORE " << len << endl;
				para=para->nextExpr;
				len++;
			}
		}
		//call object instaid of self
		this->object->generateCode();
		//check polymorphism & overriding
		if ((my_modifiers::found(this->locate->modi,Virtual))||(my_modifiers::found(this->locate->modi,Override))||(my_modifiers::found(this->locate->modi,Abstract)))
		{
			vm->file << "DUP 1" << endl;
			vm->file << "LOAD 0" << endl;
			switch_count++;
			list<string>::iterator Case = this->locate->virtualList1.begin(); int caseNum = 0;
			list<string>::iterator call = this->locate->virtualList2.begin();
			while (Case != this->locate->virtualList1.end())
			{
				caseNum++;
				vm->file << "switch_" << switch_count << "_case_" << caseNum << " :" <<endl;
				vm->file << "DUP 1" << endl;
				vm->file << "PUSHS " << '"' << ((string)*Case).c_str() << '"' << endl;
				vm->file << "EQUAL" << endl;
				vm->file << "JZ " << "switch_" << switch_count << "_case_" << caseNum+1 <<endl;
				vm->file << "POP 1" << endl;
				vm->file << "PUSHA " << ((string)*call).c_str() << endl;
				vm->file << "JUMP " << "switch_" << switch_count << "_end" <<endl;
				Case++; call++;
			}
			vm->file << "switch_" << switch_count << "_case_" << caseNum+1 << " :" <<endl;
			vm->file << "switch_" << switch_count << "_end :" <<endl;
		}
		else
			vm->file << "PUSHA " << this->locate->label.c_str() << endl;
		//call function
		vm->file << "CALL" << endl;
		//get rid of local
		//vm->file << "POP " << this->locate->Local.size() << endl;
		vm->file << "POP 1" << endl;
		//if (para->size()>0)
			vm->file << "FREE" << endl;
	}
}

void ConstructCall_Node::generateCode()
{
	vm->file << "PUSHN 1" << endl;
	//parameters
	AST* para = this->callSegn; int len=0;
	vm->file << "ALLOC " << para->size() << endl;
	if (para->size()>0)
	while(para!=NULL)
	{
		vm->file << "DUP 1" << endl;
		para->exprTree->generateCode();
		vm->file << "STORE " << len << endl;
		para=para->nextExpr;
		len++;
	}
	//self parameter
	vm->file << "ALLOC " << (((Class *)this->initClass->place)->fieldCount+1) << endl;
	vm->file << "DUP 1" << endl;
	vm->file << "PUSHS " << '"' << ((Class *)this->initClass->place)->label.c_str() << '"' << endl;
	vm->file << "STORE 0" << endl;
	Class* tmp = (Class *)this->initClass->place;
	while (tmp!=NULL)
	{
		list <Variable *>::iterator i = tmp->fields.begin();
		while (i != tmp->fields.end())
		{
			if (!my_modifiers::found((*i)->modi,Static))
			{
				vm->file << "DUP 1" << endl;
				if (((*i)->val == NULL)||((*i)->val->grp != ARRAY_SIZE))
					(*i)->val->generateCode();
				else
					(*i)->generateCode();
				vm->file << "STORE " << ((Variable *)*i)->id << endl;
			}
			i++;
		}
		tmp = (Class *)tmp->inherit_class->place;
	}
	vm->file << "PUSHA " << this->locate->label.c_str() << endl;
	vm->file << "CALL" << endl;
	//get rid of local
	//vm->file << "POP " << this->locate->Local.size() << endl;
	vm->file << "POP 1" << endl;
	//if (para->size()>0)
		vm->file << "FREE" << endl;
}

void Return_Node::generateCode()
{
	this->ReturnVal->generateCode();
	vm->file << "STOREL -3" <<endl;
	vm->file << "RETURN" << endl;
}

void Assignment_Node::generateCode()
{
	if (this->var->grp == IDENTIFIER)
	{
		if (((ID_Node *)this->var)->var->type == variable)
		{
			this->value->generateCode();
			vm->file << "STOREL " << ((ID_Node *)this->var)->var->id << endl;
		}
		else if (((ID_Node *)this->var)->var->type == parameter)
		{
			this->value->generateCode();
			vm->file << "STOREL -" << ((ID_Node *)this->var)->var->id << endl;
		}
		else if (((ID_Node *)this->var)->var->type == field)
		{
			if (my_modifiers::found(((ID_Node *)this->var)->var->modi,Static))
			{
				this->value->generateCode();
				vm->file << "STOREG " << ((ID_Node *)this->var)->var->id << endl;
			}
			else
			{
				vm->file << "PUSHL -1" << endl; //get self adress
				this->value->generateCode();
				vm->file << "STORE " << ((ID_Node *)this->var)->var->id << endl;
			}
		}
	}
	else if (this->var->grp == OBJ_ID)
	{
		if (my_modifiers::found(((ObjectID_Node *)this->var)->var->modi,Static))
			vm->file << "STOREG " << ((ObjectID_Node *)this->var)->var->id << endl;
		else
		{
			((ObjectID_Node *)this->var)->object->generateCode();
			this->value->generateCode();
			vm->file << "STORE " << ((ObjectID_Node *)this->var)->var->id << endl;
		}
	}
	else if (this->var->grp == ARRAY)
	{
		if (((Array_Node *)this->var)->var->type == variable)
		{
			vm->file << "PUSHL " << ((Array_Node *)this->var)->var->id << endl;
			((Array_Node *)this->var)->x->generateCode();
			this->value->generateCode();
			vm->file << "STOREN " << endl;
		}
		else if (((Array_Node *)this->var)->var->type == field)
		{
			vm->file << "PUSHL -1" << endl; //get self adress
			vm->file << "LOAD " << ((Array_Node *)this->var)->var->id << endl;
			((Array_Node *)this->var)->x->generateCode();
			this->value->generateCode();
			vm->file << "STOREN " << endl;
		}
	}
	else if (this->var->grp == OBJ_ARRAY)
	{
		((ObjectArray_Node *)this->var)->object->generateCode();
		vm->file << "LOAD " << ((ObjectArray_Node *)this->var)->var->id << endl;
		((ObjectArray_Node *)this->var)->x->generateCode(); 
		this->value->generateCode();
		vm->file << "STOREN " << endl;
	}
}

void Binary_Node::generateCode()
{
	this->rightSon->generateCode();
	this->leftSon->generateCode();
	my_implements * t = new my_implements(); int val = this->returnValType(t);
	if (val == 1)
		switch (this->opType)
		{
		case SUM: vm->file << "ADD" << endl; break;
		case SUB: vm->file << "SUB" << endl; break;
		case MULT: vm->file << "MUL" << endl; break;
		case DIVS: vm->file << "DIV" << endl; break;
		}
	else if (val == 2)
		switch (this->opType)
		{
		case SUM: vm->file << "FADD" << endl; break;
		case SUB: vm->file << "FSUB" << endl; break;
		case MULT: vm->file << "FMUL" << endl; break;
		case DIVS: vm->file << "FDIV" << endl; break;
		}
	else if (val == 4)
	{
		if (this->leftSon->returnValType(t) == 4)
			switch (this->opType)
			{
			case AND: vm->file << "MUL" << endl; break;
			case OR: vm->file << "PUSHA or" << endl; vm->file << "CALL" << endl; vm->file << "POP 1" << endl; break;
			}
		else if (this->leftSon->returnValType(t) == 1)
		{
			switch (this->opType)
			{
			case EQL: vm->file << "EQUAL" << endl; break;
			case LESS: vm->file << "INF" << endl; break;
			case LSEQ: vm->file << "INFEQ" << endl; break;
			case MORE: vm->file << "SUP" << endl; break;
			case MREQ: vm->file << "SUPEQ" << endl; break;
			}
		}
		else if (this->leftSon->returnValType(t) == 2)
		{
			switch (this->opType)
			{
			case EQL: vm->file << "EQUAL" << endl; break;
			case LESS: vm->file << "FINF" << endl; break;
			case LSEQ: vm->file << "FINFEQ" << endl; break;
			case MORE: vm->file << "FSUP" << endl; break;
			case MREQ: vm->file << "FSUPEQ" << endl; break;
			}
		}
	}
}

void Unary_Node::generateCode()
{
	this->son->generateCode();
	switch (this->opType)
	{
	case COMP: vm->file << "NOT" << endl; break;
	case LCOMP: vm->file << "PUSHI 1024" << endl; vm->file << "SWAP" << endl; vm->file << "SUB" << endl; break;
	case NULLCHECK: vm->file << "PUSHG 0" << endl; vm->file << "EQUAL" << endl; break;
	case DEL: vm->file << "FREE" << endl; break;
	}
}

void IF_Node::generateCode()
{
	if_count++;
	this->Condition->generateCode();
	vm->file << "JZ " << "else_begin_" << if_count << endl;
	this->if_true->generateCode();
	vm->file << "JUMP " << "else_end_" << if_count << endl;
	vm->file << "else_begin_" << if_count << " :" << endl;
	this->if_else->generateCode();
	vm->file << "else_end_" << if_count << " :" << endl;
}

void WHILE_Node::generateCode()
{
	while_count++;
	vm->file << "while_begin_" << while_count << " :" << endl;
	this->Condition->generateCode();
	vm->file << "JZ " << "while_end_" << while_count << endl;
	this->Body->generateCode();
	vm->file << "JUMP " << "while_begin_" << while_count << endl;
	vm->file << "while_end_" << while_count << " :" << endl;
}

void Upcast_Node::generateCode()
{
	if (strcmp(*this->upperType->implement.begin(),"Float") == 0)
	{
		this->son->generateCode();
		vm->file << "ITOF" << endl;
	}
}

void Downcast_Node::generateCode()
{
	this->son->generateCode();
	if (strcmp(*this->lowerType->implement.begin(),"Int") == 0)
		vm->file << "FTOI" << endl;
}

void Scope::generateCode()
{
	AST * tmpAST = this->Body;
	while (tmpAST != NULL)
	{
		tmpAST->exprTree->generateCode();
		if ((tmpAST->exprTree->grp == FUNCTION_CALL)||(tmpAST->exprTree->grp == OBJ_FUNC_CALL))
			vm->file << "POP 1" << endl;
		tmpAST = tmpAST->nextExpr;
	}
}

void CASE_Node::generateCode()
{
	switch_count++;
	this->caseOf->generateCode();
	list<Const_Node *>::iterator v = this->caseExprs.values.begin(); int caseNum = 0;
	list<Node *>::iterator b = this->caseExprs.Body.begin();
	while (v != this->caseExprs.values.end())
	{
		caseNum++;
		vm->file << "switch_" << switch_count << "_case_" << caseNum << " :" <<endl;
		vm->file << "DUP 1" << endl;
		((Const_Node *)(*v))->generateCode();
		vm->file << "EQUAL" << endl;
		vm->file << "JZ " << "switch_" << switch_count << "_case_" << caseNum+1 <<endl;
		((Node *)(*b))->generateCode();
		v++; b++;
	}
	vm->file << "switch_" << switch_count << "_case_" << caseNum+1 << " :" <<endl;
	vm->file << "POP 1" << endl;
}

void Let_Node::generateCode()
{
	let_count++;
	vm->file << "PUSHN 1" << endl;
	vm->file << "PUSHA " << "let_" << let_count << endl;
	vm->file << "CALL" << endl;
	vm->file << "JUMP " << "let_end_" << let_count << endl;
	vm->file << "let_" << let_count << " :" << endl;
	list <Variable *>::iterator i = this->letScope->Local.begin();
	while (i != this->letScope->Local.end())
	{
		((Variable *)*i)->generateCode();
		i++;
	}
	this->letScope->Body->exprTree->generateCode();
	vm->file << "STOREL -1" << endl;
	vm->file << "RETURN" << endl;
	vm->file << "let_end_" << let_count << " :" << endl;
}

void DynamicArrayInit_Node::generateCode()
{
	this->initSize->generateCode();
	vm->file << "DUP 1" << endl;
	vm->file << "ALLOCN" << endl;
	my_implements * t = new my_implements(); this->var->returnValType(t);
	while_count++;
	this->initSize->generateCode();
	vm->file << "while_begin_" << while_count << " :" << endl;
	vm->file << "PUSHI 1" << endl;
	vm->file << "SUB" << endl;
	vm->file << "DUP 1" << endl;
	vm->file << "JZ " << "while_end_" << while_count << endl;
	vm->file << "DUP 2" << endl;
	if (strcmp(*t->implement.begin(),"Int")==0)
		vm->file << "PUSHI 0" << endl;
	else if (strcmp(*t->implement.begin(),"Float")==0)
		vm->file << "PUSHF 0.0" << endl;
	else if (strcmp(*t->implement.begin(),"String")==0)
		vm->file << "PUSHS " << '"' << '"' << endl;
	else if (strcmp(*t->implement.begin(),"Bool")==0)
		vm->file << "PUSHI 0" << endl;
	else //if object
		vm->file << "PUSHG 0" << endl;
	vm->file << "STOREN" << endl;

	vm->file << "JUMP " << "while_begin_" << while_count << endl;
	vm->file << "while_end_" << while_count << " :" << endl;
	vm->file << "POP 1" << endl;
	//initialize array
	if (this->var->grp == ARRAY)
	{
		if (((Array_Node *)this->var)->var->type == variable)
			vm->file << "STOREL " << ((Array_Node *)this->var)->var->id << endl;
		else if (((Array_Node *)this->var)->var->type == field)
		{
			vm->file << "PUSHL -1" << endl; //get self adress
			vm->file << "STORE " << ((Array_Node *)this->var)->var->id << endl;
		}
	}
	else if (this->var->grp == OBJ_ARRAY)
	{
		((ObjectArray_Node *)this->var)->object->generateCode();
		vm->file << "STORE " << ((ObjectArray_Node *)this->var)->var->id << endl;
	}
}