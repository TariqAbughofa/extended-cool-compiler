#include "Actions.h"

//Symbol Table

Actions::Actions()
{
	this->sure=true;
	this->sure_=true;
	this->sure__=true;
	this->later=false;
	this->laterTree=false;
	this->currNamespace='\0';
	this->root='\0';
	this->currClass='\0';
	this->currMethod='\0';
	this->currVariable='\0';
	this->currScope='\0';
	this->my_laterDef = new LaterDef();
	this->My_ref=new Refuse();
	this->My_err=new Error();
	this->My_wrn=new Warn();
	this->my_check=new Check();
	this->FirstDad=false;
}

void Actions::Print_SymbolTable()
{
	NameSpace *temp=root;
	while(temp!='\0')
	{
		cout<<"==" << temp->name<<"=="<<'\n';
		std::list <Symbol *> ::const_iterator i=temp->Local.begin();
		while (i!=temp->Local.end())
		{
			Symbol *pp=(Symbol  *) *i;
			cout <<pp->name<<"=="<<pp->type<<"\n";
	        i++;
		}
		temp=(NameSpace *)temp->next;
    }
}

bool Actions::Search_Root(Symbol *t,Symbol *brother)
{
	bool ok=false;
	while ((t!='\0') && (strcmp (t->name,brother->name)!=0) )
	{
		NameSpace *g=(NameSpace *)t;
		t=g->next;
	}
	if(t!='\0')
		ok=true;
	return ok;
}

//-------------------------------------NameSpaceAction---------------------------
void Actions::NameSpace_Action(list<char*> implement,int line,bool exe)
{
	if (exe)
	{
		NameSpace * temp_namespace=new NameSpace();
		if (sure)
		{
			sure = true;
			if (currNamespace == NULL)
				currNamespace=SymbolTable::buildSymbolTable();
			std::list<char *>::const_iterator iNamespace=implement.begin();
			while (iNamespace!=implement.end())
			{
				char *r=(char *)*iNamespace;
				if(currNamespace=='\0')
				{
					temp_namespace =new NameSpace(r);
					if (root=='\0')
					{
						currNamespace=temp_namespace;
						root=currNamespace;
						currNamespace->parent='\0';
					}
					else
					{
						if (Search_Root(root,temp_namespace))
							My_ref->addRefuse("NAMESPACE '",temp_namespace->name,"' REDEFINATION",temp_namespace->name,name_space,line,sure);
						else
						{
							currNamespace=temp_namespace;
							currNamespace->next=root;
							root=currNamespace;
							currNamespace->parent='\0';
						}
					}
				}
				else
				{
					temp_namespace =new NameSpace(r);
					if (!currNamespace->searchNameSpace((Symbol *)temp_namespace))
					{
						currNamespace->addLocal(temp_namespace);
						temp_namespace->parent=currNamespace;
						currNamespace=temp_namespace;
					}
					else
						My_ref->addRefuse("NAMESPACE '",temp_namespace->name,"' REDEFINATION",temp_namespace->name,name_space,line,sure);
				}
				iNamespace++;
				currNamespace->label = r;
			}
		}
	}
	else
	{
		if (currNamespace!='\0')
		{
			if (sure)
			{
				if(implement.size()>1)
				{
					std::list<char *>::const_iterator iNamespace=implement.end();
					iNamespace--;
					char *end=(char *)*iNamespace;
					if ((currNamespace->parent!='\0') && (strcmp (currNamespace->name,end)!=0) )
						currNamespace=(NameSpace*)currNamespace->parent;
					else
					{
						iNamespace=implement.begin();
						char *first=(char *)*iNamespace;
						while ((currNamespace->parent!='\0')&& (strcmp (currNamespace->name,first)!=0) )
							currNamespace=(NameSpace*)currNamespace->parent;
						if(currNamespace->parent!='\0')     
							root=(NameSpace *)currNamespace->parent;
						else
						   root=(NameSpace *)currNamespace; 
						currNamespace=(NameSpace *)currNamespace->parent;
					}
				}
				else
				{
					if(currNamespace->parent!='\0')
						root=(NameSpace *)currNamespace->parent; 
					else
						root=(NameSpace *)currNamespace;
					currNamespace=(NameSpace *)currNamespace->parent;
				}
			}
			else
				sure=true; 
		}
		else
			sure=true;
	}
}

//-------------------------------------ClassAction---------------------------
void Actions::Class_Action(list <Modifier> modi,list <my_implements *>& lists,my_implements * &QID,char* name,int line)
{
 	if (sure)
	{
		currClass = new Class(name,modi,QID,lists); sure_ = true;
		currClass->label.append(currNamespace->label); currClass->label.append("_"); currClass->label.append(name);
		if (my_check->Check_ClassModifier(modi))
		{
			if (((!currNamespace->searchNameSpace((Symbol *) currClass))&&(SymbolTable::validName(name)))||(later))
			{
				if ((my_check->check_QID_LIST(currNamespace,currClass,lists))&&(my_check->Check_QID(currNamespace,currClass,QID)))
				{
					if (!my_modifiers::found(((Class *)QID->place)->modi,Sealed))
					{
						if ((!((Class *)QID->place)->Later)&&(!SomeLater(lists)))
						{
							if (later)
								currClass->Later = true;
							if ((((Class*)(currClass->inherit_class->place))->Over)||(!((Class*)(currClass->inherit_class->place))->Over_List.empty()))
								currClass->Over=true;
   							if (my_check->checkInterface_inherits(lists))
							{
								list<Class*> List; List.clear(); List.push_back(currClass);
								bool ISNULL=false;
								if (currClass->inherit_class->place==NULL)
									ISNULL=true;
								bool ok=false;
								if (!ISNULL) 
								{
									if ((my_check->checkCircleInherit((Class*)currClass->inherit_class->place,List,ISNULL,ok))) 
									{
										currClass->Cycle=true;
										My_ref->addRefuse("Circular base class dependency involving : ",name," , ",QID->place->name,name,clas,line,sure_);
									}
								}
								if (!later)
									currNamespace->addLocal((Symbol *)currClass);
							}
							else //Check inmplemented interfaces
								My_ref->addRefuse("METHODES IMPLEMENTED ARE INCOMPATIBLE",name,clas,line,sure_);
						}
						else if (!later)
						{
							currNamespace->addLocal((Symbol *)currClass); currClass->Later=true;
							my_laterDef->pointAtSymbol(currClass,false,currNamespace,line);
						}
					}
					else //Sealed
					{
						currClass->Cycle=true;
						My_ref->addRefuse("CLASS '",QID->place->name,"' Can not Be inherited",name,clas,line,sure_);
					}
				}
				else if (!later)
				{
					currClass->Later=true;
					currNamespace->addLocal((Symbol *)currClass);
					my_laterDef->pointAtSymbol(currClass,false,currNamespace,line);
				}
				else
					My_ref->addRefuse("BASE CLASS/INTERFACE UNDEFINED",name,clas,line,sure_);
			}
			else
				My_ref->addRefuse("CLASS '",currClass->name,"' REDEFINATION OR UNVALID CLASS NAME",name,clas,line,sure_);
		}
		else
		{
			Refuse_Add * R=new Refuse_Add();
			R->line=line;
			R->msg="";
			R->msg.append("illegal combination of modifiers:");
			list<Modifier>::iterator i=modi.begin();
			while (i!=modi.end())
			{
				Modifier g=(Modifier) *i;
				switch (g) {
				case (0):  R->msg.append("public"); break;
				case (1):  R->msg.append("private"); break;
				case (2):  R->msg.append("protected"); break;
				case (3):  R->msg.append("internal"); break;
				case (4):  R->msg.append("static"); break;
				case (5):  R->msg.append("readonly"); break;
				case (6):  R->msg.append("virtual"); break;
				case (7):  R->msg.append("sealed"); break;
				case (8):  R->msg.append("override"); break;
				case (9):  R->msg.append("abstract"); break;
				}
				R->msg.append(" ");
				i++;
			}
			R->name= name; R->type=clas;
			My_ref->insert_Ref(R);
		}
	}
}

void Actions::closeClass_Action(int line)
{
	if (!currClass->haveConstructor)
	{
		list <Variable *> para; para.clear(); list <Modifier> modi; modi.clear(); modi.push_back(Public);
		my_implements * QID=new my_implements(); QID->implement.push_back("SELF_TYPE");
		currMethod = new Method(currClass->name,para,modi,QID,true);
		currMethod->label.append(currClass->label); currMethod->label.append("_"); currMethod->label.append(currMethod->name);
		if ((!currClass->inherit_class->implement.empty())&&(strcmp("Object",*(--currClass->inherit_class->implement.end()))!=0)&&(currClass->inherit_class->place!=NULL))
		{
			list<Method*> Con; Con.clear();
			Con=Get_Cons_Father((Class*)currClass->inherit_class->place);
			list<Method*>::iterator i=Con.begin(); bool Sig=true;
			while ((Sig)&&(i!=Con.end()))
			{
				Method* M=(Method*) *i;
				if (M->parameters.empty())
					Sig=false;
				i++;
			}
			if (Sig)
				My_ref->addRefuse(currMethod->name," : Cannot find Symbol : Required Constructer",currClass->inherit_class->place->name,method,line,*new bool);
			else
			{
				currMethod->absTree = NULL;
				currClass->addLocal(currMethod);
				currClass->haveConstructor=true;
			}
		}
		else if (strcmp("Object",*(--currClass->inherit_class->implement.end()))!=0)
		{
			currMethod->absTree = NULL;
			currClass->addLocal(currMethod);
			currClass->haveConstructor=true;
			my_laterDef->pointAtSymbol(currMethod,true,currNamespace,line);
		}
		else //Inherit From Object
		{
			currMethod->absTree = NULL;
			currClass->addLocal((Symbol *)currMethod);
			currClass->haveConstructor=true;
		}
	}
	if ((!currClass->Later)&&(!currClass->Cycle))
	{
		if (currClass->Over)
			Get_Labels(currClass,(Class*&)currClass->inherit_class->place);
		if ( (!currClass->inherit_class->implement.empty()) || (!currClass->ImplementListInterface.empty()))
		{
			list <my_implements*>::iterator i=currClass->ImplementListInterface.begin();
			while (i!=currClass->ImplementListInterface.end())
			{
				my_implements *T=(my_implements*) *i;
				Get_Label_Interface((Interface*)T->place,currClass);
				i++;
			}
			Get_Labels_Interface(currClass,(Class*)currClass->inherit_class->place);
		}
		list<my_implements *>::iterator i = currClass->ImplementListInterface.begin(); Interface * in = new Interface();
		while (i!=currClass->ImplementListInterface.end())
		{
			if (((my_implements *) *i)->place != NULL)
			{
				in = (Interface *)((my_implements *) *i)->place;
				if ((!my_modifiers::found(currClass->modi,Abstract))&&(!my_check->checkFinal_Class(currClass,in)))
					My_ref->addRefuse("Class ",currClass->name," : MUST OVERRIDE ALL METHODS FROM IMPLEMENTED INTERFACE : ",in->name,currClass->name,clas,line,*new bool);
			}
			i++;
		}
		if ((!currClass->inherit_class->implement.empty())&&(currClass->inherit_class->place!= NULL))
			if ((!my_modifiers::found(currClass->modi,Abstract))&&(!my_check->check_abstract_inhertits(currClass,currClass->inherit_class)))
				My_ref->addRefuse("Class ",currClass->name," : MUST IMPLEMENT ALL METHODS FROM INHERITED ABSTRACT CLASSES",currClass->name,clas,line,*new bool);
		if (currClass->inherit_class->place != NULL)
			currClass->fieldCount = currClass->namerateFields();
	}
}

void Actions::Get_Labels(Class* Base,Class*& Inh)
{
	if (Base->Over)
	{
		list<Method*>::iterator i=Inh->Over_List.begin();
		while (i!=Inh->Over_List.end())
		{
			Method *M=(Method*) *i;
			Base->same_func=false;
			Base->CheckOver=false;
			string Label1=""; string Label2="";
			if ((Base->search_Class(M))&& (Base->same_func)&&(Base->CheckOver))
			{
				Label1.append(Base->label);/* Label1.append("_"); Label1.append(M->name);*/ 
				Label2.append(Base->label); Label2.append("_"); Label2.append(M->name);
				list<Variable *>::iterator ii = M->parameters.begin();
				while (ii != M->parameters.end())
				{
					/*Label1.append("_"); Label1.append(*(--((Variable *)*ii)->varType->implement.end()));*/
					Label2.append("_"); Label2.append(*(--((Variable *)*ii)->varType->implement.end()));
					ii++;
				}
			}
			else
			{
				bool found=false;
				Class * tmp=Base;
				while (!found)
				{
					tmp=(Class*)tmp->inherit_class->place;
					if ((tmp->search_Class(M))&& (tmp->same_func)&&(tmp->CheckOver))
						found=true;

				}
				Label1.append(Base->label);/* Label1.append("_"); Label1.append(M->name);*/
				Label2.append(tmp->label); Label2.append("_"); Label2.append(M->name);
				list<Variable *>::iterator ii = M->parameters.begin();
				while (ii != M->parameters.end())
				{
					Label1.append("_"); Label1.append(*(--((Variable *)*ii)->varType->implement.end()));
					Label2.append("_"); Label2.append(*(--((Variable *)*ii)->varType->implement.end()));
					ii++;
				}
			}
			((Method*) *i)->virtualList1.push_back(Label1);
			((Method*) *i)->virtualList2.push_back(Label2);
			i++;
		}
		if (Inh->inherit_class->place!=NULL)
			Get_Labels(Base,(Class*&)Inh->inherit_class->place);
	}

}

