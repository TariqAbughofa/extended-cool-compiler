
#include "Our Check.h"

class Const_Type 
{
public:

	__int64 iv;
	float fv;
	string chv;
	bool bv;
	int type;

	Const_Type()
	{
		this->iv=0;
		this->fv=0;
		this->chv=new char;
		this->bv=false;
		this->type=0;
	}
};


enum Group_Node {
EMPTY = 0,
CONST,				//Int_Value, Float_Value, String_Value, True, False
IDENTIFIER,			//ID, ID[Int_Value]
OBJ_ID,				//QID, QID[Int_Value],expr.ID, expr.ID[Int_Value]
ARRAY,
OBJ_ARRAY,
UNARY,				//not expr, ~ expr, Isvoid expr
BINARY,				//expr op expr where op={+,-,*,/,=,<,<=,>,>=}
FUNCTION_CALL,		//ID(expr,*)
OBJ_FUNC_CALL,		//expr.id(expr,*), expr.id(expr,*),QID(expr,*)
CONSTRUCTOR_CALL,	//NEW QID(expr,*)
DYNAMIC_ARRAY,
ASSIGNMENT,			// ID<-expr, ID[int_Value]<-expr
UPCAST,				//expr @ QID
DOWNCAST,			//like: x:Float<-4;

//statments
IF_STMT,
WHILE_STMT,
CASE_STMT,
LET_STMT,

RETURN_EXPR,
SCOPE,

//magic
ARRAY_SIZE,
STATIC_CALL,
STATIC_ARRAY_CALL
};

enum BinaryOp {SUM=0, SUB, MULT, DIVS, EQL, LESS, LSEQ, MORE, MREQ, AND, OR};
enum UnaryOp {COMP=0, LCOMP, NULLCHECK,DEL};

/*----------------------------------------Parent Node----------------------------------*/

class Node
{
public:

	Group_Node grp;

	bool returnValue();
	int returnValType(my_implements* &);
	Node();
	Node(Group_Node);
	virtual void generateCode();
	~Node();
};

/*----------------------------------------Node Optimizing----------------------------------*/
/* my Optizations:
			1. Const_Node op Const_Node like: true = true , 5+4 should be optimized to Const_Node
			2. ID_Node that is Readonly should be optimized to Const_Node
			3. Unary_Node: op(Const_Node) like: not(true) should be optimized to Const_Node
			4. while cant be reached like: while(false) should be deleted
			5. if cant be reached should be optimized to else as a scope
			6. if reached all the timeshould be optimized to if as a scope
*/

/*---------------------------------------Constant Leaf----------------------------------*/

class Const_Node : public Node
{
public:

	Const_Type type;

	Const_Node(Const_Type);
	static Node* buildDefaultConst(list <char*>);
	void generateCode();
	~Const_Node();
};

/*----------------------------------------Idenifier Leaf----------------------------------*/
class Scope;

class ID_Node : public Node
{
public:

	Variable* var;

	ID_Node(Variable*);
	static bool locateVar(Scope* currScope,Class *currClass,Method *currMethod,char *name,Variable* &,char*);
	void generateCode();
	~ID_Node();

private:

	static bool searchScope(Scope* scope,char *name,Variable* &locate);
	static bool searchMethodSig (list <Variable*> MethodSig,char*name,Variable* &locate);
	static bool searchMethodLocal(list <Variable*> Local,char *name,Variable*&locate);
	static bool searchMethod(Method* currMethod,char*name,Variable* &locate);
	static bool SearchClass(Class *currClass,char *name,bool in_class,Variable* &locate,char*);
	static bool SearchInherits(my_implements *inherit,char *name,Variable* &locate,char*);
};

/*----------------------------------------Object Idenifier Node----------------------------------*/

class ObjectID_Node : public Node
{
public:

	Node* object;
	Variable* var;

	ObjectID_Node(Variable* var,Node* object): Node(OBJ_ID) , var(var),object(object){}
	void generateCode();
};
/*----------------------------------------Array Leaf----------------------------------*/
class Array_Node : public Node
{
public:
	Variable* var;
	Node* x;

