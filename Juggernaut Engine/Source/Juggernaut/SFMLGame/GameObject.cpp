#include "stdafx.h"
#include "GameObject.h"
#include <vector>
#include <cmath>



GameObject::~GameObject(void)
{
	for (unsigned int i = 0; i< children.size(); i++)
	{
		delete children[i];
	}
}

void GameObject::AddChild(GameObject* s)
{
	children.push_back(s);
	s->parent = this;
}

void GameObject::Update(float msec) {

	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * transform.transformMatrix;
	}
	else { //Root node, world transform is local transform!
		worldTransform = glm::mat4(1.0f) * transform.transformMatrix;
	}

	for (std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
		(*i)->Update();
	}
	//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
	//        (*i)->Update(msec);
	//    }

	/*
	//transform.setRotation(transform.getRotation() += msec);
	//MakeRotate(msec);

	if (parent)
	{ //This node has a parent...  

	  //worldTransform = parent->worldTransform * transform;

		//worldTransform = MultiplyTransforms(parent->worldTransform, transform);
		
		MakeRotate(msec);
		worldTransform = MultiplyTransforms(parent->worldTransform, transform);

	}
	else
	{ //Root node, world transform is local transform!  
		worldTransform = transform;
		MakeRotate(msec);
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(msec);
	}
	*/
}

void GameObject::LateUpdate(float msec) {
	for (std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
		(*i)->LateUpdate();
	}
	//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
	//        (*i)->LateUpdate(msec);
	//    }
}

void GameObject::AddComponent(BaseComponent* component)
{
	m_Components.push_back(component);
}

/*
void GameObject::AddChild(GameObject* child) {
	m_Children.push_back(child);
}
*/

/*
bool GameObject::SendMessage(BaseMessage* msg)
{
	
	bool messageHandled = false;

	// Object has a switch for any messages it cares about
	switch (msg->m_messageTypeID)
	{
		            case SetPosition:
		            {
		                MsgSetPosition* msgSetPos = static_cast<MsgSetPosition*>(msg);
		                m_Position.x = msgSetPos->x;
		                m_Position.y = msgSetPos->y;
		                m_Position.z = msgSetPos->z;
		
		                messageHandled = true;
		                cout << "Object handled SetPosition\n";
		            }
		                break;
		            case GetPosition:
		            {
		                MsgGetPosition* msgSetPos = static_cast<MsgGetPosition*>(msg);
		                msgSetPos->x = m_Position.x;
		                msgSetPos->y = m_Position.y;
		                msgSetPos->z = m_Position.z;
		
		                messageHandled = true;
		                cout << "Object handling GetPosition\n";
		            }
		break;
	default:
		return PassMessageToComponents(msg);
	}
	// If the object didn't handle the message but the component
	// did, we return true to signify it was handled by something.
	messageHandled |= PassMessageToComponents(msg);

	return messageHandled;
}
*/

/*
bool GameObject::PassMessageToComponents(BaseMessage* msg)
{
	bool messageHandled = false;

	std::vector<BaseComponent*>::iterator compIt = m_Components.begin();
	for (compIt; compIt != m_Components.end(); ++compIt)
	{
		messageHandled |= (*compIt)->SendMessage(msg);
	}

	return messageHandled;
}
*/


