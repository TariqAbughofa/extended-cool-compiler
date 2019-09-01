%{
#include "yacc.hpp"
#include <stdlib.h>
#include <list>
#include <fstream>
#include "Symbol_Table.h"

int mylineno,mywords,mydigit,myfloat,space = 0;
char* temp;
int line=1;
int col=0;
string v="";
void yyerror(char *);
char * copystr(const char* s);
%}

%option c++
%option noyywrap

QUOTE ["]
DIGIT [0-9]
ID [a-z|A-Z|_][a-z0-9A-Z|_]*
FILE [a-zA-Z|:]*\\\\[a-z0-9A-Z|.]*
%x com1
%x com2 com3 strError
%x incl
%{
#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;
%}
%%

"--"				{BEGIN(com1); col+=2;}
<com1>[\n]			{line++;BEGIN(INITIAL);col=0;}
<com1>[^\n]		    {col+=yyleng;}


"(*"				{BEGIN(com2);col+=2;}
<com2>[\n]			{line++;col=0;}
<com2>"*)"			{ BEGIN(INITIAL);col+=2;}
<com2>[^*)]			{col+=yyleng;}


{QUOTE}            {v="";BEGIN(com3); col+=1; }

<com3>\\n {*yytext++ ='\n'; v+="\n"; line++; col=0;}
<com3>\\t {*yytext++ ='\t'; v+="\t"; col+=8;}
<com3>\\r {*yytext++ ='\r'; v+="\r"; col+=8;}
<com3>\\b {*yytext++ ='\b'; v+="\b"; col+=8;}
<com3>\\f {*yytext++ ='\f'; v+="\f"; col+=8;}
<com3>\\v {*yytext++ ='\v'; v+="\v"; col+=8;}

<com3>{QUOTE} {BEGIN(INITIAL);col+=1; const char * g=new char;
g=v.data();yylval.sval=(char *) g; return STRINGS;}

<com3>.		{col+=yyleng;v.append(yytext);}

(b|B)(e|E)(g|G)(I|i)(n|N) {col+=yyleng;return (BEG);}
(c|C)(l|L)(a|A)(s|S)(s|S) {col+=yyleng;return (CLASS);}
(e|E)(n|N)(D|d) {col+=yyleng;return END;}
(f(a|A)(l|L)(s|S)(e|E)) {col+=yyleng;return FALSE;}
(F(a|A)(l|L)(s|S)(e|E)) {col+=yyleng;return err_FALSE;}
(f|F)(i|I) {col+=yyleng;return FI;}
(i|I)(n|N) {col+=yyleng;return IN;}
(i|I)(n|N)(h|H)(e|E)(r|R)(i|I)(t|T)(s|S) {col+=yyleng;return INHERITS;}
(i|I)(s|S) {col+=yyleng;return IS;}
(i|I)(s|S)(v|V)(o|O)(i|I)(d|D) {col+=yyleng;return ISVOID;}
(l|L)(e|E)(t|T) {col+=yyleng;return LET;}
(l|L)(o|O)(o|O)(p|P) {col+=yyleng;return LOOP;}
(p|P)(o|O)(o|O)(l|L) {col+=yyleng;return POOL;}
(c|C)(a|A)(s|S)(e|E) {col+=yyleng;return CASE;}
(e|E)(s|S)(a|A)(c|C) {col+=yyleng;return ESAC;}
(n|N)(e|E)(W|w) {col+=yyleng;yylval.modi=New; yylval.my_modifier=new my_modifiers(New); return NEW; }
(o|O)(f|F) {col+=yyleng;return OF;}
(n|N)(o|O)(t|T) {col+=yyleng;return NOT;}
(t(r|R)(u|U)(e|E)) {col+=yyleng;return TRUE;}
(T(r|R)(u|U)(e|E)) {col+=yyleng;return err_TRUE;}
(i|I)(f|F) {col+=yyleng;return IF;}
(t|T)(h|H)(e|E)(n|N) {col+=yyleng;return THEN;}
(e|E)(l|L)(s|S)(e|E) {col+=yyleng;return ELSE;}
(w|W)(h|H)(i|I)(l|L)(e|E) {col+=yyleng;return WHILE;}
(self) {mywords++; col+=yyleng; yylval.sval=copystr(yytext); return ID;}
super {col+=yyleng;return SUPER;}
namespace {col+=yyleng;return NAMESPACE;}
"{"		  {col+=yyleng;return(LC);}
"}"       {col+=yyleng;return(RC);}
implements {col+=yyleng;return IMPLEMENTS;}
"." 	{col+=yyleng;return(DOT);}
"," {col+=yyleng;return COMMA;}
public {col+=yyleng; yylval.modi=Public;yylval.my_modifier=new  my_modifiers(Public);  return PUBLIC;}
protected {col+=yyleng;yylval.modi=Protected;yylval.my_modifier=new  my_modifiers(Protected);return PROTECTED;}
internal {col+=yyleng;yylval.modi=Internal;yylval.my_modifier=new  my_modifiers(Internal);return INTERNAL;}
private {col+=yyleng;yylval.modi=Private;yylval.my_modifier=new  my_modifiers(Private);return PRIVATE;}
abstract {col+=yyleng;yylval.modi=Abstract; yylval.my_modifier=new my_modifiers(Abstract);return (ABSTRACT);}
sealed {col+=yyleng;yylval.modi=Sealed; yylval.my_modifier=new  my_modifiers(Sealed);return SEALED;}
return {col+=yyleng;return RETURN;}
switch {col+=yyleng;return SWITCH;}
delete {col+=yyleng;return DELETE;}
and {col+=yyleng;return ND;}
or {col+=yyleng;return AOR;}
void {col+=yyleng;return VOID;}
"(" {col+=yyleng;return LP;}
")" {col+=yyleng;return RP;}
":" {col+=yyleng;return COLON;}
"[" {col+=yyleng;return LB;}
"]" {col+=yyleng;return RB;}
static {col+=yyleng;yylval.modi=Static;yylval.my_modifier=new  my_modifiers(Static);return STATIC;}
readonly {col+=yyleng;yylval.modi=Readonly; yylval.my_modifier=new  my_modifiers(Readonly);return READONLY;}
virtual {col+=yyleng;yylval.modi=Virtual; yylval.my_modifier=new  my_modifiers(Virtual);return VIRTUAL;}
override {col+=yyleng;yylval.modi=Override;yylval.my_modifier=new  my_modifiers(Override);return OVERRIDE;}
"<-" {col+=yyleng;return ASSIGN;}
"@" {col+=yyleng;return AT;}
";" {col+=yyleng;return SEMICOLON;}
"+" {col+=yyleng;return PLUS;}
"-" {col+=yyleng;return MINUS;}
"*" {col+=yyleng;return STAR;}
"/" {col+=yyleng;return DIV;}
"~" {col+=yyleng;return NEGATE;}
"<" {col+=yyleng;return LT;}
"<=" {col+=yyleng;return LE;}
">" {col+=yyleng;return GT;}
">=" {col+=yyleng;return GE;}
"=>" {col+=yyleng;return RE;}
"=" {col+=yyleng;return EQUAL;}
interface {col+=yyleng;return INTERFACE;}

