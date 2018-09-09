#include "staticbody.hpp"
using namespace std;

StaticBody::StaticBody()
{
}

StaticBody::~StaticBody()
{
	if(collider)
	{
		delete collider;
	}
}

int StaticBody::attachScript(string fileName)
{
	int ret = Node::attachScript(fileName);
	return ret;
}

int StaticBody::addCollider(int type, CollisionLayer &layer)
{
	if(type == SPHERE_COL)
	{
		collider = new CollisionSphere(1.0);
		collider->parent = this;
		layer.addNew(collider);
		return 0;
	}
	else if(type == BOX_COL)
	{
		collider = new CollisionBox(1.0, 1.0, 1.0);
		collider->parent = this;
		layer.addNew(collider);
		return 0;
	}
	else
	{
		std::cout<<"Error: collider type not supported"<<std::endl;
		return 1;
	}

}
