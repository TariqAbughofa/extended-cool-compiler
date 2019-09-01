%output ="yacc.cpp"
%{

/***Includes and Defines ***/
#define YYDEBUG 1
#include <iostream>
#include <fstream>
using namespace std;
#include "FlexLexer.h"
#include "Actions.h"
#include <cstring>

int yylex(void);
int yyparse();
void yyerror(char *);
char* copystr(const char*);

extern int line;
extern int col;

// Lets Go to Create My Symbol Table

FlexLexer* lexer = new yyFlexLexer();

//temp list
std::list <my_implements*> keke;
std::list <Modifier> meme;
std::list <Variable* > para;
my_implements* Inherit_Struct=new my_implements();
Scope * prevScope;
bool laterLoop = false;

Actions * my_action=new Actions();
bool ok=true;
int paraNum = 0;
class Parser
{
public:
	int	parse()
	{
		return yyparse();
	} 
};

%}
//=========================================================================//

%token NOT IF THEN ELSE FI WHILE LOOP POOL LET IN CASE OF ESAC SWITCH ERROR
%token LC RC DOT COMMA LP RP COLON LB RB SEMICOLON IS BEG END err_FALSE err_TRUE
%token INTERFACE NAMESPACE CLASS IMPLEMENTS RETURN INHERITS AT VOID DELETE SUPER
%token PLUS MINUS STAR DIV NEGATE LT LE GT GE EQUAL RE ND AOR ASSIGN ISVOID NEW

%union {
int ival;
float fval;
bool bval;
char * sval;
enum Modifier modi;
class	my_modifiers	*my_modifier;
class	my_implements	*my_implement;
class	Variable		*my_parameter;
class	my_parameters	*my_parameterss;
class	my_variables	*my_variable;
class	Case_Expr		*my_caseExpr;
class	my_QIDList		*my_QIDList;
class	Node			*my_Node;
class	AST				*my_AST;
}

%token <ival> INT
%token <fval> FLOAT
%token <sval> STRINGS ID
%token <bval> TRUE FALSE
%token <modi> PUBLIC PRIVATE PROTECTED INTERNAL STATIC READONLY VIRTUAL SEALED OVERRIDE ABSTRACT

%type <my_modifier> Modifier
%type <modi> ModifierBuild
%type <my_implement> QID
%type <my_parameter> formal
%type <my_parameterss> nFormal
%type <my_QIDList> QIDList
%type <my_Node> expr
%type <my_AST> nExpr
%type <my_AST> callExpr
%type <my_variable> letExpr
%type <my_caseExpr> caseExpr

%nonassoc ASSIGN
%left NOT DELETE RETURN
%left ND AOR
%nonassoc EQUAL LE LT GE GT
%left PLUS MINUS
%left STAR DIV
%left ISVOID
%left NEGATE
%nonassoc AT
%nonassoc XQID
%nonassoc DOT

%%

Program	:	Program Namespacedecl
			|Namespacedecl
			|RC {yyerror("USLESS '}' NAMESPACE DECLARATION EXPECTED");}
			|Program RC {yyerror("USLESS '}' NAMESPACE DECLARATION EXPECTED");}
			|error //{yyerror("NAMESPACE KEYWORD EXPECTED (A PROGRAM IN COOL SHOULD START WITH A NAMESPACE DECLARATION)");}
;

//---------------------------------NAMESPACE----------------------------------------------------

Namespacedecl	:	NAMESPACE QID LC {my_action->NameSpace_Action($2->implement,line,true);}
					NamespaceBody {my_action->NameSpace_Action($2->implement,line,false);}
			    
					|NAMESPACE error {yyerror("ERROR IN NAMESPACE DEFINATION"); my_action->sure=false;} NamespaceBody {my_action->sure=true;}
					|NAMESPACE QID error {yyerror("'{' EXPECTED"); my_action->sure=false;} NamespaceBody {my_action->sure=true;}
					|NAMESPACE QID RC {yyerror("'{' MISSING"); }
;

NamespaceBody	:	nTypeDecl RC
					//|nTypeDecl %prec X {yyerror("REACH END OF FILE PARSING AND STILL NO '}'");}
;

nTypeDecl	:	nTypeDecl TypeDecl
				|nTypeDecl ErrorDecl
				|
;

TypeDecl	:	Namespacedecl
				|classdecl
				|Interfacedecl
;

ErrorDecl	:	error
;

//---------------------------------CLASS----------------------------------------------------