include {BEGIN(incl);}

<incl>{FILE} {
	if(include_stack_ptr>=MAX_INCLUDE_DEPTH)
	{
		yyerror("Includes nested too deeply");
		exit(1);
	}
	include_stack[include_stack_ptr++]=YY_CURRENT_BUFFER;
	yyin=new ifstream(yytext);
	if(!*yyin)
		yyerror("Included file not found");
	yy_switch_to_buffer(yy_create_buffer(yyin,YY_BUF_SIZE));
	BEGIN(INITIAL);}
<incl>[\t| ]
<<EOF>> {
	if (--include_stack_ptr<0)
		yyterminate();
	else
	{
		yy_delete_buffer(YY_CURRENT_BUFFER);
		yy_switch_to_buffer(include_stack[include_stack_ptr]);
	}
}
{ID} {col+=yyleng;mywords++; yylval.sval=copystr(yytext); return ID;}
{DIGIT}+ {col+=yyleng;mydigit++; yylval.ival=atoi(yytext); return INT;}
{DIGIT}+"."{DIGIT}* {col+=yyleng;myfloat++;yylval.fval=(float)atof(yytext); return FLOAT;}
{DIGIT}*"."{DIGIT}+ {col+=yyleng;myfloat++;  yylval.fval=(float)atof(yytext); return FLOAT;}
[\n] {col=0;mylineno++;space++; line++;}
[\t|\b|\f|\r|\v] {col+=8;space++;}
" " {col++;}

{DIGIT}+{ID} {yyerror("LEXICAL ERROR: INVALID IDENTIFIER NAME"); col+=yyleng;mywords++; return ID;}
{DIGIT}+"."{ID} {yyerror("LEXICAL ERROR: INVALID IDENTIFIER NAME"); col+=yyleng;mywords++;  return ID;}
{QUOTE}[^"]+[\n]  {yyerror("LEXICAL ERROR: STRING ERROR Forget to close srting"); col+=yyleng;mywords++; return STRINGS;}
. {yyerror("LEXICAL ERROR: UNKNOWN CHARACTER");return ERROR;}
%%
