#include "Symbol_Table.h"

//---------------------------------------------------------------------------------------------
bool equal_Mo(list <Modifier> p1,list <Modifier> p2)
{
	bool ok=false;
	list<Modifier>::const_iterator i=p1.begin();
	list<Modifier>::const_iterator ii=p2.begin();

	while (i!=p1.end() && ii!=p2.end() && !ok)
	{
		Modifier M1=(Modifier)*i;
		Modifier M2=(Modifier)*ii;
		if(M1!=M2)
			ok=true;
		i++;
		ii++;
	}
	if ((!p1.empty())||(!p2.empty()))
		 ok=true;
return ok;
}

bool search_in_param_method(list <Variable*> p,char *name)
{
	bool ok=false;
	if (!p.empty())
	{
		list<Variable*>::iterator i=p.begin();
		while ((i!=p.end())&&(!ok))
		{
			if (strcmp (((Variable*)*i)->name,name)==0)
				ok=true;
			i++;
		}
	}
	return ok;
}

//----------------------------------------Class Symbol------------------------------------------------

Symbol::Symbol()
{
	name=" ";
}

Symbol::Symbol(char *name, TYPE_ type)
{
	this->name=name;
	this->type=type;
}
//----------------------------------------Class Variable------------------------------------------------

Variable::Variable(char* name) : Symbol(name,variable){}

Variable::Variable(char* name,my_implements* varType) : Symbol(name,variable)
{
	this->varType=varType;
	this->modi.clear();
	this->val = NULL;
}

Variable::Variable(char* name,my_implements* varType,int p) : Symbol(name,parameter)
{
	this->varType=varType;
	this->modi.clear();
	this->id = p;
	this->val = NULL;
}

Variable::Variable(char* name,my_implements* varType, list <Modifier> modi) : Symbol(name,field)
{
	this->varType=varType;
	this->modi=modi;
	this->val = NULL;
}
//----------------------------------------Class Method------------------------------------------------

Method::Method(){}

Method::Method(char *name,list<Variable*> parameters,list<Modifier> modi,my_implements *returnType,bool type) : Symbol(name,method)
{
	this->parameters=parameters;
	this->modi=modi;
	this->returnType=returnType;
	this->haveReturn = false;
	this->constructor=type;
	this->label = "";
	this->absTree = NULL;
	this->LocalScopes.clear();
	this->virtualList1.clear();
	this->virtualList2.clear();
	this->DadCall = false;
}

bool Method::searchMethod(Variable *add)
{
	bool ok=false;
	if (!search_in_param_method(this->parameters,add->name))
	{
		list <Variable *> ::const_iterator i=Local.begin();
		while ((!ok) && (i!=Local.end()))
		{
			Variable *temp=(Variable *) *i;
			if(strcmp (temp->name,add->name)==0)
				ok=true; 
			i++;
		}
	} 
	else
		ok=true;
	return ok;
}

void Method::addLocal(Variable *add)
{
	add->id = this->Local.size();
	this->Local.push_back(add);
}

bool Method::equal_param(list <Variable *> p1,list <Variable *> p2)
{
	bool ok=true;
	if ((!p1.empty())&&(!p2.empty()))
	{
		list<Variable *>::iterator i1=p1.begin();
		list<Variable *>::iterator i2=p2.begin();

		while ((i1!=p1.end())&&(i2!=p2.end())&&(ok))
		{
			Variable* temp1=(Variable *) *i1;
			Variable* temp2=(Variable *) *i2;
			if  (!commonUse::equal_char(temp1->varType->implement,temp2->varType->implement) )
				ok=false;
			i1++; i2++;
		}
		if (ok)
		{
			if ((i1!=p1.end())||(i2!=p2.end()))
				ok=false;
		}
	}

	else if ((!p1.empty())||(!p2.empty()))
			ok=false;
	return ok;
}

void Method::buildParaLabel()
{
	list<Variable *>::iterator i = this->parameters.begin();
	while (i != this->parameters.end())
	{
		this->label.append("_");
		this->label.append(*(--((Variable *)*i)->varType->implement.end()));
		i++;
	}
}

bool Method::isVirtualOn(Method *mth)
{
	if ((this->name = mth->name)&&(equal_param(this->parameters,mth->parameters)))
		return true;
	else
		return false;
}

