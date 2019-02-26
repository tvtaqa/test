#include "Data_Structures.h"
#define Error NULL

/***********************list_stark***************************/
list_stack::list_stack()
{
	top = NULL;
}

void list_stack::push_ls(LSNode node)
{
	LSNode *p = new LSNode;
	p->w = node.w;
	p->prilevel = node.prilevel;
	p->next = top;
	top = p;
}

bool list_stack::pop_ls(LSNode &node)
{
	bool iscorrect = true;
	if (top != NULL)
	{
		node.w = top->w;
		node.prilevel = top->prilevel;
		LSNode *p = top;
		top = p->next;
		delete p;
	}
	else             
		iscorrect = false;
	return iscorrect;
}
void list_stack::pop_ls()
{
	LSNode *p = top;
	top = p->next;
	delete p;
}
bool list_stack::topelem(LSNode &node)
{
	bool iscorrect = true;
	if (top != NULL)
	{
		node.w = top->w;
		node.prilevel = top->prilevel;
	}
	else              
		iscorrect = false;
	return iscorrect;
}
bool list_stack::istoplpar()
{
	return (top->w.typenum == $Lpar) ? true : false;
}
int list_stack::topprilevel()
{
	return top->prilevel;
}
bool list_stack::isEmpty()
{
	return (top == NULL) ? true : false;
}

/**********************formula_stack************************/
void formula_stack::insert(STNode T)
{
	loc.push_back(T);
}
void formula_stack::pop(STNode &T)
{
	vector<STNode>::reverse_iterator iter = this->loc.rbegin();
	T = *iter;
	loc.pop_back();
}
bool formula_stack::isEmpty()
{
	return this->loc.empty();
}
bool formula_stack::isExist(STNode T)
{
	vector<STNode>::iterator iter;
	for (iter = loc.begin(); iter != loc.end(); iter++)
	{
		if ((*iter)->formula == T->formula)
			return true;
	}
	return false;
}
bool formula_stack::decideLabel(STNode label)
{
	vector<STNode>::iterator iter;
	for (iter = loc.begin(); iter != loc.end(); iter++)
	{
		if (isHaveLabel(*iter, label))
			return true;
	}
	return false;
}
bool formula_stack::isHaveLabel(STNode T, STNode label)
{
	if (T->character == "&&")
	{
		if (isHaveLabel(T->left, label))
			return true;
		if (isHaveLabel(T->right, label))
			return true;
	}
	else if(T->formula==label->formula)
	{
		return true;
	}
	return false;
}
void formula_stack::print(string &str)
{
	vector<STNode>::iterator iter;
	for (iter = loc.begin(); iter != loc.end(); iter++)
	{
		str += "X(" + (*iter)->formula + ")&&";
	}
	str = str.substr(0, str.length() - 2);
}
int formula_stack::size()const
{
	return this->loc.size();
}

/***************************state_stack*****************************/
void state_stack::insert(CFTreeLeaf ctl)
{
	this->states.push_back(ctl);
}
void state_stack::pop(CFTreeLeaf &ctl)
{
	vector<CFTreeLeaf>::reverse_iterator riter = states.rbegin();
	ctl = (*riter);
	states.pop_back();
}
bool state_stack::isEmpty()
{
	return (states.empty());
}
int state_stack::size()
{
	return this->states.size();
}
/*bool state_stack::isExist(CFTreeLeaf ctl)
{
	vector<CFTreeLeaf>::iterator iter;
	for (iter = states.begin(); iter != states.end(); iter++)
	{
		
	}
}*/
void state_stack::clear()
{
	this->states.clear();
}
