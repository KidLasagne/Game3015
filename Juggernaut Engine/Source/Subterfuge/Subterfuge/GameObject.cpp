#include "GameObject.h"

GameObject::~GameObject()
{
}

void GameObject::Awake()
{

}

void GameObject::Start()
{

}

void GameObject::Update()
{

}

void GameObject::LateUpdate()
{

}

void GameObject::SetPosition(float x, float y)
{
	transform.Position.x = x;
	transform.Position.y = y;
}

void GameObject::SetRotation(float rot)
{
	transform.Rotation = rot;
}

void GameObject::SetScale(float s)
{
	transform.Scale = s;
}

void GameObject::InitializeGameObject()
{
	SetPosition(0, 0);
	SetRotation(0);
	SetScale(1);
	SetName("Empty");
}

void GameObject::SetTexture(std::string tex)
{
	if (!texture.loadFromFile(tex))
	{
		std::cout << "The Image Was Not Found..." << std::endl;
		return;
	}

}

void GameObject::RenderSprite()
{
	sprite.setTexture(texture);
}

sf::Sprite GameObject::GetSprite()
{
	return sprite;
}

void GameObject::AttachChild(GameObject* child)
{
	childObjects.push_back(child);
	child->parent = this;
}

void GameObject::PushBaseComponent(BaseComponent* baseC)
{
	BaseComponentList.push_back(baseC);
}

GameObject* GameObject::FindObjectByName(std::string nam)
{
	for (auto& game_object : childObjects)
	{
		if (game_object->GetName() == nam)
		{
			return game_object;
		}
	}

	return NULL;

}