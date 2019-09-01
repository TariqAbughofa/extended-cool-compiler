#include "AST.h"

//---------------------------------------------NODE--------------------------------------------------

Node::Node(){grp=EMPTY;}

Node::Node(Group_Node GN) {grp=GN;}

bool Node::returnValue()
{
	if((this->grp==UNARY)||(this->grp==BINARY)||(this->grp==CONST)||(this->grp==IDENTIFIER)||(this->grp==OBJ_ID)||(this->grp==ARRAY)
		||(this->grp==OBJ_ARRAY)||(this->grp==DOWNCAST)||(this->grp==UPCAST)||(this->grp==CONSTRUCTOR_CALL)||(this->grp==LET_STMT)||(this->grp==STATIC_CALL))
		return true;
	else if ((this->grp==FUNCTION_CALL)&&(strcmp(*((FunctionCall_Node*)this)->locate->returnType->implement.begin(),"Void")!=0))
		return true;
	else if ((this->grp==OBJ_FUNC_CALL)&&(strcmp(*((ObjectFuncCall_Node*)this)->locate->returnType->implement.begin(),"Void")!=0))
		return true;
	else
		return false;
}

int Node::returnValType(my_implements*& Qid)//0:nothing,1:int,2:float,3:string,4:boolean,5:Object,6:Class static
{
	switch (this->grp)
	{
	case CONST:
		Qid->implement.clear();
		switch (((Const_Node*)this)->type.type)
		{
		case 0:
			Qid->implement.push_back("void");
			return 0;
			break;
		case 1:
			Qid->implement.push_back("Int");
			return 1;
			break;
		case 2:
			Qid->implement.push_back("Float");
			return 2;
			break;
		case 3:
			Qid->implement.push_back("String");
			return 3;
			break;
		case 4:
			Qid->implement.push_back("Bool");
			return 4;
		}
		break;
	case IDENTIFIER:
		Qid->implement.clear();
		if (strcmp(((ID_Node*)this)->var->name,"self")==0)
		{
			Qid->implement.push_back("self");
			return 0;
		}
		*Qid=*((ID_Node*)this)->var->varType;
		if (strcmp(*((ID_Node*)this)->var->varType->implement.begin(),"Int")==0)
			return 1;
		else if (strcmp(*((ID_Node*)this)->var->varType->implement.begin(),"Float")==0)
			return 2;
		else if (strcmp(*((ID_Node*)this)->var->varType->implement.begin(),"String")==0)
			return 3;
		else if (strcmp(*((ID_Node*)this)->var->varType->implement.begin(),"Bool")==0)
			return 4;
		else
			return 5;//object
		break;
	case OBJ_ID:
		Qid->implement.clear();
		*Qid=*((ObjectID_Node*)this)->var->varType;
		if (strcmp(*((ObjectID_Node*)this)->var->varType->implement.begin(),"Int")==0)
			return 1;
		else if (strcmp(*((ObjectID_Node*)this)->var->varType->implement.begin(),"Float")==0)
			return 2;
		else if (strcmp(*((ObjectID_Node*)this)->var->varType->implement.begin(),"String")==0)
			return 3;
		else if (strcmp(*((ObjectID_Node*)this)->var->varType->implement.begin(),"Bool")==0)
			return 4;
		else
			return 5;//object
		break;
	case ARRAY:
		Qid->implement.clear();
		*Qid=*((Array_Node *)this)->var->varType;
		if (strcmp(*((Array_Node*)this)->var->varType->implement.begin(),"Int")==0)
			return 1;
		else if (strcmp(*((Array_Node*)this)->var->varType->implement.begin(),"Float")==0)
			return 2;
		else if (strcmp(*((Array_Node*)this)->var->varType->implement.begin(),"String")==0)
			return 3;
		else if (strcmp(*((Array_Node*)this)->var->varType->implement.begin(),"Bool")==0)
			return 4;
		else
			return 5;//object
		break;
	case OBJ_ARRAY:
		Qid->implement.clear();
		*Qid=*((ObjectArray_Node*)this)->var->varType;
		if (strcmp(*((ObjectArray_Node*)this)->var->varType->implement.begin(),"Int")==0)
			return 1;
		else if (strcmp(*((ObjectArray_Node*)this)->var->varType->implement.begin(),"Float")==0)
			return 2;
		else if (strcmp(*((ObjectArray_Node*)this)->var->varType->implement.begin(),"String")==0)
			return 3;
		else if (strcmp(*((ObjectArray_Node*)this)->var->varType->implement.begin(),"Bool")==0)
			return 4;
		else
			return 5;//object
		break;
	case UNARY:
		Qid->implement.clear();
		Qid->implement.push_back("Bool");
		return 4;//boolean
		break;
	case BINARY:
		if (((Binary_Node*)this)->arthmeticOp())
			return ((Binary_Node*)this)->leftSon->returnValType(Qid);
		else //comparision or logic
		{
			Qid->implement.clear();
			Qid->implement.push_back("Bool");
			return 4;
		}
		break;
	case FUNCTION_CALL:
		Qid->implement.clear();
		*Qid=*((FunctionCall_Node*)this)->locate->returnType;
		if (strcmp(*((FunctionCall_Node*)this)->locate->returnType->implement.begin(),"Void")==0)
			return 0; //dosn't return type
		else if (strcmp(*((FunctionCall_Node*)this)->locate->returnType->implement.begin(),"Int")==0)
			return 1;
		else if (strcmp(*((FunctionCall_Node*)this)->locate->returnType->implement.begin(),"Float")==0)
			return 2;
		else if (strcmp(*((FunctionCall_Node*)this)->locate->returnType->implement.begin(),"String")==0)
			return 3;
		else if (strcmp(*((FunctionCall_Node*)this)->locate->returnType->implement.begin(),"Bool")==0)
			return 4;
		else
			return 5;//object
		break;
	case OBJ_FUNC_CALL:
		Qid->implement.clear();
		*Qid=*((ObjectFuncCall_Node*)this)->locate->returnType;
		if (strcmp(*((ObjectFuncCall_Node*)this)->locate->returnType->implement.begin(),"Void")==0)
			return 0; //dosn't return type
		else if (strcmp(*((ObjectFuncCall_Node*)this)->locate->returnType->implement.begin(),"Int")==0)
			return 1;
		else if (strcmp(*((ObjectFuncCall_Node*)this)->locate->returnType->implement.begin(),"Float")==0)
			return 2;
		else if (strcmp(*((ObjectFuncCall_Node*)this)->locate->returnType->implement.begin(),"String")==0)
			return 3;
		else if (strcmp(*((ObjectFuncCall_Node*)this)->locate->returnType->implement.begin(),"Bool")==0)
			return 4;
		else
			return 5;//object
		break;
	case CONSTRUCTOR_CALL:
		Qid->implement.clear();
		*Qid = *((ConstructCall_Node *)this)->initClass;
		return 5;//object
		break;
	case UPCAST:
		Qid->implement.clear();
		*Qid=*((Upcast_Node*)this)->upperType;
		if (strcmp(*((Upcast_Node*)this)->upperType->implement.begin(),"Float")==0)
			return 2;
		else
			return 5;//object
		break;
	case DOWNCAST:
		Qid->implement.clear();
		*Qid=*((Downcast_Node*)this)->lowerType;
		if (strcmp(*((Downcast_Node*)this)->lowerType->implement.begin(),"Int")==0)
			return 1;
		else if (strcmp(*((Downcast_Node*)this)->lowerType->implement.begin(),"Float")==0)
			return 2;
		else if (strcmp(*((Downcast_Node*)this)->lowerType->implement.begin(),"String")==0)
			return 3;
		else if (strcmp(*((Downcast_Node*)this)->lowerType->implement.begin(),"Bool")==0)
			return 4;
		else
			return 5;//object
		break;
	case LET_STMT:
		return ((Let_Node*)this)->letScope->Body->exprTree->returnValType(Qid);
		break;
	case STATIC_CALL:
		Qid->implement.clear();
		*Qid = *((Static_Node *)this)->staticImp;
		return 6;//class
		break;
	default:
		Qid->implement.clear();
		Qid->implement.push_back("#NULL");
		return 0; //dosn't return type!!!!!
	}
}