void Actions::Get_Label_Interface(Interface*T ,Class * currClass)
{
	list<Method*>::iterator i=T->Local.begin();
	string Label1="",Label2="";
	while (i!=T->Local.end())
	{ 
		Method* M=(Method*)*i;
		Label1=""; Label2="";
		Label1.append(currClass->label);/* Label1.append("_"); Label1.append(M->name); */
		Label2.append(currClass->label); Label2.append("_"); Label2.append(M->name);
		
		list<Variable *>::iterator ii = M->parameters.begin();
		while (ii != M->parameters.end())
		{
			/*Label1.append("_"); Label1.append(*(--((Variable *)*ii)->varType->implement.end()));*/
			Label2.append("_"); Label2.append(*(--((Variable *)*ii)->varType->implement.end()));
			ii++;
		}
		((Method*)(*i))->virtualList1.push_back(Label1);
		((Method*)(*i))->virtualList2.push_back(Label2); 
		i++;
	}
	if (!T->inherit_interface.empty())
	{
		list<my_implements*>::iterator i=T->inherit_interface.begin();
		while (i!=T->inherit_interface.end())
		{
			Get_Label_Interface((Interface*)(*i)->place,currClass);
			i++;
		}
	}
}

void Actions::Get_Labels_Interface(Class *Base,Class * Inh)
{
	if (!Inh->ImplementListInterface.empty())
	{
		list<my_implements*>::iterator i=Inh->ImplementListInterface.begin();
		while (i!=Inh->ImplementListInterface.end())
		{
			my_implements* I=(my_implements*)*i;
			Process_Interface(Base,Inh,(Interface*&)I->place);
			i++;
		}
	}
	if (!Inh->inherit_class->implement.empty())
		Get_Labels_Interface(Base,(Class*)Inh->inherit_class->place);
}

void Actions::Process_Interface(Class * Base,Class *currClass,Interface *& currInterface)
{
	list<Method*>::iterator i=currInterface->Local.begin();
	while (i!=currInterface->Local.end())
	{
		Method* M=(Method*) *i;
		Base->same_func=false;
		Base->search_Class(M);
		string Label1="",Label2="";
		if (Base->same_func) //Found In Base 
		{
			Label1=""; Label2="";
			Label1.append(Base->label);/* Label1.append("_"); Label1.append(M->name);*/ 
			Label2.append(Base->label); Label2.append("_"); Label2.append(M->name);
			list<Variable *>::iterator ii = M->parameters.begin();
			while (ii != M->parameters.end())
			{
				/*Label1.append("_"); Label1.append(*(--((Variable *)*ii)->varType->implement.end()));*/
				Label2.append("_"); Label2.append(*(--((Variable *)*ii)->varType->implement.end()));
				ii++;
			}
		}
		else //Found In CurrClass
		{
			bool found=false;
			Class * tmp=Base;
			while ((!found) && (tmp!=currClass))
			{
				tmp=(Class*)tmp->inherit_class->place;
				if ((tmp->search_Class(M))&& (tmp->same_func)&&(tmp->OverInterface))
					found=true;
			}
			if (!found)
				tmp=currClass;
			Label1=""; Label2="";
			Label1.append(Base->label);/* Label1.append("_"); Label1.append(M->name); */
			Label2.append(tmp->label); Label2.append("_"); Label2.append(M->name);
			list<Variable *>::iterator ii = M->parameters.begin();
			while (ii != M->parameters.end())
			{
				/*Label1.append("_"); Label1.append(*(--((Variable *)*ii)->varType->implement.end()));*/
				Label2.append("_"); Label2.append(*(--((Variable *)*ii)->varType->implement.end()));
				ii++;
			}
		}
		((Method*)(*i))->virtualList1.push_back(Label1);  	
		((Method*)(*i))->virtualList2.push_back(Label2); 
		i++;
	}
}

//------------------------------------InterfaceAction---------------------------
void Actions::Interface_Action(list <Modifier> modi,list <my_implements *>& lists,char* name,int line)
{
	if (sure)
	{
		currInterface = new Interface(name,modi,lists);
		if (my_check->Check_InterfaceModifier(modi))
		{
			if (((!currNamespace->searchNameSpace((Symbol *) currInterface))&&(SymbolTable::validName(name)))||(later))
			{
				if (my_check->check_QID_LIST(currNamespace,currClass,lists))
				{
					if (!SomeLater(lists))
					{
						if (later)
							currInterface->Later = true; 
						list <Interface *> Old; list<Interface*> New; Old.clear(); New.clear();
						bool ok=false;
						Old.push_back(currInterface); New.push_back(currInterface);
						if (my_check->checkCircleInherit(currInterface,currInterface->inherit_interface,ok,Old,New))
							My_ref->addRefuse("Circular base Interface dependency involving : ",name,name,clas,line,sure_);
						else if (my_check->checkInterface_inherits(lists))
						{
							if (!later)
								currNamespace->addLocal((Symbol *)currInterface);
						}
						else
							My_ref->addRefuse("METHODES INHERITED ARE INCOMPATIBLE",name,inter_face,line,sure_);
					}
					else if (!later)
					{
						currNamespace->addLocal((Symbol *)currInterface); currInterface->Later=true;
						my_laterDef->pointAtSymbol(currInterface,false,currNamespace,line);
					}
				}
				else if (!later)
				{
					currNamespace->addLocal((Symbol *)currInterface); currInterface->Later=true;
					my_laterDef->pointAtSymbol(currInterface,false,currNamespace,line);
				}
				else
					My_ref->addRefuse("BASE INTERFACE UNDEFINED",name,inter_face,line,sure_);
			}
			else
				My_ref->addRefuse("INTERFACE '",currInterface->name,"' REDEFINATION OR UNVALID NAME",name,inter_face,line,sure_);
		}
		else
		{
			Refuse_Add* R=new Refuse_Add();
			R->line=line;
		    R->msg="";
			R->msg.append("illegal combination of modifiers : ");
			list<Modifier>::iterator i=modi.begin();
			while (i!=modi.end())
			{
				Modifier g=(Modifier) *i;
			     switch (g) {
				 case (0):  R->msg.append("public"); break;
				 case (1):  R->msg.append("private"); break;
				 case (2):  R->msg.append("protected"); break;
				 case (3):  R->msg.append("internal"); break;
				 case (4):  R->msg.append("static"); break;
				 case (5):  R->msg.append("readonly"); break;
				 case (6):  R->msg.append("virtual"); break;
				 case (7):  R->msg.append("sealed"); break;
				 case (8):  R->msg.append("override"); break;
				 case (9):  R->msg.append("abstract"); break;
				 }
				 R->msg.append(" ");
				 i++;
			}
			R->name= name; R->type=inter_face;
			My_ref->insert_Ref(R);
		}
	}
}

void Actions::closeInterface_Action(int line)
{
	if (!currInterface->Later)
	{
		list<my_implements *>::iterator i = currInterface->inherit_interface.begin(); Interface * in = new Interface();
		while (i!=currInterface->inherit_interface.end())
		{
			in = (Interface *)((my_implements *) *i)->place;
			if (in != NULL)
				if (!my_check->checkFinal_Interface(in->Local,currInterface->Local))
					My_ref->addRefuse("METHODES INHERITED ARE INCOMPATIBLE WITH INTERFACE : ",currInterface->name,currInterface->name,inter_face,line,*new bool);
			i++;
		}
	}
}

bool Actions::SomeLater(list <my_implements*> L)
{
	list<my_implements*>::iterator i=L.begin();
	while (i!=L.end())
	{
		my_implements *tmp=(my_implements*) *i;
		 if (((Interface *)(tmp->place))->Later)
			return true;
		i++;
	}
	return false;
}

//------------------------------------MehtodsInterface_Action---------------------------
void Actions::MehtodsInterface_Action(list <Variable*> parameter,my_implements *QID,char *name,int line)
{
    if ((sure)&&(sure_))
	{
		list <Modifier> modi; modi.clear(); modi.push_back(Abstract);
		currMethod=new Method(name,parameter,modi,QID,false);
		if ((!currInterface->search_interface(currMethod))||(later))
		{
			if ((my_check->Check_ReturnQID(currNamespace,currMethod,QID))&&(my_check->check_param((Symbol *)currMethod,currNamespace,parameter)))
			{
				if (!later)
					currInterface->addLocal(currMethod);
			}
			else if (!later)
			{
				currInterface->addLocal(currMethod);
				my_laterDef->pointAtSymbol(currMethod,false,currNamespace,line);
			}
			else
				My_ref->addRefuse("RETURN TYPE UNDEFINED OR SOME PARAMETERS UNDEFINED",name,method,line,*new bool);
		}
		else
			My_ref->addRefuse("FEATURE '",currMethod->name,"' REDEFINATION",name,method,line,*new bool);
	}
}

//------------------------------------FieldsClass_Action---------------------------
void Actions::VariablesClass_Action(list<Modifier> modi,my_implements *&QID,char *name,int line)
{
	if ((sure)&&(sure_))
	{
		currMethod='\0'; sure__ = true;
		currVariable=new Variable(name,QID,modi);
	   	bool re_only=false;
		if (!SymbolTable::validName(name))
			My_ref->addRefuse("un-valid name : ",name,name,variable,line,sure__);
		//remain Process readonly modifier
		else if (my_check->Check_VarModifier(modi,re_only))
		{
			if ((!currClass->search_Class((Symbol *)currVariable))||(later))
			{
				if (my_check->Check_QID(currNamespace,currClass,QID))
				{
					if (!my_modifiers::found(((Class *)QID->place)->modi,Abstract))
					{
						if ((my_modifiers::found(currVariable->modi,Readonly))&&(!((strcmp(((Class *)QID->place)->name,"Int")==0)||(strcmp(((Class *)QID->place)->name,"Float")==0)||(strcmp(((Class *)QID->place)->name,"Bool")==0)||(strcmp(((Class *)QID->place)->name,"String")==0))))
							My_ref->addRefuse("Readonly Object of non-basic type illegal : ",((Class *)QID->place)->name,name,variable,line,sure__);
						else
						{
							if (!later)
							{
								currClass->addLocal((Symbol *)currVariable);
								collectStatic(currVariable);
							}
						}	
					}
					else
						My_ref->addRefuse("can not make an object of Abstract class : ",((Class *)QID->place)->name,name,variable,line,sure__);
				}
				else if (my_check->Check_QID_two(currNamespace,currClass,QID))
				{
					if (!later)
					{
						currClass->addLocal((Symbol *)currVariable);
						collectStatic(currVariable);
					}
				}
				else if ((strcmp(*QID->implement.begin(),"SELF_TYPE")==0)&&(QID->implement.size() == 1))
				{
					if (my_modifiers::found(modi,Static))
						My_ref->addRefuse("can not make an static SELF_TYPE object : ",((Class *)QID->place)->name,name,variable,line,sure__);
					else if (!later)
						currClass->addLocal((Symbol *)currVariable);
				}
				else if (!later)
				{
					currClass->addLocal((Symbol *)currVariable);
					collectStatic(currVariable);
					my_laterDef->pointAtSymbol(currVariable,false,currNamespace,line);
				}
				else
					My_ref->addRefuse("RETURN TYPE UNDEFINED",name,variable,line,*new bool);
			}
			else
				My_ref->addRefuse("VARIABLE '",currVariable->name,"' REDEFINATION",name,variable,line,sure__);
		}
	    else
	    {
			Refuse_Add *R=new Refuse_Add();
			R->line=line;
			R->msg="";
			R->msg.append("illegal combination of modifiers:");
			list<Modifier>::iterator i=modi.begin();
			while (i!=modi.end())
			{
				 Modifier g=(Modifier) *i;
				 switch (g) {
				 case (0):  R->msg.append("public"); break;
				 case (1):  R->msg.append("private"); break;
				 case (2):  R->msg.append("protected"); break;
				 case (3):  R->msg.append("internal"); break;
				 case (4):  R->msg.append("static"); break;
				 case (5):  R->msg.append("readonly"); break;
				 case (6):  R->msg.append("virtual"); break;
				 case (7):  R->msg.append("sealed"); break;
				 case (8):  R->msg.append("override"); break;
				 case (9):  R->msg.append("abstract"); break;
				}
				R->msg.append(" ");
				i++;
			}
			R->name= name; R->type=variable;
			My_ref->insert_Ref(R);
		}
	}
}

void Actions::ArraysClass_Action(list<Modifier> modi,my_implements *&QID,char *name,int x,int line)
{
	if ((sure)&&(sure_))
	{
		if ((x<250)&&(x>0))
		{
			if (!my_modifiers::found(modi,Readonly))
			{
				VariablesClass_Action(modi,QID,name,line);
				currVariable->val = new ArraySize(x);
			}
			else
				My_ref->addRefuse("cannot declare an array with a 'readonly' modifier",name,variable,line,sure__);
		}
		else
			My_ref->addRefuse(name," : length should be between 0,250",name,variable,line,sure__);
	}
}

void Actions::DynArraysClass_Action(list<Modifier> modi,my_implements *&QID,char *name,int line)
{
	if ((sure)&&(sure_))
	{
		if (!my_modifiers::found(modi,Readonly))
		{
			VariablesClass_Action(modi,QID,name,line);
			currVariable->val = new ArraySize(0);
		}
		else
			My_ref->addRefuse("cannot declare a dynamic array with a 'readonly' modifier",name,variable,line,sure__);
	}
}

