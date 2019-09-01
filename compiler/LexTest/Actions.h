#include  "AST.h"

class Actions {

public:

	NameSpace *root;
	NameSpace *currNamespace;
	Class *currClass;
	Interface* currInterface;
	Method* currMethod;
	Variable* currVariable;
	Scope *currScope;

	bool sure;//namespace
	bool sure_; //inteface , class
	bool sure__; //method ,variable
	
	LaterDef* my_laterDef;
	bool later;
	bool laterTree;
	bool FirstDad;

	Refuse* My_ref;
	Error* My_err;
	Warn* My_wrn;
	Check * my_check;
	
    //----------------------------------Constructor-------------------------------------
	Actions();
	void Print_SymbolTable ();

	//----------------------------------NamespaceAction----------------------------------
	bool Search_Root(Symbol *t,Symbol *brother);
	void NameSpace_Action(list<char*> implement,int line,bool exe);

	//----------------------------------ClassAction--------------------------------------
	void Class_Action(list <Modifier> modi,list <my_implements *>& lists,my_implements *& QID,char* name,int line);
	void closeClass_Action(int);
	void Get_Labels(Class*,Class*&);
	void Get_Labels_Interface(Class*,Class* );
	void Process_Interface(Class*,Class*,Interface*&);
	void Get_Label_Interface(Interface*,Class*);

	//---------------------------------FieldClassAction-----------------------------
	void VariablesClass_Action(list<Modifier> modi,my_implements *&QID,char *name,int line);
	void ArraysClass_Action(list<Modifier> modi,my_implements *&QID,char *name,int x,int line);
	void DynArraysClass_Action(list<Modifier> modi,my_implements *&QID,char *name,int line);

	//---------------------------------MethodInClassAction------------------------------
	void MethodsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line);
	void FunctionsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line);
	void ConstructorsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line);
	void AbsMethodsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line);
	list<Method*> Get_Cons_Father(Class*);
	void EndFunction(Class*,AST*,int);

	//--------------------------------------Expr----------------------------------------
	Node* checkAssignment(Variable* ,Node* ,Node*&,int);
	Node* VariableDeclaration(my_implements *&,char *,int,Node *);
	Node* ArrayDeclaration(my_implements *,char *,int,int,Node *);
	Node* DynArrayDeclaration(my_implements *,char *,int,Node *);
	Node* CallLocalVar(char *,int,bool,bool);
	Node* CallVariable(my_implements *,bool, int);
	Node* CallClassVar(Node *,char *,int);
	Node* CallArrVar(my_implements *,Node *, int);
	Node* AssignVariable(my_implements * ,Node*,int );
	Node* AssignClassVar(Node*,char*,Node*,int);
	Node* AssignArrVar(my_implements * ,Node* ,Node* ,int );
	Node* InitDynArray(my_implements *,my_implements *,Node*,int);
	Node* CallLocalFunc(char *,AST *,int);
	Node* CallFunction(my_implements * ,AST *,int);
	Node* CallClassFunc(Node *,char *,AST *,my_implements *,int);
	Node* CallConstructor(my_implements *&,AST *,int);
	Node* CallFather(AST*,int);
	Node* Casting(my_implements *,Node*,int);
	Node* IfStmt(Node*,Node*,Node*,int);
	Node* ReturnExpr(Node*,int);
	Node* WhileStmt(Node*,Scope* ,int);
	Variable* LetVarDeclaration(char *,my_implements *&,int ,Node *);
	Node* LetStmt(Scope*,int);
	Node* CaseStmt(Node*,Case_Expr ,bool& ,int);
	Node* ArthmExpr(BinaryOp,Node *,Node *,int);
	Node* ComparisonExpr(BinaryOp ,Node *,Node *,int);
	Node* LogicExpr(BinaryOp,Node *,Node *,int);
	Node* UnaryExpr(UnaryOp,Node *,int);

	//----------------------------------InterfaceAction------------------------------------
	void Interface_Action(list <Modifier> modi,list <my_implements *>& lists,char* name,int line);
	void closeInterface_Action(int line);
	bool SomeLater(list <my_implements*>);

	//---------------------------------MethodInInterfaceAction------------------------------
	void MehtodsInterface_Action(list <Variable*> parameter,my_implements *QID,char *name,int line);

	//---------------------------------LaterDefenitionAction--------------------------------
	void scanBottomUp();
	//---------------------------------CodeGenerationAction---------------------------------
	bool hasNoErrors();
	void collectStatic(Variable *&);
	void isEntryMethod();	
	void generateCode();
};