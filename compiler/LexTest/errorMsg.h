#include "commonUse.h"

enum TYPE_ {name_space, clas, inter_face, method, field, variable, parameter};

//------------------------------Errors---------------------------------------

class Error_info
{
public:
  char * msg;
  int line;
  int col;
};

class Error 
{
private :
	 std::list<Error_info*> msgs;

public :

	Error();
	void printList();
	void insert_Err(Error_info *msg);
	bool isEmpty();
};

//------------------------------Refuses---------------------------------------

struct Refuse_Add
{
	 string msg;
	 char *name;
	 TYPE_ type;
	 int line;
};

class  Refuse
{
	private : 
	 std::list<Refuse_Add> msgs;

public :

	void print(string s);
	void printList();
	void insert_Ref(Refuse_Add *msg);
	void addRefuse(char* fst_msg,char* name,TYPE_ type,int line,bool &ok);
	void addRefuse(char* fst_msg,char* scd_msg,char* name,TYPE_ type,int line,bool &ok);
	void addRefuse(char* fst_msg,char* scd_msg,char* thrd_msg,char* name,TYPE_ type,int line,bool &ok);
	void addRefuse(char* fst_msg,char* scd_msg,char* thrd_msg,char* frth_msg,char* name,TYPE_ type,int line,bool &ok);
	void addRefuse(char* fst_msg,char* scd_msg,char* thrd_msg,char* frth_msg,char* ffth_msg,char* name,TYPE_ type,int line,bool &ok);
	void removeLastRefuse();
	bool isEmpty();
};

//------------------------------Warnings---------------------------------------

struct Warn_Add
{
	 string msg;
	 char *name;
	 int line;
};

class  Warn
{
	private : 
	 std::list<Warn_Add> msgs;

public :

	void print(string s);
	void printList();
	void insert_warn (Warn_Add *msg);
	void addWarn(char* fst_msg,char* name,int line);
	void addWarn(char* fst_msg,char* scd_msg,char* name,int line);
};