	Array_Node(Variable* var,Node* x): Node(ARRAY), var(var), x(x){}
	void generateCode();
};

/*----------------------------------------Object Idenifier Node----------------------------------*/

class ObjectArray_Node : public Node
{
public:

	Node* object;
	Variable* var;
	Node* x;

	ObjectArray_Node(Variable* var,Node* object,Node* x): Node(OBJ_ARRAY),object(object), var(var), x(x){}
	void generateCode();
};
/*----------------------------------------OP with one attribute----------------------------------*/

//Such as:	not exp, ~ exp, Isvoid exp, return exp.
class Unary_Node : public Node
{
public:
 
	Node* son;
	UnaryOp opType;  //what is the operater Kind (not,~,isvoid) ?...

	Unary_Node(Node *,UnaryOp);
	void generateCode();
	~Unary_Node();
};

/*------------------------------------OP with two attributes----------------------------------*/

//Such as:	exp op exp where op={+,-,*,/,=,<,<=,>,>=}.
class Binary_Node : public Node
{
public:

	Node* rightSon;
	Node* leftSon;
	BinaryOp opType;  //what is the operater Kind (+,-,*,/,=,<,<=,>,>=) ?...

	Binary_Node(Node *,Node *,BinaryOp);
	bool logicOp();
	bool arthmeticOp();
	void generateCode();
	~Binary_Node();
};

/*----------------------------------------Call_Node----------------------------------*/
class AST;
class MethodSearch
{
public:
	static bool checkReturn(AST*);
	static bool locateFunc(Class *,char *,AST*&,Method*&,char*,bool);
	static bool locateFunc(Interface *,char *,AST*&,Method*&,char*,bool);

private:
	static bool SearchClass(Class *currClass,char *name,bool in_class,AST*& seg, Method*& locate,char*,bool);
	static bool SearchInherits(my_implements *inherit,char *name,AST*& seg,Method*& locate,char*,bool);
	static bool SearchInterface(Interface *currInterface,char *name,AST*& seg,Method* &locate,char* Caller,bool later);
	static bool SearchInheritsI(list<my_implements *>inherit,char *name,AST*& seg,Method* &locate,char* Caller,bool later);
	static bool checkPara(list<Variable *> uPara,AST*& seg,bool);
};

class FunctionCall_Node : public Node
{
public:

	Method * locate;
	AST* callSegn;

	FunctionCall_Node(Method*, AST*);
	void generateCode();
	~FunctionCall_Node();
};

class ObjectFuncCall_Node : public Node
{
public:

	Node* object;
	Method * locate;
	AST* callSegn;

	ObjectFuncCall_Node(Node* object,Method* locate, AST* callSegn):Node(OBJ_FUNC_CALL),object(object),locate(locate),callSegn(callSegn){}
	void generateCode();
};

/*---------------------------------ConstructCall_Node----------------------------------*/

class ConstructCall_Node : public Node
{
public:

	Method* locate;
	AST* callSegn;
	my_implements* initClass;

	ConstructCall_Node(Method*, AST*,my_implements*);
	void generateCode();
	~ConstructCall_Node();
};

/*---------------------------------DynamicArray_Node----------------------------------*/

class DynamicArrayInit_Node : public Node
{
public:

	Node* var;
	Node* initSize;

	DynamicArrayInit_Node(Node* var, Node* initSize):Node(DYNAMIC_ARRAY), var(var), initSize(initSize) {}
	void generateCode();
};

/*----------------------------------------Assignment_Node----------------------------------*/

class Assignment_Node : public Node
{
public:

	Node* var;
	Node* value;

	Assignment_Node(Node*, Node*);
	void generateCode();
	~Assignment_Node();
};

/*----------------------------------------Upcasting----------------------------------*/

class Upcast_Node  : public Node
{
public :

	my_implements* upperType;
	Node* son;

	Upcast_Node(my_implements*,Node*);
	void generateCode();
	~Upcast_Node();
};

/*----------------------------------------Downcasting----------------------------------*/

class Downcast_Node  : public Node
{
private:

