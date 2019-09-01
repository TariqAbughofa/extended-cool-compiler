#include "Our Check.h"

Check_struct *All=new Check_struct();

Check_struct* Check::scan_one(NameSpace *parent,char *Type)
{
	 bool ok=false;

	 All=new Check_struct();
     
	 Symbol *temp=new Symbol();
	
		 list<Symbol *>::const_iterator i=parent->Local.begin();
	while ( (i!=parent->Local.end()) && (!ok)) 
		{
			Symbol *temp=(Symbol *)*i;
			if ((strcmp (temp->name,Type)==0)&&(temp->type==clas))
			{
				temp=(Class*)*i;
				All->place=(Class *)*i;
				ok=true;
			}
			i++;
		}
	All->ok=ok;
	return All;
}

Check_struct* Check::scan_two (NameSpace *parent,char *Type)
{
	 
	All=new Check_struct();

	bool ok=false;
	list<Symbol *>::const_iterator i=parent->Local.begin();
	
	while ( (i!=parent->Local.end()) && (!ok)) 
		{
			Symbol *temp=(Symbol *)*i;
			if ((strcmp (temp->name,Type)==0) && (temp->type==inter_face)) 
			{
				ok=true;
				All->place=(Interface*)*i;
			}
			i++;
		}
	All->ok=ok;
	return All;
}

//for output method , Variable  ,Parameters  , inherit class ,implement interface
Check_struct* Check::check_1(char *Type,NameSpace *father,Symbol *curr)
{
	bool ok=true;
	All=new Check_struct();
	bool p=false;	
	while ( (father!='\0') && (!p) )
	{
		All=scan_one(father,Type);
		if (All->ok)
		{
			p=true;
			All->father=father;
		}
		else
			father=(NameSpace *)father->parent;
	} 
	if (!p)
		ok=false;			
	All->ok=ok;
	return All;
}

Check_struct* Check::check_2(char *Type,NameSpace *father,Symbol *curr)
{
	bool ok=true;
	All=new Check_struct();
	bool p=false;	
	while ( (father!='\0') && (!p) )
	{
		All=scan_two(father,Type);
		if (All->ok)
		{
			p=true;
			All->father=father;
		}
		else
			father=(NameSpace *)father->parent;
	} 
	if (!p)
		ok=false;		
	All->ok=ok;
	return All;
}

//------------------------------------Process QID QIDList-----------------------------------
bool final=false;
bool Check::Check_QID(NameSpace *father,Symbol *curr,my_implements* & QID)
{
	if (QID->implement.empty())
		return true;
	if (QID->implement.size()==1)
	{
		char * Type = (char*)*QID->implement.begin();
		if (strcmp(Type,curr->name)==0)
		{
			QID->place = curr;
			return true;
		}
	}
	bool ok=true;
	list<char *>::const_iterator i=QID->implement.end();
	i--;
	char *type=(char *)*i;
	All=new Check_struct();
	All=check_1(type,father,curr);
	if (All->ok)
	{
		char *temp=new char;
		int count=1;
		while ( (i!=QID->implement.begin()) && (All->father!='\0')&&(All->ok) )
		{
			i--;
			count++;
			temp=(char *)*i;
			if (strcmp (temp,All->father->name)!=0)
				Check_QID((NameSpace*)All->father->parent,curr,QID);
			else //equal
			{
				if (i==QID->implement.begin())
				{
					final=true;
					break;
				}
				else if  (All->father->parent!='\0') 
					All->father=(NameSpace *)All->father->parent;
			}
		}
		if ((final)||(QID->implement.size()==1))
			QID->place=All->place;
		else
			ok=false;
	}
	else
		ok=false;
	return ok;
}

