#include "errorMsg.h"

//------------------------------Errors---------------------------------------

Error::Error() {this->msgs.clear();}
void Error::printList ()
{
	if (!msgs.empty() )
	{
		std::list<Error_info*>::const_iterator i;
		for (i=msgs.begin();i!=msgs.end();i++)
		{
		  Error_info* temp=(Error_info*)*i;
		  cout <<temp->msg <<"\n"<<"The Line is  "<<temp->line<<"  The column is  "<<temp->col<<endl;
		} 
	}
}

void Error::insert_Err(Error_info *msg)
{
	msgs.push_back(msg);
}

bool Error::isEmpty()
{
	return this->msgs.empty();
}

//------------------------------Refuses---------------------------------------

void Refuse::print (string s)
{
for (int i=0;i<s.length();i++)
	cout <<s[i];
}

void Refuse::printList () 
{
	std::list<Refuse_Add>::const_iterator i;
	for (i=msgs.begin();i!=msgs.end();i++)
	{
	  Refuse_Add temp=(Refuse_Add)*i;
	  cout <<"Message     ";
	  print(temp.msg);
	  cout <<"  LINE  "<<temp.line;
	  cout <<"  TYPE  "<<temp.type
		   <<"  NAME  "<<temp.name<<endl;
	 } 
}

void Refuse::insert_Ref (Refuse_Add *msg)
{
	 msgs.push_back(*msg);
}

void Refuse::addRefuse(char* fst_msg,char* name,TYPE_ type,int line,bool &ok)
{
	ok=false;
	Refuse_Add* R=new Refuse_Add();
	R->line=line;
	R->msg="";
	R->msg.append(fst_msg);
	R->name= name; R->type=type;
	this->insert_Ref(R);
}

void Refuse::addRefuse(char* fst_msg,char* scd_msg,char* name,TYPE_ type,int line,bool &ok)
{
	ok=false;
	Refuse_Add* R=new Refuse_Add();
	R->line=line;
	R->msg="";
	R->msg.append(fst_msg);
	R->msg.append(scd_msg);
	R->name= name; R->type=type;
	this->insert_Ref(R);
}

void Refuse::addRefuse(char* fst_msg,char* scd_msg,char* thrd_msg,char* name,TYPE_ type,int line,bool &ok)
{
	ok=false;
	Refuse_Add* R=new Refuse_Add();
	R->line=line;
	R->msg="";
	R->msg.append(fst_msg);
	R->msg.append(scd_msg);
	R->msg.append(thrd_msg);
	R->name= name; R->type=type;
	this->insert_Ref(R);
}

void Refuse::addRefuse(char* fst_msg,char* scd_msg,char* thrd_msg,char* frth_msg,char* name,TYPE_ type,int line,bool &ok)
{
	ok=false;
	Refuse_Add* R=new Refuse_Add();
	R->line=line;
	R->msg="";
	R->msg.append(fst_msg);
	R->msg.append(scd_msg);
	R->msg.append(thrd_msg);
	R->msg.append(frth_msg);
	R->name= name; R->type=type;
	this->insert_Ref(R);
}

void Refuse::addRefuse(char* fst_msg,char* scd_msg,char* thrd_msg,char* frth_msg,char* ffth_msg,char* name,TYPE_ type,int line,bool &ok)
{
	ok=false;
	Refuse_Add* R=new Refuse_Add();
	R->line=line;
	R->msg="";
	R->msg.append(fst_msg);
	R->msg.append(scd_msg);
	R->msg.append(thrd_msg);
	R->msg.append(frth_msg);
	R->msg.append(ffth_msg);
	R->name= name; R->type=type;
	this->insert_Ref(R);
}

void Refuse::removeLastRefuse()
{
	this->msgs.pop_back();
}

bool Refuse::isEmpty()
{
	return this->msgs.empty();
}
//------------------------------Warnings---------------------------------------

void Warn::print (string s)
{
for (int i=0;i<s.length();i++)
	cout <<s[i];
}

void Warn::printList () 
{
	std::list<Warn_Add>::const_iterator i;
	for (i=msgs.begin();i!=msgs.end();i++)
	{
		Warn_Add temp=(Warn_Add)*i;
		cout <<"Message     ";
		print(temp.msg);
		cout <<"  LINE  "<<temp.line
		   <<"  NAME  "<<temp.name<<endl;
	 } 
}

void Warn::insert_warn(Warn_Add *msg)
{
	 msgs.push_back(*msg);
}

void Warn::addWarn(char* fst_msg,char* name,int line)
{
	Warn_Add* W=new Warn_Add();
	W->line=line;
	W->msg="";
	W->msg.append(fst_msg);
	W->name= name;
	this->insert_warn(W);
}

void Warn::addWarn(char* fst_msg,char* scd_msg,char* name,int line)
{
	Warn_Add* W=new Warn_Add();
	W->line=line;
	W->msg="";
	W->msg.append(fst_msg);
	W->msg.append(scd_msg);
	W->name= name;
	this->insert_warn(W);
}