//----------------------------------------Class Class------------------------------------------------

Class::Class()
{
	modi.clear();
	this->Later = false;
}

Class::Class(char *name,list <Modifier> modi,my_implements* inherit_class,list <my_implements*> ImplementListInterface): Symbol(name,clas)
{
	this->inherit_class=inherit_class;
	this->modi=modi;
	this->localFuncs.clear();
	this->fields.clear();
	this->ImplementListInterface=ImplementListInterface;
	this->haveConstructor=false;
	this->fieldCount = 0;
	this->label = "";
	this->Over=false;
	this->Over_List.clear();
	this->CheckOver=false;
	this->OverInterface=false;
	this->Later=false;
	this->Cycle = false;
}

bool Class::search_Class(Symbol *add)
{
	bool ok=false;
	if (add->type==method) //Method
	{
		list <Method *> ::const_iterator i=localFuncs.begin();
		while ((!ok)&&(i!=localFuncs.end()))
		{
			Method * tmp=(Method *)*i;
			Method *j=(Method *)add;
			if (strcmp(tmp->name,j->name)==0)
			{
				if (Method::equal_param(tmp->parameters,j->parameters))
				{
					ok=true;
					if (commonUse::equal_char(tmp->returnType->implement,j->returnType->implement))
					{
						same_func=true;
						if ((my_modifiers::found(tmp->modi,Override))||(my_modifiers::found(tmp->modi,Virtual)))
							CheckOver=true;
						if(my_modifiers::found(tmp->modi,Override))
							OverInterface=true;
					}
				}
			}
			i++;
		}
	}
	else
	{
		list <Variable *> ::const_iterator i=fields.begin();
		while ((!ok)&&(i!=fields.end()))
		{
			if (strcmp(((Variable *) *i)->name,add->name)==0)
				ok=true;
			i++;
		}	 
	}
	return ok;
}

void Class::addLocal(Symbol *member)
{
	if (member->type == method)
		this->localFuncs.push_back((Method *)member);
	else
		this->fields.push_back((Variable *)member);
}

int Class::namerateFields()
{
	list <Variable *>::iterator i = this->fields.begin();
	int k=0;
	if (this->fields.empty())
		return ((Class *)this->inherit_class->place)->fieldCount;
	else
	{
		while (i != this->fields.end())
		{
			if (!my_modifiers::found(((Variable *)*i)->modi,Static))
			{
				k++;
				((Variable *)*i)->id = ((Class *)this->inherit_class->place)->fieldCount + k;
			}
			i++;
		}
	}
	return (((Class *)this->inherit_class->place)->fieldCount+k);
}
//----------------------------------------Class Interface------------------------------------------------

Interface::Interface()
{
	this->Local.clear();
	this->inherit_interface.clear();
	this->modi.clear();
	this->name="All";
	this->type=inter_face;
	this->Later = false;
}

Interface::Interface(char *name,std::list<Modifier> modifier,list <my_implements*> inherit_interface):Symbol(name,inter_face)
{
	this->inherit_interface.clear();
	this->modi.clear();
	this->modi=modifier;
	this->inherit_interface=inherit_interface;
	this->Later = false;
}

bool Interface::search_interface(Method *add)
{
	std::list <Method *> ::const_iterator i=Local.begin();
	bool ok=false;
	if (strcmp (add->name,this->name)==0)
		 ok=true;
	while ((!ok) && (i!=Local.end()) )
	{
		Method *temp=(Method *) *i;
		//compare Method only
		if(strcmp (add->name,temp->name)==0)
		{
			 if(Method::equal_param(temp->parameters,add->parameters))
				ok=true;
		}
		i++;
	}
	return ok;
}

void Interface::addLocal(Method *member)
{
		this->Local.push_back(member);
}

//----------------------------------------Class Namespace------------------------------------------------

NameSpace::NameSpace() : Symbol (new char,name_space)
{
	parent='\0';
	next='\0';
}

NameSpace::NameSpace(char *name) : Symbol (name,name_space)
{
	parent='\0';
	next='\0';
	this->label = "";
}

//we only insert class or interface to my namespace
//don't insert interface and class with same name very GOOOOOOOOOOOOD