//implements
bool Check::Check_QID_two (NameSpace *father,Symbol *curr,my_implements *&QID)
{
	bool ok=true;
	list<char *>::const_iterator i=QID->implement.end();
	i--;
	char *type=(char *)*i;
	All=new Check_struct();
	All=check_2(type,father,curr);
	if (All->ok)
	{
		int count=1;
		char *temp=new char ;
		while ( (i!=QID->implement.begin()) &&  (All->father!='\0') ) 
		{
		    i--;
			count++;
			temp=(char *)*i;
			if (strcmp (temp,All->father->name)!=0)
				Check_QID_two((NameSpace*)All->father->parent,curr,QID);
			else //equal
			{
				if (i==QID->implement.begin())
				{
					final=true;
					break;
				}
				else
				{
					if (All->father->parent!='\0') 
						All->father=(NameSpace *)All->father->parent;
				}
			}
		}
		if ((final)||(QID->implement.size()==1))
			QID->place=All->place;
		else
			ok=false;
	}
	else
		ok=false;
	return ok;
}

bool Check::check_QID_LIST (NameSpace *father,Symbol *curr,list <my_implements *>& mylist)
{
	bool ok=true;
	if (!mylist.empty())
	{
			list <my_implements *> New_mylist;
			list<my_implements *>::iterator i=mylist.begin();
			while ((ok)&&(i!=mylist.end()))
			{
				my_implements *QID=(my_implements*)*i;
				if(!Check_QID_two(father,curr,QID)) 
					ok=false;
				New_mylist.push_front(QID);	
				i++;
			}

			if (ok)
			{
				mylist.clear();
				mylist=New_mylist;
			}
	}
	return ok;
}

bool Check::Check_ReturnQID(NameSpace *father,Symbol *curr,my_implements* & QID)
{
	if ((QID->implement.size()==1)&&(strcmp(*QID->implement.begin(),"SELF_TYPE")==0))
	{
		QID->place=curr;
		return true;
	}
	else if ((QID->implement.size()==1)&&(strcmp(*QID->implement.begin(),"Void")==0))
		return true;
	else 
		return (Check_QID(father,curr,QID)||Check_QID_two(father,curr,QID));
}
////////////////////////////////////////////////////////////////////////////

bool Check::Contain_Var (char *var , list <char*> in)
{
	bool ok=false;
	if (in.empty())
		return ok;

	std::list<char*>::const_iterator i=in.begin();
	while ((i!=in.end()) && (!ok))
	{
		char *temp=(char*) *i;
		if (strcmp (temp,var)==0)
			ok=true;
		i++;
	}
	return ok;

}

bool Check::Contain_parameter (list <Variable*> mylist)
{
	bool ok=false;
	
	//Check Repeat Variable in Method signture
	list <char*> temp;
	std::list<Variable *>::iterator i=mylist.begin();
	while ( (i!=mylist.end()) && (!ok) )
	{
		Variable *u=(Variable *)*i;
		if (!Contain_Var(u->name,temp))
			temp.push_back(u->name);
		else
			ok=true;
		i++;
	}
  return ok;

}

bool Check::check_param (Symbol *curr,NameSpace *father,list <Variable*>& mylist)
{
	bool ok=true;
	if (Contain_parameter(mylist))
		ok=false;

	if ( (!mylist.empty()) && (ok) )
	{
		list<Variable *>::iterator i = mylist.begin();
		while ((i!=mylist.end())&&(ok))
		{
			if ((!Check_QID(father,curr,((Variable* ) *i)->varType))&&(!Check_QID_two(father,curr,((Variable* ) *i)->varType)))
				ok=false;
			i++;
		}
	}
	return ok;
}

//----------------------------------CheckVariableModifier---------------------------------------

bool Check::ProcessVar_one(Modifier modif,bool &re_only)
{
	bool ok=false;
	if ( (modif==Public)||(modif==Protected)||(modif==Private)||(modif==Static)||(modif==Readonly)||(modif==Internal) )
	{
		ok=true;
		if (modif==Readonly)
			re_only=true;
	}
	return ok;
}

bool Check::ProcessVar_two(Modifier first,Modifier sec,bool &re_only)
{
	bool ok=false;

	if (first!=sec)
	{
		if ((first==Public)||(first==Protected)||(first==Private))
		{
			if ( (sec==Static)|| (sec==Readonly)|| (sec==Internal) )
			{
				ok=true;
				if (sec==Readonly)
					re_only=true;
			}
		}
		else
		{
			if ( (first==Static)|| (first==Readonly)|| (first==Internal) )
			{
				if ((sec==Public)||(sec==Protected)||(sec==Private))
				{
					ok=true;
					if (first==Readonly)
						re_only=true;
				}
				else
				{
					if ((sec==Readonly) && (first!=Static))
					{
							ok=true;
							re_only=true;
					}
					else if ((sec==Static) && (first!=Readonly))
					{
						ok=true;
						re_only=true;
					}
					else if (sec==Internal)
					{
						re_only=true;
						ok=true;
					}
				}
			}
		}
	}
	return ok;
}

