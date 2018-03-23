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
	if (parent != NULL)
	{
		//SnapToParent();
		//sprite.setOrigin(0,0);
		//sprite.setOrigin(parent->GetTransform().Position); //+ parent->Transform.Position);
	}

	else
	{
		//Rotate(10.0f);
		//sprite.setOrigin(0,0);
	}
	//SnapToParent();
	//SnapToParentWithRotation();
	circleShape.setPosition(Transform.Position);
	sprite.setPosition(Transform.Position);
	sprite.setRotation(Transform.Rotation);
	//sprite.setScale( sprite.getLocalBounds().width, sprite.getLocalBounds().height);
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
	circleShape.setFillColor(sf::Color::Red);
	circleShape.setRadius(50.0f);
	SetTexture("Soldier.png", sprite, 100,100,0,0,Transform.Position.x, Transform.Position.y, 1, 1, 0.0f);
	//sprite.setOrigin(0,0);
}

void GameObject::SetTexture(std::string tex, sf::Sprite spr, float width, float height, float startX, float startY, float posX, float posY, float scaleX, float scaleY, float rot)
{
	if (!texture.loadFromFile(tex, sf::IntRect(startX,startY,width,height)))
	{
		std::cout << "The Image Was Not Found..." << std::endl;
		return;
	}

	sprite.setTexture(texture);
	sprite.setPosition(posX,posY);
	sprite.setScale(scaleX, scaleY);
	sprite.setRotation(rot);
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

transform GameObject::AddTransform(transform otherTransform, transform selfTransform)
{
	transform newTransform;

	newTransform.Position = {otherTransform.Position.x + selfTransform.Position.x, otherTransform.Position.y + selfTransform.Position.y};

	return newTransform;
}

void GameObject::SnapToParentWithRotation()
{
	if (parent != NULL)
	{
		//SnapToParent();
		//Rotate(parent->GetWorldTransform(), 0.001f);
		Rotate(parent->GetTransform(), parent->GetRotation() * 0.01f);
		//Rotate(parent->GetWorldTransform(), parent->GetLocalRotation() * 0.01f);
		//SetWorldPosition(AddTransform(parent->GetWorldTransform(), GetLocalTransform()).Position.x, AddTransform(parent->GetWorldTransform(), GetLocalTransform()).Position.y);
		SetRotation(GetRotation() + 1.0f);
		std::cout << "Rotating around Parent Object." << std::endl;
	}
	else
	{
		SetRotation(GetRotation() + 1.0f);
		//SetPosition(GetTransform().Position.x, GetTransform().Position.y);
		//SetLocalPosition(0,0);
		//SetLocalRotation(GetLocalRotation() + 1.0f);
		//Rotate(GetWorldTransform(), parent->GetWorldRotation() * 0.01f);
	}
}

void GameObject::SnapToParent()
{
	if (parent != NULL)
	{
		/*
		float myX = worldTransform.Position.x + Transform.Position.x - parent->GetWorldTransform().Position.x - parent->GetLocalTransform().Position.x;
		float myY = worldTransform.Position.y + Transform.Position.y - parent->GetWorldTransform().Position.y - parent->GetLocalTransform().Position.y;
		float localX = Transform.Position.x;
		float localY = Transform.Position.y;
		SetWorldPosition(0,0);
		SetLocalPosition(0,0);
		Translate(parent->GetWorldTransform().Position.x + parent->GetLocalTransform().Position.x, parent->GetWorldTransform().Position.y + parent->GetLocalTransform().Position.y);
		Translate(myX - localX, myY - localY);
		SetLocalPosition(localX, localY);
		*/

		//float myX = GetWorldTransform().Position.x + GetLocalTransform().Position.x - parent->GetWorldTransform().Position.x - parent->GetLocalTransform().Position.x;
		//float myY = GetWorldTransform().Position.y + GetLocalTransform().Position.y - parent->GetWorldTransform().Position.y - parent->GetLocalTransform().Position.y;
		//SetWorldPosition(parent->GetWorldTransform().Position.x + parent->GetLocalTransform().Position.x, parent->GetWorldTransform().Position.y + parent->GetLocalTransform().Position.y);
		//Translate(myX,myY);
		//SetWorldPosition(parent->GetWorldTransform().Position.x + parent->GetLocalTransform().Position.x + worldTransform.Position.x + Transform.Position.x, parent->GetWorldTransform().Position.y + parent->GetLocalTransform().Position.y + worldTransform.Position.y + Transform.Position.y );
		//SetWorldPosition(AddTransform(parent->GetWorldTransform(), GetLocalTransform()).Position.x, AddTransform(parent->GetWorldTransform(), GetLocalTransform()).Position.y);
		
		sf::Vector2f vec = parent->Transform.Position - Transform.Position;

		SetPosition(0,0);
		SetPosition(parent->Transform.Position.x - vec.x, parent->Transform.Position.y - vec.y);




		/*
		transform tform;
		transform localtform = Transform;

		tform.Position = GetWorldTransform().Position + GetLocalTransform().Position - parent->GetWorldTransform().Position - parent->GetLocalTransform().Position;

		SetWorldPosition(0,0);
		SetWorldPosition(parent->GetWorldTransform().Position.x + parent->GetLocalTransform().Position.x, parent->GetWorldTransform().Position.y + parent->GetLocalTransform().Position.y);
		//Translate(tform.Position.x, tform.Position.y);
		*/

		//SetWorldPosition(AddTransform(parent->GetWorldTransform(), GetLocalTransform()).Position.x, AddTransform(parent->GetWorldTransform(), GetLocalTransform()).Position.y);

		std::cout << "Snapping To Parent Object." << std::endl;
	}
	else
	{
		//SetWorldPosition(GetWorldTransform().Position.x + GetLocalTransform().Position.x, GetWorldTransform().Position.y + GetLocalTransform().Position.y);
		//SetLocalPosition(0, 0);
	}
}

/*
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
*/

void GameObject::Rotate(float angle)
{
	SetRotation(GetRotation() + angle);
	
	//for (auto& game_object : childObjects)
	//{
	//	game_object->Rotate(angle);
	//}
}


void GameObject::Rotate(transform center, float angle)
{
	if (parent != NULL)
	{
		//Transform.Position.x = (parent->GetWorldTransform().Position.x + parent->GetLocalTransform().Position.x) + cos(parent->GetLocalRotation())* GetRadius();
		//Transform.Position.y = (parent->GetWorldTransform().Position.y + parent->GetLocalTransform().Position.y) + cos(parent->GetLocalRotation())* GetRadius();

		//Transform.Rotation = Transform.Rotation + angle;
		
		SetPosition((parent->GetTransform().Position.x) + (GetTransform().Position.x * cos(angle)), (parent->GetTransform().Position.y) + (GetTransform().Position.y * sin(angle)));
		//SetWorldPosition((parent->GetWorldTransform().Position.x + GetLocalTransform().Position.x) + (GetLocalTransform().Position.x * cos(angle)), (parent->GetWorldTransform().Position.y + GetLocalTransform().Position.y) + (GetLocalTransform().Position.y * sin(angle)));
		std::cout << "Rotating around Parent Object." << std::endl;
	}
	else
	{
		Transform.Rotation = Transform.Rotation + angle;
	}

	/*
	float radians = Deg2Rad(degrees);
	float sin = std::sin(radians);
	float cos = std::cos(radians);

	float tx = center.Position.x;
	float ty = center.Position.y;

	SetWorldPosition(cos * tx - sin * ty, sin * tx + cos * ty);
	*/

	//localT.Position.x = cos * tx - sin * ty;
	//localT.Position.y = sin * tx + cos * ty;
	//return new Vector2(cos * tx - sin * ty, sin * tx + cos * ty);
}

double GameObject::Deg2Rad(double degrees) {
	return degrees * (M_PI / 180);
}

void GameObject::Translate(float Xtarget, float Ytarget)
{
	if (childObjects.size() == 0)
	{
		SetPosition(Xtarget, Ytarget);
	}
	else
	{
		int myX = Xtarget - Transform.Position.x;
		int myY = Ytarget - Transform.Position.y;
		SetPosition(Xtarget, Ytarget);
		for (auto& game_object : childObjects)
		{
			game_object->SetPosition(game_object->Transform.Position.x + myX, game_object->Transform.Position.y + myY);

			for (auto& game_object2 : game_object->childObjects)
			{
				game_object2->Translate(game_object2->Transform.Position.x + myX, game_object2->Transform.Position.y + myY);
			}
		}
	}
}

void GameObject::TranslateMe(float VectorX, float VectorY)
{
	if (childObjects.size() == 0)
	{
		SetPosition(Transform.Position.x + VectorX, Transform.Position.y + VectorY);
	}
	else
	{
		std::cout << "Size: " << childObjects.size() << std::endl;

		sf::Vector2f mini = Transform.Position;
		SetPosition(Transform.Position.x + VectorX, Transform.Position.y + VectorY);
		mini.x = Transform.Position.x - mini.x;
		mini.y = Transform.Position.y - mini.y;

		for (auto& game_object : childObjects)
		{
			sf::Vector2f difference = game_object->Transform.Position - Transform.Position;
			game_object->SetPosition(Transform.Position.x + difference.x + mini.x, Transform.Position.y + difference.y + mini.y);

			for (auto& game_object2 : game_object->childObjects)
			{
				game_object2->TranslateMe(VectorX, VectorY);
			}
			//game_object->TranslateMe(difference.x + mini.x, difference.y + mini.y);
			//game_object->TranslateMe(difference.x + mini.x, difference.y + mini.y);
		}
	}
}

sf::Vector2f GameObject::GetPosition(transform target)
{
	sf::Vector2f aVector;

	aVector = target.Position;

	return aVector;
}

sf::Vector2f GameObject::GetLocalPosition()
{
	sf::Vector2f myVector;
	myVector = ConvertToLocalPosition(Transform.Position);
	return myVector;
}

sf::Vector2f GameObject::rotate_point(float cx, float cy, float angle, sf::Vector2f p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}

sf::Vector2f GameObject::rotate_point(sf::Vector2f center, float angle, sf::Vector2f p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= center.x;
	p.y -= center.y;

	// rotate point
	float xnew = (p.x * c) - (p.y * s);
	float ynew = (p.x * s) + (p.y * c);

	// translate point back:
	p.x = xnew + center.x;
	p.y = ynew + center.y;
	
	return p;
}

void GameObject::RotateMe(GameObject *center, GameObject *me, float angle)
{
	me->Transform.Rotation = angle;
	me->Translate(me->rotate_point(center->Transform.Position, angle, me->Transform.Position).x, me->rotate_point(center->Transform.Position, angle, me->Transform.Position).y);

	std::cout << "Rotating Self, Angle = " << me->Transform.Rotation << std::endl;

	if (childObjects.size() == 0)
	{

	}
	else
	{
		for (auto& game_object : childObjects)
		{
			std::cout << "Rotating Child Object, Angle = " << game_object->Transform.Rotation << std::endl;
			game_object->RotateMe(game_object->parent, game_object, angle);
		}
	}
}