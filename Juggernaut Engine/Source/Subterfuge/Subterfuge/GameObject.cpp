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