bool NameSpace::searchNameSpace(Symbol *add)
{
	list <Symbol *> ::const_iterator i=Local.begin();
	bool ok=false;
	
	//if i have insert namespace'name same with my namespace' name
	while (!ok && i!=Local.end())
	{
		Symbol *temp=(Symbol *) *i;
		if ((strcmp (temp->name,add->name)==0))
			ok=true; 
		i++;
	}
	return ok;
}

void NameSpace::addLocal(Symbol *member)
{
	this->Local.push_back(member);
	if (member->type==name_space)
	{
		NameSpace *F=(NameSpace *) member;
		F->parent=(Symbol *)this;
	}

}

//-------------------------------------------Symbol Table------------------------------------------

SymbolTable::SymbolTable()
{
	this->entry_points = 0;
	this->hasMain = false;
	this->staticVars.clear();
	this->main = NULL;
	this->Main = NULL;
}

bool SymbolTable::validName(char* w)
{
	if ((strcmp(w,"Int")==0)||(strcmp(w,"Bool")==0)||(strcmp(w,"String")==0)||(strcmp(w,"SELF_TYPE")==0)||(strcmp(w,"self")==0)
		||(strcmp(w,"Object")==0)||(strcmp(w,"IO")==0)||(strcmp(w,"Float")==0)||(strcmp(w,"Void")==0))
		return false;
	else
		return true;
}

NameSpace* SymbolTable::buildSymbolTable()
{
	NameSpace* root = new NameSpace("#coolRoot"); root->label = "#coolRoot";
	//classes
	list <Modifier> classModi;
	classModi.push_back(Public); 
	classModi.push_back(Sealed);	//make it for public use and prevent inheritence
	my_implements * inher1 = new my_implements();
	list<my_implements *> inher2; 
	inher2.clear();
	//methods
	list <Variable *> para; 
	list <Modifier> methodModi; 
	methodModi.push_back(Public);
	list <char*> returnType; 
	list <char *> paraType;

	Class* Int = new Class("Int",classModi,inher1,inher2);
	Int->label = "Int";
	root->addLocal(Int);
	
	Class* Float = new Class("Float",classModi,inher1,inher2);
	Float->label = "Float";
	root->addLocal(Float);
	
	Class* Bool = new Class("Bool",classModi,inher1,inher2); 
	Bool->label = "Bool";
	root->addLocal(Bool);
	
	Class* String = new Class("String",classModi,inher1,inher2); 
	String->label = "String";
	returnType.clear(); returnType.push_back("String");
	
	my_implements *QID=new my_implements ();
	QID->implement=returnType;
	para.clear(); 
	para.push_back(new Variable("s",QID,1));

	Method* Concat = new Method("concat",para,methodModi,QID,false);
	Concat->haveReturn = true;
	Concat->label = "String_concat";
	String->addLocal(Concat);
	root->addLocal(String);
	
	Class* IO = new Class("IO",classModi,inher1,inher2); IO->label = "IO";
	methodModi.push_back(Static);
	returnType.clear(); returnType.push_back("Void");
	paraType.clear(); paraType.push_back("String");
	QID=new my_implements ();
	QID->implement=paraType;
	para.clear(); para.push_back(new Variable("x",QID,0));
	QID=new my_implements();
	QID->implement=returnType;
	Method* OutString = new Method("out_string",para,methodModi,QID,false); OutString->label = "IO_out_string";
	IO->addLocal(OutString);
	paraType.clear(); paraType.push_back("Int");
	QID=new my_implements ();
	QID->implement=paraType;
	para.clear(); para.push_back(new Variable("x",QID,0));
	QID=new my_implements();
	QID->implement=returnType;
	Method* OutInt = new Method("out_int",para,methodModi,QID,false); OutInt->label = "IO_out_int";
	IO->addLocal(OutInt);
	paraType.clear(); paraType.push_back("Float");
	QID=new my_implements ();
	QID->implement=paraType;
	para.clear(); para.push_back(new Variable("x",QID,0));
	QID=new my_implements();
	QID->implement=returnType;
	Method* OutFloat = new Method("out_float",para,methodModi,QID,false); OutFloat->label = "IO_out_float";
	IO->addLocal(OutFloat);
	para.clear();
	returnType.clear(); returnType.push_back("String");
	QID=new my_implements();
	QID->implement=returnType;; QID->place = String;
	Method* InString = new Method("in_string",para,methodModi,QID,false); InString->label = "IO_in_string";
	InString->haveReturn = true;
	IO->addLocal(InString);
	returnType.clear(); returnType.push_back("Int");
	QID=new my_implements();
	QID->implement=returnType; QID->place = Int;
	Method* InInt = new Method("in_int",para,methodModi,QID,false); InInt->label = "IO_in_int";
	InInt->haveReturn = true;
	IO->addLocal(InInt);
	returnType.clear(); returnType.push_back("Float");
	QID=new my_implements();
	QID->implement=returnType; QID->place = Float;
	Method* InFloat = new Method("in_float",para,methodModi,QID,false); InFloat->label = "IO_in_float";
	InFloat->haveReturn = true;
	IO->addLocal(InFloat);
	root->addLocal(IO);
	
	methodModi.pop_back(); classModi.pop_back();	//class Object must inherited drop "Sealed"
	Class* Object = new Class("Object",classModi,inher1,inher2); Object->label = "Object";
	Object->fieldCount = 0;
	returnType.clear(); returnType.push_back("String");
	para.clear();
	my_implements *R=new my_implements();
	R->implement=returnType; R->place = String;
	Method* TypeName = new Method("type_name",para,methodModi,R,false); TypeName->label = "Object_type_name";
	TypeName->haveReturn = true;
	Object->addLocal(TypeName);
	R=new my_implements(); returnType.clear(); returnType.push_back("Void"); R->implement=returnType;
	Method* Abort = new Method("abort",para,methodModi,R,false); Abort->label = "Object_abort";
	Object->addLocal(Abort);
	list <Modifier> modi; modi.clear(); modi.push_back(Public);
    returnType.clear(); returnType.push_back("SELF_TYPE");
	R=new my_implements(); R->implement=returnType;
	Method * ObjectInit = new Method("Object",para,methodModi,R,true); ObjectInit->label = "Object_Object";
	Object->haveConstructor=true;//for build default constructor
	Object->addLocal(ObjectInit);
	root->addLocal(Object);
	return root;
}