bool Check::ProcessVar_three(Modifier one,Modifier two,Modifier three,bool &re_only) 
{
	bool ok=false;
	if ((ProcessVar_two(one,two,re_only)) && (ProcessVar_two(one,three,re_only)) && (ProcessVar_two(two,three,re_only)) )
		ok=true;
	return ok;
}

bool Check::Check_VarModifier(list <Modifier> modi,bool &re_only) 
{
	bool ok=false;
	if (modi.empty())
		ok=true;
	else
	{
		if (modi.size()<4)   //max is 4 {public,private,protected}--> {internal}-->{static,readonly}.
		{
			switch (modi.size())
			{
			case 1: if (ProcessVar_one((Modifier)*modi.begin(),re_only))ok=true;break;
			case 2:if (ProcessVar_two((Modifier)*modi.begin(),(Modifier)*(++modi.begin()),re_only)) ok=true; break;
			case 3:if (ProcessVar_three((Modifier)*modi.begin(),(Modifier)*(++modi.begin()),(Modifier)*(++(++modi.begin())),re_only)) ok=true; break;
			}
		}
	}
	return ok;
}

//----------------------------------CheckClassModifier---------------------------------------
bool Check::ProcessClass_one(Modifier modif)
{
	bool ok=false;
	if ( (modif==Public)||(modif==Protected)||(modif==Private)||(modif==Abstract)||(modif==Sealed)||(modif==Internal) )
		ok=true;
	return ok;
}

bool Check::ProcessClass_two(Modifier first,Modifier sec)
{
	bool ok=false;
	if (first!=sec) 
	{
		if ((first==Public)||(first==Protected)||(first==Private))
		{
			if ( (sec==Sealed)|| (sec==Abstract)|| (sec==Internal) )
				if (!((first==Private)&&(sec==Abstract)))
					ok=true;
		}
		else
		{
			if ( (first==Sealed)|| (first==Abstract)|| (first==Internal) )
			{
				if ((sec==Public)||(sec==Protected)||(sec==Private))
					if (!((first==Abstract)&&(sec==Private)))
						ok=true;
				else
				{
					if ((sec==Abstract) && (first==Internal))
						ok=true;
					else if ((sec==Sealed) && (first==Internal))
						ok=true;
					else if ((sec==Internal) && (first==Abstract || first==Sealed))
						ok=true;
				}
			}
		}
	}
	return ok;
}

bool Check::ProcessClass_three(Modifier one,Modifier two,Modifier three) 
{
	bool ok=false;
	if ((ProcessClass_two(one,two)) && (ProcessClass_two(one,three)) && (ProcessClass_two(two,three)))
		ok=true;
	return ok;
}

bool Check::Check_ClassModifier(list <Modifier> modi) 
{
	bool ok=false;
	if (modi.empty())
		ok=true;
	else
	{
		if (modi.size()<4)   //max is 3 {public,private,protected}--> {internal} -->{abstract,sealed}.
		{
			switch (modi.size())
			{
			case 1: if (ProcessClass_one((Modifier)*modi.begin())) ok=true; break;
			case 2:if (ProcessClass_two((Modifier)*modi.begin(),(Modifier)*(++modi.begin()))) ok=true; break;
			case 3:if (ProcessClass_three((Modifier)*modi.begin(),(Modifier)*(++modi.begin()),(Modifier)*(++(++modi.begin())))) ok=true; break;
			}
		}
	}
	return ok;
}

//----------------------------------CheckMethodModifier---------------------------------------

bool Check::ProcessMethod_one(Modifier modif)
{
	bool ok=false;
	if ( (modif==Static)||(modif==Virtual)||(modif==Override)||(ProcessClass_one(modif)))
		if (!((modif==Virtual)||(modif==Override)||(modif==Abstract)))
		ok=true;
	return ok;
}