Node::~Node(){}

//---------------------------------------------Const_Node--------------------------------------------------
Const_Node::Const_Node(Const_Type CN) : Node(CONST) , type (CN) {}

Node* Const_Node::buildDefaultConst(list <char*> imp)
{
	Const_Type CT;
	if (strcmp(*imp.begin(),"Int")==0)
		{CT.iv=0; CT.type=1; return new Const_Node(CT);}
	else if (strcmp(*imp.begin(),"Float")==0)
		{CT.fv=0.0; CT.type=2; return new Const_Node(CT);}
	else if (strcmp(*imp.begin(),"String")==0)
		{CT.chv=""; CT.type=3; return new Const_Node(CT);}
	else if (strcmp(*imp.begin(),"Bool")==0)
		{CT.bv=false; CT.type=4; return new Const_Node(CT);}
	else
		{CT.type=0; return new Const_Node(CT);}
}

Const_Node::~Const_Node(){}

//---------------------------------------------ID_Node--------------------------------------------------
ID_Node::ID_Node(Variable* var): Node(IDENTIFIER) , var(var){}

//search for variable in the current Scope
bool ID_Node::searchScope(Scope* scope,char *name,Variable*& locate)
{
	if (!scope->Local.empty())
	{
		std::list<Variable*>::const_iterator i=scope->Local.begin();
		while (i!=scope->Local.end())
		{
			Variable*u=(Variable*)*i;
			if(strcmp (u->name,name)==0)
			{
				locate=u;
				return true;
			}
			i++;
		}
	}
	if (!(scope->parent=='\0'))
		searchScope(scope->parent,name,locate);
	else return false;
}