//------------------------------------MethodsClass_Action---------------------------
void Actions::MethodsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line)
{
	if ((sure)&&(sure_))
	{
		if (strcmp(name,currClass->name)!=0)
			FunctionsClass_Action(modi,parameter,QID,name,line);
		else
			ConstructorsClass_Action(modi,parameter,QID,name,line);
		this->FirstDad=false;
	}
}

void Actions::FunctionsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line)
{
 	currVariable='\0'; sure__ = true;
	currMethod=new Method(name,parameter,modi,QID,false);
	currMethod->label.append(currClass->label); currMethod->label.append("_"); currMethod->label.append(name); currMethod->buildParaLabel();
	if (!SymbolTable::validName(name))
		My_ref->addRefuse("un-valid name : ",name,name,method,line,sure__);
	else if (my_check->Check_MethodModifier(modi))
	{
		if ((!currClass->search_Class((Symbol *)currMethod))||(later))
		{
			if ((my_check->check_param((Symbol *)currMethod,currNamespace,parameter))&&(my_check->Check_ReturnQID(currNamespace,currClass,QID)))
			{					
				if ((my_modifiers::found(modi,Static))&&(strcmp(*QID->implement.begin(),"SELF_TYPE")==0)&&(QID->implement.size()==1))
						My_ref->addRefuse("can not make an static SELF_TYPE object : ",((Class *)QID->place)->name,name,variable,line,sure__);
				else if (my_check->check_Override_Method(currMethod,currClass,currNamespace))
				{
					if (!later)
					{
						isEntryMethod();
						currClass->addLocal(currMethod);
						if ((my_modifiers::found(currMethod->modi,Override))||(my_modifiers::found(currMethod->modi,Virtual)))
						{
							currMethod->virtualList1.push_back(currClass->label);
							currMethod->virtualList2.push_back(currMethod->label);
							currClass->Over_List.push_back(currMethod);
						}
					}
				}
				else
					My_ref->addRefuse("FEATURE '",currMethod->name,"' Can't Be Overriden",name,method,line,sure__);
			}
			else if (!later)
			{
				currClass->addLocal((Symbol *)currMethod);
				my_laterDef->pointAtSymbol(currMethod,true,currNamespace,line);
				if ((my_modifiers::found(currMethod->modi,Override))||(my_modifiers::found(currMethod->modi,Virtual)))
					currClass->Over_List.push_back(currMethod);
			}
			else
				My_ref->addRefuse("RETURN TYPE UNDEFINED Or SOME PARAMETERS UNDEFINED OR REPEATED",name,method,line,sure__);
		}
		else
			My_ref->addRefuse("FEATURE '",currMethod->name,"' REDEFINATION",name,method,line,sure__);
	}
	else
	{
		Refuse_Add*  R=new Refuse_Add();
		R->line=line;
		R->msg="";
		R->msg.append("illegal combination of modifiers:");
		list<Modifier>::iterator i=modi.begin();
		while (i!=modi.end())
		{
			Modifier g=(Modifier) *i;
			switch (g) {
			case (0):  R->msg.append("public"); break;
			case (1):  R->msg.append("private"); break;
			case (2):  R->msg.append("protected"); break;
			case (3):  R->msg.append("internal"); break;
			case (4):  R->msg.append("static"); break;
			case (5):  R->msg.append("readonly"); break;
			case (6):  R->msg.append("virtual"); break;
			case (7):  R->msg.append("sealed"); break;
			case (8):  R->msg.append("override"); break;
			case (9):  R->msg.append("abstract"); break;
			}
			R->msg.append(" ");
			i++;
		}
		R->name= name; R->type=method;
		My_ref->insert_Ref(R);
	}
}

void Actions::ConstructorsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line)
{
	currVariable='\0'; sure__ = true;
	currMethod=new Method(name,parameter,modi,QID,true);
	currMethod->label.append(currClass->label); currMethod->label.append("_"); currMethod->label.append(name); currMethod->buildParaLabel();
	currClass->haveConstructor=true;//for build default constructor
    if (my_check->Check_ConstructorModifier(modi))
	{
		list<char*> t; t.push_back("SELF_TYPE");
		if ( (my_check->check_param((Symbol *)currMethod,currNamespace,parameter))&&(commonUse::equal_char(QID->implement,t))) 
		{
			if(!currClass->search_Class((Symbol *) currMethod))
					currClass->addLocal((Symbol *)currMethod);
			else if (!later)
				My_ref->addRefuse("FEATURE '",currMethod->name,"' REDEFINATION",name,method,line,sure__);
		}
		else if ((!later)&&(commonUse::equal_char(QID->implement,t)))
		{
			currClass->addLocal((Symbol *)currMethod);
			my_laterDef->pointAtSymbol(currMethod,true,currNamespace,line);
		}
		else
			My_ref->addRefuse("RETURN TYPE SHOULD BE 'SELF_TYPE' OR SOME PARAMETERS UNDEFINED OR REPEATED",name,method,line,sure__);
	}
	else
	{
		Refuse_Add*  R=new Refuse_Add();
		R->line=line;
		R->msg="";
		R->msg.append("illegal combination of modifiers:");
		list<Modifier>::iterator i=modi.begin();
		while (i!=modi.end())
		{
			Modifier g=(Modifier) *i;
			switch (g) {
			case (0):  R->msg.append("public"); break;
			case (1):  R->msg.append("private"); break;
			case (2):  R->msg.append("protected"); break;
			case (3):  R->msg.append("internal"); break;
			case (4):  R->msg.append("static"); break;
			case (5):  R->msg.append("readonly"); break;
			case (6):  R->msg.append("virtual"); break;
			case (7):  R->msg.append("sealed"); break;
			case (8):  R->msg.append("override"); break;
			case (9):  R->msg.append("abstract"); break;
			}
			R->msg.append(" ");
			i++;
		}
		R->name= name; R->type=method;
		My_ref->insert_Ref(R);
	}
}

void Actions::AbsMethodsClass_Action(list<Modifier> modi,list <Variable*> parameter,my_implements *&QID,char *name,int line)
{
	if ((sure)&&(sure_))
	{
		if (!my_modifiers::found(currClass->modi,Abstract))
			My_ref->addRefuse("class must declared as abstract to have abstract method",currClass->name,clas,line,sure__);
		if (strcmp(name,currClass->name)!=0)
		{
			if (my_modifiers::found(modi,Abstract))
				FunctionsClass_Action(modi,parameter,QID,name,line);
			else
				My_ref->addRefuse(name," : must declared as abstract",name,method,line,sure__);
		}	
		else
			My_ref->addRefuse("constructor can't be abstract",name,method,line,sure__);
	}
}

list <Method*> Actions::Get_Cons_Father(Class* Inh)
{
	list <Method*> out; out.clear();
	list<Method*>::iterator i=Inh->localFuncs.begin();
	while (i!=Inh->localFuncs.end())
	{
		Method * M=(Method*) *i;
		if (M->constructor)
			out.push_back(M);
		i++;
	}

	return out;
}

void Actions::EndFunction(Class *currClass,AST* exprN,int line)
{
	if ((sure_)&&(sure)&&(sure__))
	{
		if (my_modifiers::found(currMethod->modi,Abstract))
			My_ref->addRefuse("Abstract methods can't have body",currMethod->name,method,line,*new bool);
		if (strcmp(*currMethod->returnType->implement.begin(),"Void")==0)
			currMethod->absTree = exprN;
		else if (currMethod->constructor)
		{
			if ((!currClass->inherit_class->implement.empty())&&(strcmp("Object",*(--currClass->inherit_class->implement.end()))!=0)&&(currClass->inherit_class->place!=NULL))
			{
				list<Method*> Con; Con.clear();
				Con=Get_Cons_Father((Class*)currClass->inherit_class->place);
				list<Method*>::iterator i=Con.begin(); bool Sig=true;
				while ((Sig) && (i!=Con.end()))
				{
					Method* M=(Method*) *i;
					if (M->parameters.empty())
						Sig=false;
					i++;
				}
				if ((!currMethod->DadCall)&&(Sig))
					My_ref->addRefuse(currMethod->name," : Cannot find Symbol : Required Constructer",currClass->inherit_class->place->name,method,line,*new bool);
                else
					currMethod->absTree = exprN;
			}
			else if (strcmp(*(--currClass->inherit_class->implement.end()),"Object")==0)
			{
				if (!later)
					currMethod->absTree = exprN;
			}
			else
			{
				if ((strcmp(*(--currClass->inherit_class->implement.end()),"Object")!=0)&&(!later))
				{
					currMethod->absTree = exprN;
					my_laterDef->pointAtSymbol(currMethod,true,currNamespace,line);
				}
				if (later)
				{
					my_implements *QID = new my_implements();
					QID->implement.push_back(*(--currClass->inherit_class->implement.end()));
					my_check->Check_QID(currNamespace,currClass,QID);
					if (QID->place!=NULL)
					{
						list<Method*> Con; Con.clear();
						Con=Get_Cons_Father((Class*)QID->place);
						list<Method*>::iterator i=Con.begin(); bool Sig=true;
						while ((Sig) && (i!=Con.end()))
						{
							Method* M=(Method*) *i;
							if (M->parameters.empty())
								Sig=false;
							i++;
						}
						if ((!currMethod->DadCall) && (Sig) )
							My_ref->addRefuse(currMethod->name," : Cannot find Symbol : Required Constructer",QID->place->name,method,line,*new bool);
						else
							currMethod->absTree = exprN;
					}
				}
			}
		}
		else if (currMethod->haveReturn)
		{
			if (!MethodSearch::checkReturn(exprN))
				My_wrn->addWarn(currMethod->name," Not all control pathes return a value","method return",line);
			currMethod->absTree = exprN;
		}
		else
			My_ref->addRefuse("missing return statement",currMethod->name,method,line,*new bool);
	}
	sure__=true;
}

