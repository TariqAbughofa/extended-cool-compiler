# extended-cool-compiler
An extended compiler for the cool programming language
It includes these steps
1. Lexical Analysis.
2. Syntax Analysis.
3. Semantic Analysis.
4. Code Generation.

The original cool rules:

```
Program  ::= namespacedecl+ 
Namespacedecl ::= namespace QID { Typedecl*}
Typedecl ::= 	classdecl
|Interfacedecl
|namespacedecl
Classdecl ::= [class_modifier]* class ID [ inherits QID ] [ implements QID_List ] is feature* end 
QID	:= 	QID . ID
|ID
QID_List	::=	QID_List , QID 
| QID
Modifier  ::= PUBLIC
				|PROTECTED
|INTERNAL
	 			|PRIVATE
|STATIC
|VIRTUAL
				|SEALED
				|OVERRIDE
				|ABSTRACT
|READONLY
Feature ::= [Method-modifier]* ID ( formal* ) : QID is expr;* end
|[Method-modifier]* ID ( formal* ) : QID ;
|[Field-modifier]* ID : QID [ <- expr ] ;
|[Field-modifier]* ID : QID [ int_Value ] * ;
Formal ::= ID : QID
expr ::=  ID : QID [ <- expr]
| ID : QID [int_Value]
| QID [ <- expr ]
| QID [int_Value] [ <- expr ]
| QID [ID] [ <- expr ]
| expr . ID [ <- expr]
| QID ( expr , * )
| expr . ID ( expr , * )
| new QID (expr , * )
| expr @ QID
| return expr
| if expr then expr else expr fi 
| while expr loop expr pool 
| begin expr ; * end 
| let { ID : QID [ <- expr ] , }+ in expr end 
| switch expr of {case ID : QID => expr ;}+ esac 
| isvoid expr
| expr + expr
| expr - expr
| expr * expr
| expr / expr
| ~ expr
| expr = expr
| expr < expr
| expr <= expr
| expr > expr
| expr >= expr
| expr or expr
| expr and expr
| not expr
| ( expr )
| int_Value
| string_Value
| float_Value
| true
| false
| void

Interfacedecl ::= [interface-modifier]* interface ID [ inherits QID { , QID }* ] { interface-method *}
interface-method ::= QID ID ( [formal*] ) ;

class-modifier::= new |public |protected |internal |private |abstract |sealed
Field-modifier::= public |protected |internal |private |static |readonly 
Method-modifier::= public |protected |internal |private |static |virtual |sealed |override |abstract
interface-modifier::= new |public |protected |internal |private
constructor-modifier::= public |protected |internal |private
```

We added OOP, later definition.