//search for variable in the current method signeture
bool ID_Node::searchMethodSig(list <Variable*> MethodSig,char*name,Variable*& locate)
{
	if (MethodSig.empty())
		return false;
	list<Variable*>::iterator i=MethodSig.begin();
	while (i!=MethodSig.end())
	{
		Variable*u=(Variable*)*i;
		if(strcmp (u->name,name)==0)
		{
			locate=u;
			return true;
		}
		i++;
	}
	return false;
}

//search for variable in the current method locals
bool ID_Node::searchMethodLocal(list <Variable*> Local,char *name,Variable*& locate)
{
	if (Local.empty())
		return false;
	bool ok=false;
	std::list<Variable*>::const_iterator i=Local.begin();
	while ((i!=Local.end())&&(!ok))
	{
		Variable*u=(Variable*)*i;
		if (strcmp(u->name,name)==0)
		{
			locate=u;
			ok=true;
		}
		i++;
	}
	return ok;
}

//search for variable in the current method
bool ID_Node::searchMethod(Method*currMethod,char*name,Variable*& locate)
{
	Variable* tmp='\0';
	if (searchMethodLocal(currMethod->Local,name,tmp))
	{
		locate=tmp;
		return true;
	}
	else if (searchMethodSig(currMethod->parameters,name,tmp))
	{
		locate=tmp;
		return true;
	}
	else return false;
}

//search for variable in the current class
bool ID_Node::SearchClass(Class *currClass,char *name,bool in_class,Variable*& locate,char* Caller)
{
	bool ok=false;
	list<Variable *>::const_iterator i=currClass->fields.begin();
	while ((i!=currClass->fields.end())&&(!ok))
	{
		Variable *u=(Variable*)*i;
		if ((strcmp (u->name,name)==0) && (in_class))
		{
			char* type=(char*)*(--u->varType->implement.end());
			//IF ID TYPE IS SELF_TYPE
			if(strcmp(type,"SELF_TYPE")==0)
			{
				list<char*> new_type; new_type.clear();
				new_type.push_front(Caller);
				Variable *tmp=new Variable(u->name);
				*tmp=*u;
				my_implements *R=new my_implements();
				R->implement=new_type;
				tmp->varType=R;
				locate = tmp;
			}
			else
				locate = u;
			ok=true;
		}
		else
		{
			if (!u->modi.empty())
			{
				if ((strcmp(u->name,name)==0)&&((my_modifiers::found(u->modi,Public))||(my_modifiers::found(u->modi,Protected))))
				{
					char* type=(char*)*(--u->varType->implement.end());
					//IF ID TYPE IS SELF_TYPE
					if(strcmp (type,"SELF_TYPE")==0)
					{
						list<char*> new_type; new_type.clear();
						new_type.push_front(Caller);
						Variable *tmp=new Variable(u->name);
						*tmp=*u;
						my_implements *R=new my_implements ();
						R->implement=new_type;
						tmp->varType=R;
						locate = tmp;
					}
					else
						locate = u;
					ok=true;
				}
			}
		}
		i++;
	}
	return ok;
}

