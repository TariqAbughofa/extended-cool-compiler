#include "errorMsg.h"

//----------------------------------------------Enum&&typedef--------------------------------------------

enum Modifier {Public=0,Private,Protected,Internal,Static,Readonly,Virtual,Sealed,Override,Abstract,New};

//---------------------Symbol----------------------------
class my_implements;
class Symbol
{
public:
	char* name;
	TYPE_ type;

	Symbol();
	virtual void generateCode();
	Symbol(char* name,TYPE_ type);
};

//----------------Variable & Parameter-------------------
class Node;
class Variable : public Symbol
{
public:

	list <Modifier> modi;
	my_implements* varType;
	int id;
	Node* val;

	Variable(char*);
	Variable(char* name,my_implements* varType);						//variable
	Variable(char* name,my_implements* varType,int paraID);			//Parameter
	Variable(char* name,my_implements* varType,list <Modifier> modi); //field
	void generateCode();
};

//---------------------Method----------------------------
class AST;
class Scope;
class Method : public Symbol
{
public:
	list <Modifier> modi;
	list <Variable *> parameters; //list of parameters
	my_implements *returnType;
	list <Variable *> Local;
	list <Scope *> LocalScopes;
	list <string> virtualList1; //<string for actual label>
	list <string> virtualList2; //<string for called label>
	AST* absTree;

	bool haveReturn;
	bool constructor;
	bool DadCall;
	string label;

	Method();
	Method(char* name,list<Variable *> parameters,list<Modifier> modi,my_implements* returnType,bool type);
	void addLocal(Variable *);
	bool searchMethod(Variable *);
	static bool equal_param (list <Variable *> ,list <Variable *> );
	void buildParaLabel();
	bool isVirtualOn(Method *);
	void generateCode();
};

//---------------------Class----------------------------

class Class : public Symbol
{
public:

	list<Variable *> fields;
	list<Method *> localFuncs;
	list<Modifier> modi;
	my_implements* inherit_class;
	list <my_implements*> ImplementListInterface; //list of interface
	list <Method*> Over_List;
	bool Over;
	bool OverInterface;
	bool Later;
	bool Cycle;

	bool haveConstructor;
	bool same_func;
	bool CheckOver;
	string label;
	int fieldCount;

	Class();
	Class(char* name,list <Modifier> modi,my_implements* inherit_class,list <my_implements*> ImplementListInterface);
	void addLocal(Symbol* member);
	bool search_Class(Symbol *);
	int namerateFields();
	void generateCode();
};

//---------------------Interface----------------------------
class Interface : public Symbol
{
public:
	list<Modifier> modi;
	list<Method *> Local;
	list <my_implements*> inherit_interface; //inherit's from interface
	bool Later;

	Interface();
	Interface(char* name,list <Modifier> modifier,list <my_implements*>inherit_interface);
	void addLocal(Method* member);
	bool search_interface(Method *);
};

//---------------------NameSpace----------------------------
class NameSpace : public Symbol
{
public:
	Symbol* next;
	Symbol* parent;
	list<Symbol *> Local;
	string label;

	NameSpace();
	NameSpace(char* name);
	void addLocal(Symbol *);
	bool searchNameSpace(Symbol *);
	void generateCode();
};

//------------------------------Symbol Table------------------
class SymbolTable
{
public:

	list <Variable *> staticVars;
	bool hasMain;
	int entry_points;
	Class * Main;
	Method* main;

	SymbolTable();
	static bool validName(char*);
	static NameSpace* buildSymbolTable();
	void GenerateCodeStatic();
	void GenerateCodeClassString();
	void GenerateCodeClassIO();
	void GenerateCodeClassObject();
};

//------------------------------my_modifiers ---------------------------------------
class my_modifiers
{
public :
	std::list <Modifier> modi;

	my_modifiers(Modifier init);
	void add_modifier(Modifier add);
	static bool found(list<Modifier> modi,Modifier g);
	~my_modifiers();
};

//------------------------------my_implements---------------------------------------
class my_implements 
{
public :
	std::list <char *> implement;
	Symbol *place;
	
	my_implements();
    my_implements(char *);
	void add_implement(char *add);
	~my_implements();
};

//------------------------------my_parameters---------------------------------------
class my_parameters 
{
public :
	std::list <Variable*> parameter;

	my_parameters();
	my_parameters(Variable *);
	void add_parameter(Variable*);
	~my_parameters ();
};

//------------------------------my_variables---------------------------------------

class my_variables 
{
public :
	std::list <Variable *> variable;

	my_variables(Variable *init);
	void add_variable (Variable* add);
	~my_variables();
};

//------------------------------my_QIDList---------------------------------------
class my_QIDList
{
public :
	std::list <my_implements *> lists;

	my_QIDList(my_implements *init);
	void add_list(my_implements *add);
	~my_QIDList();
};

//-------------------------------------------