bool Check::ProcessMethod_two(Modifier first,Modifier sec)
{
	bool ok=false;

	if (first != sec)
	{
		if ((ProcessClass_one(first)) && (ProcessClass_one(sec)) )
		{
			if (ProcessClass_two(first,sec))
				ok=true;
		}
		else
		{
			if (ProcessClass_one(first))
			{
				if ((ProcessMethod_one(sec))||( (sec==Virtual)|| (sec==Override)))
				{
					if ( (!((first==Private)&& (sec==Virtual))) &&(!((first==Sealed)&& (sec==Virtual))) && (!((first==Abstract)&& (sec==Virtual))) && (!((first==Abstract)&& (sec==Override))))
						if (!((first==Private)&& (sec==Override)))
							ok=true;
				}
			}
			else
			{
				if (ProcessClass_one(sec))
				{
					if ((ProcessMethod_one(first))||( (first==Virtual)|| (first==Override)))
					{
						if ((!((sec==Private)&& (first==Virtual))) &&(!((sec==Sealed)&& (first==Virtual))) && (!((sec==Abstract)&& (first==Virtual))) && (!((sec==Abstract)&& (first==Override))) )
							if (!((sec==Private)&& (first==Override)))
								ok=true;
					}
				}
			}
		}
	}
	return ok;
}

bool Check::ProcessMethod_three(Modifier one,Modifier two,Modifier three) 
{
	bool ok=false;
	if ((ProcessMethod_two(one,two)) && (ProcessMethod_two(one,three)) && (ProcessMethod_two(two,three)))
		ok=true;
	return ok;
}

bool Check::ProcessMethod_four(Modifier one,Modifier two,Modifier three,Modifier four) 
{
	bool ok=false;
	if ( (ProcessMethod_three(one,two,three))&&(ProcessMethod_three(one,two,four))&&(ProcessMethod_three(one,three,four))&&(ProcessMethod_three(two,three,four)))
		ok=true;
	return ok;
}

bool Check::ProcessMethod_five(Modifier one,Modifier two,Modifier three,Modifier four,Modifier five) 
{
	bool ok=false;
	if ( (ProcessMethod_four(one,two,three,four))&&(ProcessMethod_four(one,two,three,five))&&(ProcessMethod_four(one,two,four,five))&&
		(ProcessMethod_four(one,three,four,five))&& (ProcessMethod_four(two,three,four,five)))
		ok=true;
	return ok;
}

bool Check::Check_MethodModifier(list <Modifier> modi) 
{
	 //max is 5 {public,private,protected}--> {internal} -->{abstract,sealed,virtual}-->{override}-->{static}.
	bool ok=false;
	switch (modi.size()){
	
	case 0: ok=true; break;
	case 1:     if (ProcessMethod_one((Modifier) *modi.begin()))
						ok=true;
				break;

	case 2:if (ProcessMethod_two((Modifier) *modi.begin(),(Modifier) *(++modi.begin())))
						ok=true;
				break;
	case 3 :  if (ProcessMethod_three((Modifier) *modi.begin(),(Modifier) *(++modi.begin()),(Modifier) *(++(++modi.begin()))))
					 ok=true;
			 break;
	case 4 :  if (ProcessMethod_four((Modifier) *modi.begin(),(Modifier) *(++modi.begin()),(Modifier) *(++(++modi.begin())),
				  (Modifier) *(++(++(++modi.begin())))))
					 ok=true;
			 break;
	case 5 :  if (ProcessMethod_five((Modifier) *modi.begin(),(Modifier) *(++modi.begin()),(Modifier) *(++(++modi.begin())), 
				  (Modifier) *(++(++(++modi.begin()))), (Modifier) *(++(++(++(++modi.begin()))))))
					 ok=true;
			 break;
	}
	return ok;
}