//search for variable in the current class inherits
bool ID_Node::SearchInherits(my_implements *inherit,char *name,Variable*& locate,char *Caller)
{
	Variable* tmp='\0';
	if (!inherit->implement.empty()&&(inherit->place != NULL))
	{
		Class *myclass=(Class *)inherit->place;
		if (SearchClass(myclass,name,false,tmp,Caller))
		{
			locate=tmp;
			return true;
		}
		else
		{
			if (!myclass->inherit_class->implement.empty())
				return SearchInherits(myclass->inherit_class,name,locate,Caller);
			else
				return false;
		}
	}
	else
		 return false;
}

bool ID_Node::locateVar(Scope* currScope,Class *currClass ,Method *currMethod, char *name,Variable*& locate,char * Caller)
{
	Variable* tmp='\0';
	if (currScope!=NULL)
	{
		if (searchScope(currScope,name,tmp))
		{
			locate=tmp;
			return true;
		}
	}
	if (currMethod!=NULL)
	{
		if (searchMethod(currMethod,name,tmp))
		{
			locate=tmp;
			return true;
		}
	}
	if (SearchClass(currClass,name,true,tmp,Caller))
	{
		locate=tmp;
		return true;
	}
	else if (SearchInherits(currClass->inherit_class,name,tmp,Caller))
	{
		locate=tmp;
		return true;
	}
	else return false;
}

ID_Node::~ID_Node() {}

//---------------------------------------------Unary_Node--------------------------------------------------
Unary_Node::Unary_Node(Node *SON, UnaryOp op) :Node(UNARY)  , son(SON) ,opType(op) {}

Unary_Node::~Unary_Node() { delete son; }

//---------------------------------------------Binary_Node--------------------------------------------------
Binary_Node::Binary_Node(Node *right,Node *left,BinaryOp op): Node(BINARY) , opType(op), rightSon(right), leftSon(left) {}

bool Binary_Node::logicOp()
{
	if ((this->opType==AND)||(this->opType==OR))
		return true;
	else
		return false;
}

bool Binary_Node::arthmeticOp() 
{
	if ((this->opType==SUM)||(this->opType==SUB)||(this->opType==MULT)||(this->opType==DIVS))
		return true;
	else
		return false;
}

Binary_Node::~Binary_Node() {delete leftSon; delete rightSon;}

//---------------------------------------------FunctionCall_Node--------------------------------------------------

bool MethodSearch::checkReturn(AST* absTree)
{
	if (absTree==NULL)
		return false;
	else if (absTree->exprTree == NULL)
		return false;
	else if (absTree->exprTree->grp==IF_STMT)
	{
		AST* ifAST = ((Scope *)((IF_Node *)absTree->exprTree)->if_true)->Body; AST* elseAST = ((Scope *)((IF_Node *)absTree->exprTree)->if_else)->Body;
		if ((checkReturn(ifAST))&&(checkReturn(elseAST)))
			return true;
		else if ((!checkReturn(ifAST))&&(!checkReturn(elseAST)))
			return checkReturn(absTree->nextExpr);
		else
			return false;
	}
	else if (absTree->exprTree->grp==SCOPE)
	{
		if (checkReturn(((Scope *)absTree->exprTree)->Body))
			return true;
		else
			return checkReturn(absTree->nextExpr);
	}
	else if (absTree->exprTree->grp==RETURN_EXPR)
		return true;
	else
		return checkReturn(absTree->nextExpr);
}