//////////////////////////////////////////////////////END///////////////////////////////////////////////////////////////

//other class my_modifiers and my_implements
my_modifiers::my_modifiers (Modifier init)
{
	this->modi.push_back(init);
}

void  my_modifiers::add_modifier(Modifier add)
{
	this->modi.push_back(add);
}

bool my_modifiers::found(list<Modifier> modi,Modifier g)
{
	list<Modifier>::iterator i = modi.begin();
	while (i!=modi.end())
	{
		Modifier m = (Modifier) *i;
		if (m == g)
			return true;
		i++;
	}
	return false;
}

my_modifiers::~my_modifiers()
{
	this->modi.clear();
}

////////////////////////////////////////////////////

my_implements::my_implements()
{
	this->implement.clear();
	this->place=NULL;
}

my_implements::my_implements(char *init)
{
	this->implement.push_back(init);
	this->place=NULL;
}

void my_implements::add_implement(char* add)
{
	this->implement.push_back(add);
}

my_implements::~my_implements()
{
	this->implement.clear();
}

////////////////////////////////////////////////////
my_parameters::my_parameters()
{
	this->parameter.clear();
}

my_parameters::my_parameters(Variable *init)
{
	this->parameter.push_back(init);
}

void my_parameters::add_parameter(Variable *add)
{
	this->parameter.push_back(add);
}

my_parameters::~my_parameters()
{
	this->parameter.clear();
}

//////////////////////////////////////////////////////

my_variables::my_variables(Variable *init)
{
	this->variable.push_back(init);
}

void my_variables::add_variable(Variable *add)
{
	this->variable.push_back(add);
}

my_variables::~my_variables()
{
	this->variable.clear();
}
////////////////////////////////////////////////////////

my_QIDList::my_QIDList (my_implements *init)
{
	this->lists.push_back(init);
}

void my_QIDList::add_list(my_implements *add)
{
	this->lists.push_back(add);
}

my_QIDList::~my_QIDList ()
{
	this->lists.clear();
}