	static bool checkCastInherits(my_implements *,Interface *);
	static bool checkCastImplements(list<my_implements*>,Interface *);

public :

	my_implements* lowerType;
	Node* son;

	Downcast_Node(my_implements*,Node*);
	static bool checkCastType(Class *,Class *);
	static bool checkCastType(Interface *,Class*);
	void generateCode();
	~Downcast_Node();
};

/*----------------------------------------if_Node----------------------------------*/

class IF_Node  : public Node
{
public :

	Node *Condition; //Binary_Node (not, isvoid) or Unary_Node (=,<,<=,>,>=) or Call_Node (function returnType=bool)
	Node *if_true;
	Node *if_else;

	IF_Node(Node*,Node*,Node*);
	void generateCode();
	~IF_Node();
};

/*----------------------------------------while_Node----------------------------------*/

class WHILE_Node  : public Node
{
public :

	Node *Condition; //Binary_Node (not, isvoid) or Unary_Node (=,<,<=,>,>=) or Call_Node (function returnType=bool)
	Scope *Body;

	WHILE_Node(Node*,Scope*);
	void generateCode();
	~WHILE_Node();
};

/*----------------------------------------Case_Node----------------------------------*/

class Case_Expr
{
public:

	list <Const_Node *> values;
	list <Node *> Body;

	Case_Expr(Const_Node *, Node *);
	void addExpr(Const_Node *, Node *);
	~Case_Expr();
};

class CASE_Node  : public Node
{
public :

	Node * caseOf;
	Case_Expr caseExprs;

	CASE_Node(Node *, Case_Expr);
	static bool checkCaseType(int,Case_Expr);
	void generateCode();
	~CASE_Node();
};

/*-------------------------------------Let_Node----------------------------------*/

class Let_Node  : public Node
{
public :

	Scope* letScope;

	Let_Node(Scope*);
	void generateCode();
	~Let_Node();
};

//--------------------------------Return_Node---------------------------------------*/

class Return_Node  : public Node
{
public:

	Node* ReturnVal;

	Return_Node(Node*);
	void generateCode();
	~Return_Node();
};

//--------------------------------Scope_Node---------------------------------------*/

class Scope  : public Node
{
public:
	list<Variable *> Local;
	AST* Body;
	Scope* parent;

	Scope();
	Scope(Scope* parent);
	void addLocal(Variable *);
	void addLocals(my_variables);
	bool searchScope(Variable *);
	void generateCode();
	~Scope();
};
/*-----------------------------------Array Node---------------------------------------*/

class ArraySize : public Node
{
public:
	int x;

	ArraySize(int);
	static bool checkArraySize(int,Node *);
};
/*-----------------------------------Static Node--------------------------------------*/
//----------------------------------- unused node -----------------------------------

class Static_Node : public Node
{
public:
	my_implements* staticImp;
	bool define;

	Static_Node(char *);
	Static_Node(my_implements*);
};

/*-----------------------------------Static Array Node---------------------------------*/
//------------------------------------- unused node ----------------------------------

class StaticArray_Node : public Node
{
public:
	my_implements* staticImp;
	Node* xArray;

	StaticArray_Node(my_implements*,Node *);
};

/*----------------------------------------Abstract Tree------------------------------*/

class AST
{
public:
	AST* nextExpr;	//next expression node
	Node* exprTree;	//the expression

	AST();
	AST(Node*);
	void addNode(Node*);
	void removeNode();
	void printAST();
	int size();
	~AST(void);
};

/*--------------------------------- Later Defenition --------------------------------*/
struct memLater
{
	Node* mem;
	NameSpace * nameSpace;
	Class * clas;
	Method * method;
	Scope * scope;
	int line;
};
struct typeLater
{
	Symbol * type;
	bool method;
	NameSpace * nameSpace;
	int line;
};
class LaterDef
{
public:
	vector<memLater> MemberExpectLater;
	list<typeLater> TypeExpectLater;

	LaterDef();
	void pointAtAST(Node *,NameSpace * ,Class * clas,Method*,Scope *,int);
	void pointAtSymbol(Symbol *,bool,NameSpace *,int);
};