bool MethodSearch::locateFunc(Class *currClass,char *name,AST*& seg,Method*&locate,char* Caller,bool later)
{
	if (SearchClass(currClass,name,true,seg,locate,Caller,later))
		return true;
	else if (SearchInherits(currClass->inherit_class,name,seg,locate,Caller,later))
		return true;
	else
		return false;
}

bool MethodSearch::locateFunc(Interface *currInterface,char *name,AST*& seg,Method*&locate,char *Caller,bool later)
{
	if (SearchInterface(currInterface,name,seg,locate,Caller,later))
		return true;
	else if (SearchInheritsI(currInterface->inherit_interface,name,seg,locate,Caller,later))
		return true;
	else
		return false;
}

bool MethodSearch::SearchClass(Class *currClass,char *name,bool in_class,AST*& seg,Method* &locate,char* Caller,bool later)
{
	bool ok=false;
	list<Method *>::const_iterator i=currClass->localFuncs.begin();
	while ( (i!=currClass->localFuncs.end()) && (!ok))
	{
		Method *u=(Method*)*i;
		list<Variable *> uPara = u->parameters;
		if ((strcmp (u->name,name)==0) &&(in_class))
		{
			if (checkPara(uPara,seg,later))
			{
				//Get return method type
				char* type=(char*)*(--u->returnType->implement.end());
				if (strcmp (type,"SELF_TYPE")==0)
				{
					Method* tmpo=new Method();
					*tmpo=*u;
					list <char*> new_type; new_type.clear();
					new_type.push_front(Caller);
					tmpo->returnType->implement=new_type;
					locate=tmpo;
				}
				else
					locate=u;
				ok=true;
			}
			else
				locate=u;
		}
		else
		{
			if (!u->modi.empty())
			{
				if ((strcmp (u->name,name)==0)&&((my_modifiers::found(u->modi,Public))||(my_modifiers::found(u->modi,Protected))))
				{
					if (checkPara(uPara,seg,later))
					{
						//Get return method type
						char* type=(char*)*(--u->returnType->implement.end());
						if (strcmp (type,"SELF_TYPE")==0)
						{
							Method* tmpo=new Method();
							*tmpo=*u;
							list <char*> new_type; new_type.clear();
							new_type.push_front(Caller);
							tmpo->returnType->implement=new_type;
							locate=tmpo;
						}
						else
							locate=u;
						ok=true;
					}
					else
						locate=u;
				}
			}
		}
		i++;
	}
	return ok;
}

bool MethodSearch::SearchInherits(my_implements *inherit,char *name,AST*& seg,Method* &locate,char* Caller,bool later)
{
	Method* tmp='\0';
	if (!inherit->implement.empty()&&(inherit->place != NULL))
	{
		Class *myclass=(Class *)inherit->place;
		if (SearchClass(myclass,name,false,seg,tmp,Caller,later))
		{
			locate=tmp;
			return true;
		}
		else
		{
			if ((!myclass->inherit_class->implement.empty())&&(myclass->inherit_class->place != NULL))
				return SearchInherits(myclass->inherit_class,name,seg,locate,Caller,later);
		}
	}
	return false;
}

bool MethodSearch::SearchInterface(Interface *currInterface,char *name,AST*& seg,Method* &locate,char* Caller,bool later)
{
	bool ok=false;
	if (currInterface!=NULL)
	{
		list<Method *>::const_iterator i=currInterface->Local.begin();
		while ( (i!=currInterface->Local.end()) && (!ok))
		{
			Method *u=(Method*)*i;
			list<Variable *> uPara = u->parameters;
			if (strcmp (u->name,name)==0)
			{
				if (checkPara(uPara,seg,later))
				{
					//Get return method type
					char* type=(char*)*(--u->returnType->implement.end());
					if (strcmp (type,"SELF_TYPE")==0)
					{
						Method* tmpo=new Method();
						*tmpo=*u;
						list <char*> new_type; new_type.clear();
						new_type.push_front(Caller);
						tmpo->returnType->implement=new_type;
						locate=tmpo;
					}
					else
						locate=u;
					ok=true;
				}
				else
					locate=u;
			}
			i++;
		}
	}
	return ok;
}