classdecl	:	Modifier CLASS ID INHERITS QID IMPLEMENTS QIDList IS {my_action->Class_Action($1->modi,$7->lists,$5,$3,line);} classBody {my_action->closeClass_Action(line);}

				|Modifier CLASS ID IMPLEMENTS QIDList IS {Inherit_Struct=new my_implements("Object"); my_action->Class_Action($1->modi,$5->lists,Inherit_Struct,$3,line);} classBody {my_action->closeClass_Action(line);}

				|Modifier CLASS ID INHERITS QID IS {keke.clear(); my_action->Class_Action($1->modi,keke,$5,$3,line);} classBody {my_action->closeClass_Action(line);}

				|Modifier CLASS ID IS {Inherit_Struct=new my_implements("Object"); keke.clear(); my_action->Class_Action($1->modi,keke,Inherit_Struct,$3,line);} classBody {my_action->closeClass_Action(line);}

                |CLASS ID INHERITS QID IMPLEMENTS QIDList IS {meme.clear(); my_action->Class_Action(meme,$6->lists,$4,$2,line);} classBody {my_action->closeClass_Action(line);}

				|CLASS ID IMPLEMENTS QIDList IS {meme.clear(); Inherit_Struct=new my_implements("Object"); my_action->Class_Action(meme,$4->lists,Inherit_Struct,$2,line);} classBody {my_action->closeClass_Action(line);}

                |CLASS ID INHERITS QID IS {keke.clear(); meme.clear(); my_action->Class_Action(meme,keke,$4,$2,line);} classBody {my_action->closeClass_Action(line);}
                
                |CLASS ID IS {Inherit_Struct=new my_implements("Object"); meme.clear(); keke.clear(); my_action->Class_Action(meme,keke,Inherit_Struct,$2,line);} classBody {my_action->closeClass_Action(line);}

                |Modifier CLASS ID IMPLEMENTS error {yyerror("ERROR IN IMPLEMENTATION LIST"); my_action->sure_=false;} classBody {my_action->sure_=true;}
                |CLASS ID IMPLEMENTS error {yyerror("ERROR IN IMPLEMENTATION LIST");my_action->sure_=false;} classBody {my_action->sure_=true;}
                
                |Modifier CLASS ID INHERITS  error {yyerror("ERROR IN INHERITANCE LIST"); my_action->sure_=false;} classBody {my_action->sure_=true;}
				|CLASS ID INHERITS  error {yyerror("ERROR IN INHERITANCE LIST");my_action->sure_=false;} classBody {my_action->sure_=true;}
				
				|Modifier CLASS error {yyerror("ERROR IN CLASS DEFINATION");my_action->sure_=false;} classBody {my_action->sure_=true;}
                |CLASS error {yyerror("ERROR IN CLASS DEFINATION");my_action->sure_=false;} classBody {my_action->sure_=true;}
                
                |Modifier CLASS ID INHERITS QID  IMPLEMENTS  QIDList error {yyerror("'IS' KEYWORD EXPECTED");my_action->sure_=false;} classBody {my_action->sure_=true;}
                |CLASS ID INHERITS QID   IMPLEMENTS  QIDList error {yyerror("'IS' KEYWORD EXPECTED"); my_action->sure_=false;} classBody {my_action->sure_=true;}
                |Modifier CLASS ID IMPLEMENTS  QIDList error {yyerror("'IS' KEYWORD EXPECTED");my_action->sure_=false;} classBody {my_action->sure_=true;}
                |CLASS ID IMPLEMENTS  QIDList error {yyerror("'IS' KEYWORD EXPECTED");my_action->sure_=false;} classBody {my_action->sure_=true;}
                
                |Modifier CLASS ID INHERITS QID error {yyerror("'IS' or 'IMPLEMENTS' KEYWORD EXPECTED");my_action->sure_=false; } classBody {my_action->sure_=true;}
                |CLASS ID INHERITS QID error {yyerror("'IS' or 'IMPLEMENTS' KEYWORD EXPECTED"); my_action->sure_=false;} classBody {my_action->sure_=true;}
                
                |Modifier CLASS ID error {yyerror("'IS' or 'IMPLEMENTS' or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;} classBody {my_action->sure_=true;}
                |CLASS ID error {yyerror("'IS' or 'IMPLEMENTS' or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;} classBody {my_action->sure_=true;}
                
                //-----------------------------is missing-------------------------------------------------
                |Modifier CLASS ID INHERITS QID   IMPLEMENTS  QIDList END {yyerror("'IS' KEYWORD MISSING");}
                |CLASS ID INHERITS QID   IMPLEMENTS  QIDList END	{yyerror("'IS' KEYWORD MISSING");}
                |Modifier CLASS ID INHERITS QID END	{yyerror("'IS' KEYWORD MISSING");}
                |CLASS ID INHERITS QID END	{yyerror("'IS' KEYWORD MISSING");}
                |Modifier CLASS ID IMPLEMENTS  QIDList END	{yyerror("'IS' KEYWORD MISSING");}
                |CLASS ID IMPLEMENTS  QIDList END	{yyerror("'IS' KEYWORD MISSING");}
                |Modifier CLASS ID END	{yyerror("'IS' KEYWORD MISSING");}
                |CLASS ID END {yyerror("'IS' KEYWORD MISSING");}
;

classBody	:	nFeature END
				|nFeature TypeDecl {yyerror("'END' KEYWORD EXPECTED CAN NOT DECLARE AN INNER NAMESPACE/INTERFACE/CLASS");}
				//|nFeature {yyerror("'END' KEYWORD EXPECTED");}
;

QID		: 	QID DOT ID {$1->add_implement($3); $$=$1;}
			|ID {$$=new my_implements($1);}
;

QIDList		:	QIDList COMMA QID {$1->add_list($3); $$=$1;}
				|QID {$$=new my_QIDList($1);}
;

nFormal		:    nFormal COMMA formal  {$1->add_parameter($3);$$=$1;}
				|formal {$$=new my_parameters($1);}
;

formal		:	ID COLON  QID {$$=new Variable($1,$3,paraNum); paraNum++;}
				|ID COLON error {yyerror("TYPE EXPECTED AFTER ':' IN VARIABLE DEFINATION"); }
				|ID error {yyerror("':' MISSING");}
;

//-------------------------------------VARIABLE & FUNCTION------------------------------------

nFeature	:	nFeature Feature
				|nFeature ErrorDecl
				|
;

Feature		:	fieldDecl
				|functionDecl
				|abstFuncDecl
;

//---------Variable

fieldDecl	:	Modifier ID COLON QID {my_action->VariablesClass_Action($1->modi,$4,$2,line);} fieldBody
				|ID  COLON  QID {meme.clear(); my_action->VariablesClass_Action(meme,$3,$1,line);} fieldBody
				|Modifier ID COLON error {yyerror("TYPE EXPECTED"); my_action->sure=false;} fieldBody {my_action->sure=true;}
				|ID COLON error {yyerror("TYPE EXPECTED"); my_action->sure=false;} fieldBody {my_action->sure=true;}

				|Modifier ID COLON QID error {yyerror("';' OR '[' OR '<-' MISSING");}
				|ID COLON QID error {yyerror("';' OR '[' OR '<-' MISSING");}
				
				//array
				|Modifier ID COLON QID LB INT RB SEMICOLON {my_action->ArraysClass_Action($1->modi,$4,$2,$6,line)}
				
				|ID  COLON  QID LB INT RB SEMICOLON {meme.clear(); my_action->ArraysClass_Action(meme,$3,$1,$5,line)}
				
				|Modifier ID COLON QID LB RB SEMICOLON {my_action->DynArraysClass_Action($1->modi,$4,$2,line)}
				|ID COLON QID LB RB SEMICOLON {meme.clear(); my_action->DynArraysClass_Action(meme,$3,$1,line)}
				
				|Modifier ID  COLON  QID LB INT RB INTValue SEMICOLON {yyerror("1 Demonitions is the max for arrays");}
				|ID  COLON  QID LB INT RB INTValue SEMICOLON {yyerror("1 Demonitions is the max for arrays");}
;

INTValue	:	INTValue LB INT RB
                |INTValue LB INT error {yyerror("']' MISSING");}
                |INTValue LB RB {yyerror("MUST DEFINE ARRAY LENGTH AT DECLARATION TIME");}
                |INTValue LB error {yyerror("MUST DEFINE AN INTEGER ARRAY LENGTH");} RB
				
                |LB INT RB
                |LB INT error {yyerror("']' MISSING"); }
                |LB RB {yyerror("MUST DEFINE ARRAY LENGTH AT DECLARATION TIME");}
                |LB error {yyerror("MUST DEFINE AN INTEGER ARRAY LENGTH");} RB
;
//---------Function

functionDecl	:	Modifier ID LP nFormal RP COLON QID IS {my_action->MethodsClass_Action($1->modi,$4->parameter,$7,$2,line);} functionBody {paraNum = 0;}
					
					|Modifier ID LP RP COLON QID IS {para.clear(); my_action->MethodsClass_Action($1->modi,para,$6,$2,line);} functionBody
					
					|ID LP nFormal RP COLON QID IS {meme.clear(); my_action->MethodsClass_Action(meme,$3->parameter,$6,$1,line);} functionBody {paraNum = 0;}
					
					|ID LP RP COLON QID IS {para.clear(); meme.clear(); my_action->MethodsClass_Action(meme,para,$5,$1,line);} functionBody
					
					|Modifier ID LP error {yyerror("')' MISSING"); my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|Modifier ID LP RP COLON error {yyerror("RETURN TYPE EXPECTED"); my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|Modifier ID LP RP error {yyerror("':' MISSING");my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|Modifier ID LP RP COLON QID {yyerror("'IS' KEYWORD EXPECTED");my_action->sure__=false;} functionBody {my_action->sure__=true;}
					
					|Modifier ID LP nFormal error {yyerror("')' MISSING");my_action->sure__=false; } functionBody {my_action->sure__=true;}
					|Modifier ID LP nFormal RP error {yyerror("':' MISSING");my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|Modifier ID LP nFormal RP COLON error {yyerror("RETURN TYPE EXPECTED");my_action->sure__=false; } functionBody {my_action->sure__=true;}
					|Modifier ID LP nFormal RP  COLON  QID {yyerror("'IS' KEYWORD EXPECTED");my_action->sure__=false;} functionBody {my_action->sure__=true;}
					
					|ID LP error {yyerror("')' MISSING");my_action->sure__=false; } functionBody {my_action->sure__=true;}
					|ID LP RP error {yyerror("':' MISSING");my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|ID LP RP COLON error {yyerror("RETURN TYPE EXPECTED");my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|ID LP RP COLON QID {yyerror("'IS' KEYWORD EXPECTED"); my_action->sure__=false;} functionBody {my_action->sure__=true;}
					
					|ID LP nFormal error {yyerror("')' MISSING"); my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|ID LP nFormal RP COLON error {yyerror("RETURN TYPE EXPECTED"); my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|ID LP nFormal RP error {yyerror("':' MISSING");my_action->sure__=false;} functionBody {my_action->sure__=true;}
					|ID LP nFormal RP COLON QID {yyerror("'IS' KEYWORD EXPECTED");my_action->sure__=false;} functionBody {my_action->sure__=true;}

//------------Variable or Function

					//|ID error SEMICOLON {yyerror("':' OR '(' MISSING");}
					//|Modifier ID error SEMICOLON {yyerror("':' OR '(' MISSING");}
					
					|Modifier error {yyerror("ERROR IN CLASS MEMBER DEFINATION"); }
					
					|ID {yyerror("':' OR '(' MISSING");}
					|Modifier ID {yyerror("':' OR '(' MISSING");}
;

//------------Abstract Function
abstFuncDecl	:	Modifier ID LP nFormal RP COLON QID SEMICOLON {my_action->AbsMethodsClass_Action($1->modi,$4->parameter,$7,$2,line);}
					|Modifier ID LP RP COLON QID SEMICOLON {para.clear(); my_action->AbsMethodsClass_Action($1->modi,para,$6,$2,line);}
					
					|ID LP RP COLON QID SEMICOLON {my_action->My_ref->addRefuse($1," : must declared as abstract",$1,method,line,*new bool);}
					|ID LP nFormal RP COLON QID SEMICOLON {my_action->My_ref->addRefuse($1," : must declared as abstract",$1,method,line,*new bool);}
;

fieldBody	:	ASSIGN expr SEMICOLON
				{
					if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
					{
						if ($2!=NULL)
						{
							my_action->currVariable->val=new Node();
							if (my_action->laterTree)
							{
								Node* expr = new Assignment_Node(new ID_Node(my_action->currVariable),$2);
								my_action->my_laterDef->pointAtAST(expr,my_action->currNamespace,my_action->currClass,NULL,NULL,line);
								my_action->currVariable->val=$2;
							}
							else if (my_action->checkAssignment(my_action->currVariable,new ID_Node(my_action->currVariable),$2,line)->grp!=EMPTY)
								my_action->currVariable->val=$2;
						}
						my_action->laterTree = false;
					}
				}
				|SEMICOLON
				{
					if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
					{
						if (my_modifiers::found(my_action->currVariable->modi,Readonly))
						{
							my_action->currVariable->val=new Node();
							my_action->My_ref->addRefuse("readonly variable should assign value at declaration time",my_action->currVariable->name,variable,line,*new bool);
						}
						else
						{
							my_action->currVariable->val=new Node();
							my_action->currVariable->val=Const_Node::buildDefaultConst(my_action->currVariable->varType->implement);
						}
					}
				}
;

functionBody	:	nExpr END {my_action->EndFunction(my_action->currClass,$1,line);}
					|END {my_action->EndFunction(my_action->currClass,NULL,line);}

					//|nExpr Feature {yyerror("'END' KEYWORD EXPECTED CANT DECLARE A FUNCTION IN ANOTHER");}
					//|expr {yyerror("'END' KEYWORD EXPECTED");}
;

//------------------------MODIFIERS-----------------------------------

ModifierBuild	:    PUBLIC {$$=Public;}
					|PROTECTED {$$=Protected;}
					|INTERNAL {$$=Internal;}
					|PRIVATE {$$=Private;}
					|STATIC {$$=Static;}
					|READONLY {$$= Readonly;}
					|ABSTRACT {$$=Abstract;}
					|SEALED {$$=Sealed;}
					|OVERRIDE {$$=Override;}
					|VIRTUAL {$$=Virtual;}
					|NEW {$$=New;}
;

Modifier	:	Modifier ModifierBuild {$1->add_modifier($2); $$=$1}
				|ModifierBuild {$$ = new my_modifiers($1);}
;

//------------------------EXPRESSIONS-----------------------------------

callExpr	:	callExpr COMMA expr {$1->addNode($3); $$=$1;}
				|expr {$$ = new AST($1);}
;

letExpr		:	letExpr COMMA ID COLON QID ASSIGN expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $1->add_variable(my_action->LetVarDeclaration($3,$5,line,$7)); $$=$1;}
                |letExpr COMMA ID COLON QID {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $1->add_variable(my_action->LetVarDeclaration($3,$5,line,Const_Node::buildDefaultConst($5->implement))); $$=$1;}
				|letExpr COMMA ID COLON error {yyerror("TYPE EXPEXTED");}
                |letExpr COMMA ID error {yyerror("':' MISSING");}
                |letExpr error {yyerror("'IN' KEYWORD EXPECTED");}
                
                |ID COLON QID ASSIGN expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = new my_variables(my_action->LetVarDeclaration($1,$3,line,$5));}
                |ID COLON QID {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = new my_variables(my_action->LetVarDeclaration($1,$3,line,Const_Node::buildDefaultConst($3->implement)));}
				|ID COLON error {yyerror("TYPE EXPEXTED");}
                |ID error {yyerror("':' MISSING");}
                //|ID COLON QID error {yyerror("'IN' KEYWORD EXPECTED"); }
;

caseExpr	:	caseExpr CASE expr RE expr SEMICOLON
				{
					if ($3->grp==CONST)
					{
						if ($1 != NULL)
							$1->addExpr((Const_Node *)$3,$5);
						else
							$1=new Case_Expr((Const_Node *)$3,$5);
					}
					else
						my_action->My_ref->addRefuse("case expression should be constant","caseExpr",variable,line,*new bool);
					$$=$1;
				}
                |caseExpr CASE expr RE expr {yyerror("';' MISSING"); }
                |caseExpr CASE expr error SEMICOLON {yyerror("'=>' MISSING"); }
				|caseExpr error{yyerror("'ESAC' KEYWORD EXPECTED"); }
				
                |CASE expr RE expr SEMICOLON
                {
					if ($2->grp==CONST) 
						$$=new Case_Expr((Const_Node *)$2,$4);
					else
					{
						my_action->My_ref->addRefuse("case expression should be constant","caseExpr",variable,line,ok);
						$$ = NULL;
					}
				}
                |CASE expr RE expr {yyerror("';' MISSING");}
                |CASE expr error SEMICOLON {yyerror("'=>' MISSING");}
;

nExpr	:	nExpr expr SEMICOLON
			{
				my_action->FirstDad=true;
				my_action->laterTree = false;
				if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
				{
					if ($2->grp!=EMPTY)
					{
						if ($1!=NULL)
							$1->addNode($2);
						else
							$1 = new AST($2);
					}
					$$=$1;
				}
			}
			//|nExpr expr {yyerror("';' MISSING"); $$ = $1;}
			|expr SEMICOLON
			{
				my_action->FirstDad=true;
				my_action->laterTree = false;
				if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__))
					if ($1->grp!=EMPTY)
						$$ = new AST($1);
			}
			|nExpr exprError SEMICOLON {$$ = $1;}
			|exprError {$$ = new AST();}
			//|expr {yyerror("';' MISSING"); $$ = new AST();}
			|error {$$ = new AST();}
;

expr	:	//variable definition-------------------------------------------------
			ID COLON QID %prec XQID {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->VariableDeclaration($3,$1,line,Const_Node::buildDefaultConst($3->implement));}
			|ID COLON QID LB INT RB {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ArrayDeclaration($3,$1,$5,line,Const_Node::buildDefaultConst($3->implement));}
			|ID COLON QID ASSIGN expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$=my_action->VariableDeclaration($3,$1,line,$5);}
			|ID COLON QID LB RB {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->DynArrayDeclaration($3,$1,line,Const_Node::buildDefaultConst($3->implement));}
			|ID COLON QID LB RB ASSIGN NEW QID LB ID RB {my_implements* Qid = new my_implements($1); my_implements* imp = new my_implements($10); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) my_action->DynArrayDeclaration($3,$1,line,Const_Node::buildDefaultConst($3->implement)); $$ = my_action->InitDynArray(Qid,$8,my_action->CallVariable(imp,false,line),line);}
			|ID COLON QID LB RB ASSIGN NEW QID LB INT RB {my_implements* Qid = new my_implements($1); Const_Type CT; CT.iv=$10; CT.type=1; Const_Node * n =new Const_Node(CT);  if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) my_action->DynArrayDeclaration($3,$1,line,Const_Node::buildDefaultConst($3->implement)); $$ = my_action->InitDynArray(Qid,$8,n,line);}
			
			//Call Identifier-----------------------------------------------------
			|QID %prec XQID {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$=my_action->CallVariable($1,false,line);}
			
			|QID LB INT RB {Const_Type CT; CT.iv=$3; CT.type=1; Const_Node * n =new Const_Node(CT); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$=my_action->CallArrVar($1,n,line);}
			|QID LB ID RB {my_implements* imp = new my_implements($3); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$=my_action->CallArrVar($1,my_action->CallVariable(imp,false,line),line);}
			
			|QID ASSIGN expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$=my_action->AssignVariable($1,$3,line);}
			|QID LB INT RB ASSIGN expr {Const_Type CT; CT.iv=$3; CT.type=1; Const_Node * n =new Const_Node(CT); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$=my_action->AssignArrVar($1,n,$6,line);}
			|QID LB ID RB ASSIGN expr {my_implements* imp = new my_implements($3); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$=my_action->AssignArrVar($1,my_action->CallVariable(imp,false,line),$6,line);}
			
			//calling a friend function------------------------------------------
			|QID LP RP {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallFunction($1,new AST(),line);}
			|QID LP callExpr RP {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallFunction($1,$3,line);}
		    
		    //calling a Constructor----------------------------------------------
			|NEW QID LP RP {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallConstructor($2,new AST(),line);}
			|NEW QID LP callExpr RP {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallConstructor($2,$4,line);}
			|SUPER LP RP {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallFather(new AST(),line);}
		    |SUPER LP callExpr RP {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallFather($3,line);}
			
			|QID ASSIGN NEW QID LB ID RB {my_implements* imp = new my_implements($6); if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->InitDynArray($1,$4,my_action->CallVariable(imp,false,line),line);}
			|QID ASSIGN NEW QID LB INT RB {Const_Type CT; CT.iv=$6; CT.type=1; Const_Node * n =new Const_Node(CT);  if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->InitDynArray($1,$4,n,line);}

			//calling a class attribute------------------------------------------
			|expr DOT ID ASSIGN expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->AssignClassVar($1,$3,$5,line);}
			|expr DOT ID {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallClassVar($1,$3,line);}

			//|expr DOT ID INTValue
			//|expr DOT ID INTValue ASSIGN expr
			
			//calling a class method----------------------------------------------
			|expr DOT ID LP RP	{if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallClassFunc($1,$3,new AST(),new my_implements(),line);}			
			|expr DOT ID LP callExpr RP	{if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->CallClassFunc($1,$3,$5,new my_implements(),line);}
			
			//expression in brackets
			|LP expr RP {$$=$2;}
			
			//Downcasting-----------------------------------------------------------
			|expr AT QID {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->Casting($3,$1,line);}
			
			//If statment-----------------------------------------------------------
			|IF expr THEN {if (my_action->laterTree) laterLoop=true; my_action->laterTree = false; Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp); my_action->currMethod->LocalScopes.push_back(my_action->currScope);}
			nExpr {my_action->currScope->Body=$5; prevScope = my_action->currScope;}
			ELSE {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(my_action->currScope->parent); my_action->currMethod->LocalScopes.push_back(my_action->currScope);}
			nExpr {my_action->currScope->Body=$9;}
			FI {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(); my_action->currScope = tmp->parent;
			if (laterLoop)
			{
				$$ = new IF_Node($2,prevScope,tmp);
				my_action->my_laterDef->pointAtAST($$,my_action->currNamespace,my_action->currClass,my_action->currMethod,my_action->currScope,line);
			}
			else
				$$ = my_action->IfStmt($2,prevScope,tmp,line);
			laterLoop = false;}
			
			//while statment---------------------------------------------------------
			|WHILE expr LOOP {if (my_action->laterTree) laterLoop=true; my_action->laterTree = false; Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp); my_action->currMethod->LocalScopes.push_back(my_action->currScope);}
			nExpr {my_action->currScope->Body=$5;}
			POOL {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(); my_action->currScope = tmp->parent;
			if (laterLoop)
			{
				$$ = new WHILE_Node($2,tmp);
				my_action->my_laterDef->pointAtAST($$,my_action->currNamespace,my_action->currClass,my_action->currMethod,my_action->currScope,line);
			}
			else
				$$ = my_action->WhileStmt($2,tmp,line);
			laterLoop = false;}
			
			//Scope------------------------------------------------------------------
			|BEG {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp); my_action->currMethod->LocalScopes.push_back(my_action->currScope);}
			nExpr {my_action->currScope->Body=$3;}
			END {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(); my_action->currScope =tmp->parent;$$=tmp;}

			|BEG END {my_action->My_wrn->addWarn("SCOPE WITHOUT BODY. Droped","SCOPE",line); $$ = new Node();}

			//let statment-----------------------------------------------------------
			|LET {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) {Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope = new Scope(tmp);}}
			letExpr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) {my_action->currScope->addLocals(*$3);}} IN expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) my_action->currScope->Body=new AST($6);}
			END {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)&&(my_action->currMethod!=NULL)) {$$ = my_action->LetStmt(my_action->currScope,line); Scope* tmp=new Scope(); tmp=my_action->currScope; my_action->currScope=new Scope();my_action->currScope = tmp->parent;}}

			//Case statment----------------------------------------------------------
			|SWITCH expr OF caseExpr ESAC {$$=my_action->CaseStmt($2,*$4,ok,line);}

			//Binary operations------------------------------------------------------
			|expr PLUS expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ArthmExpr(SUM,$1,$3,line);}
			|expr MINUS expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ArthmExpr(SUB,$1,$3,line);}
			|expr STAR expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ArthmExpr(MULT,$1,$3,line);}
			|expr DIV expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ArthmExpr(DIVS,$1,$3,line);}
			|expr LT expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ComparisonExpr(LESS,$1,$3,line);}
			|expr LE expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ComparisonExpr(LSEQ,$1,$3,line);}
			|expr GT expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ComparisonExpr(MORE,$1,$3,line);}
			|expr GE expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ComparisonExpr(MREQ,$1,$3,line);}
			|expr EQUAL expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ComparisonExpr(EQL,$1,$3,line);}
			|expr ND expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->LogicExpr(AND,$1,$3,line);}
			|expr AOR expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->LogicExpr(OR,$1,$3,line);}

			//Unary operations---------------------------------------------------------
			|ISVOID expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->UnaryExpr(NULLCHECK,$2,line);}
			|NEGATE expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->UnaryExpr(LCOMP,$2,line);}
			|NOT expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->UnaryExpr(COMP,$2,line);}
			|DELETE expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->UnaryExpr(DEL,$2,line);}
			//return statment--------------------------------------------------------
			|RETURN expr {if ((my_action->sure_)&&(my_action->sure)&&(my_action->sure__)) $$ = my_action->ReturnExpr($2,line); else $$=new Node();}
			
			//Constant-------------------------------------------------------------------
			|MINUS INT {Const_Type CT; CT.iv=-$2; CT.type=1; $$=new Const_Node(CT);}
			|PLUS INT {Const_Type CT; CT.iv=$2; CT.type=1; $$=new Const_Node(CT);}
			|INT {Const_Type CT; CT.iv=$1; CT.type=1; $$=new Const_Node(CT);}
			|FLOAT {Const_Type CT; CT.fv=$1; CT.type=2; $$=new Const_Node(CT);}
			|STRINGS {char * s = new char; s = $1; Const_Type CT; CT.chv=s; CT.type=3; $$=new Const_Node(CT);}
			|TRUE {Const_Type CT; CT.bv=true; CT.type=4; $$=new Const_Node(CT);}
			|FALSE {Const_Type CT; CT.bv=false; CT.type=4; $$=new Const_Node(CT);}
			|VOID {Const_Type CT; CT.type=0; $$=new Const_Node(CT);}
