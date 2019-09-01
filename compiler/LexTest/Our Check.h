#include "Symbol_Table.h"

class Check_struct
{
public:
	bool ok;
	NameSpace *father;
	Symbol *place;

	Check_struct(){}
};

class Check
{

public :

	//------------------------------------Process QID , QIDList-----------------------------------
	Check_struct* scan_one(NameSpace *parent,char *Type);
	Check_struct* scan_two(NameSpace *parent,char *Type);

	//for output method , Variable  ,Parameters  , inherit class ,implement interface
	Check_struct* check_1(char *Type,NameSpace *father,Symbol *curr);
	Check_struct* check_2(char *Type,NameSpace *father,Symbol *curr);				
			
	bool Check_QID(NameSpace *father,Symbol *curr,my_implements* &QID);

	//implements
	bool Check_QID_two(NameSpace *father,Symbol *curr,my_implements *& QID);
	bool check_QID_LIST(NameSpace *father,Symbol *curr,list <my_implements *>& mylist);
	//method return type
	bool Check_ReturnQID(NameSpace *father,Symbol *curr,my_implements* & QID);

	//----------------------------------CheckMethod'sParameter---------------------------------------
	bool Contain_Var(char *var , list <char*> in);
	bool Contain_parameter(list <Variable*> mylist);
	bool check_param(Symbol *curr,NameSpace *father,list <Variable*>& mylist);

	//----------------------------------CheckVariableModifier---------------------------------------
	bool ProcessVar_one(Modifier modif,bool &re_only);
	bool ProcessVar_two(Modifier first,Modifier sec,bool &re_only);
	bool ProcessVar_three(Modifier one,Modifier two,Modifier three,bool &re_only);
	bool ProcessVar_four(Modifier one,Modifier two,Modifier three,Modifier four,bool &re_only);
	bool Check_VarModifier(list <Modifier> modi,bool &re_only);

	//----------------------------------CheckClassModifier---------------------------------------
	bool ProcessClass_one(Modifier modif);
	bool ProcessClass_two(Modifier first,Modifier sec);
	bool ProcessClass_three(Modifier one,Modifier two,Modifier three);
	bool Check_ClassModifier(list <Modifier> modi);

	//----------------------------------CheckMethodModifier---------------------------------------
	bool ProcessMethod_one(Modifier modif);
	bool ProcessMethod_two(Modifier first,Modifier sec);
	bool ProcessMethod_three(Modifier one,Modifier two,Modifier three);
	bool ProcessMethod_four(Modifier one,Modifier two,Modifier three,Modifier four);
	bool ProcessMethod_five(Modifier one,Modifier two,Modifier three,Modifier four,Modifier five);
	bool Check_MethodModifier(list <Modifier> modi);
	bool Check_ConstructorModifier(list <Modifier> modi);
	bool check_Override_Method(Method* ,Class *,NameSpace *);
	Symbol* search_method(list <Method*> ,Method *);
	bool search_Method_inheritsClass(Symbol * ,Method *);

	bool Check_Typein_inherits(char*,my_implements*);
	bool Check_Return_Detected(list<char*>,Class*);

	//----------------------------------CheckInetrfaceModifier---------------------------------------
	bool ProcessInterface_one(Modifier modif);
	bool ProcessInterface_two(Modifier first,Modifier sec);
	bool Check_InterfaceModifier(list <Modifier> modi);

	//----------------------------------CheckClassInherit---------------------------------------
	bool checkFinal_Class(Class* ,Interface *);
	bool check_abstract_inhertits(Class*,my_implements*);
	bool checkCircleInherit(Class * a, list<Class*>&,bool,bool&); //where: a inherits b
	bool IsFound(list<Class*>,Class*,bool,bool &);

	//----------------------------------CheckInterfaceInherit---------------------------------------
	bool search_inherits(list <Method*> Local, Method *add);
	bool Bulid(Interface *ALL,Interface* Sub);
	bool InterfaceCheck_Start(Interface *ALL,list <my_implements*> inherit_interface);
	bool checkInterface_inherits(list <my_implements*> inherit_interface);
	bool checkFinal_Interface(list <Method*> ALL,list<Method*> Local);
	bool checkCircleInherit(Interface * a,  list <my_implements *> b,bool&,list <Interface*>,list <Interface*>); //where: a inherits b //Modify
	bool IsFound(list<Interface*>,Interface*);
	bool same_type(list <char*>,list<char *>);
	bool checkEntryPoint();
};