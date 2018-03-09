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
	circleShape.setPosition(worldTransform.Position);
}

void GameObject::LateUpdate()
{

}

void GameObject::SetPosition(float x, float y)
{
	Transform.Position.x = x;
	Transform.Position.y = y;
}

void GameObject::SetRotation(float rot)
{
	Transform.Rotation = rot;
}

void GameObject::SetScale(float s)
{
	Transform.Scale = s;
}

void GameObject::InitializeGameObject()
{
	SetPosition(0, 0);
	SetRotation(0);
	SetScale(1);
	SetName("Empty");
	circleShape.setFillColor(sf::Color::Blue);
	circleShape.setRadius(50.0f);
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

void GameObject::CombineTransforms()
{
	if (parent != NULL)
	{
		//worldTransform.Position.x = worldTransform.Position.x + Transform.Position.x;
		//worldTransform.Position.x = worldTransform.Position.x + Transform.Position.y;

		worldTransform = Rotate(parent->worldTransform, parent->worldTransform.Rotation);
	}

	worldTransform.Rotation = Transform.Rotation;
	//combinedTransform.Position.x = worldTransform.Position.x + Transform.Position.x;
	//combinedTransform.Position.y = worldTransform.Position.y + Transform.Position.y;
	//combinedTransform.Rotation = 
}

void GameObject::SetWorldPosition(float x, float y)
{
	worldTransform.Position.x = x;
	worldTransform.Position.y = y;
}

void GameObject::SetWorldRotation(float rot)
{
	worldTransform.Rotation = rot;
}

transform GameObject::Rotate(transform v, float degrees)
{
	transform localT;
	float radians = Deg2Rad(degrees);
	float sin = std::sin(radians);
	float cos = std::cos(radians);

	float tx = v.Position.x;
	float ty = v.Position.y;

	localT.Position.x = cos * tx - sin * ty;
	localT.Position.y = sin * tx + cos * ty;
	//return new Vector2(cos * tx - sin * ty, sin * tx + cos * ty);
	return localT;
}

double GameObject::Deg2Rad(double degrees) {
	return degrees * (M_PI / 180);
}