;

exprError	:	//calling a friend function or variable------------------------------------------
				//QID LP error {yyerror("')' MISSING"); }
				//|QID error {yyerror("'(' OR '<-' EXPECTED"); }
				//|QID LP error RP {yyerror("ERROR IN PARAMETER LIST"); }
				//|QID LP callExpr error {yyerror("')' MISSING"); }
			    
				//calling a Constructor----------------------------------------------
				NEW error {yyerror("TYPE EXPECTED"); }
				
				//calling a class method----------------------------------------------
				//|expr DOT ID error {yyerror("'(' MISSING");}
				//|expr DOT ID LP error {yyerror("')' MISSING");}
				//|expr DOT error {yyerror("FUNCTION NAME EXPECTED");}
				//|expr DOT ID LP callExpr error {yyerror("')' MISSING");}
				
				//expression in brackets
				//|LP expr error {yyerror("')' MISSING"); }
				
				//Downcasting-----------------------------------------------------------
				|expr AT error {yyerror("TYPE EXPECTED");}
				
				//If statment-----------------------------------------------------------
				//|IF expr THEN nExpr ELSE expr error {yyerror("'FI' KEYWORD EXPECTED");}
				//|IF expr THEN nExpr error {yyerror("'ELSE' KEYWORD EXPECTED");}
				//|IF expr error {yyerror("'THEN' KEYWORD EXPECTED");}
				
				//while statment---------------------------------------------------------
				//|WHILE expr LOOP nExpr error {yyerror("'POOL' KEYWORD EXPECTED");}
				//|WHILE expr error {yyerror("'LOOP' KEYWORD EXPECTED");}
			
				//Scope------------------------------------------------------------------
				//|BEG nExpr error {yyerror("'END' KEYWORD EXPECTED");}

				//let statment-----------------------------------------------------------
				//|LET letExpr IN expr error {yyerror("'END' KEYWORD EXPECTED");}

				//Case statment----------------------------------------------------------
				|SWITCH expr error {yyerror("'OF' KEYWORD EXPECTED");}
				
				//Constant---------------------------------------------------------------
				|err_FALSE error {yyerror("'false' KEYWORD EXPECTED"); }
				|err_TRUE error {yyerror("'true' KEYWORD EXPECTED"); }