Method* tmp='\0';
bool MethodSearch::SearchInheritsI(list <my_implements *>inherit,char *name,AST*& seg,Method* &locate,char* Caller,bool later)
{
	if (!inherit.empty())
	{
		list<my_implements*>::iterator i=inherit.begin();
		while ((i!=inherit.end())&&(tmp=='\0'))
		{
			my_implements* R=(my_implements*) *i;
			if (R->place!=NULL)
			{
				if (SearchInterface((Interface*)R->place,name,seg,locate,Caller,later))
					tmp=locate;
				if (tmp=='\0')
				{
					if (!((Interface*)R->place)->inherit_interface.empty())
						SearchInheritsI(((Interface*)R->place)->inherit_interface,name,seg,locate,Caller,later);
				}
			}
			i++;
		}
	}
	if (tmp != NULL)
		return true;
	return false;
}

bool MethodSearch::checkPara(list<Variable *> uPara,AST*& seg,bool later)
{
	if ((uPara.empty())&&(seg->exprTree == NULL))
		return true;
	else if (uPara.size() == seg->size())
	{
		list<Variable *>::iterator i1=uPara.begin();
		AST* p2 = new AST(); p2 = seg; my_implements * type = new my_implements();
		while(i1!=uPara.end())
		{
			p2->exprTree->returnValType(type);
			Variable* p1=(Variable*)* i1;
			if (!commonUse::equal_char(p1->varType->implement,type->implement))
			{
				//if ((strcmp(*p1->varType->implement.begin(),"Float")==0)&&(strcmp(*type->implement.begin(),"Int")==0)&&(later))
				//{
				//	my_implements* imp = new my_implements("Float");
				//	Node * castNode = new Upcast_Node(imp,p2->exprTree);
				//	p2->exprTree = castNode;
				//}
				//else
					return false;
			}
			i1++;
			p2=p2->nextExpr;
		}
		return true;
	}
	else return false;
}

FunctionCall_Node::FunctionCall_Node(Method *locate,AST* callSegn): Node(FUNCTION_CALL), locate(locate), callSegn(callSegn) {}

FunctionCall_Node::~FunctionCall_Node() {delete locate;callSegn->~AST();}

//---------------------------------------------ConstructCall_Node--------------------------------------------------
ConstructCall_Node::ConstructCall_Node(Method *locate,AST* callSegn,my_implements* initClass): Node(CONSTRUCTOR_CALL), locate(locate), callSegn(callSegn),initClass(initClass) {}

ConstructCall_Node::~ConstructCall_Node() {delete locate;callSegn->~AST();}

//---------------------------------------------Assignment_Node--------------------------------------------------
Assignment_Node::Assignment_Node(Node *var, Node* value): Node(ASSIGNMENT), var(var), value(value) {}

Assignment_Node::~Assignment_Node() {delete var; delete value;}

//---------------------------------------------Upcast_Node--------------------------------------------------
Upcast_Node::Upcast_Node(my_implements* upperType,Node* son): Node(UPCAST), upperType(upperType), son(son) {}

Upcast_Node::~Upcast_Node() {delete upperType; delete son;}

//---------------------------------------------Downcast_Node--------------------------------------------------
Downcast_Node::Downcast_Node(my_implements* lowerType,Node* son): Node(DOWNCAST), lowerType(lowerType), son(son) {}

bool Downcast_Node::checkCastImplements(list<my_implements*> imp,Interface *curr)
{
	list<my_implements*>::iterator i=imp.begin();
	while (i!=imp.end()) 
	{
		my_implements * p=(my_implements*)*i;
		if(strcmp (p->place->name,curr->name)==0)
			return true;
		else //inherits interface
		{
			Interface * o=(Interface*) p->place;
			if (!o->inherit_interface.empty())
				return checkCastImplements(o->inherit_interface,curr);
			else
				return false;
		}
		i++;
	}
}

