#pragma once

#include <vector>

/*

class GameObject 
{ 
	public:

			GameObject() { parent = NULL; } 
			~GameObject(void); 
			void SetTransform(const Matrix4 &matrix) { transform = matrix; } 
			Matrix4 GetTransform() { return transform; } 
			Matrix4 GetWorldTransform() { return worldTransform; } 
			void SetParent(GameObject& p) { parent = p; } 
			void AddChild(GameObject* s);  
			virtual void Update(float msec);

	Protected: 
			
			GameObject* parent; 
			Matrix4 worldTransform;
			Matrix4 transform;
			std::vector<GameObject*> children;
};

class Sun
{
	GameObject *scene; 
	GameObject *sun; 
	GameObject *earth; 
	GameObject *moon; 
	
	scene->AddChild(sun); 
	sun->AddChild(earth); 
	earth->AddChild(moon); // Translating the earth will translate the moon as well. 
	
	earth->SetTransform(Matrix4::Translation(Vector3(7,0,0)));
	
};

*/