;

//------------------------------------INTERFACE----------------------------------------------

Interfacedecl	:	Modifier INTERFACE ID INHERITS QIDList LC {my_action->Interface_Action($1->modi,$5->lists,$3,line);} interfacebody {my_action->closeInterface_Action(line);}

				|Modifier INTERFACE ID LC {keke.clear(); my_action->Interface_Action($1->modi,keke,$3,line);} interfacebody {my_action->closeInterface_Action(line);}
               
				|INTERFACE ID INHERITS QIDList LC {meme.clear(); my_action->Interface_Action(meme,$4->lists,$2,line);} interfacebody {my_action->closeInterface_Action(line);}

				|INTERFACE ID LC {meme.clear(); keke.clear(); my_action->Interface_Action(meme,keke,$2,line);} interfacebody {my_action->closeInterface_Action(line);}
           
				|INTERFACE ID INHERITS QIDList error {yyerror("'{' MISSING"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}
				|INTERFACE ID INHERITS error {yyerror("ERROR IN INHERITANCE LIST"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}
				|INTERFACE ID error {yyerror("'{' MISSING or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}
				|INTERFACE error {yyerror("ERROR IN INTERFACE DEFINATION"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}
           
				|Modifier INTERFACE ID  INHERITS QIDList error {yyerror("'{' MISSING"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}
				|Modifier INTERFACE ID  INHERITS error {yyerror("ERROR IN INHERITANCE LIST"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}
				|Modifier INTERFACE ID error {yyerror("'{' MISSING or 'INHERITS' KEYWORD EXPECTED"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}
				|Modifier INTERFACE error {yyerror("ERROR IN INTERFACE DEFINATION"); my_action->sure_=false;} interfacebody {my_action->sure_=true;}

				|Modifier INTERFACE ID INHERITS QIDList RC {yyerror("'{' MISSING");}
				|INTERFACE ID INHERITS QIDList RC {yyerror("'{' MISSING");}
				|Modifier INTERFACE ID RC {yyerror("'{' MISSING");}
				|INTERFACE ID RC {yyerror("'{' MISSING");}
;

interfacebody	:	nInterfaceMethod RC
		 			|nInterfaceMethod TypeDecl {yyerror(" '}' MISSING CAN NOT DECLARE AN INNER NAMESPACE/INTERFACE/CLASS");}
					//|nInterfaceMethod {yyerror(" '}' MISSING");}
;

nInterfaceMethod	:	nInterfaceMethod InterfaceMethod
						|nInterfaceMethod ErrorDecl
						|
;

InterfaceMethod	:	ID LP RP COLON QID SEMICOLON {para.clear(); my_action->MehtodsInterface_Action(para,$5,$1,line);}
					|ID LP nFormal RP COLON QID SEMICOLON {my_action->MehtodsInterface_Action($3->parameter,$6,$1,line);}

					|ID LP RP COLON QID {yyerror("';' MISSING");}
					|ID LP error SEMICOLON {yyerror("')' MISSING");}
					|ID error SEMICOLON {yyerror("'(' MISSING ");}
					|error SEMICOLON {yyerror("ERROR IN FUNCTION DEFINATION");}

					|ID LP nFormal RP COLON QID {yyerror("';' MISSING");}
					|ID LP nFormal error SEMICOLON{yyerror("')' MISSING");}
					|ID LP nFormal RP COLON QID LC error SEMICOLON {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");}
                    |ID LP nFormal RP COLON QID IS error SEMICOLON {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");}
                    |ID LP RP COLON QID LC error SEMICOLON {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");}
					|ID LP RP COLON QID IS error SEMICOLON {yyerror("INTERFACE FUNCTIONS CAN NOT HAVE BODY");}
;

%%
   /***********UserCode**************/

void yyerror(char *s) 
{
  //fprintf(stderr, "%s\n", s);
  Error_info *R=new Error_info();
  R->msg=s ;  R->line=line;   R->col=col;
  my_action->My_err-> insert_Err (R);
}

int yylex()
{
	return lexer->yylex();
}

char * copystr(const char* s)
{
	char * res;
	if (s==NULL) return NULL;
	if( (res=(char*)malloc(strlen(s)+1))!=NULL)
		strcpy(res,s);
	else{
		yyerror("there are not enough memory");
		return 0;
	}		
	return res;
}

//======================================//

void main(void)
{
	//const char* A="read.txt" ;
	//ifstream *in=new ifstream(A);
	//if (in)
	//	lexer->yyrestart(in);
	//else
	//	cout <<"ERORR FILE NOT FOUND";
	
	Parser* p = new Parser();
	p->parse();
	my_action->scanBottomUp();
	if (!my_action->my_check->checkEntryPoint())
		my_action->My_ref->addRefuse("entry point ambigious: should be main():SELF_TYPE","main",method,0,*new bool);
	
	cout <<"My Symbol Table is "<<endl;
	my_action->Print_SymbolTable();
	cout<<endl;
 
	cout <<"My Errors are "<<endl;
	my_action->My_err->printList();
	cout<<endl;
    
	cout <<"My Refuse Addings are "<<endl;
	my_action->My_ref->printList();
	cout<<endl;

	cout <<"My Warnings are "<<endl;
	my_action->My_wrn->printList();
	
	if (my_action->hasNoErrors())
		my_action->generateCode();
}

//==================================//