bool Check::Check_ConstructorModifier(list <Modifier> modi)
{
	bool ok=false;
	if (modi.size()==0)
		return true;
	else if (modi.size()==1)
	{
		if ((my_modifiers::found(modi,Public))||(my_modifiers::found(modi,Private))||(my_modifiers::found(modi,Protected))||(my_modifiers::found(modi,Internal)))
			return true;
		else
			return false;
	}
	else if (modi.size()==2)
	{
		if (my_modifiers::found(modi,Internal))
		{
			if ((my_modifiers::found(modi,Public))||(my_modifiers::found(modi,Private))||(my_modifiers::found(modi,Protected)))
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

Symbol* Check::search_method(list <Method*> Local,Method *se)
{
	if (!Local.empty())
	{
		list<Method*>::iterator i=Local.begin();
		while (i!=Local.end())
		{
			Method *p=(Method *) *i;
			Method *tmp='\0';
			tmp=(Method*)p;
			if(strcmp (tmp->name,se->name)==0)
			{
				if (Method::equal_param(tmp->parameters,se->parameters))
				{
					if (commonUse::equal_char(tmp->returnType->implement,se->returnType->implement))
					  return tmp;
				}
			}
			i++;
		}
	}
	return new Symbol();
}

bool Check::search_Method_inheritsClass(Symbol * locate,Method *my_method)
{
	Class *tmp=new Class ();
	tmp=(Class*)locate;
	Method *found=(Method *)search_method(tmp->localFuncs,my_method);
    Class *rep=new Class();
	if(strcmp(found->name," ")==0)  //Not found
	{
		rep=(Class*)locate;
		if (rep->inherit_class->implement.empty())
			return false;
		else
			 search_Method_inheritsClass(rep->inherit_class->place,my_method);
	}
	else
		return ((my_modifiers::found(found->modi,Abstract))||(my_modifiers::found(found->modi,Virtual))||
		((my_modifiers::found(found->modi,Override))&&(!my_modifiers::found(found->modi,Sealed))));
}

bool Check::check_Override_Method(Method* currMethod,Class *currClass,NameSpace * currNamespace)
{
	bool ok=true;
	if (my_modifiers::found(currMethod->modi,Override))
	{
		if (currClass->inherit_class->implement.empty())
			ok=false;
		else
		{
			if (currClass->inherit_class->place==NULL)
				Check_QID (currNamespace,currClass,currClass->inherit_class);
			if (currClass->inherit_class->place!=NULL)
				if (!search_Method_inheritsClass(currClass->inherit_class->place,currMethod))
					ok=false;
		}
	}
	return ok;
}

bool Check::Check_Typein_inherits(char* type,my_implements* inherit_class)
{
	if (inherit_class->implement.empty())
		return false;

	char *Comp=new char;
	Comp=(char*) *(--inherit_class->implement.end());
	if(strcmp (type,Comp)==0)
		return true;
	else
		return  Check_Typein_inherits(type,((Class*)inherit_class->place)->inherit_class); 
}

bool Check::Check_Return_Detected(list<char*>my_type,Class* curr)
{
	bool ok=true;
	char *type=new char;
	//Get type name
	if (my_type.size()==1)
		type=(char*)*my_type.begin();
	else
		type=(char*)*(--my_type.end());

	if(strcmp (type,curr->name)==0)
		return ok;
	else
	{
		//search inherits or his father as ...
		if (Check_Typein_inherits(type,curr->inherit_class))
			return ok;
		else
			ok=false;
	}
	return ok;
}

//----------------------------------CheckInetrfaceModifier---------------------------------------
bool Check::ProcessInterface_one(Modifier modif)
{
	bool ok=false;
	if ( (modif==Public)||(modif==Protected)||(modif==Private)||(modif==Internal) )
		ok=true;
	return ok;
}

bool Check::ProcessInterface_two(Modifier first,Modifier sec)
{
	bool ok=false;
	if ((first==Public)||(first==Protected)||(first==Private))
	{
		if (sec==Internal) 
			ok=true;
	}
	else
	{
		if (first==Internal) 
		{
			if ((sec==Public)||(sec==Protected)||(sec==Private))
				ok=true;
		}
	}
		return ok;
}

bool Check::Check_InterfaceModifier(list <Modifier> modi) 
{

	 //max is 2 {public,private,protected}--> {internal}.
	bool ok=false;
	switch (modi.size()){
	case 0: ok=true; break;
	case 1:     if (ProcessInterface_one((Modifier) *modi.begin()))
						ok=true;
				break;
	case 2:if (ProcessInterface_two((Modifier) *modi.begin(),(Modifier) *(++modi.begin())))
						ok=true;
				break;
	}
	return ok;
}

//---------------------------------------CheckInheritsInterface----------------------------------

bool Check::search_inherits(list <Method*> Local, Method *add)
{
	bool ok=true;
	if (!Local.empty())
	{
		std::list <Method *> ::const_iterator i=Local.begin();
		while ((ok) && (i!=Local.end()) )
		{
			Method *temp=(Method *) *i;
			if ((strcmp (add->name,temp->name)==0)&&(Method::equal_param(temp->parameters,add->parameters)))
			{
				char* first=*(--temp->returnType->implement.end()); 
				char* sec=*(--add->returnType->implement.end());
				if (!strcmp (first,sec)==0)
					ok=false;
			}
			i++;
		}
	}
	return ok;
}

bool InterfaceCheck_Start(Interface* ,list <my_implements*>);

bool Check::Bulid(Interface *ALL,Interface* Sub)
{
	bool ok=true;
	if (!Sub->Local.empty())
	{
		list<Method*>::iterator i=Sub->Local.begin();
		while ( (ok) && (i!=Sub->Local.end()) )
		{
			Method* k=(Method*)*i;
			if (!search_inherits(ALL->Local,k))
				ok=false;
			else
				ALL->Local.push_back(k);
				i++;
		}
	}
	if (ok)
	{
		if (!Sub->inherit_interface.empty())
		{
			if (!InterfaceCheck_Start (ALL,Sub->inherit_interface))
				ok=false;
		}
	}
	return ok;
}

bool Check::InterfaceCheck_Start(Interface *ALL,list <my_implements*> inherit_interface)
{
	bool ok=true;
	list<my_implements*>::iterator i=inherit_interface.begin();
	while ( (i!=inherit_interface.end()) && (ok) )
	{
		my_implements* p=(my_implements*)*i;
		if (p->place!=NULL)
		{
			Interface *Sub=(Interface*)p->place;
			if (!Bulid(ALL,Sub))
				ok=false;
		}
		else
			ok = true;
		i++;
	}
	return ok;
}

bool Check::checkInterface_inherits(list <my_implements*> inherit_interface)
{
	bool ok=true;
	Interface *ALL=new Interface();
	if (!inherit_interface.empty())
	{
		if (!InterfaceCheck_Start(ALL,inherit_interface))
			ok=false;
	}
	return ok;
}

bool Check::checkFinal_Interface(list <Method*> ALL,list<Method*> Local)
{
	bool ok=true;
	std::list<Method*>::iterator i=Local.begin();
	while  ( (i!=Local.end()) && (ok ))
	{
		Method *p=(Method*) *i;
		if (!search_inherits(ALL,p))
			ok=false;
		i++;
	}
	return ok;
}

//----------------------------------CheckClassInherit---------------------------------------

bool Check::IsFound(list<Class*>L,Class* I,bool ISNULL,bool &NULL_INH) 
{
	bool ok=false;

	if (!ISNULL)
	{
		list<Class*>::iterator i=L.begin();
		while ((!ok) && (i!=L.end()))
		{
			Class* tmp=(Class*) *i;
			if (tmp==I)
				ok=true;
			i++;
		}
	}
	else //NULL Later Compare With name
	{
		list<Class*>::iterator i=L.begin();
		while ((!ok) && (i!=L.end()))
		{
			Class* r=(Class*)*i;	
			if (I->inherit_class->implement.size()==r->inherit_class->implement.size())
			{
				if ((I->inherit_class->implement==r->inherit_class->implement) && (r->inherit_class->place!=NULL))
					ok=true; //cycle Later
			}
			i++;
		}

		if (!ok)
			NULL_INH=false;
	}

	return ok;
}

bool Check::checkCircleInherit(Class *a,list<Class*> &List,bool ISNULL,bool &ok) //where: a inherits b
{
	bool Y=true;
	if (strcmp(a->name,"Object")!=0)
	{
		if (!IsFound(List,a,ISNULL,Y))
		{
			if (Y)
			{
				List.push_back(a);
				if (a->inherit_class->place!=NULL)
					checkCircleInherit((Class*)a->inherit_class->place,List,false,ok);
				else 
				{
					Class *tmp=new Class();
					tmp->inherit_class=a->inherit_class;
					checkCircleInherit(tmp,List,true,ok);
				}
			}
			else
				ok=false;
		}
		else
			ok=true;
	}
	return ok;
}

bool y=true;
bool Check::checkFinal_Class(Class* currClass,Interface * currInterface)
{
	list<Method*>::iterator i=currInterface->Local.begin();
	while ( (i!=currInterface->Local.end()) && (y) )
	{
		Method *p=(Method*) *i;
		currClass->same_func=false;
		currClass->search_Class((Symbol*)p);
		if (!currClass->same_func)
			y=false;
		i++;
	}
	if ((y)&&(!currInterface->inherit_interface.empty()))
	{
		list <my_implements *>::iterator i;
		Interface * I = new Interface(); my_implements * t = new my_implements();
		for (i = currInterface->inherit_interface.begin(); i!= currInterface->inherit_interface.end();i++)
		{
			t = (my_implements *) *i;
			I = (Interface *)t->place;
			if (I != NULL)
			{
				checkFinal_Class(currClass,I);
				if (!y)
					break;
			}
			else
				break;
		}
	}
	return y;
}

list<Method*> extract_ALL_AbstractMethod(list<Method*> local)
{
	list <Method*> out;
	list<Method*>::iterator i=local.begin();
	while (i!=local.end())
	{
		Method *tmpo=(Method*)*i;
		if (my_modifiers::found(tmpo->modi,Abstract))
			out.push_back(tmpo);
		i++;
	}
	return out;
}

bool Check::check_abstract_inhertits(Class* curr,my_implements*inherit)
{
	if (!inherit->implement.empty())
	{
		if (inherit->place!=NULL)
		{
			Class *inh=(Class*)inherit->place;
			list <Method*> All;
			if (my_modifiers::found(inh->modi,Abstract))
			{
				All=extract_ALL_AbstractMethod(inh->localFuncs);
				if (!All.empty())
				{
					Interface* I = new Interface();
					I->Local=All; I->inherit_interface.clear();
					if (!checkFinal_Class(curr,I))
						return false;
					else
						return check_abstract_inhertits(curr,inh->inherit_class);
				}
			}
		}
	}
	return true;
}

bool Check::same_type(list <char*> t1,list<char *> t2)
{
	if ((t1.empty())||(t2.empty()))
		return false;
	else if ((strcmp(*t1.begin(),"Int")==0)&&(strcmp(*t2.begin(),"Int")==0))
		return true;
	else if ((strcmp(*t1.begin(),"Float")==0)&&(strcmp(*t2.begin(),"Float")==0))
		return true;
	else if ((strcmp(*t1.begin(),"Bool")==0)&&(strcmp(*t2.begin(),"Bool")==0))
		return true;
	else if	((strcmp(*t1.begin(),"String")==0)&&(strcmp(*t2.begin(),"String")==0))
		return true;
	else
		return false;
}
//----------------------------------CheckInterfaceInherit---------------------------------------

bool Check::IsFound(list<Interface*>L,Interface* I) 
{
	bool ok=false;
	list<Interface*>::iterator i=L.begin();
	while ((!ok) && (i!=L.end()))
	{
		Interface *tmp=(Interface*) *i;
		if (tmp==I)
			ok=true;
		i++;
	}
	return ok;
}

bool Check::checkCircleInherit(Interface * a, list <my_implements *> b,bool &ok,list <Interface*> Old,list <Interface*> New) //where: a inherits b
{
	list<my_implements *>::iterator i = b.begin(); 
	while ((i != b.end()) && (!ok))
	{
		my_implements * T=(my_implements*) *i;
		Interface *currInterface=(Interface*) T->place;
		if ((currInterface!=NULL) && (!IsFound(New,currInterface)))
		{
			New.push_back(currInterface);
			if ((!currInterface->inherit_interface.empty()) )
				checkCircleInherit(currInterface,currInterface->inherit_interface,ok,Old,New);
		}
		else
			ok=true;

		if (!ok)
		{
			Old.push_back(currInterface);
			New=Old;
		}

		i++;
	}
	return ok;
}