//---------------------------------------------------------Expr---------------------------------------------------------
Node* Actions::checkAssignment(Variable * var,Node* obj,Node*&ass_exp,int line)
{
	Node * expr = new Node();
	my_implements * t = new my_implements(); my_implements * t2 = new my_implements();
	if (laterTree)
	{
		expr = new Assignment_Node(obj,ass_exp);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if (ass_exp->returnValType(t)!=0)
	{
		if (my_check->same_type(var->varType->implement,t->implement))
			expr = new Assignment_Node(obj,ass_exp);
		else if ((t->place == var->varType->place)&&(strcmp(*(--t->implement.end()),*(--var->varType->implement.end()))==0))
			expr = new Assignment_Node(obj,ass_exp);
		else if ((strcmp(*var->varType->implement.begin(),"Float")==0)&&(ass_exp->returnValType(t)==1))
		{
			My_wrn->addWarn("assignment expression has been upcasted to float","UPCAST",line);
			if (ass_exp->grp==CONST)
			{
				Const_Type CT; CT.type=2; CT.fv=((Const_Node*)ass_exp)->type.iv;
				ass_exp=new Const_Node(CT);
				expr = new Assignment_Node(obj,ass_exp);
			}
			else
			{
				my_implements* t = new my_implements("Float");
				ass_exp = new Upcast_Node(t,ass_exp);
				expr = new Assignment_Node(obj,ass_exp);
			}
		}
		else if ((strcmp(*var->varType->implement.begin(),"Int")==0)&&(ass_exp->returnValType(t)==2))
		{
			My_wrn->addWarn("assignment expression has been cut to integer","DOWNCAST",line);
			if (ass_exp->grp==CONST)
			{
				Const_Type CT; CT.type=1; CT.iv=((Const_Node*)ass_exp)->type.fv;
				ass_exp=new Const_Node(CT);
				expr = new Assignment_Node(obj,ass_exp);
			}
			else
			{
				my_implements* t = new my_implements("Int");
				ass_exp = new Downcast_Node(t,ass_exp);
				expr = new Assignment_Node(obj,ass_exp);
			}
		}
		else if ((obj->returnValType(t)==5)&&(ass_exp->returnValType(t2) == 5))
		{
			//Polymorphism
			my_implements * imp1 = new my_implements(); my_implements * imp2 = new my_implements();
			*imp1 = *var->varType; ass_exp->returnValType(imp2);
			if ((imp2->place == NULL)||(((Class *)imp2->place)->Later)||(imp1->place == NULL))
			{
				if (!later)
				{
					expr = new Assignment_Node(obj,ass_exp);
					my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
				}
				else
					My_ref->addRefuse("Incompatible Types",var->name,variable,line,*new bool);
			}
			else if ((imp1->place->type == clas)&&(Downcast_Node::checkCastType((Class*)imp1->place,(Class*)imp2->place)))
				expr = new Assignment_Node(obj,ass_exp);
			else if ((imp1->place->type == inter_face)&&(Downcast_Node::checkCastType((Interface*)imp1->place,(Class*)imp2->place)))
				expr = new Assignment_Node(obj,ass_exp);
			else
				My_ref->addRefuse("Incompatible Types",var->name,variable,line,*new bool);
		}
		else
			My_ref->addRefuse("Incompatible Types",var->name,variable,line,*new bool);
	}
	else if ((obj->returnValType(t2)==5)&&(strcmp(*t->implement.begin(),"void")==0))
		expr = new Assignment_Node(obj,ass_exp);
	else
		My_ref->addRefuse("Illegal initializer for : ",var->name,var->name,variable,line,*new bool);
	return expr;
}

Node* Actions::VariableDeclaration(my_implements *&QID,char *name,int line,Node *ass_exp)
{
	Node * expr = new Node();
	currVariable=new Variable(name,QID); currVariable->val = new Node();
	if (currScope!=NULL)
	{
		if ((!currScope->searchScope(currVariable))||(later))
		{
			if (my_check->Check_QID(currNamespace,currClass,QID))  // object of class
			{
				if (!my_modifiers::found(((Class *)QID->place)->modi,Abstract))
				{
					if (!later)
					{
						currScope->addLocal(currVariable);
						expr = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
						if (currMethod->searchMethod(currVariable))
							My_wrn->addWarn(name," : covers a variable in the current function",name,line);
						if (currClass->search_Class(currVariable))
							My_wrn->addWarn(name," : covers a class member",name,line);
					}
				}
				else
					My_ref->addRefuse("can not make an object of Abstract class : ",((Class *)QID->place)->name,name,variable,line,*new bool);
			}
			else if (my_check->Check_QID_two(currNamespace,currClass,QID))  // object of interface
			{
				if (!later)
				{
					currScope->addLocal(currVariable);
					expr = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
					if (currMethod->searchMethod(currVariable))
						My_wrn->addWarn(name," : covers a variable in the current function",name,line);
					if (currClass->search_Class(currVariable))
						My_wrn->addWarn(name," : covers a class member",name,line);
				}
			}
			else if (!later)
			{
				currScope->addLocal(currVariable);
				expr = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
				my_laterDef->pointAtSymbol(currVariable,false,currNamespace,line);
			}
			else
				My_ref->addRefuse("TYPE UNDEFINED",name,variable,line,*new bool);
		}
		else
			My_ref->addRefuse("VARIABLE '",currVariable->name,"' REDEFINATION",name,variable,line,*new bool);
	}
	else if ((!currMethod->searchMethod(currVariable))||(later))
	{
		if (my_check->Check_QID(currNamespace,currClass,QID))
		{
			if (!my_modifiers::found(((Class *)QID->place)->modi,Abstract))
			{
				if (!later)
				{
					currMethod->addLocal(currVariable);
					expr = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
					if (currClass->search_Class(currVariable))
						My_wrn->addWarn(name," : covers a class member",name,line);
				}
			}
			else
				My_ref->addRefuse("can not make an object of Abstract class : ",((Class *)QID->place)->name,name,variable,line,*new bool);
		}
		else if (my_check->Check_QID_two(currNamespace,currClass,QID))  // object of interface
		{
			if (!later)
			{
				currMethod->addLocal(currVariable);
				expr = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
				if (currClass->search_Class(currVariable))
					My_wrn->addWarn(name," : covers a class member",name,line);
			}
		}
		else if (!later)
		{
			currMethod->addLocal(currVariable);
			expr=checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
			my_laterDef->pointAtSymbol(currVariable,false,currNamespace,line);
		}
		else
			My_ref->addRefuse("TYPE UNDEFINED",name,variable,line,*new bool);
	}
	else
		My_ref->addRefuse("VARIABLE '",currVariable->name,"' REDEFINATION",name,variable,line,*new bool);
	return expr;
}

Node* Actions::ArrayDeclaration(my_implements *QID,char *name,int x,int line,Node * ass_exp)
{
	Node * expr = new Node();
	if ((x<250)&&(x>0))
	{
		VariableDeclaration(QID,name,line,ass_exp);
		currVariable->val = new ArraySize(x);
	}
	else
		My_ref->addRefuse(name," : length should be between 0,250",name,variable,line,*new bool);
	return expr;
}

Node* Actions::DynArrayDeclaration(my_implements *QID,char *name,int line,Node * ass_exp)
{
	Node * expr = new Node();
	VariableDeclaration(QID,name,line,ass_exp);
	currVariable->val = new ArraySize(0);
	return expr;
}

Node* Actions::CallLocalVar(char * name,int line,bool define,bool self)
{
	Node * expr = new Node();
	Variable* locate='\0';
	if ((self)&&(ID_Node::locateVar(NULL,currClass,NULL,name,locate,currClass->name)))
	{
		if (my_modifiers::found(locate->modi,Readonly))
		{
			expr = locate->val;
			My_wrn->addWarn("constant replaced with its value","CONSTANT",line);
		}
		else
			expr=new ID_Node(locate);
	}
	else if ((!self)&&(ID_Node::locateVar(currScope,currClass,currMethod,name,locate,currClass->name))&&((locate->type == field)||(!later)))
	{
		if ((my_modifiers::found(currMethod->modi,Static))&&(!my_modifiers::found(locate->modi,Static))&&(locate->type == field))
			My_ref->addRefuse("non-static variable : ",name," cannot be called by a static method",name,variable,line,*new bool);
		else if (my_modifiers::found(locate->modi,Readonly))
		{
			expr = locate->val;
			My_wrn->addWarn("constant replaced with its value","CONSTANT",line);
		}
		else
			expr=new ID_Node(locate);
	}
	else if ((!self)&&(later)&&(define)&&(ID_Node::locateVar(currScope,currClass,currMethod,name,locate,currClass->name)))
		expr=new ID_Node(locate);
	else
		expr = new Static_Node(name);
	return expr;
}

Node* Actions::CallVariable(my_implements * imp,bool define,int line)
{
	Node * expr = new Node();
	list<char*> QID = imp->implement; char * name; bool ok = false;
	commonUse::divBegList(QID,name);
	if (strcmp(name ,"self")==0)
	{
		if (my_modifiers::found(currMethod->modi,Static))
		{
			My_ref->addRefuse("non-static variable : ",name," cannot be called by a static method",name,variable,line,*new bool);
			QID.clear();
		}
		else if (QID.empty())
		{
			imp->place = currClass;
			expr = new ID_Node(new Variable("self",imp,0));
		}
		else
		{
			commonUse::divBegList(QID,name);
			expr = CallLocalVar(name,line,true,false);
		}
	}
	else
	{
		expr = CallLocalVar(name,line,define,false);
		if (expr->grp == IDENTIFIER)
			ok = true;
	}
	if (expr->grp == IDENTIFIER)
		if ((((ID_Node*)expr)->var->varType->place == NULL)&&(!later))
		{
			expr = new Static_Node(imp); laterTree = true; ((Static_Node *)expr)->define = ok;
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
			return expr;
		}
	Node * expr1 = new Node();
	while (!QID.empty())
	{
		if (expr->grp==EMPTY)
		{
			My_ref->removeLastRefuse();
			if (expr1->grp==STATIC_CALL)
				((Static_Node *)expr1)->staticImp->add_implement(name);
			else 
				expr1 = new Static_Node(name);
			expr=expr1;
		}
		commonUse::divBegList(QID,name);
		expr1 = expr;
		expr = CallClassVar(expr1,name,line);
	}
	if (expr->grp==STATIC_CALL)
	{
		if (!later)
		{
			expr = new Static_Node(imp); laterTree = true;
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else
			My_ref->addRefuse(name," : variable not found or can't be reached",name,variable,line,*new bool);
	}
	return expr;
}

Node* Actions::CallClassVar(Node *exp_in,char *name,int line)
{
	my_implements * QID = new my_implements();
	Node * expr = new Node();
	Variable * locate='\0';
	if ((laterTree)&&(exp_in->grp == FUNCTION_CALL)||(exp_in->grp == OBJ_FUNC_CALL))
	{
		locate = new Variable(name);
		expr=new ObjectID_Node(locate,exp_in); laterTree = true;
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if ((exp_in->returnValType(QID)==5)||(exp_in->returnValType(QID)==6))
	{
		if ((my_check->Check_QID(currNamespace,currClass,QID))&&(exp_in->grp!=STATIC_CALL))
		{
			char* Type_Caller=(char*)*(--QID->implement.end());
			if ((ID_Node::locateVar(NULL,(Class*)QID->place,NULL,name,locate,Type_Caller)))
			{
				if (!my_modifiers::found(locate->modi,Static))
				{
					if (currClass==(Class*)QID->place)
						expr=new ObjectID_Node(locate,exp_in);
					else if ((Downcast_Node::checkCastType((Class*)QID->place,currClass))&&((my_modifiers::found(locate->modi,Public))||(my_modifiers::found(locate->modi,Protected))))
						expr=new ObjectID_Node(locate,exp_in);
					else if (my_modifiers::found(locate->modi,Public))
						expr=new ObjectID_Node(locate,exp_in);
					else
						My_ref->addRefuse(name,": is a member of ",QID->place->name," but can not be reached",name,variable,line,*new bool);
				}
				else
				{
					if (currClass==(Class*)QID->place)
						expr=new ID_Node(locate);
					else if ((Downcast_Node::checkCastType((Class*)QID->place,currClass))&&((my_modifiers::found(locate->modi,Public))||(my_modifiers::found(locate->modi,Protected))))
						expr=new ID_Node(locate);
					else if (my_modifiers::found(locate->modi,Public))
						expr=new ID_Node(locate);
					else
						My_ref->addRefuse(name,": is a member of ",QID->place->name," but can not be reached",name,variable,line,*new bool);
				}
			}
			else
				My_ref->addRefuse(name,": isn't a member of ",QID->place->name,name,variable,line,*new bool);
		}
		else if ((my_check->Check_QID(currNamespace,currClass,QID))&&(exp_in->grp==STATIC_CALL))
		{
			Variable * locate='\0';
			char* Type_Caller=(char*)*(--QID->implement.end());
			if ((ID_Node::locateVar(NULL,(Class*)QID->place,NULL,name,locate,Type_Caller)))
			{
				if (my_modifiers::found(locate->modi,Static))
				{
					if (currClass==(Class*)QID->place)
						expr=new ID_Node(locate);
					else if ((Downcast_Node::checkCastType((Class*)QID->place,currClass))&&((my_modifiers::found(locate->modi,Public))||(my_modifiers::found(locate->modi,Protected))))
						expr=new ID_Node(locate);
					else if (my_modifiers::found(locate->modi,Public))
						expr=new ID_Node(locate);
					else
						My_ref->addRefuse(name,": is a member of ",QID->place->name," but can not be reached",name,variable,line,*new bool);
				}
				else
					My_ref->addRefuse(name,": is a member of ",QID->place->name," but not static",name,variable,line,*new bool);
			}
			else
				My_ref->addRefuse(name,": isn't a member of ",QID->place->name,name,variable,line,*new bool);
		}
		else if (exp_in->grp==STATIC_CALL)
		{
			((Static_Node *)exp_in)->staticImp->add_implement(name);
			expr = exp_in;
		}
		else if ((laterTree)&&(exp_in->grp != OBJ_ID)&&(exp_in->grp != IDENTIFIER))
		{
			locate = new Variable(name);
			expr=new ObjectID_Node(locate,exp_in); laterTree = true;
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else
			My_ref->addRefuse("undefined type : ",*(--QID->implement.end()),name,variable,line,*new bool);
	}
	else
		My_ref->addRefuse("class expected before '.'",name,variable,line,*new bool);
	return expr;
}

Node* Actions::CallArrVar(my_implements * imp,Node * x, int line)
{
	Node * expr = new Node();
	expr = CallVariable(imp,false,line);
	char * name = *(--imp->implement.end());
	if (laterTree)
	{
		if (expr->grp == STATIC_CALL)
		{
			expr = new StaticArray_Node(((Static_Node *)expr)->staticImp,x);
			my_laterDef->MemberExpectLater.pop_back();
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else if (expr->grp == OBJ_ID)
		{
			expr = new ObjectArray_Node(((ObjectID_Node *)expr)->var,((ObjectID_Node *)expr)->object,x);
			my_laterDef->MemberExpectLater.pop_back();
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
	}
	else if (expr->grp == IDENTIFIER)
	{
		if (((ID_Node *)expr)->var->val!=NULL)
		{
			if (((ID_Node *)expr)->var->val->grp==ARRAY_SIZE)
			{
				if ((((ArraySize *)((ID_Node *)expr)->var->val)->x == 0)||(ArraySize::checkArraySize(((ArraySize *)((ID_Node *)expr)->var->val)->x,x)))
					expr = new Array_Node(((ID_Node *)expr)->var,x);
				else
					My_ref->addRefuse("called array variable out of range",name,variable,line,*new bool);
			}
			else
				My_ref->addRefuse("normal variable called as array",name,variable,line,*new bool);
		}
		else
			My_ref->addRefuse("normal variable called as array",name,variable,line,*new bool);
	}
	else if (expr->grp == OBJ_ID)
	{
		if (((ObjectID_Node *)expr)->var->val!=NULL)
		{
			if (((ObjectID_Node *)expr)->var->val->grp==ARRAY_SIZE)
			{
				if ((((ArraySize *)((ObjectID_Node *)expr)->var->val)->x == 0)||(ArraySize::checkArraySize(((ArraySize *)((ObjectID_Node *)expr)->var->val)->x,x)))
					expr = new ObjectArray_Node(((ObjectID_Node *)expr)->var,((ObjectID_Node *)expr)->object,x);
				else
					My_ref->addRefuse("called array variable out of range",name,variable,line,*new bool);
			}
			else
				My_ref->addRefuse("normal variable called as array",name,variable,line,*new bool);
		}
		else
			My_ref->addRefuse("normal variable called as array",name,variable,line,*new bool);
	}
	return expr;
}

Node* Actions::AssignVariable(my_implements * imp,Node* ass_exp,int line)
{
	Node * expr = new Node();
	expr = CallVariable(imp,false,line);
	if (laterTree)
	{
		expr = new Assignment_Node(expr,ass_exp);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if (expr->grp==IDENTIFIER)
		expr = checkAssignment(((ID_Node *)expr)->var,expr,ass_exp,line);
	else if (expr->grp==OBJ_ID)
		expr = checkAssignment(((ObjectID_Node *)expr)->var,expr,ass_exp,line);
	else if (expr->grp==CONST)
		My_ref->addRefuse("can not assign value to constant variable : ",*(--imp->implement.end()),*(--imp->implement.end()),variable,line,*new bool);
	return expr;
}

Node* Actions::AssignClassVar(Node* exp_in,char *name,Node* ass_exp,int line)
{
	Node * expr = new Node();
	expr = CallClassVar(exp_in,name,line);
	if (laterTree)
	{
		expr = new Assignment_Node(expr,ass_exp);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if (expr->grp==IDENTIFIER)
		expr = checkAssignment(((ID_Node *)expr)->var,expr,ass_exp,line);
	else if (expr->grp==OBJ_ID)
		expr = checkAssignment(((ObjectID_Node *)expr)->var,expr,ass_exp,line);
	else if (expr->grp==CONST)
		My_ref->addRefuse("can not assign value to constant variable : ",name,name,variable,line,*new bool);
	return expr;
}

Node* Actions::AssignArrVar(my_implements * imp,Node* x,Node* ass_exp,int line)
{
	Node * expr = new Node();
	expr = CallArrVar(imp,x,line);
	if (laterTree)
	{
		expr = new Assignment_Node(expr,ass_exp);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if (expr->grp==ARRAY)
		expr = checkAssignment(((Array_Node *)expr)->var,expr,ass_exp,line);
	else if (expr->grp==OBJ_ARRAY)
		expr = checkAssignment(((ObjectArray_Node *)expr)->var,expr,ass_exp,line);
	else if (expr->grp==CONST)
		My_ref->addRefuse("can not assign value to constant variable : ",*(--imp->implement.end()),*(--imp->implement.end()),variable,line,*new bool);
	return expr;
}

Node* Actions::InitDynArray(my_implements * imp,my_implements * QID,Node* size,int line)
{
	Node * expr = new Node();
	expr = CallArrVar(imp,size,line);
	my_implements * t = new my_implements(); expr->returnValType(t);
/*	if (laterTree)
	{
		expr = new DynamicArrayInit_Node(expr,size);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else */if (expr->grp==ARRAY)
	{
		if (((ArraySize *)((Array_Node *)expr)->var->val)->x == 0)
		{
			if ((my_check->Check_QID(currNamespace,currClass,QID))&&(QID->place == t->place))
				expr = new DynamicArrayInit_Node(expr,size);
			else
				My_ref->addRefuse("illegal initializer for : ",*(--imp->implement.end()),*(--imp->implement.end()),variable,line,*new bool);
		}
		else
			My_ref->addRefuse("static Array Initialize as Dynamic : ",*(--imp->implement.end()),*(--imp->implement.end()),variable,line,*new bool);
	}
	else if (expr->grp==OBJ_ARRAY)
	{
		if (((ObjectArray_Node *)((Array_Node *)expr)->var->val)->x == 0)
		{
			if ((my_check->Check_QID(currNamespace,currClass,QID))&&(QID->place == t->place))
				expr = new DynamicArrayInit_Node(expr,size);
			else
				My_ref->addRefuse("illegal initializer for : ",*(--imp->implement.end()),*(--imp->implement.end()),variable,line,*new bool);
		}
		else
			My_ref->addRefuse("static Array Initialize as Dynamic : ",*(--imp->implement.end()),*(--imp->implement.end()),variable,line,*new bool);
	}
	return expr;
}

Node* Actions::CallFunction(my_implements * imp,AST *call_expr,int line)
{
	Node * expr = new Node();
	list<char*> QID = imp->implement; char * name;
	if (imp->implement.size()==1)
		expr = CallLocalFunc(*imp->implement.begin(),call_expr,line);
	else if ((imp->implement.size()==2)&&(strcmp(*imp->implement.begin(),"self")==0))
		expr = CallLocalFunc(*(++(imp->implement.begin())),call_expr,line);
	else
	{
		commonUse::divBegList(QID,name);
		if (strcmp(name,"self")==0)
		{
			commonUse::divBegList(QID,name);
			expr = CallLocalVar(name,line,true,false);
		}
		else
			expr = CallLocalVar(name,line,false,false);
		Node * expr1 = new Node();
		while (!QID.empty())
		{
			if (expr->grp==EMPTY)
			{
				My_ref->removeLastRefuse();
				if (expr1->grp==STATIC_CALL)
					((Static_Node *)expr1)->staticImp->add_implement(name);
				else 
					expr1 = new Static_Node(name);
				expr=expr1;
			}
			commonUse::divBegList(QID,name);
			expr1 = expr;
			if (QID.empty())
				expr = CallClassFunc(expr,name,call_expr,imp,line);
			else
				expr = CallClassVar(expr,name,line);
		}
	}
	return expr;
}

Node* Actions::CallLocalFunc(char *name,AST *call_expr,int line)
{
	Node * expr = new Node();
	Method* locate='\0';
	if (laterTree)
	{
		list<Variable*> p; list<Modifier> m;
		locate = new Method(name,p,m,new my_implements(),false);
		expr = new FunctionCall_Node(locate,call_expr); laterTree = true;
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if((MethodSearch::locateFunc(currClass,name,call_expr,locate,new char,later))&&(locate!='\0')&&((locate->returnType->place != NULL)||(strcmp(*(--locate->returnType->implement.end()),"Void")==0)))
	{
		if (locate->constructor)
			My_ref->addRefuse(name," : can't call a constructor this way",name,method,line,*new bool);
		else if (my_modifiers::found(locate->modi,Abstract))
			My_ref->addRefuse(name," : can't call abstract method",name,method,line,*new bool);
		else
			expr=new FunctionCall_Node(locate,call_expr);
	}
	else if (!later)
	{
		list<Variable*> p; list<Modifier> m;
		locate = new Method(name,p,m,new my_implements(),false);
		expr = new FunctionCall_Node(locate,call_expr); laterTree = true;
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if((!MethodSearch::locateFunc(currClass,name,call_expr,locate,new char,later))&&(locate!='\0'))
		My_ref->addRefuse(name," : method found but no overloaded match function found",name,method,line,*new bool);
	else
		My_ref->addRefuse(name," : undeclared method or Can't access member declare in class",name,method,line,*new bool);
	return expr;
}

Node* Actions::CallClassFunc(Node *exp_in,char *name,AST *call_exp,my_implements * imp,int line)
{
	Node * expr = new Node(); 
	Method * locate='\0'; my_implements * QID=new my_implements();
	if (laterTree)
	{
		list<Variable*> p; list<Modifier> m; 
		locate = new Method(name,p,m,new my_implements(),false);
		expr = new ObjectFuncCall_Node(exp_in,locate,call_exp); laterTree = true;
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if ((exp_in->returnValType(QID)==5)||(exp_in->returnValType(QID)==6))
	{
		char * Caller=(char*)*(--QID->implement.end()); char* ParentName=new char;
		if ((my_check->Check_QID(currNamespace,currClass,QID))&&(exp_in->grp!=STATIC_CALL))
		{
			if ((MethodSearch::locateFunc((Class*)QID->place,name,call_exp,locate,Caller,later))&&(locate!='\0')&&((locate->returnType->place != NULL)||(strcmp(*(--locate->returnType->implement.end()),"Void")==0)))
			{
				if (locate->constructor)
					My_ref->addRefuse(name," : can't call a constructor this way",name,method,line,*new bool);
				else if (my_modifiers::found(locate->modi,Abstract))
					My_ref->addRefuse(name," : can't call abstract method",name,method,line,*new bool);
				else if (currClass==(Class*)QID->place)
					expr = new ObjectFuncCall_Node(exp_in,locate,call_exp);
				else if ((Downcast_Node::checkCastType((Class*)QID->place,currClass))&&((my_modifiers::found(locate->modi,Public))||(my_modifiers::found(locate->modi,Protected))))
					expr = new ObjectFuncCall_Node(exp_in,locate,call_exp);
				else if ((my_modifiers::found(locate->modi,Public)))
					expr = new ObjectFuncCall_Node(exp_in,locate,call_exp);
				else
					My_ref->addRefuse(name," : is member of ",QID->place->name," but cant be reached",name,method,line,*new bool);
			}
			else if (!later)
			{
				list<Variable*> p; list<Modifier> m;
				locate = new Method(name,p,m,new my_implements(),false);
				expr = new ObjectFuncCall_Node(exp_in,locate,call_exp); laterTree = true;
				my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
			}
			else if((!MethodSearch::locateFunc((Class*)QID->place,name,call_exp,locate,Caller,later))&&(locate!='\0'))
				My_ref->addRefuse(name," : method found but no overloaded match function found",name,method,line,*new bool);
			else
				My_ref->addRefuse(name," : isn't member of or Can't access member declare in class ",QID->place->name,name,method,line,*new bool);
		}
		else if ((my_check->Check_QID_two(currNamespace,currClass,QID))&&(exp_in->grp!=STATIC_CALL))
		{
			if ((MethodSearch::locateFunc((Interface*)QID->place,name,call_exp,locate,Caller,later))&&(locate!='\0')&&((locate->returnType->place != NULL)||(strcmp(*(--locate->returnType->implement.end()),"Void")==0)))
				expr = new ObjectFuncCall_Node(exp_in,locate,call_exp);
			else if (!later)
			{
				list<Variable*> p; list<Modifier> m;
				locate = new Method(name,p,m,new my_implements(),false);
				expr = new ObjectFuncCall_Node(exp_in,locate,call_exp); laterTree = true;
				my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
			}
			else if((!MethodSearch::locateFunc((Interface*)QID->place,name,call_exp,locate,Caller,later))&&(locate!='\0'))
				My_ref->addRefuse(name," : method found but no overloaded match function found",name,method,line,*new bool);
			else
				My_ref->addRefuse(name," : isn't member of interface ",QID->place->name,name,method,line,*new bool);
		}
		else if ((my_check->Check_QID(currNamespace,currClass,QID))&&(exp_in->grp==STATIC_CALL))
		{
			if ((MethodSearch::locateFunc((Class*)QID->place,name,call_exp,locate,Caller,later))&&(locate!='\0')&&((locate->returnType->place != NULL)||(strcmp(*(--locate->returnType->implement.end()),"Void")==0)))
			{
				if (my_modifiers::found(locate->modi,Static))
				{
					if (locate->constructor)
						My_ref->addRefuse(name," : can't call a constructor this way",name,method,line,*new bool);
					else if (currClass==(Class*)QID->place)
						expr = new FunctionCall_Node(locate,call_exp);
					else if ((Downcast_Node::checkCastType((Class*)QID->place,currClass))&&((my_modifiers::found(locate->modi,Public))||(my_modifiers::found(locate->modi,Protected))))
						expr = new FunctionCall_Node(locate,call_exp);
					else if ((my_modifiers::found(locate->modi,Public)))
						expr = new FunctionCall_Node(locate,call_exp);
					else
						My_ref->addRefuse(name," : is member of ",QID->place->name," but cant be reached",name,method,line,*new bool);
				}
				else
					My_ref->addRefuse(name," : is a member of ",QID->place->name," but not static",name,variable,line,*new bool);
			}
			else if (!later)
			{
				list<Variable*> p; list<Modifier> m; 
				locate = new Method(name,p,m,new my_implements(),false);
				expr = new ObjectFuncCall_Node(exp_in,locate,call_exp); laterTree = true;
				my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
			}
			else if((!MethodSearch::locateFunc((Class*)QID->place,name,call_exp,locate,Caller,later))&&(locate!='\0'))
				My_ref->addRefuse(name," : method found but no overloaded match function found",name,method,line,*new bool);
			else
				My_ref->addRefuse(name," : isn't member of or Can't access member declare in class",QID->place->name,name,method,line,*new bool);
		}
		else if (!later)
		{
			list<Variable*> p; list<Modifier> m; 
			locate = new Method(name,p,m,new my_implements(),false);
			expr = new ObjectFuncCall_Node(exp_in,locate,call_exp); laterTree = true;
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else
			My_ref->addRefuse("class expected before . : ",*(--QID->implement.end()),name,method,line,*new bool);
	}
	else if (exp_in->returnValType(QID)==3)
	{
		if (MethodSearch::locateFunc((Class*)QID->place,name,call_exp,locate,"String",later))
			expr = new ObjectFuncCall_Node(exp_in,locate,call_exp);
		else
			My_ref->addRefuse(name," : isn't member of or Can't access member declare in class",QID->place->name,name,method,line,*new bool);
	}
	else
		My_ref->addRefuse("class expected before '.'",name,method,line,*new bool);
	return expr;
}

Node* Actions::CallConstructor(my_implements *&QID,AST *call_expr,int line)
{
	Node * expr = new Node();
	Method* locate='\0';
	if (laterTree)
	{
		locate = new Method(); locate->name = *(--QID->implement.end());
		expr=new ConstructCall_Node(locate,call_expr,QID); laterTree = true;
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if (my_check->Check_QID(currNamespace,currClass,QID))
	{
		char * Caller=new char;
		Caller=(char*) *(--QID->implement.end());
		if((MethodSearch::locateFunc((Class*)QID->place,((Class*)QID->place)->name,call_expr,locate,Caller,later))&&(locate!='\0'))
		{
			if (currClass==(Class*)QID->place)
				expr=new ConstructCall_Node(locate,call_expr,QID);
			else if ((Downcast_Node::checkCastType((Class*)QID->place,currClass))&&((my_modifiers::found(locate->modi,Public))||(my_modifiers::found(locate->modi,Protected))))
				expr=new ConstructCall_Node(locate,call_expr,QID);
			else if ((my_modifiers::found(locate->modi,Public)))
				expr=new ConstructCall_Node(locate,call_expr,QID);
			else
				My_ref->addRefuse("constructor : ",QID->place->name," cant be reached",QID->place->name,method,line,*new bool);
		}
		else if (!later)
		{
			locate = new Method(); locate->name = Caller;
			expr=new ConstructCall_Node(locate,call_expr,QID); laterTree = true;
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else if((!MethodSearch::locateFunc((Class*)QID->place,((Class*)QID->place)->name,call_expr,locate,Caller,later))&&(locate!='\0'))
			My_ref->addRefuse(QID->place->name," : constructor found but no overloaded match found",QID->place->name,method,line,*new bool);
		else
			My_ref->addRefuse(QID->place->name," : undeclared constructor or Can't access member declared in class",QID->place->name,method,line,*new bool);
	}
	else if (!later)
	{
		locate = new Method(); locate->name = *(--QID->implement.end());
		expr=new ConstructCall_Node(locate,call_expr,QID); laterTree = true;
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else
		My_ref->addRefuse(*(--QID->implement.end())," : class not found",*(--QID->implement.end()),method,line,*new bool);
	return expr;
}

Node* Actions::CallFather(AST* call_exp,int line)
{
	Node * expr = new Node();
	if (strcmp(currMethod->name,currClass->name)==0) //Constructer
	{
		if (!FirstDad) //first Statement
		{
			my_implements *Inherit=currClass->inherit_class;
			if ((Inherit->implement.size()==1)&& (strcmp(*Inherit->implement.begin(),"Object")==0))
			{
				if (!((call_exp->exprTree==NULL)&&(call_exp->nextExpr==NULL))) //super();
					My_ref->addRefuse(currMethod->name,"Constructer Object Cannot be applied to given types : required No arguments",method,line,*new bool);	
			}
			else if (!later)
			{
				currMethod->DadCall=true;
				expr=CallConstructor(Inherit,call_exp,line);
			}
		}
		else
			My_ref->addRefuse(currMethod->name,"call to super must be first statement in this Constructer",method,line,*new bool);
	}
	else
		My_ref->addRefuse(currMethod->name,"call to super must be first statement in Constructer Only",method,line,*new bool);

	return expr;
}

Node* Actions::Casting(my_implements *QID,Node *in_expr,int line)
{
	Node * expr = new Node();
	my_implements* m = new my_implements();
	if (laterTree)
	{
		expr = new Downcast_Node(QID,in_expr);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if (in_expr->returnValType(m)==5)
	{
		if ((my_check->Check_QID(currNamespace,currClass,QID))&&(my_check->Check_QID(currNamespace,currClass,m))&&((!((Class*)QID->place)->Later)||(later)))
		{
			Class* castClass = (Class*)QID->place; Class* thisClass = (Class*)m->place;
			if (Downcast_Node::checkCastType(thisClass,castClass))
				expr = new Downcast_Node(QID,in_expr);
			else
				My_ref->addRefuse("can not do cast into this type : ",*(--QID->implement.end()),"Downcast",variable,line,*new bool);
		}
		else if ((my_check->Check_QID(currNamespace,currClass,QID))&&(my_check->Check_QID_two(currNamespace,currClass,m))&&((!((Class*)QID->place)->Later)||(later)))
		{
			Class* castClass = (Class*)QID->place; Interface* thisInterface = (Interface*)m->place;
			if (Downcast_Node::checkCastType(thisInterface,castClass))
				expr = new Downcast_Node(QID,in_expr);
			else
				My_ref->addRefuse("can not do cast into this type : ",*(--QID->implement.end()),"Downcast",variable,line,*new bool);
		}
		else if (!later)
		{
			expr = new Downcast_Node(QID,in_expr); laterTree = true;
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else
			My_ref->addRefuse("cast into a type that dosnt exist : ",*(--QID->implement.end()),"Downcast",variable,line,*new bool);
	}
	else if (((strcmp(*QID->implement.begin(),"Int")==0)&&(strcmp(*m->implement.begin(),"Int")==0))||((strcmp(*QID->implement.begin(),"Int")==0)&&(strcmp(*m->implement.begin(),"Float")==0))||((strcmp(*QID->implement.begin(),"Float")==0)&&(strcmp(*m->implement.begin(),"Float")==0))||((strcmp(*QID->implement.begin(),"Bool")==0)&&(strcmp(*m->implement.begin(),"Bool")==0))||((strcmp(*QID->implement.begin(),"String")==0)&&(strcmp(*m->implement.begin(),"String")==0)))
		expr = new Downcast_Node(QID,in_expr);
	else
		My_ref->addRefuse("can not do cast to this expression","Downcast",variable,line,*new bool);
	return expr;
}

Node* Actions::IfStmt(Node* exp_1, Node* exp_2, Node* exp_3, int line)
{
	Node * expr = new Node();
	my_implements * t= new my_implements();
	if (exp_1->grp==CONST)
	{
		if (((Const_Node*)exp_1)->type.type==4)
		{
			if (((Const_Node*)exp_1)->type.bv)
			{
				My_wrn->addWarn("else droped because it can't be reached","IfStmt",line);
				expr = exp_2;
			}
			else 
			{
				My_wrn->addWarn("if droped because it can't be reached","IfStmt",line);
				expr = exp_3;
			}
		}
		else
			My_ref->addRefuse("boolean expression required in if condition","If Statment",variable,line,*new bool);
	}
	else if (exp_1->returnValType(t)==4)
		expr = new IF_Node(exp_1,exp_2,exp_3);
	else
		My_ref->addRefuse("boolean expression required in if condition","If Statment",variable,line,*new bool);
	return expr;
}

Node* Actions::ReturnExpr(Node* in_exp,int line)
{
	Node * expr = new Node();
	if ((strcmp(*currMethod->returnType->implement.begin(),"Void")==0)&&(!later))
		My_ref->addRefuse(currMethod->name," : 'void' function can not return value","ReturnExpr",variable,line,*new bool);
	else if ((currMethod->constructor)&&(!later))
		My_ref->addRefuse(currMethod->name," : constructor can not return value","ReturnExpr",variable,line,*new bool);
	else if (laterTree)
	{
		currMethod->haveReturn=true;
		expr = new Return_Node(in_exp);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if (in_exp->returnValue())
	{
		my_implements* t = new my_implements();
		in_exp->returnValType(t); my_check->Check_QID(currNamespace,currClass,t);
		char* method_type=(char*)*currMethod->returnType->implement.begin();
		char* return_type=(char*) *t->implement.begin();
		if (strcmp(return_type,"self")==0)
		{
			if (strcmp(method_type,"SELF_TYPE")==0)
			{
				currMethod->haveReturn=true;
				expr = new Return_Node(in_exp);
			}
			else if (my_check->Check_Return_Detected(currMethod->returnType->implement,currClass))
			{
				currMethod->haveReturn=true;
				expr = new Return_Node(in_exp);
			}
			else
				My_ref->addRefuse(" 'return' : cannot convert from ",return_type," to ",method_type,"ReturnExpr",variable,line,*new bool);
		}
		else if ((my_check->same_type(t->implement,currMethod->returnType->implement))||(t->place == currMethod->returnType->place))
		{
			currMethod->haveReturn=true;
			expr = new Return_Node(in_exp);
		}
		else if ((strcmp(*currMethod->returnType->implement.begin(),"Float")==0)&&(in_exp->returnValType(t)==1))
		{
			My_wrn->addWarn("return expression has been upcasted to float","UPCAST",line);
		}
		else if ((currMethod->returnType->place->type == clas)&&(Downcast_Node::checkCastType((Class*)currMethod->returnType->place,(Class*)t->place)))
		{
			currMethod->haveReturn=true;
			expr = new Return_Node(in_exp);
		}
		else if ((currMethod->returnType->place->type == inter_face)&&(Downcast_Node::checkCastType((Interface*)currMethod->returnType->place,(Class*)t->place)))
		{
			currMethod->haveReturn=true;
			expr = new Return_Node(in_exp);
		}
		else
			My_ref->addRefuse(" 'return' : cannot convert from ",return_type," to ",method_type,"ReturnExpr",variable,line,*new bool);
	}
	else
		My_ref->addRefuse(" 'return' :Syntax Error ","ReturnExpr",variable,line,*new bool);
	return expr;
}

Node* Actions::WhileStmt(Node* condition,Scope* body,int line)
{
	Node * expr = new Node();
	my_implements * t = new my_implements();
	if (condition->grp==CONST)
	{
		if (((Const_Node*)condition)->type.type==4)
		{
			if (((Const_Node*)condition)->type.bv)
			{
				My_wrn->addWarn("infinite loop!!","WhileStmt",line);
				expr = new WHILE_Node(condition,body);
			}
			else
				My_wrn->addWarn("unreached loop!! droped out","WhileStmt",line);
		}
		else
			My_ref->addRefuse("boolean expression required in while condition","WhileStmt",variable,line,*new bool);
	}
	else if (condition->returnValType(t)==4)
		expr = new WHILE_Node(condition,body);
	else
		My_ref->addRefuse("boolean expression required in while condition","WhileStmt",variable,line,*new bool);
	return expr;
}

Variable* Actions::LetVarDeclaration(char *name,my_implements *&QID,int line,Node *ass_exp)
{
	currVariable=new Variable(name,QID); currVariable->val = new Node();
	if (currScope!=NULL)
	{
		if ((!currScope->searchScope(currVariable))||(later))
		{
			if (my_check->Check_QID(currNamespace,currClass,QID))  // object of class
			{
				if (!my_modifiers::found(((Class *)QID->place)->modi,Abstract))
				{
					if (!later)
					{
						currScope->addLocal(currVariable);
						currVariable->val = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
						if (currMethod->searchMethod(currVariable))
							My_wrn->addWarn(name," : covers a variable in the current function",name,line);
						if (currClass->search_Class(currVariable))
							My_wrn->addWarn(name," : covers a class member",name,line);
					}
				}
				else
					My_ref->addRefuse("can not make an object of Abstract class : ",((Class *)QID->place)->name,name,variable,line,*new bool);
			}
			else if (my_check->Check_QID_two(currNamespace,currClass,QID))  // object of interface
			{
				if (!later)
				{
					currScope->addLocal(currVariable);
					currVariable->val = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
					if (currMethod->searchMethod(currVariable))
						My_wrn->addWarn(name," : covers a variable in the current function",name,line);
					if (currClass->search_Class(currVariable))
						My_wrn->addWarn(name," : covers a class member",name,line);
				}
			}
			else if (!later)
			{
				currScope->addLocal(currVariable);
				currVariable->val = checkAssignment(currVariable,new ID_Node(currVariable),ass_exp,line);
				my_laterDef->pointAtSymbol(currVariable,false,currNamespace,line);
			}
			else
				My_ref->addRefuse("TYPE UNDEFINED",name,variable,line,*new bool);
		}
		else
			My_ref->addRefuse("VARIABLE '",currVariable->name,"' REDEFINATION",name,variable,line,*new bool);
	}
	return currVariable;
}

Node* Actions::LetStmt(Scope* letScope,int line)
{
	Node * expr = new Node();
	if (letScope!=NULL)
	{
		my_implements * t = new my_implements();
		if (letScope->Body->exprTree->returnValue())
			expr = new Let_Node(letScope);
		else
			My_ref->addRefuse("let expression should return value","LetExpr",variable,line,*new bool);
	}
	return expr;
}

Node* Actions::CaseStmt(Node* expHed,Case_Expr Case_exp,bool& ok,int line)
{
	Node *expr=new Node();
	if (ok)
	{
		if (expHed->returnValue())
		{
			my_implements * t = new my_implements(); int return_val = expHed->returnValType(t);
			if ((return_val!=5)&&(return_val!=6)&&(return_val!=3))
			{
				if (CASE_Node::checkCaseType(return_val,Case_exp))
					expr= new CASE_Node(expHed,Case_exp);
				else
					My_ref->addRefuse("compatible types in case expression","CaseStmt",variable,line,ok);
			}
			else
				My_ref->addRefuse("Case expression of type ",(char*)*(--t->implement.end())," :illegal","CaseStmt",variable,line,ok);
		}
		else
			My_ref->addRefuse("Case must return value","CaseStmt",variable,line,ok);
	}
    else 
		ok=true;
	return expr;
}

Node* Actions::ArthmExpr(BinaryOp op,Node *exp_1,Node *exp_2,int line)
{
	Node * expr = new Node();
	my_implements * t = new my_implements();
	Const_Type CT;
	if (laterTree)
	{
		expr=new Binary_Node(exp_1,exp_2,op);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	//the tow nodes are constants
	else if ((exp_1->grp==CONST)&&(exp_2->grp==CONST))
	{
		My_wrn->addWarn("arithmatic have been optimized","ArthmExpr",line);
		if ((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==1))
		{
			CT.type=1;
			switch (op) {
			case SUM: CT.iv = ((Const_Node*)exp_1)->type.iv + ((Const_Node*)exp_2)->type.iv; expr=new Const_Node(CT); break;
			case SUB: CT.iv = ((Const_Node*)exp_1)->type.iv - ((Const_Node*)exp_2)->type.iv; expr=new Const_Node(CT); break;
			case MULT: CT.iv = ((Const_Node*)exp_1)->type.iv * ((Const_Node*)exp_2)->type.iv; expr=new Const_Node(CT); break;
			case DIVS: 
				if (((Const_Node*)exp_2)->type.iv!=0)
				{		
					CT.iv = ((Const_Node*)exp_1)->type.iv / ((Const_Node*)exp_2)->type.iv;
					expr=new Const_Node(CT);
				}
				else
					My_ref->addRefuse("divide by zero","ArthmExpr",variable,line,*new bool);
			}
		}
		else if ((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==2))
		{
			CT.type=2;
			switch (op) {
			case SUM: CT.fv = ((Const_Node*)exp_1)->type.fv + ((Const_Node*)exp_2)->type.fv; expr=new Const_Node(CT); break;
			case SUB: CT.fv = ((Const_Node*)exp_1)->type.fv - ((Const_Node*)exp_2)->type.fv; expr=new Const_Node(CT); break;
			case MULT: CT.fv = ((Const_Node*)exp_1)->type.fv * ((Const_Node*)exp_2)->type.fv; expr=new Const_Node(CT); break;
			case DIVS:
				if (((Const_Node*)exp_2)->type.fv!=0)
				{		
					CT.fv =  ((Const_Node*)exp_1)->type.fv / ((Const_Node*)exp_2)->type.fv;
					expr=new Const_Node(CT);
				}
				else
					My_ref->addRefuse("divide by zero","ArthmExpr",variable,line,*new bool);
			}
		}
		else if ((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==2))
		{
			My_wrn->addWarn("1st have been upcasted to float","ArthmExpr",line);
			CT.type=2;
			switch (op) {
			case SUM: CT.fv =  ((Const_Node*)exp_1)->type.iv + ((Const_Node*)exp_2)->type.fv; expr=new Const_Node(CT); break;
			case SUB: CT.fv =  ((Const_Node*)exp_1)->type.iv - ((Const_Node*)exp_2)->type.fv; expr=new Const_Node(CT); break;
			case MULT: CT.fv =  ((Const_Node*)exp_1)->type.iv * ((Const_Node*)exp_2)->type.fv; expr=new Const_Node(CT); break;
			case DIVS: 
				if (((Const_Node*)exp_2)->type.fv!=0)
				{
					CT.fv =  ((Const_Node*)exp_1)->type.iv / ((Const_Node*)exp_2)->type.fv;
					expr=new Const_Node(CT);
				}
				else
					My_ref->addRefuse("divide by zero","ArthmExpr",variable,line,*new bool);
			}
		}
		else if ((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==1))
		{
			My_wrn->addWarn("2nd have been upcasted to float","ArthmExpr",line);
			CT.type=2;
			switch (op) {
			case SUM: CT.fv =  ((Const_Node*)exp_2)->type.iv + ((Const_Node*)exp_1)->type.fv; expr=new Const_Node(CT); break;
			case SUB: CT.fv =  ((Const_Node*)exp_2)->type.iv - ((Const_Node*)exp_1)->type.fv; expr=new Const_Node(CT); break;
			case MULT: CT.fv =  ((Const_Node*)exp_2)->type.iv * ((Const_Node*)exp_1)->type.fv; expr=new Const_Node(CT); break;
			case DIVS:	
				if (((Const_Node*)exp_2)->type.iv!=0)
				{
					CT.fv =  ((Const_Node*)exp_1)->type.fv / ((Const_Node*)exp_2)->type.iv;
					expr=new Const_Node(CT);
				}
				else
					My_ref->addRefuse("divide by zero","ArthmExpr",variable,line,*new bool);
			}
		}
		else
			My_ref->addRefuse("float or integer required in arthmatic expression","ArthmExpr",variable,line,*new bool);
	}
	//if one or the tow nodes are not constant
	else if (((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==1))||((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==2)))
	{
		switch (op) {
		case DIVS:
			if (((Const_Node*)exp_2)->type.fv!=0)
				expr = new Binary_Node(exp_1,exp_2,DIVS);
			else
				My_ref->addRefuse("divide by zero","ArthmExpr",variable,line,*new bool);
			break;
		default:
			expr = new Binary_Node(exp_1,exp_2,op);
		}
	}
	else if ((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==2))
	{
		My_wrn->addWarn("1st have been upcasted to float","ArthmExpr",line);
		if (exp_1->grp==CONST)
		{
			CT.type=2; CT.fv=((Const_Node*)exp_1)->type.iv; exp_1 = new Const_Node(CT);
		}
		else
		{
			my_implements* t = new my_implements("Float");
			exp_1 = new Upcast_Node(t,exp_1);
		}
		switch (op) {
		case DIVS: 
			if (((Const_Node*)exp_2)->type.fv!=0)
				expr=new Binary_Node(exp_1,exp_2,DIVS);
			else
				My_ref->addRefuse("divide by zero","ArthmExpr",variable,line,*new bool);
			break;
		default: expr=new Binary_Node(exp_1,exp_2,op);
		}
	}
	else if((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==1))
	{
		My_wrn->addWarn("2nd have been upcasted to float","ArthmExpr",line);
		if (exp_2->grp==CONST)
		{
			CT.type=2; CT.fv=((Const_Node*)exp_2)->type.iv; exp_2 = new Const_Node(CT);
		}
		else
		{
			my_implements* t = new my_implements("Float");
			exp_2 = new Upcast_Node(t,exp_2);
		}
		switch (op) {
		case DIVS: 
			if (((Const_Node*)exp_2)->type.fv!=0)
				expr=new Binary_Node(exp_1,exp_2,DIVS);
			else
				My_ref->addRefuse("divide by zero","ArthmExpr",variable,line,*new bool);
			break;
		default: expr=new Binary_Node(exp_1,exp_2,op);
		}
	}
	else
		My_ref->addRefuse("float or integer required in arthmatic expression","ArthmExpr",variable,line,*new bool);
	return expr;
}

Node* Actions::ComparisonExpr(BinaryOp op,Node *exp_1,Node *exp_2,int line)
{
	Node * expr = new Node();
	my_implements * t = new my_implements();
	if (laterTree)
	{
		expr=new Binary_Node(exp_1,exp_2,op);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if ((exp_1->grp==CONST)&&(exp_2->grp==CONST))
	{
		My_wrn->addWarn("Logic Operation have been optimized","ComparationExpr",line);
		Const_Type CT; CT.type=4;
		if ((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==1))
		{
			switch (op) {
			case LESS:CT.bv=(((Const_Node*)exp_1)->type.iv < ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case LSEQ:CT.bv=(((Const_Node*)exp_1)->type.iv <= ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case MORE:CT.bv=(((Const_Node*)exp_1)->type.iv > ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case MREQ:CT.bv=(((Const_Node*)exp_1)->type.iv <= ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case EQL:CT.bv=(((Const_Node*)exp_1)->type.iv == ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT);
			}
		}
		else if ((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==2))
		{
			switch (op) {
			case LESS:CT.bv=(((Const_Node*)exp_1)->type.fv < ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case LSEQ:CT.bv=(((Const_Node*)exp_1)->type.fv <= ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case MORE:CT.bv=(((Const_Node*)exp_1)->type.fv > ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case MREQ:CT.bv=(((Const_Node*)exp_1)->type.fv <= ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case EQL:CT.bv=(((Const_Node*)exp_1)->type.fv == ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT);
			}
		}
		else if ((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==2))
		{
			switch (op) {
			case LESS:CT.bv=(((Const_Node*)exp_1)->type.iv < ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case LSEQ:CT.bv=(((Const_Node*)exp_1)->type.iv <= ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case MORE:CT.bv=(((Const_Node*)exp_1)->type.iv > ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case MREQ:CT.bv=(((Const_Node*)exp_1)->type.iv <= ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT); break;
			case EQL:CT.bv=(((Const_Node*)exp_1)->type.iv == ((Const_Node*)exp_2)->type.fv); expr=new Const_Node(CT);
			}
		}
		else if ((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==1))
		{
			switch (op) {
			case LESS:CT.bv=(((Const_Node*)exp_1)->type.fv < ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case LSEQ:CT.bv=(((Const_Node*)exp_1)->type.fv <= ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case MORE:CT.bv=(((Const_Node*)exp_1)->type.fv > ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case MREQ:CT.bv=(((Const_Node*)exp_1)->type.fv <= ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT); break;
			case EQL:CT.bv=(((Const_Node*)exp_1)->type.fv == ((Const_Node*)exp_2)->type.iv); expr=new Const_Node(CT);
			}
		}
		else
			My_ref->addRefuse("float or integer required in Comparation expression","ComparationExpr",variable,line,*new bool);
	}
	else if (((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==1))||((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==2))||((exp_1->returnValType(t)==1)&&(exp_2->returnValType(t)==2))||((exp_1->returnValType(t)==2)&&(exp_2->returnValType(t)==1)))
		expr = new Binary_Node(exp_1,exp_2,op);
	else
		My_ref->addRefuse("float or integer required in Comparation expression","ComparationExpr",variable,line,*new bool);
	return expr;
}

Node* Actions::LogicExpr(BinaryOp op,Node *exp_1,Node *exp_2,int line)
{
	Node * expr = new Node();
	my_implements * t = new my_implements();
	if (laterTree)
	{
		expr=new Binary_Node(exp_1,exp_2,op);
		my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
	}
	else if ((exp_1->returnValType(t)==4)&&(exp_2->returnValType(t)==4))
	{
		if ((exp_1->grp==CONST)&&(exp_2->grp==CONST))
		{
			My_wrn->addWarn("And/Or have been optimized","LogicExpr",line);
			Const_Type CT; CT.type=4;
			if (op==AND)
				CT.bv=(((Const_Node*)exp_1)->type.bv)&&(((Const_Node*)exp_2)->type.bv);
			else
				CT.bv=(((Const_Node*)exp_1)->type.bv)||(((Const_Node*)exp_2)->type.bv);
			expr = new Const_Node(CT);
		}
		else if (exp_1->grp==CONST)
		{
			My_wrn->addWarn("And/Or have been optimized","LogicExpr",line);
			if (((Const_Node*)exp_1)->type.bv)
			{
				if (op==AND)
					expr=exp_2;
				else
				{
					Const_Type CT; CT.type=4; CT.bv=true;
					expr = new Const_Node(CT);
				}		
			}
			else
			{
				if (op==AND)
				{
					Const_Type CT; CT.type=4; CT.bv=false;
					expr = new Const_Node(CT);
				}
				else
					expr=exp_2;
			}
		}
		else if (exp_2->grp==CONST)
		{
			My_wrn->addWarn("And/Or have been optimized","LogicExpr",line);
			if (((Const_Node*)exp_2)->type.bv)
			{
				if (op==AND)
					expr=exp_1;
				else
				{
					Const_Type CT; CT.type=4; CT.bv=true;
					expr = new Const_Node(CT);
				}		
			}
			else
			{
				if (op==AND)
				{
					Const_Type CT; CT.type=4; CT.bv=false;
					expr = new Const_Node(CT);
				}
				else
					expr=exp_1;
			}
		}
		else
		{
			if (op==AND)
				expr=new Binary_Node(exp_1,exp_2,AND);
			else
				expr=new Binary_Node(exp_1,exp_2,OR);
		}
	}
	else
		My_ref->addRefuse("bool required in boolean expression","LogicExpr",variable,line,*new bool);
	return expr;
}

Node* Actions::UnaryExpr(UnaryOp op,Node *exp_in,int line)
{
	Node * expr = new Node();
	my_implements * t = new my_implements();
	switch (op) {
	case NULLCHECK:
		if (laterTree)
		{
			expr=new Unary_Node(exp_in,NULLCHECK);
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else if (exp_in->returnValType(t)==5)
			expr=new Unary_Node(exp_in,NULLCHECK);
		else
			My_ref->addRefuse("object required in isvoid expression","UnaryExpr",variable,line,*new bool);
		break;
	case LCOMP:
		if (laterTree)
		{
			expr=new Unary_Node(exp_in,LCOMP);
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else if (exp_in->returnValType(t)==1)
			expr=new Unary_Node(exp_in,LCOMP);
		else
			My_ref->addRefuse("'~' operation require integer","UnaryExpr",variable,line,*new bool);
		break;
	case COMP:
		if (laterTree)
		{
			expr=new Unary_Node(exp_in,COMP);
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else if (exp_in->grp==CONST)
		{
			Const_Node* tmpo=(Const_Node*)exp_in;
			if (tmpo->type.type==4)
			{
				My_wrn->addWarn("'not' operation have been optimized","LogicExpr",line);
				Const_Type CT; CT.bv=!(tmpo->type.bv); CT.type=4;
				expr = new Const_Node(CT);
			}
			else
				My_ref->addRefuse("boolean expression required in not expression","UnaryExpr",variable,line,*new bool);
		}
		else if (exp_in->returnValType(t)==4)
			expr=new Unary_Node(exp_in,COMP);
		else
			My_ref->addRefuse("boolean expression required in not expression","UnaryExpr",variable,line,*new bool);
		break;
	case DEL:
		if (laterTree)
		{
			expr=new Unary_Node(exp_in,DEL);
			my_laterDef->pointAtAST(expr,currNamespace,currClass,currMethod,currScope,line);
		}
		else if (exp_in->returnValType(t)==5)
			expr=new Unary_Node(exp_in,DEL);
		else
			My_ref->addRefuse("object required in delete expression","UnaryExpr",variable,line,*new bool);
		break;
	}
	return expr;
}

//---------------------------------LaterDeclarationAction----------------------------

void Actions::scanBottomUp()
{
	later = true;
	laterTree = false;
	//check type list
	if (!my_laterDef->TypeExpectLater.empty())
	{
		list <typeLater>::iterator i = my_laterDef->TypeExpectLater.begin();
		while (i!=my_laterDef->TypeExpectLater.end())
		{
			typeLater t = (typeLater) *i; Symbol* s = ((typeLater) *i).type;
			currNamespace = t.nameSpace;
			if (s->type == clas)
			{
				Class_Action(((Class*) s)->modi,((Class*) s)->ImplementListInterface,((Class*) s)->inherit_class,((Class*) s)->name,t.line);
				if (currClass->Cycle)
					((Class*)s)->Cycle = true;
				if (currClass->Later)
					((Class*)s)->Later = false;
				cout <<currClass->Later;
				currClass = (Class*)s;
				closeClass_Action(t.line);
				if (!currClass->inherit_class->implement.empty()) //Override
				{
					list<Method*> M=currClass->localFuncs;
					if (!M.empty())
					{
						list<Method*>::iterator i=M.begin();
						while (i!=M.end())
						{
							Method *tmp=(Method*) *i;
							if (!my_check->check_Override_Method(tmp,currClass,currNamespace))
								My_ref->addRefuse("FEATURE '",tmp->name,"' Can't Be Overriden",method,t.line,*new bool);
							i++;
						}
					}
				}
			}
			else if (s->type == inter_face)
			{
				Interface_Action(((Interface*) s)->modi,((Interface*) s)->inherit_interface,((Interface*) s)->name,t.line);
				if (currInterface->Later)
					((Interface*)s)->Later = false;
				currInterface = (Interface *)s;
				closeInterface_Action(t.line);
			}
			else if (s->type == method)
			{
				if (t.method)
				{
					MethodsClass_Action(((Method*) s)->modi,((Method*) s)->parameters,((Method*) s)->returnType,((Method*) s)->name,t.line);
					if (((Method*) s)->constructor)
					{
						*currMethod=*((Method*) s);
						my_implements *QID=new my_implements(); QID->implement.push_back(currMethod->name);
						my_check->Check_QID(currNamespace,currClass,QID);
						EndFunction((Class*)QID->place,currMethod->absTree,t.line);
					}
				}
				else
					MehtodsInterface_Action(((Method*) s)->parameters,((Method*) s)->returnType,((Method*) s)->name,t.line);
			}
			else if ((s->type == variable)||(s->type == field))
				VariablesClass_Action(((Variable*) s)->modi,((Variable*) s)->varType,((Variable*) s)->name,t.line);
			i++;
			//my_laterDef->TypeExpectLater.pop_front();
		}
	}
	//check member list
	if (!my_laterDef->MemberExpectLater.empty())
	{
		memLater m; vector <memLater>::iterator i = my_laterDef->MemberExpectLater.begin(); Node * n = new Node();  Node * tmp = new Node();
		while (i!=my_laterDef->MemberExpectLater.end())
		{
			m = ((memLater) *i); n = ((memLater) *i).mem; AST* para = new AST();
			currNamespace = m.nameSpace; currClass = m.clas;
			currMethod = m.method; currScope = m.scope;
			switch (n->grp)
			{
			case STATIC_CALL:
				break;
			case STATIC_ARRAY_CALL:
				break;
			case OBJ_ID:
				if (((ObjectID_Node *)n)->object->grp == STATIC_CALL)
					((ObjectID_Node *)n)->object = CallVariable(((Static_Node *)((ObjectID_Node *)n)->object)->staticImp,((Static_Node *)((ObjectID_Node *)n)->object)->define,m.line);
				*(ObjectID_Node *)n = *(ObjectID_Node *)CallClassVar(((ObjectID_Node *)n)->object,((ObjectID_Node *)n)->var->name,m.line);
				break;
			//case OBJ_ARRAY:
			//	*(ObjectArray_Node *)n = *(ObjectArray_Node *)Callcla(((ObjectArray_Node *)n)->object,((ObjectArray_Node *)n)->var->name,m.line);
			//	break;
			case CONSTRUCTOR_CALL:
				para = ((ConstructCall_Node *)n)->callSegn;
				if (para->size()>0)
				while(para!=NULL)
				{
					if (para->exprTree->grp == STATIC_CALL)
						para->exprTree = CallVariable(((Static_Node *)para->exprTree)->staticImp,((Static_Node *)para->exprTree)->define,m.line);
					para=para->nextExpr;
				}
				*(ConstructCall_Node *)n =*(ConstructCall_Node *) CallConstructor(((ConstructCall_Node *)n)->initClass,((ConstructCall_Node*)n)->callSegn,m.line);
				break;
			case FUNCTION_CALL:
				para = ((FunctionCall_Node *)n)->callSegn;
				if (para->size()>0)
				while(para!=NULL)
				{
					if (para->exprTree->grp == STATIC_CALL)
						para->exprTree = CallVariable(((Static_Node *)para->exprTree)->staticImp,((Static_Node *)para->exprTree)->define,m.line);
					para=para->nextExpr;
				}
				*(FunctionCall_Node*)n = *(FunctionCall_Node*)CallLocalFunc(((FunctionCall_Node *)n)->locate->name,((FunctionCall_Node *)n)->callSegn,m.line);
				break;
			case OBJ_FUNC_CALL:
				para = ((ObjectFuncCall_Node *)n)->callSegn;
				if (para->size()>0)
				while(para!=NULL)
				{
					if (para->exprTree->grp == STATIC_CALL)
						para->exprTree = CallVariable(((Static_Node *)para->exprTree)->staticImp,((Static_Node *)para->exprTree)->define,m.line);
					para=para->nextExpr;
				}
				//if (((ObjectFuncCall_Node *)n)->object->grp == STATIC_CALL)
				//	((ObjectFuncCall_Node *)n)->object = CallVariable(((Static_Node *)((ObjectFuncCall_Node *)n)->object)->staticImp,((Static_Node *)((ObjectFuncCall_Node *)n)->object)->define,m.line);
				if (((ObjectFuncCall_Node*)n)->object->grp == STATIC_CALL)
				{
					((Static_Node*)((ObjectFuncCall_Node*)n)->object)->staticImp->implement.push_back(((ObjectFuncCall_Node*)((memLater) *i).mem)->locate->name);
					*(ObjectFuncCall_Node*)n = *(ObjectFuncCall_Node*)CallFunction(((Static_Node*)((ObjectFuncCall_Node*)n)->object)->staticImp,((ObjectFuncCall_Node*)((memLater) *i).mem)->callSegn,m.line);
				}
				else
					*(ObjectFuncCall_Node*)n = *(ObjectFuncCall_Node*)CallClassFunc(((ObjectFuncCall_Node*)n)->object,((ObjectFuncCall_Node*)n)->locate->name,((ObjectFuncCall_Node*)n)->callSegn,new my_implements(),m.line);
				break;
			case DOWNCAST:
				if (((Downcast_Node *)n)->son->grp == STATIC_CALL)
					((Downcast_Node *)n)->son = CallVariable(((Static_Node *)((Downcast_Node *)n)->son)->staticImp,((Static_Node *)((Downcast_Node *)n)->son)->define,m.line);
				*(Downcast_Node*)n = *(Downcast_Node*)Casting(((Downcast_Node*)n)->lowerType,((Downcast_Node*)n)->son,m.line);
				break;
			case UNARY:
				if (((Unary_Node *)n)->son->grp == STATIC_CALL)
					((Unary_Node *)n)->son = CallVariable(((Static_Node *)((Unary_Node *)n)->son)->staticImp,((Static_Node *)((Unary_Node *)n)->son)->define,m.line);
				*(Unary_Node*)n = *(Unary_Node*)UnaryExpr(((Unary_Node*)n)->opType,((Unary_Node*)n)->son,m.line);
				break;
			case BINARY:
				if (((Binary_Node *)n)->leftSon->grp == STATIC_CALL)
					((Binary_Node *)n)->leftSon = CallVariable(((Static_Node *)((Binary_Node *)n)->leftSon)->staticImp,((Static_Node *)((Binary_Node *)n)->leftSon)->define,m.line);
				if (((Binary_Node *)n)->rightSon->grp == STATIC_CALL)
					((Binary_Node *)n)->rightSon = CallVariable(((Static_Node *)((Binary_Node *)n)->rightSon)->staticImp,((Static_Node *)((Binary_Node *)n)->rightSon)->define,m.line);
				if (((Binary_Node*)n)->arthmeticOp())
					*(Binary_Node*)n = *(Binary_Node*)ArthmExpr(((Binary_Node*)n)->opType,((Binary_Node*)n)->leftSon,((Binary_Node*)n)->rightSon,m.line);
				else if (((Binary_Node*)n)->logicOp())
					*(Binary_Node*)n = *(Binary_Node*)LogicExpr(((Binary_Node*)n)->opType,((Binary_Node*)n)->leftSon,((Binary_Node*)n)->rightSon,m.line);
				else
					*(Binary_Node*)n = *(Binary_Node*)ComparisonExpr(((Binary_Node*)n)->opType,((Binary_Node*)n)->leftSon,((Binary_Node*)n)->rightSon,m.line);
				break;
			case IF_STMT:
				if (((IF_Node *)n)->Condition->grp == STATIC_CALL)
					((IF_Node *)n)->Condition = CallVariable(((Static_Node *)((IF_Node *)n)->Condition)->staticImp,((Static_Node *)((IF_Node *)n)->Condition)->define,m.line);
				*(IF_Node*)n = *(IF_Node*)IfStmt(((IF_Node*)n)->Condition,((IF_Node*)n)->if_true,((IF_Node*)n)->if_else,m.line);
				break;
			case WHILE_STMT:
				if (((WHILE_Node *)n)->Condition->grp == STATIC_CALL)
					((WHILE_Node *)n)->Condition = CallVariable(((Static_Node *)((WHILE_Node *)n)->Condition)->staticImp,((Static_Node *)((WHILE_Node *)n)->Condition)->define,m.line);
				*(WHILE_Node*)n = *(WHILE_Node*)WhileStmt(((WHILE_Node*)n)->Condition,((WHILE_Node*)n)->Body,m.line);
				break;
			case RETURN_EXPR:
				if (((Return_Node *)n)->ReturnVal->grp == STATIC_CALL)
					((Return_Node *)n)->ReturnVal = CallVariable(((Static_Node *)((Return_Node *)n)->ReturnVal)->staticImp,((Static_Node *)((Return_Node *)n)->ReturnVal)->define,m.line);
				*(Return_Node*)n = *(Return_Node*)ReturnExpr(((Return_Node*)n)->ReturnVal,m.line);
				break;
			case ASSIGNMENT:
				if (((Assignment_Node *)n)->var->grp == STATIC_CALL)
					((Assignment_Node *)n)->var = CallVariable(((Static_Node *)((Assignment_Node *)n)->var)->staticImp,((Static_Node *)((Assignment_Node *)n)->var)->define,m.line);
				if (((Assignment_Node *)n)->value->grp == STATIC_CALL)
					((Assignment_Node *)n)->value = CallVariable(((Static_Node *)((Assignment_Node *)n)->value)->staticImp,((Static_Node *)((Assignment_Node *)n)->value)->define,m.line);
				if (((Assignment_Node *)n)->var->grp == IDENTIFIER)
					*(Assignment_Node *)n = *(Assignment_Node *)checkAssignment(((ID_Node *)((Assignment_Node *)n)->var)->var,(ID_Node *)((Assignment_Node *)n)->var,((Assignment_Node *)n)->value,m.line);
				else if (((Assignment_Node *)n)->var->grp == OBJ_ID)
					*(Assignment_Node *)n = *(Assignment_Node *)checkAssignment(((ObjectID_Node *)((Assignment_Node *)n)->var)->var,((ObjectID_Node *)((Assignment_Node *)n)->var)->object,((Assignment_Node *)n)->value,m.line);
				else if (((Assignment_Node *)n)->var->grp == ARRAY)
					*(Assignment_Node *)n = *(Assignment_Node *)checkAssignment(((Array_Node *)((Assignment_Node *)n)->var)->var,(Array_Node *)((Assignment_Node *)n)->var,((Assignment_Node *)n)->value,m.line);
				else if (((Assignment_Node *)n)->var->grp == OBJ_ARRAY)
					*(Assignment_Node *)n = *(Assignment_Node *)checkAssignment(((ObjectArray_Node *)((Assignment_Node *)n)->var)->var,((ObjectArray_Node *)((Assignment_Node *)n)->var)->object,((Assignment_Node *)n)->value,m.line);
			}
			i++;
			//my_laterDef->MemberExpectLater.pop_front();
		}
	}
}

bool Actions::hasNoErrors()
{
	if ((My_err->isEmpty())&&(My_ref->isEmpty()))
		return true;
	else
		return false;
}