bool Downcast_Node::checkCastInherits(my_implements *in,Interface *curr)
{
	if (in->place!=NULL)
	{
	Class *C=(Class*)(in->place);
	list <my_implements*> imp=C->ImplementListInterface;
	list<my_implements*>::iterator i=imp.begin();
	while (i!=imp.end())
	{
		my_implements * p=(my_implements*)*i;
		if(strcmp (p->place->name,curr->name)==0)
			return true;
		else //inherits interface
		{
			Interface * o=(Interface*) p->place;
			if (!o->inherit_interface.empty())
				return checkCastImplements(o->inherit_interface,curr);
			else
				return false;
		}
		i++;
	}
	if (!C->inherit_class->implement.empty())
		return checkCastInherits(C->inherit_class,curr);
	}
	else
		return false;
}

bool Downcast_Node::checkCastType(Class * thisClass,Class* castClass)
{
	if (castClass == thisClass)
		return true;
	while ((castClass->inherit_class->place != NULL)&&(strcmp(*castClass->inherit_class->implement.begin(),"Object")!=0))
	{
		castClass=(Class*)castClass->inherit_class->place;
		if (castClass == thisClass)
			return true;
	}
	return false;
}

bool Downcast_Node::checkCastType(Interface * thisInterface,Class* castClass)
{
	if ((castClass->ImplementListInterface.empty())&&(strcmp(*castClass->inherit_class->implement.begin(),"Object")==0))
		return false;
	if ((!checkCastImplements(castClass->ImplementListInterface,thisInterface))&&(!checkCastInherits(castClass->inherit_class,thisInterface)))
		return false;
	else return true;
}

Downcast_Node::~Downcast_Node() {delete lowerType; delete son;}

//---------------------------------------------IF_Node--------------------------------------------------
IF_Node::IF_Node(Node *Condition, Node *if_true, Node *if_else): Node(IF_STMT) , Condition(Condition) , if_true(if_true) , if_else(if_else){}

IF_Node::~IF_Node(){ delete Condition; delete if_true; delete if_else; }

//---------------------------------------------WHILE_Node--------------------------------------------------
WHILE_Node::WHILE_Node(Node *Condition, Scope *Body) :Node(WHILE_STMT) , Condition(Condition), Body(Body){}

WHILE_Node::~WHILE_Node() {delete Condition; delete Body;}

//---------------------------------------------CASE_Node--------------------------------------------------
Case_Expr::Case_Expr(Const_Node * val, Node * expr)
{
	this->values.push_back(val);
	this->Body.push_back(expr);
}

void Case_Expr::addExpr(Const_Node * val, Node * expr)
{
	this->values.push_back(val);
	this->Body.push_back(expr);
}


Case_Expr::~Case_Expr()
{
	this->values.clear();
	this->Body.clear();
}

CASE_Node::CASE_Node(Node* caseOf,Case_Expr caseExprs) :Node(CASE_STMT) , caseOf(caseOf), caseExprs(caseExprs){}

bool CASE_Node::checkCaseType(int r,Case_Expr caseExprs)
{
	my_implements * t = new my_implements();
	list <Const_Node *>::iterator i = caseExprs.values.begin();
	while (i != caseExprs.values.end())
	{
		if (r != ((Const_Node *)*i)->returnValType(t))
			return false;
		i++;
	}
	return true;
}

CASE_Node::~CASE_Node() {delete caseOf; caseExprs.~Case_Expr();}

//---------------------------------------------Let_Node--------------------------------------------------
Let_Node::Let_Node(Scope* letScope) :Node(LET_STMT) , letScope(letScope){}

Let_Node::~Let_Node() {delete letScope;}

//---------------------------------------------Return_Node--------------------------------------------------
Return_Node::Return_Node(Node * ReturnVal) :Node(RETURN_EXPR), ReturnVal(ReturnVal){}

Return_Node::~Return_Node() {delete ReturnVal;}

//----------------------------------------Scope_Node------------------------------------------------

Scope::Scope():Node(SCOPE){}

Scope::Scope(Scope* parent):Node(SCOPE), parent(parent){}

bool Scope::searchScope(Variable *add)
{
	bool ok=false;
	list <Variable *> ::const_iterator i=Local.begin();
	while (!ok && i!=Local.end())
	{
		Variable *temp=(Variable *) *i;
		if(strcmp (temp->name,add->name)==0)
			ok=true; 
		i++;
	}
	return ok;
}

void Scope::addLocals(my_variables var)
{
	list<Variable*>::iterator i=var.variable.begin();
	while ((i!=var.variable.end()))
	{
		this->addLocal((Variable*)*i);
		i++;
	}
}

void Scope::addLocal(Variable *add)
{
	add->id = Local.size();
	Local.push_back(add);
}

Scope::~Scope(){}

/*-----------------------------------Array Node---------------------------------------*/

ArraySize::ArraySize(int x):Node(ARRAY_SIZE), x(x){}

bool ArraySize::checkArraySize(int xx,Node * x)
{
	if (x->grp == CONST)
		if ((xx<=((Const_Node *)x)->type.iv)||(((Const_Node *)x)->type.iv)<0)
			return false;
	return true;
}

//---------------------------------------------Static Node-------------------------------------------------

Static_Node::Static_Node(char * name):Node(STATIC_CALL)
{
	this->staticImp = new my_implements(name);
	this->define = false;
}
Static_Node::Static_Node(my_implements* imp):Node(STATIC_CALL)
{
	this->staticImp = new my_implements();
	this->staticImp = imp;
	this->define = false;
}

//-------------------------------------------Static Array Node-------------------------------------------------

StaticArray_Node::StaticArray_Node(my_implements* staticImp,Node * xArray):Node(STATIC_ARRAY_CALL),staticImp(staticImp),xArray(xArray){}

//---------------------------------------------Abstract Tree-----------------------------------------------

AST::AST()
{
	this->nextExpr=NULL;
	this->exprTree=NULL;
}

AST::AST(Node* node)
{
	this->nextExpr=NULL;
	this->exprTree=node;
}

void AST::printAST()
{
	AST * tmpo=new AST();
	my_implements * t = new my_implements();
	tmpo=this;
	while (tmpo!=NULL)
	{
		cout<<tmpo->exprTree->grp;
		cout<<tmpo->exprTree->returnValType(t);
		tmpo=tmpo->nextExpr;
	}
}

void AST::addNode(Node* node)
{
	AST * tmp=new AST ();
	tmp=this;
	bool added=false;
	if (this->exprTree==NULL)
	{
		this->exprTree=node;
		this->nextExpr=NULL;
	}
	else
	{
		while (!added)
		{
			if (tmp->nextExpr==NULL)
			{
				AST* add = new AST(node);
				tmp->nextExpr=add;
				added=true;
			}
			else tmp=tmp->nextExpr;
		}
	}
}

void AST::removeNode()
{
	AST * tmp=new AST();
	tmp=this->nextExpr->nextExpr;
	this->nextExpr=new AST();
	this->nextExpr=tmp;
}

int AST::size()
{
	int l=0;
	if (this == NULL)
		return l;
	else if (this->exprTree==NULL)
		return l;
	else
	{
		AST* tmpo = new AST();
		tmpo=this;
		while (tmpo!=NULL)
		{
			tmpo = tmpo->nextExpr;
			l++;
		}
		return l;
	}
}

AST::~AST(void)
{
	delete this->nextExpr;
	delete this->exprTree;
}

/*--------------------------------- Later Defenition --------------------------------*/

LaterDef::LaterDef()
{
	this->MemberExpectLater.clear();
	this->TypeExpectLater.clear();
}

void LaterDef::pointAtAST(Node * node,NameSpace * nameSpace,Class * clas,Method * method,Scope * scope,int line)
{
	memLater m; m.mem = node; m.line = line; m.nameSpace = nameSpace; m.clas = clas; m.method = method; m.scope = scope;
	this->MemberExpectLater.push_back(m);
}

void LaterDef::pointAtSymbol(Symbol * sym,bool type,NameSpace * nameSpace,int line)
{
	typeLater t; t.type = sym; t.line = line; t.nameSpace = nameSpace; t.method = type;
	this->TypeExpectLater.push_front(t);
}